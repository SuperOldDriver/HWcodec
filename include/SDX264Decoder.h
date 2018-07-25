//**************************************************************************
//* ��Ȩ����
//*
//* �ļ����ƣ�SDX264Decoder
//* ����ժҪ��ʹ��ffmpeg�ӿڵ���H264�����װ������㸺��ӿ�������
//* ��ǰ�汾��V1.0
//*	��	  �ģ�		
//* ��    �ߣ�mediapro
//* ������ڣ�
//***************************************************************************/

#if !defined(X264_DECODER_H)
#define X264_DECODER_H

#include <stdio.h>
#include <stdlib.h>
#include "SDCodecCommon.h"
#include <string>
#include "memory.h"
#include "time.h"
#ifdef _WIN32
#include <conio.h>
#endif

#define snprintf _snprintf 


class CX264_Decoder
{
public:
	CX264_Decoder();
	virtual ~CX264_Decoder();

	bool Open(int nWidth, int nHeight, DecodeOutputImageType eOutputType);
	void Close();
	int Decode(void* data, unsigned int size, void* pRetBuf, int* pnWidth = NULL, int* pnHeight = NULL);

private:
    AVCodec*               m_codec;
    AVCodecContext*        m_ctx;
	AVFrame*               m_picture;
	AVCodecParserContext * m_h264Parser;

	DecodeOutputImageType  m_eOutputType;	
	int*				   m_piInputBuff;	 
	int x264_dec(const BYTE* in_buf, int in_buf_size, BYTE *out_buf, int* pnWidth, int* pnHeight);
};



#endif // !defined(X264_DECODER_H)
