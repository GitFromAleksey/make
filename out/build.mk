.PHONY: all clean 

all: 
	tricore-g++ -mcpu=tc23xx -Wl,-Map,../out/artifacts/HelloTSim.map -Wl,--extmap="a" -Wl,--gc-sections -o ../out/artifacts/HelloTSim.elf 

../out/%.d: ;
.PRECIOUS: ../out/%.d
include $(wildcard ../out/*.d)

clean:
	rm -rf ../out/*.o
	rm -rf ../out/*.d