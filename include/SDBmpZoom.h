//**************************************************************************
//* ��Ȩ����
//*
//* �ļ����ƣ�SDBmpZoom
//* ����ժҪ��FFMPEG�������ź�ɫ�ȿռ�ת��
//* ��ǰ�汾��V1.0
//*	��	  �ģ�		
//* ��    �ߣ�mediapro
//* ������ڣ�
//***************************************************************************/

#if !defined(SDBMPZOOM_H)
#define SDBMPZOOM_H

#include <stdio.h>
#include <stdlib.h>

extern "C"{
#ifdef WIN32
#include "ffmpeg/libavcodec/avcodec.h"
#include "ffmpeg/libswscale/swscale.h"
#include "ffmpeg/libavutil/frame.h"
#include "ffmpeg/libavutil/imgutils.h"
#else
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
#include "libavutil/frame.h"
#endif
}
 

//ʹ��swscale����ͼ������
//ע�⣺��ģ��ӿڵĻ�������㸺��
class CSDBmpZoom  
{
public:	 
	CSDBmpZoom();
	virtual ~CSDBmpZoom();

	bool CreateBmpZoom(int nSrcWidth, int nSrcHeight, int nDesWidth, int nDesHeight,
		AVPixelFormat eSrcPixFmt, AVPixelFormat eDstPixFmt, bool bHighQuality);

	bool BmpZoom(int nSrcWidth, int nSrcHeight, BYTE *pSrcImgbuf, 
		int nDesWidth, int nDesHeight, BYTE *pDesImgbuf);

	bool BmpZoom(AVFrame *pAVFrameSrc, int nDesWidth, int nDesHeight, BYTE* pDesImgbuf);

	void CloseBmpZoom();

private:
	struct SwsContext *m_ptImgConvertCtx;

	AVFrame *m_ptAVFrameSrc;
	AVPixelFormat m_eSrcPixFmt;

	AVFrame *m_ptAVFrameDes;
	AVPixelFormat m_eDstPixFmt;

	bool m_bCreated;
};

#endif // !defined(SDBMPZOOM_H)
