#ifndef _H264_CODEC_COMMON_H_
#define _H264_CODEC_COMMON_H_

extern "C"{
#include "ffmpeg/libavformat/avformat.h"
#include "ffmpeg/libavcodec/avcodec.h"
#include "ffmpeg/libavcodec/qsv.h"
#include "ffmpeg/libavutil/imgutils.h"
#include "ffmpeg/libavutil/opt.h"
#include "ffmpeg/libavutil/hwcontext.h"
#include "ffmpeg/libswscale/swscale.h"
}

//������������ݸ�ʽ
typedef enum video_input_format
{
	VIDEO_INPUT_YUV420P = 0,   ///< planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)
	VIDEO_INPUT_YUYV422,   ///< packed YUV 4:2:2, 16bpp, Y0 Cb Y1 Cr
	VIDEO_INPUT_RGB24,     ///< packed RGB 8:8:8, 24bpp, RGBRGB...
	VIDEO_INPUT_BGR24,     ///< packed RGB 8:8:8, 24bpp, BGRBGR...
	VIDEO_INPUT_YUV422P,   ///< planar YUV 4:2:2, 16bpp, (1 Cr & Cb sample per 2x1 Y samples)
	VIDEO_INPUT_YUV444P,   ///< planar YUV 4:4:4, 24bpp, (1 Cr & Cb sample per 1x1 Y samples)
	VIDEO_INPUT_NV12,      ///< planar YUV 4:2:0, 12bpp, 1 plane for Y and 1 plane for the UV components, which are interleaved (first byte U and the following byte V)
	VIDEO_INPUT_NV21,      ///< as above, but U and V bytes are swapped
	VIDEO_INPUT_ARGB,      ///< packed ARGB 8:8:8:8, 32bpp, ARGBARGB...
	VIDEO_INPUT_RGBA,      ///< packed RGBA 8:8:8:8, 32bpp, RGBARGBA...
	VIDEO_INPUT_ABGR,      ///< packed ABGR 8:8:8:8, 32bpp, ABGRABGR...
	VIDEO_INPUT_BGRA,      ///< packed BGRA 8:8:8:8, 32bpp, BGRABGRA...

}video_input_format;

//������preset
typedef enum video_enc_preset
{
	VIDEO_ENC_VERY_FAST = 0,   
	VIDEO_ENC_FASTER,
	VIDEO_ENC_FAST,
	VIDEO_ENC_MEDIUM,
	VIDEO_ENC_SLOW,
	VIDEO_ENC_SLOWER,
	VIDEO_ENC_VERY_SLOW,
}video_enc_preset;

//����������
typedef struct h264_enc_params
{
	//����Level������40����ʾLevel4.0
	UINT unLevel;
	//�����Profile��0-Baseline  1-HighProfile
	UINT unProfile;
	//�����ߺ�֡��
	UINT unEncWidth;
	UINT unEncHeight;
	UINT unFramerate;
	//�������ʣ���λkbps
	UINT unBitrateKbps;
	//IDR֡�������λ��
	UINT unGopSeconds;
	//�Ƿ�����VBV
	BOOL bEnableVbv;
	//�����Preset
	video_enc_preset ePreset;
}h264_enc_params;

//����������ͼ�����
typedef struct h264_input_params
{
	video_input_format eInputFormat;
	UINT unInputWidth;
	UINT unInputHeight;
}h264_input_params;


//�������������
enum DecodeOutputImageType{

	DEC_OUTPUT_RGBA = 0,
	DEC_OUTPUT_BGRA,
	DEC_OUTPUT_RGB,
	DEC_OUTPUT_BGR,
	DEC_OUTPUT_YUV420
};

//ffmpeg�ĳ�ʼ����ϵͳ�е���һ�μ���
void ffmpeg_global_init();
void ffmpeg_global_uninit();

AVPixelFormat GetInputFormat(video_input_format eVideoInputFormat);

//��һ֡�����в���Ҫ��NALU���ˣ�ֻ����������NALU���������紫��ʱ��ʡ����
//���˵�NALU������NAL_SEI��NAL_AUD��NAL_FILLER_DATA
bool AVCFilterNalUnits(const char *bufIn, int inSize, char* bufOut, int* outSize);

//����SPS NALU�����н���
bool AVCParseSpsNal(unsigned char * buf,unsigned int nLen,int &Width,int &Height);

//����һ֡���������а���SPS����н�����ͼ���ߣ���������SPS�����ʧ��
bool AVCGetWidthHeightFromFrame(const char* frameBuf, int bufLen, int& width, int& height);

#endif // _H264_CODEC_COMMON_H_
