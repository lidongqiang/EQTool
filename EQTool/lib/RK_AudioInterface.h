/************************************************************************************
�ļ����ƣ�
�ļ����ܣ�
�����б�
�޸����ڣ�
*************************************************************************************/
#ifndef RK_AUDIO_INTERFACE_H
#define RK_AUDIO_INTERFACE_H

/*--------------------------------------- include -----------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


/*--------------------------------------- �궨�� -----------------------------------------*/
#define AUDIOPOST_SCRGBASS     (0)
#define AUDIOPOST_SCRGPEAK1    (1)  
#define AUDIOPOST_SCRGTREBLE   (6)
#define AUDIOPOST_SCRCFBASS    (7)
#define AUDIOPOST_SCRCFPEAK1   (8)
#define AUDIOPOST_SCRCFTREBLE  (13)
#define AUDIOPOST_SCRQ1        (14)


/*--------------------------------------- ö�ٶ��� ----------------------------------------*/




/*--------------------------------------- �ṹ�嶨�� --------------------------------------*/





/*-------------------------------------- ȫ�ֱ������� --------------------------------------*/






/*----------------------------------------- �������� ---------------------------------------*/
extern void AudioPost_EQProduct(float *pfPara, float *pfCurve, signed int swFs, float fMinFreq, signed int swCurvePNum);
/*���У�pfPara��ָ��EQ�����ڴ��ָ�룬pfCurve��ָ��Ƶ�������ڴ��ָ�룬swFs�ǲ����ʣ�
fMinFreq��Ҫ���Ƶ�Ƶ�����ߺ����꣨Ƶ�ʣ�����Сֵ��fCurvePNum��Ҫ���Ƶ�Ƶ�����ߵĵ���*/


#ifdef __cplusplus
} 
#endif

#endif