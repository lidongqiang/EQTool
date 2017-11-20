#ifndef _SETTINGBASE_H_
#define _SETTINGBASE_H_
#define USER_LOGIN
#define APP_VERSION " EQTool V1.0.0"
#include "inifile.h"
#include "../RK_ToolInterface.h"

#include <vector>
#define LAN_ACTION TRUE
#define nof(x) (sizeof(x) / sizeof(x[0]))
#define MASK_FUSE  1
#define MASK_WV    2
#define MASK_BASIC 3
#define CALIB_CONFIG

#define FLAG_WVKEY 				0
#define FLAG_WVFLG				1
#define FLAG_DEVSN				2
#define FLAG_WVCNT				3

#define FLAG_UNSD               TEXT("0")
#define FLAG_BUSY               TEXT("2")
#define FLAG_USED               TEXT("1")


#define IMEI_LEN                15
#define MAC_LEN                 6

#define COL_WOID                0
#define MAX_COLUMN              100

/********** DEBUG_LEVEL ***********/
#define DLEVEL_DEBUG            0
#define DLEVEL_INFO             1
#define DLEVEL_WARNING          2
#define DLEVEL_ERROR            3
#define DLEVEL_NONE             4

#define EQGAIN_LEN				9
#define EQCF_LEN				9
#define EQQ_LEN					7
#define DRC_LEN					11

class CSettingBase
{
private:
    CIniSection *pCurSection;
    CIniSection *pOldSection;
protected:
    CIniFile    *pIniFile;


    std::wstring APPNAME;
    std::wstring szFileName;
    std::wstring strModulePath;
public:
    CSettingBase()
    {
        pIniFile    = NULL;
        pCurSection = NULL;
    };
    static std::string wstr2str(const std::wstring& arg)
    {
    	int requiredSize;
    	requiredSize = WideCharToMultiByte(CP_ACP,0,arg.c_str(),arg.length(),NULL,0,NULL,NULL);
    	std::string res;
    	if (requiredSize<=0) {
    		res = "";
    		return res;
    	}
    	res.assign(requiredSize,'\0');
    	WideCharToMultiByte(CP_ACP,0,arg.c_str(),arg.length(),const_cast<char*>(res.data()),requiredSize,NULL,NULL);
    	return res;
    }
    static std::wstring str2wstr(const std::string& arg)
    {
    	int requiredSize;
    	requiredSize = MultiByteToWideChar(CP_ACP,0,arg.c_str(),arg.length(),NULL,0);
    	std::wstring res;
    	if (requiredSize<=0) {
    		res = L"";
    		return res;
    	}
    	res.assign(requiredSize,L'\0');
    	MultiByteToWideChar(CP_ACP,0,arg.c_str(),arg.length(),const_cast<wchar_t *>(res.data()),requiredSize);
    	return res;
    }
	virtual ~CSettingBase(){};
    virtual bool SaveToolSetting(std::wstring strConfig) = 0;
    virtual bool LoadToolSetting(std::wstring strConfig) = 0;
    virtual std::wstring GetStr(std::wstring &key) = 0;
    virtual std::wstring GetStr(const wchar_t *key) = 0;
    virtual bool SetStr(std::wstring &key,std::wstring &value) = 0;
    virtual bool SetStr(const wchar_t *key,const wchar_t * value) = 0;
    bool    IsPathFileExists(const std::wstring strFilaName);
    bool    CreateFolder(std::wstring strDir);

    std::wstring int2str(int i)
    {
        wchar_t szTmep[32] = {0};
        swprintf(szTmep,32,TEXT("%d"),i);
        return szTmep;
    }

    CIniSection * GetCurSection(){
        return pCurSection;
    }

    void SetCurSection(CIniSection * pSec)
    {
        if(pCurSection) pOldSection = pCurSection;
        pCurSection = pSec;
    }
    void ResumeSection()
    {
        CIniSection *pSec;
        if(pOldSection) {
            pSec        = pCurSection;
            pCurSection = pOldSection;
            pOldSection = pSec;
        }
    }

};

class CIniSettingBase:public CSettingBase
{
public:
    CIniSettingBase()
    {
    };
	virtual ~CIniSettingBase();
    virtual bool SaveToolSetting(std::wstring strConfig) ;
    virtual bool LoadToolSetting(std::wstring strConfig) ;

    virtual std::wstring GetStr(std::wstring &key);
    virtual std::wstring GetStr(const wchar_t *key);
    virtual bool SetStr(std::wstring &key,std::wstring &value);
    virtual bool SetStr(const wchar_t *key,std::wstring &value);
    virtual bool SetStr(const wchar_t *key,const wchar_t * value);

    void    ParseIntegers(std::wstring s, double *pInt, int *pLen);
    void    ParseIntegers(std::wstring s, int *pInt, int *nLen);
    void    ParseIntegers(std::wstring s, float *pInt, int *pLen);
    void    ParseStr(std::wstring s, std::wstring *pInt, int *pLen);
    void    ParseIp(std::wstring s, unsigned int *IPV4);
    void    ParseBools(std::wstring s, bool *pBool, int *pLen);
    static int MemoryCompare(std::wstring &s2,std::wstring &s1)
    {
        return s2.compare(s1);
    }

    std::wstring EncryptPassWord(std::wstring plaintext);
    std::wstring DecryptPassWord(std::wstring ciphertext);

public:
	std::wstring			strLanPath;
	int						nCurLan;
	std::wstring			strCnFilename;
	std::wstring			strEnFilename;
	std::wstring			strCnFontName;
	std::wstring			strEnFontName;
	int						nCnFontSize;
	int						nEnFontSize;
	bool					bDebug;	
	int						nLogLevel;
	std::wstring			strLogPath;
	bool					bLink;
	bool					bEQSwtch;
	bool					bDrcSwtch;
	int						nChannel;

