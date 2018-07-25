//**************************************************************************
//* ��Ȩ����
//*
//* �ļ����ƣ�SDNviEncoderInterface
//* ����ժҪ��Nvidia nvencӲ�����װ
//* ��ǰ�汾��V1.0
//*	��	  �ģ�		
//* ��    �ߣ�mediapro
//* ������ڣ�2018-4-12
//***************************************************************************/
#if !defined(NVI_ENC_PACKAGE_H)
#define NVI_ENC_PACKAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDCommon.h"
#include "SDLog.h"
#include "SDMutex.h"
#include "SDNvi264Encoder.h"
#include "SDCodecCommon.h"
#include "SDBmpZoom.h"


class CSDNviEnc
{
public:
	CSDNviEnc();
	virtual ~CSDNviEnc();

private:
	//����ӿ���
	void* m_pvEnc;
	BOOL m_bEncClose;

	CNvi264_Encoder* m_pNvi264Enc;
	CSDBmpZoom m_BmpZoom;
	AVFrame* m_ptAVFrameEncode;
	AVPixelFormat m_tEncFormat;
	BYTE* m_pucBuffEncode;

	UINT m_unInputWidth;
	UINT m_unInputHeight;
	UINT m_unEncWidth;
	UINT m_unEncHeight;

private:
	void mfGetPresetString(video_enc_preset ePreset, char* strPreset);
	void mfCloseEncoder();

public:
	//����������	
	BOOL CreateEncoder(h264_input_params* pInputParams, h264_enc_params* pEncParams);
	//�رձ�����
	void CloseEncoder();

	//����һ֡
	int Encode(const char* pImageData, char* pBitstreamData, int nMaxSupportLen);

};

#endif