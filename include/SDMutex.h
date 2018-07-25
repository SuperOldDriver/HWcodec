//**************************************************************************
//* ��Ȩ����
//*
//* �ļ����ƣ�SDMutex
//* ����ժҪ����ƽ̨Mutex
//* ��ǰ�汾��V1.0
//*	��	  �ģ�		
//* ��    �ߣ�mediapro
//* ������ڣ�
//***************************************************************************/

#if !defined(SDMUTEX_H)
#define SDMUTEX_H

class CSDMutex  
{
public:
	CSDMutex(void *cs);
	virtual ~CSDMutex();

public:
	static void *CreateObject();
	static void RealseObject(void*m);
#ifdef ANDROID
	bool lock();
	bool Unlock();
#endif // ANDROID
private:
	void *m_cs;
};

class CSDMutexX
{
public:
	CSDMutexX();
	virtual ~CSDMutexX();
	
public:
	bool lock();
	bool Unlock();
	
private:
	void *m_cs;
};




#endif // !defined(SDMUTEX_H)
