.PHONY: all clean 

all: ../out/factorial.o ../out/hello.o ../out/main.o
	tricore-g++ -mcpu=tc23xx -Wl,-Map,../out/artifacts/HelloTSim.map -Wl,--extmap="a" -Wl,--gc-sections -o ../out/artifacts/HelloTSim.elf ../out/factorial.o ../out/hello.o ../out/main.o

../out/factorial.o: ../src/factorial.cpp ../out/factorial.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/factorial.o -MMD -MP -MF ../out/factorial.Td @../out/inc.opt -c -o ../out/factorial.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../src/factorial.cpp
	@mv -f ../out/factorial.Td ../out/factorial.d && touch ../out/factorial.o

../out/hello.o: ../src/hello.cpp ../out/hello.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/hello.o -MMD -MP -MF ../out/hello.Td @../out/inc.opt -c -o ../out/hello.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../src/hello.cpp
	@mv -f ../out/hello.Td ../out/hello.d && touch ../out/hello.o

../out/main.o: ../src/main.cpp ../out/main.d ../out/inc.opt ../out/build.mk
	tricore-g++ -mcpu=tc23xx -MT ../out/main.o -MMD -MP -MF ../out/main.Td @../out/inc.opt -c -o ../out/main.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../src/main.cpp
	@mv -f ../out/main.Td ../out/main.d && touch ../out/main.o

../out/%.d: ;
.PRECIOUS: ../out/%.d
include $(wildcard ../out/*.d)

clean:
	rm -rf ../out/*.o
	rm -rf ../out/*.d