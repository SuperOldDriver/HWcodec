//**************************************************************************
//* ��Ȩ����
//*
//* �ļ����ƣ�SDHW264DecoderInterface
//* ����ժҪ��H264Ӳ�����װ
//* ��ǰ�汾��V1.0
//*	��	  �ģ�		
//* ��    �ߣ�mediapro
//* ������ڣ�2018-7-19
//***************************************************************************/
#if !defined(H264_DEC_PACKAGE_H)
#define H264_DEC_PACKAGE_H

#include "SDCommon.h"
#include "SDLog.h"
#include "SDMutex.h"
#include "SDCodecCommon.h"
#include "SDHW264Decoder.h"

class CSDH264Dec
{
public:
	CSDH264Dec();
	virtual ~CSDH264Dec();

private:
	//����ӿ���
	void* m_pvDec;
	BOOL m_bDecClose;
	CH264_HW_Decoder* m_pH264Dec;
	
private:
	void mfCloseDecoder();
	
public:
	//����������	
	BOOL CreateDecoder(int nMaxWidth, int nMaxHeight, DecodeOutputImageType eOutputType);
	//�رս�����
	void CloseDecoder();

	//����һ֡
	int Decode(const void* pBitstreamData, int nBitstreamSize, void* pImageData, int* pnWidth, int* pnHeight);

};

#endif
