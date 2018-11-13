#!python3
# coding=utf8

# TODO: отдельный .mk файл для каждого объектника
# TODO: проверить применяемость подхода https://pytest.readthedocs.io/en/reorganize-docs/goodpractices.html

'''
* Фыйлы тестов должны начинаться c test_*
* Для включения объектников в тест используется директива @import в комментариях
   // @import obj1 obj2
* Поиск заголовочных файлов начинаестся с папок тестового окружения 
* Использование разных наборов заголовочных файлов не реализовано

Генерируемый make соответствует:
     http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/ 
'''

import glob
import sys
import itertools
import os
import re
import io
import subprocess
import yaml
from pathlib import Path, PurePath
import sys
import getopt

argv = sys.argv[1:]

try:
    opts = getopt.getopt(argv, "abc")
except getopt.GetoptError:
    print('GetoptError i dunno')
    sys.exit(2)

build_tests = False
run_tests = False
build_project = False
run_sim = False

for opt in opts[1:]:
    for x in opt:
        if x == 'tests':
            build_tests = True
        elif x == 'build':
            build_project = True
        elif x == 'runtests':
            run_tests = True
        elif x == 'runsim':
            run_sim = True

conf = {
    'src': {'pth': ['0_Sm', '0_Src', 'src', 'source'], 'tgt': ''},
    'tst': {'pth': ['tests'], 'tgt': 'test_'},
}

inc_patterns = ['.h', '.hpp', '.inc']
c_patterns = ['.c']
cpp_patterns = ['.cpp', '.cxx']
src_patterns = [*c_patterns, *cpp_patterns]

compiler_param = {
    'pc': {
        'lang': {
            'c': {
                'cmp': 'gcc',
                'std': 'c99'},
            'cpp': {
                'cmp': 'g++',
                'std': 'c++11'},
        },
        'exec_extension': '.exe',
    },

    'tricore': {
        'lang': {
            'c': {
                'cmp': 'tricore-gcc',
                'std': 'c99'},
            'cpp': {
                'cmp': 'tricore-g++',
                'std': 'c++11'},
        },
        'exec_extension': '.elf',
    },
}

# -----------------------------------------------------------------------------
path_to_settings = Path("settings.yaml")

# чтение настроек из файла
settings = object()
with open(path_to_settings, 'r') as stream:
    try:
        settings = yaml.safe_load(stream)
    except yaml.YAMLError as exc:
        print(exc)

path_tc161_dconfig = Path(settings['path_to_tc161_dconfig'])
path_tc161_mconfig = Path(settings['path_to_tc161_mconfig'])
build_dir = Path(settings['build_dir'])
core = settings['core']
language_link = settings['language_link']
artifacts_name = settings['artifacts_name']
project_platform = settings['platform']
tests_platform = settings['tests_platform']

# -----------------------------------------------------------------------------
# Функции
# содержит компилятор:его расширения
compiler_to_ext = dict(zip(['c', 'cpp'], [c_patterns, cpp_patterns]))
# содержит расширение:компилятор
ext_to_compiler = {k: v for v, kk in compiler_to_ext.items() for k in kk}

# на вход путь, выход - компилятор ц или цпп
compiler_from_fn = lambda p: ext_to_compiler[Path(p).suffix]

def update_file(f, content):
    content = content.replace('\\', '/')
    content0 = None
    if Path.exists(f):
        with open(f, 'r') as fobj:
            content0 = fobj.read()
    if content0 != content:
        print(f'update {f}')
        with open(f, 'w') as fobj:
            fobj.write(content)

add_obj_extension = lambda t: (t + '.o')

# тут будут все имена исходных файлов
all_obj = []
# тут будут все имена C файлов
all_c_obj = []
# тут будут все имена C++ файлов
all_cpp_obj = []

# -----------------------------------------------------------------------------

