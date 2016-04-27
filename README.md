# Timer-module-for-FRDM-KL25Z
It is a timer module for dev-board FRDM-KL25Z, which realize a 1-ms-interrupt, and update the global software clock for further use. For more infomation, please see descriptions in the files.

How to use:

    1. Add the KL25_Lpt_Time.c & KL25_Lpt_Time.h files into your project.
    
    2. Copy the comments from the buttom of KL25_Lpt_Time.h file into the isr.h. (or change the MARCO of VECTOR_044 in vectors.h    with isr function. It is NOT a good method).
    
    3. Call the functon Timer_Init to start the module.
    
使用方法：

    1、工程中添加模块中的.C和.H文件；

    2、将.H文件中注释的代码复制到工程中的isr.h中(或修改vectors.H文件中 VECTOR_044的宏定义为中断函数，此法不推荐)；

    3、在系统初始化时使用Timer_Init()函数初始化。

