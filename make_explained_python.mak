
.PHONY : all
# 'all : {}\n'.format(' '.join(map(trgt_full_name, build_cfg["targets"].keys())))
all : out/test/test_protocol.exe

# {trgt}.o					{src}						{trgt}.d				{opt}				{mk}
out/test/test_protocol.o : tests/test_protocol.cpp ! out/test/test_protocol.d ! out/test/inc.opt ! out/test/build.mk
#	{gcc}			{trgt}.o								{trgt}.Td					{std}	{opt}				{src}						{trgt}.o
	tricore-g++ -MT out/test/test_protocol.o -MMD -MP -MF out/test/test_protocol.Td -std=c++11 @out/test/inc.opt -c tests/test_protocol.cpp -o out/test/test_protocol.o
#			{trgt}.Td					{trgt}.d						{trgt}.o
	@mv -f out/test/test_protocol.Td out/test/test_protocol.d && touch out/test/test_protocol.o

# trgt_full_name(tn)							{objs}					{mk}
out/test/test_protocol.exe : out/test/test_protocol.o out/test/build.mk
#				{trgt}					{objs}
	g++ -o out/test/test_protocol.exe out/test/test_protocol.o

# {build_cfg["dir"]}/%.d:
out/test/%.d: ;
#			{build_cfg["dir"]}/%.d
.PRECIOUS: out/test/%.d
#				   {build_cfg["dir"]}/%.d)
include $(wildcard out/test/%.d)