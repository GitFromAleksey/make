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

conf = {
    'src': {'pth': ['0_Sm', '0_Src', 'src', 'source'], 'tgt': ''},
    'tst': {'pth': ['tests'], 'tgt': 'test_'},
    }

# TODO: имена стрёмные
path_to_settings = Path("settings.yaml")

path_tc161_dconfig = Path('tsim/tc161/DConfig')
path_tc161_mconfig = Path('tsim/tc161/MConfig')

build_dir = Path('../out')

# чтение настроек из файла
settings = object()
with open(path_to_settings, 'r') as stream:
    try:
        settings = yaml.safe_load(stream)
    except yaml.YAMLError as exc:
        print(exc)

cflags = "-c -Wall"

inc_patterns = ['.h', '.hpp', '.inc']
c_patterns = ['.c']
cpp_patterns = ['.cpp', '.cxx']
src_patterns = [*c_patterns, *cpp_patterns]

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

build_join = lambda f: PurePath.joinpath(build_cfg['dir'], f)

# путь билда + параметр + расширение
trgt_full_name = lambda t: Path(str(build_join(t)) + '.exe')
add_obj_extension = lambda t: (t + '.o')

# get_paths = lambda p: list(set(itertools.chain(*map(glob.iglob, p))))
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

    # тут будут все имена исходных файлов
    all_obj = []

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
    'inc':[*prj_env['tst']['inc'], *prj_env['src']['inc']],
    'obj':prj_env['obj'],
    'targets':{},  # name:[obj1, obj2]
    }

# регулярка с директивой // @import
rep = re.compile('// *@import +(.+)')

# выбираются все имена исходников, которые записаны как таргеты src
for trgt in prj_env['src']['targets']:
    # взять путь исходника из словаря 'obj' (а он там точно есть)
    with open(prj_env['obj'][trgt], 'rb') as tf:
        import_objs = []
        for line in tf:
            line = line.decode('utf8')
            m = rep.match(line)
            if m:
                # вписать из директивы
                import_objs.extend(re.split(' +', m.groups()[0]))
        import_objs.append(trgt)
        import_objs = sorted(list(set(import_objs)))
        # вписать из конфига
        build_cfg['targets'][trgt] = import_objs
print("---DEBUG HERE!---")
print(build_cfg)
print("-----------------")
# -----------------------------------------------------------------------------
# создаем папку билда
if not Path.exists(build_cfg['dir']):
    os.makedirs(build_cfg['dir'], exist_ok=True)

incopt_file = build_join('inc.opt')

# в opt вписываются все папки с инклюдниками
incopt_content = []
for inc in build_cfg['inc']:
    incopt_content.append(f'"-iquote{inc}"')
incopt_content = '\n'.join(incopt_content)

update_file(incopt_file, incopt_content)
# -----------------------------------------------------------------------------

mk_file = build_join('build.mk')

compiler_param = {
    'gcc': {
        'c': {
            'cmp': 'gcc',
            'std': 'c99'},
        'cpp': {
            'cmp': 'g++',
            'std': 'c++11'},
    },

    'tricore_gcc': {
        'c': {
            'cmp': 'tricore-gcc',
            'std': 'c99'},
        'cpp': {
            'cmp': 'tricore-g++',
            'std': 'c++11'},
    },
}

# -----------------------------------------------------------------------------
mk_io = io.StringIO()
mk_io.write('.PHONY: all clean\n\n')
# -----------------------------------------------------------------------------
# таргет all:
collect = map(add_obj_extension, build_cfg["obj"].keys())
joined_str = ' '.join(str(x) for x in collect)
mk_io.write('all: {}\n'.format(joined_str))

# TODO: вынести в настройки
core = 'tc23xx'
language = 'cpp'

gcc = compiler_param[settings['platform']][language]['cmp']
std = compiler_param[settings['platform']][language]['std']

s = (
        f'\t{gcc} -mcpu={core} '
        f'-Wl, -Map, HelloTSim.map -Wl, --extmap="a" -Wl, --gc-sections -o HelloTSim.elf ' + joined_str
    )
mk_io.write(s)
mk_io.write('\n\t@echo running rule')

s = (
        f'\n\t'
        f'tsim16p_e '
        f'-DConfig {path_tc161_dconfig} '
        f'-MConfig {path_tc161_mconfig} '
        f'-h -s -H -disable-watchdog -o HelloTSim.elf -log-file tsim.log'
    )
mk_io.write(s)
mk_io.write('\n\t@echo -- end of make\n\n')

# -----------------------------------------------------------------------------
# таргеты объектников
all_obj = sorted(set(itertools.chain(*build_cfg['targets'].values(),
                                     build_cfg['targets'].keys())))
for tn in all_obj:
    trgt = tn
    src = build_cfg['obj'][tn]
    cmp = compiler_from_fn(src)
    opt = incopt_file
    mk = mk_file
    s = (
        f'\n'
        f'{trgt}.o: {src}\n'
        f'\t{gcc} -mcpu={core} -c -o {trgt}.o -g '
        f'-ffunction-sections -msmall-data=65535 -msmall-const=65535'
        f'-O0 -fno-common --std={std}'
        f'-Wall -W -Werror -Isrc / h src / {trgt}.cpp\n'
    )
    mk_io.write(s)

# -----------------------------------------------------------------------------

mk_io.write('clean:\n')
mk_io.write('\trm -rf *.o')
# -----------------------------------------------------------------------------

update_file(mk_file, mk_io.getvalue())

# subprocess.run(f'make -f {mk_file} all', check=True)

# запускает все тесты
# for tn in build_cfg['targets'].keys():
#     subprocess.run(str(trgt_full_name(tn)))


if __name__ == '__main__':
    pass
