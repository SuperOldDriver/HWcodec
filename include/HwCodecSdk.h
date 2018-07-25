//**************************************************************************
//* ��Ȩ����
//*
//* �ļ����ƣ�HwCodecSdk
//* ����ժҪ��Windowsƽ̨Intel QSV\Ӣΰ��NVI H264 H265Ӳ�����DLL��װ
//* ��ǰ�汾��V1.0
//*	��	  �ģ�		
//* ��    �ߣ�mediapro
//* ������ڣ�2018-6-20
//***************************************************************************/
#ifndef _HW_CODEC_SDK_H_
#define _HW_CODEC_SDK_H_

#ifndef BUILDING_DLL
#define DLLIMPORT __declspec (dllexport)
#else /* Not BUILDING_DLL */
#define DLLIMPORT __declspec (dllimport)
#endif /* Not BUILDING_DLL */

#include "SDLog.h"
#include "SDCodecCommon.h"
#include "SDNviEncoderInterface.h"
#include "SDQsvEncoderInterface.h"
#include "SDHW264DecoderInterface.h"

extern "C"
{
//////////////////////////////////////////////////////////////////////////
// HWCodec�ӿ�

/***
* ������ʼ����ϵͳֻ�����һ��
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
DLLIMPORT void  HwCodec_Enviroment_Init(const char* logPath, int logLevel);

DLLIMPORT void  HwCodec_Enviroment_Free();

/***
* �жϵ�ǰƽ̨�Ƿ�֧��Intel QSV H264Ӳ����
* @param��
* @return: ֧��true, ��֧��false һ������Ԥ���ж��Ծ���Create������
*/
DLLIMPORT bool  HwCodec_Is_QsvH264Enc_Support();


/***
* �жϵ�ǰƽ̨�Ƿ�֧��Ӣΰ�� NVI H264Ӳ����
* @param��
* @return: ֧��true, ��֧��false һ������Ԥ���ж��Ծ���Create������
*/
DLLIMPORT bool  HwCodec_Is_NviH264Enc_Support();

/***
* �жϵ�ǰƽ̨�Ƿ�֧��H264Ӳ����
* @param��
* @return: ֧��true, ��֧��false һ������Ԥ���ж��Ծ���Create������
*/
DLLIMPORT bool  HwCodec_Is_HwH264Dec_Support();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/***
* ����QSV H264Ӳ����
* @param pInputParams: ����ͼ���ʽ����������������ͼ��Ŀ�ߡ�ɫ�ȿռ�
* @param pEncParams: �������ɹ����õĲ������������Ŀ�ߡ����ʡ�Level��Profile��
*					��ģ���ڲ��Դ�ɫ�ȿռ�ת�������Ź��ܣ���������㱣֤�����߼�������
* @return: ����ģ��ָ�룬ΪNULL��ʧ��
*/
DLLIMPORT void* QsvH264Enc_Create(h264_input_params* pInputParams, h264_enc_params* pEncParams);


/***
* ����QSVӲ����
* @param pQsvEnc: ģ��ָ��
* @return: 
*/
DLLIMPORT void  QsvH264Enc_Delete(void* pQsvEnc);


/***
* QSV����һ֡
* @param pQsvEnc: ģ��ָ��
* @param pImageData: ����ͼ������
* @param pBitstreamData: ���������������
* @param nMaxSupportLen: ���������������Ĵ�С
* @return: �ɹ�����>0������<=0������ֵ����0ʱ������ʾpBitstreamData�д�ŵ�һ֡ʵ����������
*/
DLLIMPORT int  QsvH264Enc_Encode(void* pQsvEnc, const char* pImageData, char* pBitstreamData, int nMaxSupportLen);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/***
* ����NVI H264Ӳ����
* @param pInputParams: ����ͼ���ʽ����������������ͼ��Ŀ�ߡ�ɫ�ȿռ�
* @param pEncParams: �������ɹ����õĲ������������Ŀ�ߡ����ʡ�Level��Profile��
*					��ģ���ڲ��Դ�ɫ�ȿռ�ת�������Ź��ܣ���������㱣֤�����߼�������
* @return: ����ģ��ָ�룬ΪNULL��ʧ��
*/
DLLIMPORT void* NviH264Enc_Create(h264_input_params* pInputParams, h264_enc_params* pEncParams);


/***
* ����NVIӲ����
* @param pNviEnc: ģ��ָ��
* @return: 
*/
DLLIMPORT void  NviH264Enc_Delete(void* pNviEnc);


/***
* NVI����һ֡
* @param pNviEnc: ģ��ָ��
* @param pImageData: ����ͼ������
* @param pBitstreamData: ���������������
* @param nMaxSupportLen: ���������������Ĵ�С
* @return: �ɹ�����>0������<=0������ֵ����0ʱ������ʾpBitstreamData�д�ŵ�һ֡ʵ����������
*/
DLLIMPORT int  NviH264Enc_Encode(void* pNviEnc, const char* pImageData, char* pBitstreamData, int nMaxSupportLen);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/***
* ����H264Ӳ����
* @param nMaxWidth: ������֧�ֵ������
* @param nMaxHeight: ������֧�ֵ����߶�
* @param eOutputType: �������������Ƶ��ʽ
* @return: ����ģ��ָ�룬ΪNULL��ʧ��
*/
DLLIMPORT void* HwH264Dec_Create(int nMaxWidth, int nMaxHeight, DecodeOutputImageType eOutputType);


/***
* ����H264Ӳ����
* @param pHwDec: ģ��ָ��
* @return: 
*/
DLLIMPORT void  HwH264Dec_Delete(void* pHwDec);


/***
* ����һ֡
* @param pHwDec: ģ��ָ��
* @param pBitstreamData: ����һ֡�������ݣ���Ҫ������ʼ��
* @param nBitstreamSize: ���������ĳ���
* @param pImageData: �����ͼ�������
* @param pnWidth: ���ͼ��Ŀ��
* @param pnHeight: ���ͼ��ĸ߶�
* @return: �ɹ�����>0������<=0������ֵ����0ʱ������ʾpImageData�д�ŵ�һ֡ʵ��ͼ���ֽ���
*/
DLLIMPORT int  HwH264Dec_Decode(void* pHwDec, const void* pBitstreamData, int nBitstreamSize, void* pImageData, int* pnWidth, int* pnHeight);


};

#endif // _HW_CODEC_SDK_H_
