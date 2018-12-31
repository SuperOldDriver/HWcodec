//**************************************************************************
//* ��Ȩ����
//*
//* �ļ����ƣ�X264EncoderSdk
//* ����ժҪ��X264����DLL��װ
//* ��ǰ�汾��V1.0
//*	��	  �ģ�		
//* ��    �ߣ�mediapro
//* ������ڣ�2018-11-20
//***************************************************************************/
#include "X264EncoderSdk.h"

#define H264_CODEC_SDK_VERSION	20180112001


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������ʼ����ϵͳֻ�����һ��
void  X264Enc_Enviroment_Init(const char* logPath, int logLevel)
{
	SDLOG_INIT(logPath, logLevel);
}

//��������ʼ��
void  X264Enc_Enviroment_Free()
{
	SDLOG_CLOSE();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// X264���������󴴽��ӿ�
void* X264Enc_Create()
{
    CX264_Encoder* x264_encoder = new CX264_Encoder();

    return x264_encoder;
}

// X264������Open�ӿ�
bool X264Enc_Open(void* pX264Enc, int nWidth, int nHeight, int nFrameRate, int nBitrate, int nKeyFrameInterval, int nNaluSize, X264ExternParams *ptExternParams)
{
	if ((ptExternParams == NULL) || (pX264Enc == NULL))
	{
		SDLOG_PRINTF("X264", SD_LOG_LEVEL_ERROR, "X264Enc_Open Failed, params null:%p %p!", pX264Enc, ptExternParams);
		return NULL;
	}

    CX264_Encoder* x264_encoder = (CX264_Encoder*)pX264Enc;

	bool bRet = x264_encoder->Open(nWidth, nHeight, nFrameRate, nBitrate, nKeyFrameInterval, nNaluSize, ptExternParams);
	if (bRet == false)
	{
		SDLOG_PRINTF("X264", SD_LOG_LEVEL_ERROR, "X264Enc_Open failed (Ver:%d) Enc:%dx%d  framerate:%d  bitrate:%d!!",
					H264_CODEC_SDK_VERSION, nWidth, nHeight, nFrameRate, nBitrate);
	}
	else
	{	
		SDLOG_PRINTF("X264", SD_LOG_LEVEL_INFO, "X264Enc_Open success (Ver:%d) Enc:%dx%d  framerate:%d  bitrate:%d!!", 
					H264_CODEC_SDK_VERSION, nWidth, nHeight, nFrameRate, nBitrate);
	}

    return bRet;
}

// X264������Close�ӿ�
void X264Enc_Close(void* pX264Enc)
{
    CX264_Encoder* x264_encoder = (CX264_Encoder*)pX264Enc;
     if (x264_encoder)
     {
		 x264_encoder->Close();
     }
}

// X264�������������ٽӿ�
void X264Enc_Delete(void* pX264Enc)
{
    CX264_Encoder* x264_encoder = (CX264_Encoder*)pX264Enc;
     if (x264_encoder)
     {
		 x264_encoder->Close();
         delete x264_encoder;
     }
}

// X264����ӿ�
int X264Enc_Encode(void* pX264Enc, BYTE *pucInputYuv, BYTE *pucOutputStream, int *pnNaluLen, UINT unMaxNaluCnt, bool bForceIdr)
{
	CX264_Encoder* x264_encoder = (CX264_Encoder*)pX264Enc;
	if (x264_encoder && pucInputYuv && pucOutputStream && pnNaluLen)
	{
		return x264_encoder->Encode(pucInputYuv, pucOutputStream, pnNaluLen, unMaxNaluCnt, bForceIdr);
	}
	else
	{
		SDLOG_PRINTF("X264", SD_LOG_LEVEL_ERROR, "X264Enc_Encode Failed!. pX264Enc:%p  pucInputYuv:%p pucOutputStream:%p pnNaluLen:%p", 
					pX264Enc, pucInputYuv, pucOutputStream, pnNaluLen);
		return 0;
	}
}

// X264����Reset�ӿ�
bool X264Enc_Reset(void* pX264Enc, int nWidth, int nHeight, int nFrameRate, int nBitrate, int nKeyFrameInterval, int nNaluSize)
{
    CX264_Encoder* x264_encoder = (CX264_Encoder*)pX264Enc;
    if (x264_encoder)
    {
		bool bRet = x264_encoder->Control(nWidth, nHeight, nFrameRate, nBitrate, nKeyFrameInterval, nNaluSize);
		if (bRet == false)
		{
			SDLOG_PRINTF("X264", SD_LOG_LEVEL_ERROR, "X264Enc_Reset Failed with param: %d %d %d %d %d %d!!",
						nWidth, nHeight, nFrameRate, nBitrate, nKeyFrameInterval, nNaluSize);
		}
		return bRet;
    }
	else
	{
		SDLOG_PRINTF("X264", SD_LOG_LEVEL_ERROR, "X264Enc_Reset Failed, params null:%p!", pX264Enc);
		return false;
	}		
}
