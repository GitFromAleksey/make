.PHONY: all clean all_tests 

all: ../out/factorial.o ../out/hello.o ../out/main.o
	g++ -Wl,-Map,../out/artifacts/HelloTSim.map -Wl, -Wl,--gc-sections -o ../out/artifacts/HelloTSim.exe ../out/factorial.o ../out/hello.o ../out/main.o

all_tests: ../out/tests/test_protocol.exe 


../out/factorial.o: ../src/factorial.cpp ../out/factorial.d ../out/inc.opt ../out/build.mk
	g++ -MT ../out/factorial.o -MMD -MP -MF ../out/factorial.Td @../out/inc.opt -c -o ../out/factorial.o -g -ffunction-sections -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../src/factorial.cpp 
	@mv -f ../out/factorial.Td ../out/factorial.d && touch ../out/factorial.o

../out/hello.o: ../src/hello.cpp ../out/hello.d ../out/inc.opt ../out/build.mk
	g++ -MT ../out/hello.o -MMD -MP -MF ../out/hello.Td @../out/inc.opt -c -o ../out/hello.o -g -ffunction-sections -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../src/hello.cpp 
	@mv -f ../out/hello.Td ../out/hello.d && touch ../out/hello.o

../out/main.o: ../src/main.cpp ../out/main.d ../out/inc.opt ../out/build.mk
	g++ -MT ../out/main.o -MMD -MP -MF ../out/main.Td @../out/inc.opt -c -o ../out/main.o -g -ffunction-sections -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../src/main.cpp 
	@mv -f ../out/main.Td ../out/main.d && touch ../out/main.o

../out/tests/test_protocol.o: ../tests/test_protocol.cpp ../out/tests/test_protocol.d ../out/inc.opt ../out/build.mk
	g++ -MT ../out/tests/test_protocol.o -MMD -MP -MF ../out/tests/test_protocol.Td @../out/inc.opt -c -o ../out/tests/test_protocol.o -g -ffunction-sections -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../tests/test_protocol.cpp 
	@mv -f ../out/tests/test_protocol.Td ../out/tests/test_protocol.d && touch ../out/tests/test_protocol.o

../out/tests/test_protocol.exe: ../out/tests/test_protocol.o ../out/build.mk
	g++ -o ../out/tests/test_protocol.exe ../out/tests/test_protocol.o

../out/%.d: ;
.PRECIOUS: ../out/%.d
include $(wildcard ../out/*.d)

clean:
	rm -rf ../out/*.o
	rm -rf ../out/*.d