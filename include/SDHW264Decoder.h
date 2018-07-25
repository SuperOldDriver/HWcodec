//**************************************************************************
//* ��Ȩ����
//*
//* �ļ����ƣ�SDHW264Decoder
//* ����ժҪ��ʹ��DXVA2�ӿڵ�Ӳ�����װ
//* ��ǰ�汾��V1.0
//*	��	  �ģ�		
//* ��    �ߣ�mediapro
//* ������ڣ�2018-7-19
//***************************************************************************/

#if !defined(H264_HW_DECODER_H)
#define H264_HW_DECODER_H

#include "SDCommon.h"
#include "SDCodecCommon.h"

class CH264_HW_Decoder
{
public:
	CH264_HW_Decoder();
	virtual ~CH264_HW_Decoder();

	//�жϵ�ǰ�����Ƿ�֧��Ӳ����
	static bool IsHwAcclSupported(void);
	bool Open(int nMaxWidth, int nMaxHeight, DecodeOutputImageType eOutputType);
	void Close();
	int Decode(const void* data, unsigned int size, void* pRetBuf, int* pnWidth = NULL, int* pnHeight = NULL);


private:
    AVCodec*               m_codec;
    AVCodecContext*        m_ctx;
	AVFrame*               m_picture;
	AVCodecParserContext * m_h264Parser;

	enum AVPixelFormat	   m_hwPixFmt;
	AVBufferRef*		   m_hwDeviceCtx;
	
	DecodeOutputImageType  m_eOutputType;	
	int*				   m_pnInputBuff;	 
	int mf_hw_decode_dec(const BYTE* in_buf, int in_buf_size, BYTE *out_buf, int* pnWidth, int* pnHeight);
	int mf_hw_decode_init(AVCodecContext *ctx, const enum AVHWDeviceType type);
	int avcodec_decode_video_hw(AVCodecContext *avctx, AVFrame *sw_frame, int *got_picture_ptr, const AVPacket *packet);
};



#endif // !defined(X264_DECODER_H)