	/* 1.1 ���������������� */
	int		swFs;			//������
	float	fMinFreq;		//���Ƶ�Ƶ�����ߺ����꣨Ƶ�ʣ�����Сֵ
	int		shwChaNum;		//������
	int		nEqSwitch;		//EQ����
	int		nDrcSwitch;		//DRC����
	int		swCurveLen;		//

	/* 1.2 ���������� */
	/* 1.2.1 ���������� */
	float		ScrGainL;
	/* 1.2.2 ������EQ���� */
	float	EqGainLeft[EQGAIN_LEN];
	float	EqCFLeft[EQCF_LEN];
	float   EqQLeft[EQQ_LEN];
	//float	DrcLeft[DRC_LEN];
	/* 1.2.2 ������DRC���� */
	float	DivFreq_L;		//����RMS������ͳ��ʱ�䣬��λms
	// ��Ƶ�Ӵ�
	float	Offset_LL;		// ���Զ�����dB��
	float	Threl_LL;		// ���ܶ�������ֵ����λdB		
	float	Threh_LL;		// ���ܶ�������ֵ����λdB
	float	Ecaltime_LL;	//����RMS������ͳ��ʱ�䣬��λms
	float	Ratlnom_LL;		// ���ܶ�ѹ�������ķ���
	float	Ratlden_LL;		// ���ܶ�ѹ�������ķ�ĸ
	float	Rathnom_LL;		// ���ܶ�ѹ�������ķ���
	float	Rathden_LL;		// ���ܶ�ѹ�������ķ�ĸ
	float	Rlstime_LL;		// release time����λms
	float	Smthtime_LL;	// �м��ʱ��ƽ��ʱ�䣬��λms
	float	Attatime_LL;	// attack time����λms
	// ��Ƶ�Ӵ�
	float	Offset_LH;
	float	Threl_LH;
	float	Threh_LH;
	float	Ecaltime_LH;	//����RMS������ͳ��ʱ�䣬��λms
	float	Ratlnom_LH;
	float	Ratlden_LH;
	float	Rathnom_LH;
	float	Rathden_LH;
	float	Rlstime_LH;
	float	Smthtime_LH;
	float	Attatime_LH;

	/* 1.3 ���������� */
	/* 1.2.1 ���������� */
	float	ScrGainR;
	/* 1.2.2 ������EQ���� */
	float	EqGainRight[9];
	float	EqCFRight[9];
	float   EqQRight[7];
	//sfloat	DrcRight[11];
	/* 1.2.3 ������DRC���� */
	float	DivFreq_R;		//����RMS������ͳ��ʱ�䣬��λms
	// ��Ƶ�Ӵ�
	float	Offset_RL;		// ���Զ�����dB��
	float	Threl_RL;		// ���ܶ�������ֵ����λdB		
	float	Threh_RL;		// ���ܶ�������ֵ����λdB
	float	Ecaltime_RL;	//����RMS������ͳ��ʱ�䣬��λms
	float	Ratlnom_RL;		// ���ܶ�ѹ�������ķ���
	float	Ratlden_RL;		// ���ܶ�ѹ�������ķ�ĸ
	float	Rathnom_RL;		// ���ܶ�ѹ�������ķ���
	float	Rathden_RL;		// ���ܶ�ѹ�������ķ�ĸ
	float	Rlstime_RL;		// release time����λms
	float	Smthtime_RL;	// �м��ʱ��ƽ��ʱ�䣬��λms
	float	Attatime_RL;	// attack time����λms
	// ��Ƶ�Ӵ�
	float	Offset_RH;
	float	Threl_RH;
	float	Threh_RH;
	float	Ecaltime_RH;	//����RMS������ͳ��ʱ�䣬��λms
	float	Ratlnom_RH;
	float	Ratlden_RH;
	float	Rathnom_RH;
	float	Rathden_RH;
	float	Rlstime_RH;
	float	Smthtime_RH;
	float	Attatime_RH;

};
class CIniLocalLan:public CSettingBase
{
private:
    CIniSection  *pLanSec;
    bool         bLanLoadOK;
public:
    CIniLocalLan():pLanSec(NULL),bLanLoadOK(false)
    {
    }
	virtual ~CIniLocalLan()
    {
        if(pIniFile) {
            delete pIniFile;
            /* pIniFile = NULL; **/
        }
    }
    virtual bool SaveToolSetting(std::wstring strConfig);
    virtual bool LoadToolSetting(std::wstring strConfig) ;

    virtual std::wstring GetStr(std::wstring &key,std::wstring default);
    virtual std::wstring GetStr(std::wstring &key);
    virtual std::wstring GetStr(const wchar_t *key);

    virtual bool SetStr(std::wstring &key,std::wstring &value);
    virtual bool SetStr(const wchar_t *key,const wchar_t * value);


    std::wstring GetLanStr(std::wstring key);
    void    SetListViewString(HWND pWnd,TCHAR *strKey);
    void    GetListViewString(HWND pWnd,TCHAR *strKey);
public:
    bool    SetStringProc (void *pParam,void* lParam );
    bool    GetStringProc (void * pParam,void* lParam );
    bool    TreeControls(void * pParam,BOOL bSvae,int DlgId,bool bVer = false);
    void    TreeMenu(void * pParam,std::wstring strMainKeyPart);
};
/*
 * Encode a buffer into base64 format
 */
int base64_encode( unsigned char *dst, unsigned int *dlen,
                   const unsigned char *src, unsigned int slen );
/*
 * Decode a base64-formatted buffer
 */
int base64_decode( unsigned char *dst, unsigned int *dlen,
                   const unsigned char *src, unsigned int slen );
#endif