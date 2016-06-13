#ifndef __GAMESCOKET_H__
#define __GAMESCOKET_H__

#ifdef WIN32 
#include <WinSock2.h> 
#else 
#include <sys/socket.h> 
#include <fcntl.h> 
#include <errno.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 

#define SOCKET int 
#define SOCKET_ERROR -1 
#define INVALID_SOCKET -1 

#endif 


#define _MAX_MSGSIZE (65536)     // �ݶ�һ����Ϣ���Ϊ16k 

#ifndef CHECKF 
#define CHECKF(x)
//
//#define CHECKF(x) \ 
//do \ 
//{ \ 
//if (!(x)) { \ 
//	log_msg("CHECKF", #x, __FILE__, __LINE__); \ 
//	return 0; \ 
//} \ 
//} while (0) 

#endif 


#define BLOCKSECONDS    12          // INIT��������ʱ�� 
#define INBUFSIZE   (65536)       //? ����ߴ�������汨�����  �������ݵĻ��� 
#define OUTBUFSIZE  (4096)        //? ����ߴ�������汨������� �������ݵĻ��棬��������8Kʱ��FLUSHֻ��ҪSENDһ�� 

class CGameSocket { 
public: 
	CGameSocket(void);
	~CGameSocket();
	bool    Create(const char* pszServerIP, int nServerPort, int nBlockSec, bool bKeepAlive); 
	bool    SendMsg(const void* pBuf, int nSize); 
	bool    ReceiveMsg(void* pBuf, int& nSize); 
	bool    Flush(void); 
	bool    Check(void); 
	void    Destroy(void); 
	SOCKET  GetSocket(void) const { return m_sockClient; } 
	void clear() ;
private: 
	bool    recvFromSock(void);     // �������ж�ȡ�����ܶ������ 
	bool    hasError();         // �Ƿ�������ע�⣬�첽ģʽδ��ɷǴ��� 
	void    closeSocket(); 

	SOCKET  m_sockClient; 

	// �������ݻ��� 
	char    m_bufOutput[OUTBUFSIZE];    //? ���Ż�Ϊָ������ 
	int     m_nOutbufLen; 

	// ���λ����� 
	// char    m_bufInput[INBUFSIZE]; 
	char    *m_bufInput;
	int     m_nInbufLen; 
	int     m_nInbufStart;              // INBUFʹ��ѭ��ʽ���У��ñ���Ϊ������㣬0 - (SIZE-1) 
}; 


#endif