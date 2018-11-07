/**
 * \file Ifx_Cfg.h
 * \brief Project configuration file.
 *
 * \copyright Copyright (c) 2012 Infineon Technologies AG. All rights reserved.
 */

#if !defined(IFX_CFG_H_)
#   define IFX_CFG_H_

//#############################################################################
// Configuration for "IfxCpu_CStart0.c"
//#############################################################################
// Program is to be called by bootloader or by externally defined BMH
#define IFX_CFG_CPUCSTART_BMHD_NOT_NEEDED

//#############################################################################
// Configuration for "IfxScu_cfg.h"
//#############################################################################

// F_XTAL[MHz] = {8, 16, 20, 40}
#   define IFX_CFG_SCU_XTAL_FREQUENCY (8000000UL)
// F_PLL[MHz] = {80, 100, 133, 160, 200}
#   if defined(CONF_PCB_10P0P2)
#      define IFX_CFG_SCU_PLL_FREQUENCY (100000000UL)
#   else
#      define IFX_CFG_SCU_PLL_FREQUENCY (200000000UL)
#   endif

//#############################################################################
// Configuration for "Compilers.h"
//#############################################################################

// Software managed interrupts
//#   define IFX_USE_SW_MANAGED_INT

// Hardware managed interrupts
#   if !defined(IFX_USE_SW_MANAGED_INT)
#       define IFX_INTERRUPT(...) IFX_INTERRUPT_INTERNAL(__VA_ARGS__)
#       define IFX_INTERRUPT_INTERNAL(isr, vectabNum, prio, groupPrio) \
    __asm__ (\
        ".ifndef .intr.entry.include                                    \n"\
        ".altmacro                                                      \n"\
        "# define the section and inttab entry code                     \n"\
        ".macro .int_entry.2 intEntryLabel, name, groupPrio             \n"\
        "    .pushsection .\\intEntryLabel,\"ax\",@progbits             \n"\
        "    __\\intEntryLabel :                                        \n"\
        "        bisr groupPrio                                         \n"\
        "        j name                                                 \n"\
        "    .popsection                                                \n"\
        ".endm                                                          \n"\
        ".macro .int_entry.1 prio,vectabNum,u,name,groupPrio            \n"\
        "# build the unique name                                        \n"\
        ".int_entry.2 intvec_tc\\vectabNum\\u\\prio,(name),(groupPrio)  \n"\
        ".endm                                                          \n"\
        ".macro .intr.entry name,vectabNum,prio,groupPrio               \n"\
        "# evaluate the priority and the cpu number                     \n"\
        ".int_entry.1 %(prio),%(vectabNum),_,name,%(groupPrio)          \n"\
        ".endm                                                          \n"\
        ".intr.entry.include:                                           \n"\
        ".endif                                                         \n"\
        ".intr.entry "#isr","#vectabNum","#prio","#groupPrio);\
IFX_EXTERN void __attribute__ ((interrupt_handler)) isr();\
void isr (void)
#   endif  // IFX_USE_SW_MANAGED_INT

//#############################################################################
// Configuration for Trap Hook Functions' Extensions ("IfxCpu_Trap.c")
//#############################################################################

//#define IFX_CFG_EXTEND_TRAP_HOOKS

//#############################################################################
// Stacks
//#############################################################################

extern unsigned int __USTACK0_END[];
extern unsigned int __ISTACK0_END[];

#   if defined(__DEBUG__)
#       define DEBUG_STACK_INIT_VAL 0x12345678
#       define DEBUG_STACK_INIT_CODE_0(stack_name) \
        { \
            register long *p = (long *)stack_name##_END; \
            while (p < (long *)stack_name) *p++ = DEBUG_STACK_INIT_VAL; \
        }
#       define DEBUG_STACK_INIT_CODE(s) DEBUG_STACK_INIT_CODE_0(s)
#       define IFX_CFG_CPU_CSTART_PRE_C_INIT_HOOK(cpu) \
            DEBUG_STACK_INIT_CODE(__USTACK(cpu)) \
            DEBUG_STACK_INIT_CODE(__ISTACK(cpu))
#   else
#       define DEBUG_STACK_INIT_VAL 0
#   endif

// Data Cache enabled by default
#   define IFX_CFG_CPU_CSTART_ENABLE_TRICORE0_DCACHE (1)

#   define IFXCPU_CSTART_CCU_INIT_HOOK()

#endif  // IFX_CFG_H_
