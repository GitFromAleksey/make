.PHONY: all main.o hello.o factorial.o clean

CFLAGS = -c -Wall

# LDFLAGS=
# SOURCES=main.cpp hello.cpp factorial.cpp
SRCFLDR=src/
OBJFLDR=obj/
OUTFLDR=out/
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=hello

LIB_FLDR_SET_CMD = --sysroot=
LIB_FLDR_PATH = C:\devel\hightec\toolchains\tricore\v4.9.1.0-infineon-1.1\tricore\include\c++\4.9.4


STD_CPP11 = --std=c++11
STD_GNU11 = --std=gnu++11

GPP = g++
FFUNC = -ffunction-sections -msmall-data=65535 -msmall-const=65535
SIZE1 = -Os
FNOCOM = -fno-common --std=c99  -Wall -W -Werror

PATH_bsp_tricore_TriBoard_TC23xx = C:/devel/hightec/toolchains/tricore/v4.9.1.0-infineon-1.1/bsp/tricore/TriBoard-TC23xx/
PATH_common_tsim = C:/devel/hightec/toolchains/tricore/v4.9.1.0-infineon-1.1/bsp/tricore/common/tsim/
PATH_common_tsim_tc161 = C:/devel/hightec/toolchains/tricore/v4.9.1.0-infineon-1.1/bsp/tricore/common/tsim/tc161/
PATH_TC161_DConfig = C:\WorkSpace\make\make_g++\tsim\tc161\DConfig
PATH_TC161_MConfig = C:\WorkSpace\make\make_g++\tsim\tc161\MConfig

TSIM = tsim
#TSIM = tsim16
TSIM = tsim16p_e
#TSIM = tsim16p_e_astep
#TSIM = tsim1311

#tsim16p_e
#tc161
# -c  -  Compile and assemble, but do not link
# -Wall  -  turns warnings
# -o <file>  -  Place the output into <file>

all: main.o hello.o factorial.o
	$(GPP) -o HelloTSim.exe main.o hello.o factorial.o
	@echo  -- end of make

main.o: $(SRCFLDR)main.cpp
	$(GPP) -c -o main.o -O0 $(STD_CPP11)  -Wall -W -Werror -Isrc/h $(SRCFLDR)main.cpp

hello.o: $(SRCFLDR)hello.cpp
	$(GPP) -c -o hello.o -O0  $(STD_CPP11)  -Wall -W -Werror -Isrc/h $(SRCFLDR)hello.cpp

factorial.o:  $(SRCFLDR)factorial.cpp
	$(GPP) -c -o factorial.o -O0  $(STD_CPP11)  -Wall -W -Werror -Isrc/h $(SRCFLDR)factorial.cpp

	
clean:
	rm -rf *.o
	#rm -rf $(OUTFLDR)hello.exe