#if    (IFX_CFG_SCU_PLL_FREQUENCY == (100000000UL)) \
    && (IFX_CFG_SCU_XTAL_FREQUENCY == (8000000UL))

#   define IFXSCU_CFG_PLL_FREQ 100MHZ

//! \brief Macro for Pll step for profile with 8MHz Crystal and 100MHz target
#   define IFXSCU_CFG_PLL_STEPS_8MHZ_100MHZ \
    {              /*Step 0 Config: 100MHz*/                     \
        (6 - 1),   /*uint8 k2Step;*/                             \
        0.000100,  /*float32 waitTime;*/                         \
        0          /*IfxScu_PllStepsFunctionHook hookFunction;*/ \
    },

//! \brief Macro for Pll step for profile with 8MHz Crystal and 100MHz target
#   define IFXSCU_CFG_PLL_INITIAL_STEP_8MHZ_100MHZ \
    /*{u8 pDivider, u8 nDivider, u8 k2Initial, f32 waitTime}*/ \
    {(1 - 1), (75 - 1), (6 - 1), 0.000200F}

//! \brief Macro to configure MAXDIV at 100MHz target frequency
#   define IFXSCU_CFG_MAXDIV_100MHZ (1)
//! \brief Macro to configure SRIDIV at 100MHz target frequency
#   define IFXSCU_CFG_SRIDIV_100MHZ (IFXSCU_CFG_MAXDIV_100MHZ)
//! \brief Macro to configure BAUD2DIV at 100MHz target frequency
#   define IFXSCU_CFG_BAUD2DIV_100MHZ (IFXSCU_CFG_MAXDIV_100MHZ)
//! \brief Macro to configure SPBDIV at 100MHz target frequency (max: 100MHz)
#   define IFXSCU_CFG_SPBDIV_100MHZ (IFXSCU_CFG_MAXDIV_100MHZ * 2)
//! \brief Macro to configure FSI2DIV at 100MHz target frequency
#   define IFXSCU_CFG_FSI2DIV_100MHZ (IFXSCU_CFG_MAXDIV_100MHZ)
//! \brief Macro to configure FSIDIV at 100MHz target frequency (max: 100MHz)
#   define IFXSCU_CFG_FSIDIV_100MHZ (IFXSCU_CFG_MAXDIV_100MHZ)
//! \brief Macro to configure CANDIV at 100MHz target frequency (max: 100MHz)
#   define IFXSCU_CFG_CANDIV_100MHZ (IFXSCU_CFG_MAXDIV_100MHZ)
//! \brief Macro to configure STMDIV at 100MHz target frequency (max: 100MHz)
#   define IFXSCU_CFG_STMDIV_100MHZ (IFXSCU_CFG_MAXDIV_100MHZ)
//! \brief Macro to configure GTMDIV at 100MHz target frequency (max: 100MHz)
#   define IFXSCU_CFG_GTMDIV_100MHZ (IFXSCU_CFG_MAXDIV_100MHZ)
//! \brief Macro to configure ETHDIV at 100MHz target frequency
#   define IFXSCU_CFG_ETHDIV_100MHZ (IFXSCU_CFG_MAXDIV_100MHZ * 2)
//! \brief Macro to configure ASCLINFDIV at 100MHz target frequency
#   define IFXSCU_CFG_ASCLINFDIV_100MHZ (IFXSCU_CFG_MAXDIV_100MHZ)
//! \brief Macro to configure ASCLINSDIV at 100MHz target freq (max: 100MHz)
#   define IFXSCU_CFG_ASCLINSDIV_100MHZ (IFXSCU_CFG_MAXDIV_100MHZ)
//! \brief Macro to configure BBBDIV at 100MHz target frequency
#   define IFXSCU_CFG_BBBDIV_100MHZ (IFXSCU_CFG_SRIDIV_100MHZ * 2)
//! \brief Macro to configure CPU0DIV at 100MHz target frequency
#   define IFXSCU_CFG_CPU0DIV_100MHZ (0)  /* ??? Same as SRIDIV ??? */
//! \brief Macro to configure FCON.WSPFLASH at 100MHz target frequency
#   define IFXSCU_CFG_FLASH_FCON_WSPFLASH_100MHZ (3 - 1)
//! \brief Macro to configure FCON.WSECP_ at 100MHz target frequency
#   define IFXSCU_CFG_FLASH_FCON_WSECPF_100MHZ (1 - 1)
//! \brief Macro to configure FCON.WSDFLASH at 100MHz target frequency
#   define IFXSCU_CFG_FLASH_FCON_WSDFLASH_100MHZ (16 - 1)
//! \brief Macro to configure FCON.WSECDF at 100MHz target frequency
#   define IFXSCU_CFG_FLASH_FCON_WSECDF_100MHZ (2 - 1)
#else
#   error   "Wrong PLL frequency configuration!, " \
            "check IFX_CFG_SCU_PLL_FREQUENCY configuration in Ifx_Cfg.h."
#   error   "Supported PLL frequencies are 80MHz, 100MHz (with 8MHz XTAL), " \
            "133MHz (8MHz XTAL doesn't support), 160Mhz, and 200MHz."
#endif
