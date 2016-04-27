    /******************************************************************************
    * 文件名称：KL25_Lpt_Time.c
    * 内容摘要：LPTMR定时器软件模块
    * 其他说明：本软件模块适合于FRDM-KL25平台，用于提供ms的计时和延时，Sec的延时。
                在工程中加载C文件及H文件，将H文件中需要增加到isr.h的内容复制过去，
                在应用程序用Timer_Init()用于启动定时器
    * 当前版本：V1.00
    * 作 者：Ian
    * 完成日期：2015年3月11日
    ******************************************************************************/

    #include "common.h"
    #include "KL25_Lpt_Time.h"

    static WORD32 sg_dwSystime = 0; /* Global system time in ms */

    /*************************************************************************
    * 函数名称：WORD32 Timer_Init()
    * 功能说明：初始化计时器
    * 输入参数：无
    * 输出参数：无
    * 返 回 值：SW_ERROR: 操作失败
                SW_OK 操作成功
    * 其它说明：无
    **************************************************************************/
    WORD32 Timer_Init()
    {
        WORD32 dwData = 0; // For temp value of register

        MCG_SC &= (~MCG_SC_FCRDIV_MASK);     // Do this before set value of FCRDIV to evoid wrong masking
        MCG_SC |= MCG_SC_FCRDIV(2);          // We choose to divided clock by 4
        MCG_C2 |= MCG_C2_IRCS_MASK;          // And we choose the fast internal refenced clock(4MHz),
                                             // So final clock is 1Mhz.
        MCG_C1 |= MCG_C1_IRCLKEN_MASK;       // Then turn on MCGIRCLK and it works even in stop mode
        SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;   // Enable LPTMR software accessing

        LPTMR0_CSR &= ~LPTMR_CSR_TEN_MASK;   // Turn off LPTMR before LPTMR register configration
        dwData |= (LPTMR_CSR_TIE_MASK\
                  |LPTMR_CSR_TCF_MASK);      // We do this to reduce operations of register to save time
        LPTMR0_CSR = dwData;                 // In this case, we just operate register for once.
        LPTMR0_PSR |= LPTMR_PSR_PBYP_MASK;   // We do not need to divided the clock any more here
        LPTMR0_PSR &= (~LPTMR_PSR_PCS_MASK); // Choose MCGIRCLK as the clock source (1MHz)
        LPTMR0_CMR = (1025);                 // Then turn it as a period in 1ms

        LPTMR0_CSR |= LPTMR_CSR_TEN_MASK;    // After all, we turn on LPTMR and start counting
        
        NVIC_ICPR |= 1 << 28;
        NVIC_ISER |= 1 << 28;                // Enable interrupt
        return SW_OK;                        // That is all
    }

    /*************************************************************************
    * 函数名称：void lpt_isr()
    * 功能说明：计时器中断处理函数，每毫秒中断一次，更新sg_Systime
    * 输入参数：无
    * 输出参数：无
    * 返 回 值：无
    * 其它说明：无
    **************************************************************************/
    void lpt_isr()
    {
        LPTMR0_CSR |= LPTMR_CSR_TCF_MASK;    /* Clear Int flag */
        sg_dwSystime++;                      /* Update system time in ms */
    }

    /*************************************************************************
    * 函数名称：WORD16 App_GetSystemTime_ms()
    * 功能说明：获取当前毫秒数
    * 输入参数：无
    * 输出参数：无
    * 返 回 值：当前毫秒数 0~0xFFFF
    * 其它说明：无
    **************************************************************************/
    WORD16 App_GetSystemTime_ms()
    {
        return (uint32)sg_dwSystime; /* Return system time in ms */
    }

    /*************************************************************************
    * 函数名称：WORD16 App_GetSystemDelay_ms(WORD16 wTime)
    * 功能说明：获取延时毫秒数
    * 输入参数：WORD16 wTime 0~0xFFFF 起始时间
    * 输出参数：无
    * 返 回 值：延时毫秒数 0~0xFFFF
    * 其它说明：无
    **************************************************************************/
    WORD16 App_GetSystemDelay_ms(WORD16 wTime)
    {
        WORD16 wTemp = 0;
        wTemp = App_GetSystemTime_ms(); /* Get current time in ms */
        wTemp = wTemp - wTime;
        
        return wTemp; /* Return the time delay */
    }

    /*************************************************************************
    * 函数名称：void Delay_ms(WORD16 wTime)
    * 功能说明：延时固定毫秒数
    * 输入参数：WORD16 wTime 0~0xFFFF 延时时间ms
    * 输出参数：无
    * 返 回 值：无
    * 其它说明：无
    **************************************************************************/
    void Delay_ms(WORD16 wTime)
    {
        WORD16 wTemp;
        wTemp = App_GetSystemTime_ms(); /* Get current time in ms */
        while(1)
        {
            if(App_GetSystemDelay_ms(wTemp) >= wTime) /* If Delay time is over */
            {
                return;
            }
        }
    }

    /*************************************************************************
    * 函数名称：void Delay_s(WORD16 wTime)
    * 功能说明：延时固定秒数
    * 输入参数：WORD16 wTime 0~0xFFFF 延时时间s
    * 输出参数：无
    * 返 回 值：无
    * 其它说明：无
    **************************************************************************/
    void Delay_s(WORD16 wTime)
    {
        WORD16 wTemp = 0;
        while(1)
        {
            Delay_ms(1000); /* Wait 1000ms = 1s */
            wTemp++; /* Plus 1s */
            if(wTemp >= wTime) /* If delay time in s is over */
            {
                return;
            }
        }
    }

