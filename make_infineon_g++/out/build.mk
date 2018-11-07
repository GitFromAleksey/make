.PHONY: all clean factorial.o hello.o main.o

all: factorial.o hello.o main.o
	tricore-g++ -mcpu=tc23xx -Wl,-Map,HelloTSim.map -Wl,--extmap="a" -Wl,--gc-sections -o HelloTSim.elf factorial.o hello.o main.o
	@echo -- end of make


factorial.o: ../src/factorial.cpp
	tricore-g++ -mcpu=tc23xx -c -o factorial.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../src/factorial.cpp

hello.o: ../src/hello.cpp
	tricore-g++ -mcpu=tc23xx -c -o hello.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../src/hello.cpp

main.o: ../src/main.cpp
	tricore-g++ -mcpu=tc23xx -c -o main.o -g -ffunction-sections -msmall-data=65535 -msmall-const=65535 -O0 -fno-common --std=c++11 -Wall -W -Werror -Isrc/h ../src/main.cpp
clean:
	rm -rf *.o