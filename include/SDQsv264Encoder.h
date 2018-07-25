//**************************************************************************
//* ��Ȩ����
//*
//* �ļ����ƣ�CQsv264_Encoder
//* ����ժҪ��Intel QsvӲ�����װ
//* ��ǰ�汾��V1.0
//*	��	  �ģ�		
//* ��    �ߣ�mediapro
//* ������ڣ�2018-4-12
//***************************************************************************/

#if !defined(QSV264_ENCODER_H)
#define QSV264_ENCODER_H

#include "SDCommon.h"
#include "SDCodecCommon.h"


//�����޸ģ���Ҫ��֤��X264 preset��Ӧ��ϵ
//static const char * const x264_preset_names[] = { "ultrafast", "superfast", "veryfast", "faster", "fast", "medium", "slow", "slower", "veryslow", "placebo", 0 };
static const char * const qsv264_preset_names[] = { "veryfast", "veryfast", "veryfast", "faster", "fast", "medium", "slow", "slower", "veryslow", "veryslow", 0 };

#define QSV264_BASELINE_PROFILE					   0
#define QSV264_HIGH_PROFILE						   1  	


//�û�ָ��Profile �� Level�Ȳ���
typedef struct Qsv264ExternParams
{
	int nLevel;
	int nProfile;
	int bEnableVbv;
	char acPreset[64];
}Qsv264ExternParams;


class CQsv264_Encoder 
{
public:
	CQsv264_Encoder();
	virtual ~CQsv264_Encoder();

	bool	Open(int nWidth, int nHeight, int nFrameRate, int nBitrate, int nKeyFrameInterval, Qsv264ExternParams *pExternParams);
	void	Close();
	int		Encode(AVFrame* ptEncFrame, BYTE* pucBitstreamData, int nBitstreamMaxLen, int64_t* pPts, int64_t* pDts);
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

	Qsv264ExternParams	m_tExternParams;
	//�������IDR��־
	bool				m_bRequestIdr;

private:
	bool mfOpen(int nWidth, int nHeight, int nFrameRate, int bitrate, int nKeyFrameInterval, Qsv264ExternParams *pExternParams);
	void mfClose();
	int64_t mfGeneratePts();	
};


#endif // !defined(QSV264_ENCODER_H)