def make_prj_env(conf):
    penv = {
        'src': {
            'inc':set(),
            'targets':[],
            'obj': [],
        },
        'tst': {
            'inc':set(),
            'targets':[],
            'obj': [],
        },
        'obj': {},
    }

    # выбираются все пары ключ:значение из conf
    for env, env_cfg in conf.items():
        # в значениях(настройках) env_cfg выбираются члены каждого пути ('pth')
        for root in env_cfg['pth']:
            # для каждой папки root делается волк
            for top, dirs, files in os.walk('../' + root):
                # для всех файлов в них
                for file in files:
                    file_path = Path(top, file)
                    file_ext = Path(file).suffix
                    file_name = Path(file).stem

                    #  если расширение файла - инклюдное
                    if file_ext in inc_patterns:
                        # записать папку, в которой нашелся такой файл, в inc. соотв окружения
                        penv[env]['inc'].add(top)
                    #  если расширение - исходник
                    elif file_ext in src_patterns:
                        # имя файла вписать в all_obj
                        all_obj.append(file_name)

                        if file_ext in c_patterns:
                            all_c_obj.append(file_name)
                        elif file_ext in cpp_patterns:
                            all_cpp_obj.append(file_name)

                        # в obj соотв. окружения дописать имя файла
                        penv[env]['obj'].append(file_name)
                        # в 'obj' вписать пару имя-путь
                        penv['obj'][file_name] = file_path
                        # а если исходник еще и цель (начинается с)...
                        if file_name.startswith(env_cfg['tgt']):
                            # ...дописать его к таргетсам соотв. окружения
                            penv[env]['targets'].append(file_name)
                            
        penv[env]['inc'] = sorted(penv[env]['inc'])
        penv[env]['obj'] = sorted(penv[env]['obj'])
        penv[env]['targets'] = sorted(penv[env]['targets'])
    
    def dupl(l):
        s = set(l)
        return [v for v in l if v not in s]

    # в наборе исходников не должно быть повторяющихся имен
    dupl_obj = set([x for x in all_obj if all_obj.count(x) > 1])

    if dupl_obj:
        raise Exception(f'Duplicate objects {dupl_obj}')

    return penv

# -----------------------------------------------------------------------------
prj_env = make_prj_env(conf)

# взять папку билда, развернуть все папки с инклюдами в одну коллекцию
# в obj будет словарь с исходниками вида имя:путь
build_cfg = {
    'dir': build_dir,
    'artifacts_dir': Path(build_dir, 'artifacts'),
    'tests_dir': Path(build_dir, 'tests'),
    'inc':[*prj_env['tst']['inc'], *prj_env['src']['inc']],
    'obj':prj_env['obj'],
    'targets':{},  # name:[obj1, obj2]
    'tests_targets':{},
}

# регулярка с директивой // @import
rep = re.compile('// *@import +(.+)')

# выбираются все имена исходников, которые записаны как таргеты src
for trgt in prj_env['src']['targets']:
    # взять путь исходника из словаря 'obj' (а он там точно есть)
    with open(prj_env['obj'][trgt], 'rb') as tf:
        import_objs = []
        for line in tf:
            line = line.decode('cp1252')
            m = rep.match(line)
            if m:
                # вписать из директивы
                import_objs.extend(re.split(' +', m.groups()[0]))
        import_objs.append(trgt)
        import_objs = sorted(list(set(import_objs)))
        # вписать из конфига
        build_cfg['targets'][trgt] = import_objs

# выбираются все имена исходников, которые записаны как таргеты tst
for trgt in prj_env['tst']['targets']:
    # взять путь исходника из словаря 'obj' (а он там точно есть)
    with open(prj_env['obj'][trgt], 'rb') as tf:
        import_objs = []

        import_objs.append(trgt)
        import_objs = sorted(list(set(import_objs)))
        # вписать из конфига
        build_cfg['tests_targets'][trgt] = import_objs

