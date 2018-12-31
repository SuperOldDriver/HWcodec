//**************************************************************************
//* ��Ȩ����
//*
//* �ļ����ƣ�X264EncoderSdk
//* ����ժҪ��X264����DLL��װ������YUV420P
//* ��ǰ�汾��V1.0
//*	��	  �ģ�		
//* ��    �ߣ�mediapro
//* ������ڣ�2018-11-20
//***************************************************************************/
#ifndef _X264ENC_SDK_H_
#define _X264ENC_SDK_H_

#ifdef WIN32
#ifndef BUILDING_DLL
#define DLLIMPORT __declspec (dllexport)
#else /* Not BUILDING_DLL */
#define DLLIMPORT __declspec (dllimport)
#endif /* Not BUILDING_DLL */
#else
#define DLLIMPORT
#endif

#include "SDLog.h"
#include "SDX264Encoder.h"

extern "C"
{
//////////////////////////////////////////////////////////////////////////
// HWCodec�ӿ�

/***
* ����ѡ�ӿڡ�������ʼ����ϵͳֻ�����һ�Σ���������������־���
* @param logPath:��־�ļ����·�����ڲ��Զ������ļ���
* @param logLevel:��־�ļ��������ֻ�и��ڻ���ڸü������־�Ż���������ü������£�
*					LOG_LEVEL_DEBUG = 1;
*					LOG_LEVEL_INFO = 2;
*					LOG_LEVEL_WARN = 3;
*					LOG_LEVEL_ERROR = 4;
*					LOG_LEVEL_ALARM = 5;
*					LOG_LEVEL_FATAL = 6;
*					LOG_LEVEL_NONE = 7;
* ������ΪLOG_LEVEL_NONEʱ���ر���־����
* @return: 
*/
DLLIMPORT void  X264Enc_Enviroment_Init(const char* logPath, int logLevel);

DLLIMPORT void  X264Enc_Enviroment_Free();


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/***
* X264���������󴴽��ӿ�
* @return: ����ģ��ָ�룬ΪNULL��ʧ��
*/
DLLIMPORT void* X264Enc_Create();


/***
* X264������Open�ӿ�
* @param pX264Enc: ģ��ָ��
* @param nWidth: ����YUV420Pͼ����
* @param nHeight: ����YUV420Pͼ��߶�
* @param nFrameRate: ����֡�� fps
* @param nBitrate: �������� kbps�� ��������1000 ��ʾ1Mbps
* @param nKeyFrameInterval: ����IDR�������  ��
* @param nNaluSize: ���������ɵ���NALU�������ֽ���
* @param ptExternParams: �������ɹ����õĶ����������������Level��Profile��Preset���Ƿ�ʹ��VBV
* @return: true or false
*/
DLLIMPORT bool X264Enc_Open(void* pX264Enc, int nWidth, int nHeight, int nFrameRate, int nBitrate, 
							int nKeyFrameInterval, int nNaluSize, X264ExternParams *ptExternParams);


/***
* X264����Reset�ӿ�
* @param pX264Enc: ģ��ָ��
* @param nWidth: ����YUV420Pͼ����
* @param nHeight: ����YUV420Pͼ��߶�
* @param nFrameRate: ����֡�� fps
* @param nBitrate: �������� kbps
* @param nKeyFrameInterval: ����IDR�������  ��
* @param nNaluSize: ���������ɵ���NALU�������ֽ���
* @return: true or false
*/
DLLIMPORT bool X264Enc_Reset(void* pX264Enc, int nWidth, int nHeight, int nFrameRate, int nBitrate, 
							int nKeyFrameInterval, int nNaluSize);


/***
* X264������Close�ӿ�
* @param pX264Enc: ģ��ָ��
* @return: 
*/
DLLIMPORT void X264Enc_Close(void* pX264Enc);


/***
* X264�������������ٽӿ�
* @param pX264Enc: ģ��ָ��
* @return: 
*/
DLLIMPORT void X264Enc_Delete(void* pX264Enc);


/***
* X264����ӿ�
* @param pX264Enc: ģ��ָ��
* @param pucInputYuv[IN]: ����YUV420Pͼ������
* @param pucOutputStream[OUT]: ��������������򣬱��������ɴ���ʼ���һ֡������������
* @param pnNaluLen[OUT]: ����ű��������ɵ�NALU��Ϣ���������ڲ������ɵĸ���NALU������Ϣ������У����������NALUΪ���緢�͵�Ԫ���������н���
* @param unMaxNaluCnt[OUT]: һ֡�������֧�ֵ�NALU��Ŀ����pnNaluLen ����Ĵ�С��
* @param bForceIdr[IN]: �Ƿ�ǿ�Ƶ�ǰ֡ʹ��IDR���룬true��ǿ�Ʊ���ΪIDR
* @return: �ɹ�����>0��������󷵻�<0����ǰ֡���������������0������ֵ����0ʱ������ʾpucOutputStream�д�ŵ�һ֡ʵ����������
*/
DLLIMPORT int X264Enc_Encode(void* pX264Enc, BYTE *pucInputYuv, BYTE *pucOutputStream, int *pnNaluLen, UINT unMaxNaluCnt, bool bForceIdr);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


};

#endif // _X264ENC_SDK_H_
