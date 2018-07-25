//**************************************************************************
//* ��Ȩ����
//*
//* �ļ����ƣ�CNvi264_Encoder
//* ����ժҪ��Nvidia nvencӲ�����װ
//* ��ǰ�汾��V1.0
//*	��	  �ģ�		
//* ��    �ߣ�mediapro
//* ������ڣ�2018-4-12
//***************************************************************************/
#if !defined(NVI264_ENCODER_H)
#define NVI264_ENCODER_H

#include "SDCommon.h"
#include "SDCodecCommon.h"



//�����޸ģ���Ҫ��֤��X264 preset��Ӧ��ϵ
//static const char * const x264_preset_names[] = { "ultrafast", "superfast", "veryfast", "faster", "fast", "medium", "slow", "slower", "veryslow", "placebo", 0 };
static const char * const nvi264_preset_names[] = { "veryfast", "veryfast", "veryfast", "faster", "fast", "medium", "slow", "slower", "veryslow", "veryslow", 0 };

#define NVI264_BASELINE_PROFILE					   0
#define NVI264_HIGH_PROFILE						   1  	


//�û�ָ��Profile �� Level�Ȳ���
typedef struct Nvi264ExternParams
{
	int nLevel;
	int nProfile;
	int bEnableVbv;
	char acPreset[64];
}Nvi264ExternParams;


class CNvi264_Encoder 
{
public:
	CNvi264_Encoder();
	virtual ~CNvi264_Encoder();

	bool	Open(int nWidth, int nHeight, int nFrameRate, int nBitrate, int nKeyFrameInterval, Nvi264ExternParams *pExternParams);
	void	Close();
	int		Encode(AVFrame* ptEncFrame, BYTE* pucBitstreamData, int nMaxSupportLen, int64_t* pPts, int64_t* pDts);
	bool	Control(int nFrameRate, int bitrate, int nIdrInterval, int nWidth, int nHeight);

	//��ȡӲ������������ĸ�ʽ��һ��ΪAV_PIX_FMT_NV12���������Open����ñ�API��õ�ǰ������֧�ֵ������ʽ
	//���һ�������Ŵ����õ�����ʽ�����ͱ���
	bool	GetInputFormat(int *pnFormat, int *pnWidth, int *pnHeight);	
	//Ԥ�е�ǰƽ̨�Ƿ�֧�ָ�Ӳ���룬��ʵ֧�������Open��������Ϊ׼
	static bool IsHwAcclSupported(void);

	//���󼴿̱���IDR֡
	bool	IdrRequest();
	//���󼴿̱���IDR֡�������³�ʼ��ʱ���
	void	ReInit();

private:
	bool				m_bClosed;
	void*				m_pClosedCs;

	AVCodecContext*		m_ptEncContext;

	//��HPʱ��ֹDTS���ָ����������PTS��ֵ
	int64_t				m_nPtsBaseNum;
	int64_t				m_nPtsStartTime;

	int					m_nKeyFrameIntervalTime;
	int					m_nReqFormat;
	int					m_nReqWidth;
	int					m_nReqHeight;

	//��һ�α���IDR֡��ʱ�䣬���ڱ�������ʵ������֡Ƶ�������õ�֡�ʣ������³�ʱ�䣨����ָ�������I֡�������IDR֡�����
	long				m_nPrevIdrTime;

	Nvi264ExternParams	m_tExternParams;
	//�����NALU�Ƿ������ʼ��(0x000001 0x00000001)
	bool				m_bUseNaluStartCode;
	//�Ƿ�ʹ��90KHZʱ���������ʹ��ʵ�ʻ���ʱ�䣩
	bool				m_bUse90KTimeStamp;
	//ʹ�õ����ʿ����㷨
	int					m_nRateControlMethod;
	//�������IDR��־
	bool				m_bRequestIdr;

private:
	bool mfOpen(int nWidth, int nHeight, int nFrameRate, int bitrate, int nKeyFrameInterval, Nvi264ExternParams *pExternParams);
	void mfClose();
	int64_t mfGeneratePts();	
};


#endif // !defined(NVI264_ENCODER_H)
