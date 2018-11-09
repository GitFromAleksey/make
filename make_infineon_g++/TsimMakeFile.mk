.PHONY: sim

SIM_FILE_NAME=C:\WorkSpace\ProjectLifeCycleAutomation\2_Out\Tricore_Gnuc\prog_tc.elf
#SIM_FILE_NAME=out\artifacts\HelloTSim.elf

# -x 0 - forever
SIM_TIME_CYCLES = -x 5179
#5178
#SIM_TIME_CYCLES = -x 0

PATH_TC161_CFG_FILES = .\tsim\tc161

FILE_MCFG = MConfig
FILE_DCFG = DConfig
FILE_ICFG = IConfig
FILE_PCFG = PConfig

TC161_MConfig = -MConfig $(PATH_TC161_CFG_FILES)\$(FILE_MCFG)
TC161_DConfig = -DConfig $(PATH_TC161_CFG_FILES)\$(FILE_DCFG)
TC161_IConfig = -IConfig $(PATH_TC161_CFG_FILES)\$(FILE_ICFG)
TC161_PConfig = -PConfig $(PATH_TC161_CFG_FILES)\$(FILE_PCFG)

COFG_INP_FILES = $(TC161_MConfig) $(TC161_DConfig) $(TC161_IConfig) $(TC161_PConfig)

# Complete histogram output at the end of simulation in the log-file
LOG_HIST=-h
#standalone execution
STAL_EX=-s
# Enable syscall handling (for HighTec tools) Also sets –use-elf-paddr
EN_SYSCALL_HNDL=-H

SIM_OPTIONS= $(LOG_HIST) $(STAL_EX) $(EN_SYSCALL_HNDL)

# тип ядра
#TSIM = tsim
#TSIM = tsim16

TSIM = tsim16p_e.exe

#TSIM = tsim16p_e_astep
#TSIM = tsim1311

sim: $(SIM_FILE_NAME)
	$(TSIM) $(COFG_INP_FILES) $(SIM_TIME_CYCLES) $(SIM_OPTIONS) -disable-watchdog -o $(SIM_FILE_NAME) -log-file tsim.log


