/************************************************************************************
文件名称：
文件功能：
函数列表：
修改日期：
*************************************************************************************/
#ifndef RK_TOOLINTERFACE_H
#define RK_TOOLINTERFACE_H

/*--------------------------------------- include -----------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif


/*--------------------------------------- 宏定义 -----------------------------------------*/
// 参数的数目
#define PARANUM               (614)    

/********** 各参数的内存位置 **********/
#define PARA_CHANUM           (0)
#define PARA_FS               (1)
#define PARA_EQ10SWTCH        (2)
#define PARA_DRCSWTCH         (3)
#define PARA_LIMITERSWTCH     (4)
#define PARA_EQ8SWTCH         (5)

#define PARA_L_GAIN1          (16)

#define PARA_LEQ10_GBASS      (27)
#define PARA_LEQ10_GPEAK1     (28)  
#define PARA_LEQ10_GTREBLE    (36)
#define PARA_LEQ10_CFBASS     (37)
#define PARA_LEQ10_CFPEAK1    (38)
#define PARA_LEQ10_CFTREBLE   (46)
#define PARA_LEQ10_Q1         (47)
	
#define PARA_LDRC_DIVFREQ     (145)
#define PARA_LDRC_B1_ECALTIME (146)
#define PARA_LDRC_B1_MAKEUPG  (147)
#define PARA_LDRC_B1_THREL    (148)
#define PARA_LDRC_B1_THREH    (149)
#define PARA_LDRC_B1_RATLNOM  (150)
#define PARA_LDRC_B1_RATLDEN  (151)
#define PARA_LDRC_B1_RATHNOM  (152)
#define PARA_LDRC_B1_RATHDEN  (153)
#define PARA_LDRC_B1_RLSTIME  (154)
#define PARA_LDRC_B1_SMTHTIME (155)
#define PARA_LDRC_B1_ATTATIME (156)
#define PARA_LDRC_B2_ECALTIME (157)
#define PARA_LDRC_B2_MAKEUPG  (158)
#define PARA_LDRC_B2_THREL    (159)
#define PARA_LDRC_B2_THREH    (160)
#define PARA_LDRC_B2_RATLNOM  (161)
#define PARA_LDRC_B2_RATLDEN  (162)
#define PARA_LDRC_B2_RATHNOM  (163)
#define PARA_LDRC_B2_RATHDEN  (164)
#define PARA_LDRC_B2_RLSTIME  (165)
#define PARA_LDRC_B2_SMTHTIME (166)
#define PARA_LDRC_B2_ATTATIME (167)
	
#define PARA_LLMT_ECALTIME    (188)
#define PARA_LLMT_THRESHOLD   (189)
#define PARA_LLMT_ATTACKTIME  (190)
#define PARA_LLMT_SMOOTHTIME  (191)

#define PARA_LEQ8_GBASS       (202)
#define PARA_LEQ8_GPEAK1      (203)  
#define PARA_LEQ8_GTREBLE     (209)
#define PARA_LEQ8_CFBASS      (210)
#define PARA_LEQ8_CFPEAK1     (211)
#define PARA_LEQ8_CFTREBLE    (217)
#define PARA_LEQ8_Q1          (218)

#define PARA_L_GAIN2          (304)
	
#define PARA_R_GAIN1          (315)

#define PARA_REQ10_GBASS      (326)
#define PARA_REQ10_GPEAK1     (327)  
#define PARA_REQ10_GTREBLE    (335)
#define PARA_REQ10_CFBASS     (336)
#define PARA_REQ10_CFPEAK1    (337)
#define PARA_REQ10_CFTREBLE   (345)
#define PARA_REQ10_Q1         (346)
	
#define PARA_RDRC_DIVFREQ     (444)
#define PARA_RDRC_B1_ECALTIME (445)
#define PARA_RDRC_B1_MAKEUPG  (446)
#define PARA_RDRC_B1_THREL    (447)
#define PARA_RDRC_B1_THREH    (448)
#define PARA_RDRC_B1_RATLNOM  (449)
#define PARA_RDRC_B1_RATLDEN  (450)
#define PARA_RDRC_B1_RATHNOM  (451)
#define PARA_RDRC_B1_RATHDEN  (452)
#define PARA_RDRC_B1_RLSTIME  (453)
#define PARA_RDRC_B1_SMTHTIME (454)
#define PARA_RDRC_B1_ATTATIME (455)
#define PARA_RDRC_B2_ECALTIME (456)
#define PARA_RDRC_B2_MAKEUPG  (457)
#define PARA_RDRC_B2_THREL    (458)
#define PARA_RDRC_B2_THREH    (459)
#define PARA_RDRC_B2_RATLNOM  (460)
#define PARA_RDRC_B2_RATLDEN  (461)
#define PARA_RDRC_B2_RATHNOM  (462)
#define PARA_RDRC_B2_RATHDEN  (463)
#define PARA_RDRC_B2_RLSTIME  (464)
#define PARA_RDRC_B2_SMTHTIME (465)
#define PARA_RDRC_B2_ATTATIME (466)
	
#define PARA_RLMT_ECALTIME    (487)
#define PARA_RLMT_THRESHOLD   (488)
#define PARA_RLMT_ATTACKTIME  (489)
#define PARA_RLMT_SMOOTHTIME  (490)

#define PARA_REQ8_GBASS       (501)
#define PARA_REQ8_GPEAK1      (502)  
#define PARA_REQ8_GTREBLE     (508)
#define PARA_REQ8_CFBASS      (509)
#define PARA_REQ8_CFPEAK1     (510)
#define PARA_REQ8_CFTREBLE    (516)
#define PARA_REQ8_Q1          (517)

#define PARA_R_GAIN2          (603)


/*--------------------------------------- 枚举定义 ----------------------------------------*/
typedef enum
{
	SWITCH_OFF = 0,     // 开关打开
	SWITCH_ON           // 开关关闭
}SWITCH_FLAG_ENUM;




/*--------------------------------------- 结构体定义 --------------------------------------*/





/*-------------------------------------- 全局变量声明 --------------------------------------*/






/*----------------------------------------- 函数声明 ---------------------------------------*/

#ifdef __cplusplus
} 
#endif

#endif