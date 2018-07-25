//**************************************************************************
//* ��Ȩ����
//*
//* �ļ����ƣ�SDEvent
//* ����ժҪ����ƽ̨Event
//* ��ǰ�汾��V1.0
//*	��	  �ģ�		
//* ��    �ߣ�mediapro
//* ������ڣ�
//***************************************************************************/

#if !defined(SDEVENT_H)
#define SDEVENT_H

#ifndef WIN32
#include <pthread.h>
#endif

class CSDEvent
{
public:
	CSDEvent(const char *strName = NULL);
	virtual ~CSDEvent();

public:
	BOOL CreateSdEvent();
	void ReleaseSdEvent();

public:
	BOOL wait();
	BOOL waittime(int dwMilliseconds);
	BOOL post();
	void Reset();
private:
	void  *m_pEvent;
	char  m_strEventName[64];
#ifndef WIN32
	pthread_mutex_t m_event_mutex;
	pthread_cond_t m_event_cond;
	bool m_event_status;
#endif
};

#endif // !defined(SDEVENT_H)