build_join = lambda f: PurePath.joinpath(build_cfg['dir'], f)
build_join_tests = lambda f: PurePath.joinpath(build_cfg['tests_dir'], f)

# путь билда + параметр + расширение
# trgt_full_name = lambda t: Path(str(build_join(t)) + '.exe')

incopt_file = build_join('inc.opt')
mk_file = build_join('build.mk')

# создаем папку билда
if not Path.exists(build_cfg['dir']):
    os.makedirs(build_cfg['dir'], exist_ok=True)

# создаем папку для артефактов
if not Path.exists(build_cfg['artifacts_dir']):
    os.makedirs(build_cfg['artifacts_dir'], exist_ok=True)

# создаем папку для тестов
if not Path.exists(build_cfg['tests_dir']):
    os.makedirs(build_cfg['tests_dir'], exist_ok=True)

# в opt вписываются все папки с инклюдниками
incopt_content = []
for inc in build_cfg['inc']:
    incopt_content.append(f'"-iquote{inc}"')
incopt_content = '\n'.join(incopt_content)

update_file(incopt_file, incopt_content)

all_obj_src = sorted(set(itertools.chain(*build_cfg['targets'].values(),
                                     build_cfg['targets'].keys())))

all_obj_tests = sorted(set(itertools.chain(*build_cfg['tests_targets'].values(),
                                     build_cfg['tests_targets'].keys())))

all_obj = all_obj_src + all_obj_tests

# -----------------------------------------------------------------------------
# temp = build_cfg['targets'].keys() build_cfg['tests_targets'].keys()
collect_src = map(add_obj_extension, build_cfg['targets'].keys())
collect_tests = map(add_obj_extension, build_cfg['tests_targets'].keys())

joined_str_src = ' '.join(str(build_join(x)) for x in collect_src)
joined_str_tests = ' '.join(str(build_join_tests(x)) for x in collect_tests)

joined_str = joined_str_src + ' ' + joined_str_tests
# -----------------------------------------------------------------------------
mk_io = io.StringIO()
mk_io.write('.PHONY: all clean all_tests ' + '\n\n')

# -----------------------------------------------------------------------------
# таргет all:

if project_platform == 'tricore':
    tricore_specific_options = True
else:
    tricore_specific_options = False

# таргет all создавать, только если есть таргеты объектников
if all_obj:
    s = f'all: {joined_str_src}\n'
    mk_io.write(s)

    compiler_link = compiler_param[project_platform]['lang'][language_link]['cmp']

    map_file_path = Path(build_cfg['artifacts_dir'], artifacts_name + '.map')
    elf_file_path = Path(build_cfg['artifacts_dir'], artifacts_name + compiler_param[project_platform]['exec_extension'])

    s = (
            f'\t{compiler_link} '
            f'-Wl,-Map,{map_file_path} -Wl,'
        )

    mk_io.write(s)

    # TODO: разобраться с опциями компилятора
    # и вынести это как-то поудачнее, чем в середину строки опций
    if tricore_specific_options:
        s = (
            f'--extmap="a"'
            f' -mcpu={core}'
        )
        mk_io.write(s)

    s = (
        f' -Wl,--gc-sections -o {elf_file_path} ' + joined_str_src
    )
    mk_io.write(s + '\n')

# -----------------------------------------------------------------------------
# таргет all_tests:
# таргет all_tests создавать, только если есть таргеты объектников тестов

if all_obj_tests:
    s = f'\nall_tests: '
    mk_io.write(s)
    for tn in all_obj_tests:
        extension = compiler_param[tests_platform]['exec_extension']
        trgt_path = Path(build_cfg['tests_dir'], tn)
        s = (
            f'{trgt_path}{extension} '
        )
        mk_io.write(s)
    mk_io.write('\n\n')

# -----------------------------------------------------------------------------
# таргеты объектников

