/************************************************************************************
文件名称：
文件功能：
函数列表：
修改日期：
*************************************************************************************/
#ifndef RK_AUDIO_INTERFACE_H
#define RK_AUDIO_INTERFACE_H

/*--------------------------------------- include -----------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


/*--------------------------------------- 宏定义 -----------------------------------------*/
#define AUDIOPOST_SCRGBASS     (0)
#define AUDIOPOST_SCRGPEAK1    (1)  
#define AUDIOPOST_SCRGTREBLE   (6)
#define AUDIOPOST_SCRCFBASS    (7)
#define AUDIOPOST_SCRCFPEAK1   (8)
#define AUDIOPOST_SCRCFTREBLE  (13)
#define AUDIOPOST_SCRQ1        (14)


/*--------------------------------------- 枚举定义 ----------------------------------------*/




/*--------------------------------------- 结构体定义 --------------------------------------*/





/*-------------------------------------- 全局变量声明 --------------------------------------*/






/*----------------------------------------- 函数声明 ---------------------------------------*/
extern void AudioPost_EQProduct(float *pfPara, float *pfCurve, signed int swFs, float fMinFreq, signed int swCurvePNum);
/*其中，pfPara是指向EQ参数内存的指针，pfCurve是指向频响曲线内存的指针，swFs是采样率，
fMinFreq是要绘制的频响曲线横坐标（频率）的最小值，fCurvePNum是要绘制的频响曲线的点数*/


#ifdef __cplusplus
} 
#endif

#endif