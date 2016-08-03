/******************************************************************************
* 文件名称：KL25_Lpt_Time.h
* 内容摘要：LPTMR定时器软件模块头文件
* 其他说明：本软件模块适合于FRDM-KL25平台，用于提供ms的计时和延时，Sec的延时。
*           在工程中加载C文件及H文件，将H文件中需要增加到isr.h的内容复制过去，
*           在应用程序用Timer_Init()用于启动定时器
* 当前版本：V1.00
* 作 者：Ian
* 完成日期：2015年3月11日
******************************************************************************/

#ifndef __KL25_LPT_TIME_H_
#define __KL25_LPT_TIME_H_

typedef uint8_t BYTE;
typedef uint16_t WORD16;
typedef uint32_t WORD32;

#define SW_ERR (-1)
#define SW_OK 0

/*************************************************************************
* 函数名称：WORD32 Timer_Init()
* 功能说明：初始化计时器
* 输入参数：无
* 输出参数：无
* 返 回 值：SW_ERROR: 操作失败
*           SW_OK 操作成功
* 其它说明：无
**************************************************************************/
WORD32 Timer_Init();

/*************************************************************************
* 函数名称：void lpt_isr()
* 功能说明：计时器中断处理函数，每毫秒中断一次，更新sg_Systime
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：无
**************************************************************************/
void lpt_isr();

/*************************************************************************
* 函数名称：WORD16 App_GetSystemTime_ms()
* 功能说明：获取当前毫秒数
* 输入参数：无
* 输出参数：无
* 返 回 值：当前毫秒数 0~0xFFFF
* 其它说明：无
**************************************************************************/
WORD16 App_GetSystemTime_ms();

/*************************************************************************
* 函数名称：WORD16 App_GetSystemDelay_ms(WORD16 wTime)
* 功能说明：获取延时毫秒数
* 输入参数：WORD16 wTime 0~0xFFFF 起始时间
* 输出参数：无
* 返 回 值：延时毫秒数 0~0xFFFF
* 其它说明：无
**************************************************************************/
WORD16 App_GetSystemDelay_ms(WORD16 wTime);

/*************************************************************************
* 函数名称：void Delay_ms(WORD16 wTime)
* 功能说明：延时固定毫秒数
* 输入参数：WORD16 wTime 0~0xFFFF 延时时间ms
* 输出参数：无
* 返 回 值：无
* 其它说明：无
**************************************************************************/
void Delay_ms(WORD16 wTime);

/*************************************************************************
* 函数名称：void Delay_s(WORD16 wTime)
* 功能说明：延时固定秒数
* 输入参数：WORD16 wTime 0~0xFFFF 延时时间s
* 输出参数：无
* 返 回 值：无
* 其它说明：无
**************************************************************************/
void Delay_s(WORD16 wTime);


/* Copy follow to isr.h

#undef VECTOR_044
#define VECTOR_044 lpt_isr

extern void lpt_isr(void);
*/

#endif //__KL25_LPT_TIME_H_

/* End of file */ 