for tn in all_obj:

    if tn in all_obj_src:
        platform = project_platform
        trgt_path = build_join(tn)
        dep_file_path = str(build_join(tn)) + '.d'
    elif tn in all_obj_tests:
        platform = tests_platform
        trgt_path = build_join_tests(tn)
        dep_file_path = str(build_join_tests(tn)) + '.d'

    if platform == 'tricore':
        tricore_specific_options = True
    else:
        tricore_specific_options = False

    if tn in all_cpp_obj:
        language = 'cpp'
    elif tn in all_c_obj:
        language = 'c'

    compiler = compiler_param[platform]['lang'][language]['cmp']
    std = compiler_param[platform]['lang'][language]['std']

    src = build_cfg['obj'][tn]
    opt = incopt_file
    mk = mk_file
    s = (
        f'\n'
        f'{trgt_path}.o: {src} {dep_file_path} {opt} {mk_file}\n'
        f'\t{compiler} '
        f'-MT {trgt_path}.o -MMD -MP -MF {trgt_path}.Td @{opt} '
        f'-c -o {trgt_path}.o -g '
        f'-ffunction-sections '
        f'-O0 -fno-common --std={std} '
        f'-Wall -W -Werror -Isrc/h {src} '
    )

    mk_io.write(s)

    if tricore_specific_options:
        s = (
            f'-msmall-data=65535 -msmall-const=65535 '
            f'-mcpu={core} '
        )
        mk_io.write(s)

    # переименовать файл зависимостей
    s = f'\n\t@mv -f {trgt_path}.Td {trgt_path}.d && touch {trgt_path}.o\n'
    mk_io.write(s)

# -----------------------------------------------------------------------------
# таргеты тестовых исполнимых файлов

for tn in all_obj_tests:

    platform = tests_platform

    if tn in all_cpp_obj:
        language = 'cpp'
    elif tn in all_c_obj:
        language = 'c'

    compiler = compiler_param[platform]['lang'][language]['cmp']

    extension = compiler_param[tests_platform]['exec_extension']
    trgt_path = Path(build_cfg['tests_dir'], tn)
    src = add_obj_extension(str(trgt_path))
    mk = mk_file
    s = (
        f'\n'
        f'{trgt_path}{extension}: {src} {mk_file}\n'
        f'\t{compiler} '
        f'-o {trgt_path}{extension} {src}\n'
    )

    mk_io.write(s)

# -----------------------------------------------------------------------------
build_dir_slash = str(build_cfg['dir']) + '/'
s = (
    f'\n'
    f'{build_dir_slash}%.d: ;'
    f'\n'
    f'.PRECIOUS: {build_dir_slash}%.d'
    f'\n'
    f'include $(wildcard {build_dir_slash}*.d)'
)
mk_io.write(s)

# -----------------------------------------------------------------------------
mk_io.write('\n\nclean:\n')
s = (
    f'\trm -rf {build_dir_slash}*.o\n'
    f'\trm -rf {build_dir_slash}*.d'
)
mk_io.write(s)

update_file(mk_file, mk_io.getvalue())
# -----------------------------------------------------------------------------

# побилдить проект
if build_project:
    subprocess.run(f'make -f {mk_file} all', check=True)

# побилдить тесты
if build_tests:
    subprocess.run(f'make -f {mk_file} all_tests', check=True)

# запустить тесты
if run_tests:
    for x in all_obj_tests:
        strnew = Path(build_cfg['tests_dir'], x).with_suffix(extension)
        subprocess.run(str(strnew))

# запустить симуляцию
log_file_path = build_join('tsim.log')

if run_sim:
    subprocess.run(f'tsim16p_e '
                   f'-DConfig {path_tc161_dconfig} '
                   f'-MConfig {path_tc161_mconfig} '
                   f'-h -s -H -disable-watchdog -o HelloTSim.elf '
                   f'-log-file {log_file_path}', check=True)

if __name__ == '__main__':
    pass