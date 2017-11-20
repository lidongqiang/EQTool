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
#define PARANUM               (342)

#define PARA_CHANUM           (0)
#define PARA_EQSWTCH          (1)
#define PARA_DRCSWTCH         (2)
#define PARA_FS               (3)

#define PARA_L_GAIN           (14)

#define PARA_LEQ_GBASS        (25)
#define PARA_LEQ_GPEAK1       (26)  
#define PARA_LEQ_GTREBLE      (33)
#define PARA_LEQ_CFBASS       (34)
#define PARA_LEQ_CFPEAK1      (35)
#define PARA_LEQ_CFTREBLE     (42)
#define PARA_LEQ_Q1           (43)
	
#define PARA_LDRC_DIVFREQ     (135)
#define PARA_LDRC_B1_ECALTIME (136)
#define PARA_LDRC_B1_MAKEUPG  (137)
#define PARA_LDRC_B1_THREL    (138)
#define PARA_LDRC_B1_THREH    (139)
#define PARA_LDRC_B1_RATLNOM  (140)
#define PARA_LDRC_B1_RATLDEN  (141)
#define PARA_LDRC_B1_RATHNOM  (142)
#define PARA_LDRC_B1_RATHDEN  (143)
#define PARA_LDRC_B1_RLSTIME  (144)
#define PARA_LDRC_B1_SMTHTIME (145)
#define PARA_LDRC_B1_ATTATIME (146)
#define PARA_LDRC_B2_ECALTIME (147)
#define PARA_LDRC_B2_MAKEUPG  (148)
#define PARA_LDRC_B2_THREL    (149)
#define PARA_LDRC_B2_THREH    (150)
#define PARA_LDRC_B2_RATLNOM  (151)
#define PARA_LDRC_B2_RATLDEN  (152)
#define PARA_LDRC_B2_RATHNOM  (153)
#define PARA_LDRC_B2_RATHDEN  (154)
#define PARA_LDRC_B2_RLSTIME  (155)
#define PARA_LDRC_B2_SMTHTIME (156)
#define PARA_LDRC_B2_ATTATIME (157)

#define PARA_R_GAIN           (178)

#define PARA_REQ_GBASS        (189)
#define PARA_REQ_GPEAK1       (190)  
#define PARA_REQ_GTREBLE      (197)
#define PARA_REQ_CFBASS       (198)
#define PARA_REQ_CFPEAK1      (199)
#define PARA_REQ_CFTREBLE     (206)
#define PARA_REQ_Q1           (207)
	
#define PARA_RDRC_DIVFREQ     (299)
#define PARA_RDRC_B1_ECALTIME (300)
#define PARA_RDRC_B1_MAKEUPG  (301)
#define PARA_RDRC_B1_THREL    (302)
#define PARA_RDRC_B1_THREH    (303)
#define PARA_RDRC_B1_RATLNOM  (304)
#define PARA_RDRC_B1_RATLDEN  (305)
#define PARA_RDRC_B1_RATHNOM  (306)
#define PARA_RDRC_B1_RATHDEN  (307)
#define PARA_RDRC_B1_RLSTIME  (308)
#define PARA_RDRC_B1_SMTHTIME (309)
#define PARA_RDRC_B1_ATTATIME (310)
#define PARA_RDRC_B2_ECALTIME (311)
#define PARA_RDRC_B2_MAKEUPG  (312)
#define PARA_RDRC_B2_THREL    (313)
#define PARA_RDRC_B2_THREH    (314)
#define PARA_RDRC_B2_RATLNOM  (315)
#define PARA_RDRC_B2_RATLDEN  (316)
#define PARA_RDRC_B2_RATHNOM  (317)
#define PARA_RDRC_B2_RATHDEN  (318)
#define PARA_RDRC_B2_RLSTIME  (319)
#define PARA_RDRC_B2_SMTHTIME (320)
#define PARA_RDRC_B2_ATTATIME (321)


/*--------------------------------------- 枚举定义 ----------------------------------------*/
typedef enum
{
	SWITCH_OFF = 0,
	SWITCH_ON
}SWITCH_FLAG_ENUM;




/*--------------------------------------- 结构体定义 --------------------------------------*/





/*-------------------------------------- 全局变量声明 --------------------------------------*/






/*----------------------------------------- 函数声明 ---------------------------------------*/

#ifdef __cplusplus
} 
#endif

#endif