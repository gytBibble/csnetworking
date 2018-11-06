//#define TCP
#include<iostream>
#include<WinSock2.h>
#include<list>
#include<string>
#include<string.h>
#include<algorithm>

#define MAXCONN 5
#define BUFLEN 255

typedef list<SOCKET> ListCONN;
typedef list<SOCKET> ListConErr;

using namespace std;

void main(int argc, char const *argv[])
{
	WSADATA wsaData;
	int nRC;
	sockaddr_in srvAddr, clientAddr;
	SOCKET srvSock;
	int nAddrLen = sizeof(sockaddr);
	char sendBuf[BUFLEN], recvBuf[BUFLEN];
	ListCONN conList;		//����������Ч�ĻỰSOCKET
	//ListCONN::iterator itor;
	ListConErr conErrList;	//��������ʧЧ�ĻỰSOCKET
	//ListConErr::iterator itor1;
	FD_SET rfds, wfds;
	u_long uNonBlock;

	//WSAStarup()��ʼ��Winsock
	nRC = WSAStartup(0x0101, &wsaData);
	if (nRC)
	{
		//Winsock��ʼ������
		cout << "Server's Winsock Initialize Error!\n";
		return;
	}
	if (wsaData.wVersion != 0x1010)
	{
		//�汾֧�ֲ���
		//���������û������Winsock������
		cout << "Server's Winsock Version Error!\n";
		WSACleanup();
		return;
	}
	cout<< "Server's Winsock Initialized!\n";


	//socket��������һ������SOCKET���ж���TCP����UDP
//#ifdef TCP
	//������socket
	srvSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//#endif // TCP
//#ifndef TCP
	//�������ݱ�socket
//	srvSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
//#endif // !TCP
	if (srvSock == INVALID_SOCKET)
	{
		//����ʧ��
		cout << "Socket Create Error!\n";
		WSACleanup();
		return;
	}
	//�����ɹ�
//#ifdef TCP
	cout << "TCP Socket Create Ok\n";
//#endif // TCP
//#ifndef TCP
//	cout << "UDP Socket Create Ok\n";
//#endif // !TCP

	//bind��������SOCKET
	cout << "Please input your IP address:";
	string ipaddr;
	cin >> ipaddr;
	char *IpAddr = (char *)malloc((ipaddr.length() + 1) * sizeof(char));
	ipaddr.copy(IpAddr,ipaddr.length(),0);
	IpAddr[ipaddr.length()] = '\0';
	srvAddr.sin_family = AF_INET;
	cout << "Please input your port:";
	int port = 80;
	cin >> port;
	srvAddr.sin_port = htons(port);
	//srvAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	srvAddr.sin_addr.S_un.S_addr = inet_addr(IpAddr);
	nRC = bind(srvSock, (LPSOCKADDR)&srvAddr, sizeof(srvAddr));
	if (nRC == SOCKET_ERROR)
	{
		//��ʧ��
		cout << "Server Socket Bind Error!\n";
		closesocket(srvSock);
		WSACleanup();
		return;
	}
	//�󶨳ɹ�
	cout << "Server Socket Bind Ok!\n";


	//listen�������õȴ�����״̬
	nRC = listen(srvSock, MAXCONN);
	if (nRC == SOCKET_ERROR)
	{
		//����ʧ��
		cout << "Server Socket Listen Error!\n";
		closesocket(srvSock);
		WSACleanup();
		return;
	}
	//���ӳɹ�
	cout << "Server Socket Listen Ok!\n";


	//accept�������Ӳ����ɻỰSOCKET
	int nSockErr;
	int nNumConns = 0;	//��ǰ����������
	SOCKET sConns[MAXCONN];	//�ỰSOCKET����
	sockaddr ConnAddrs[MAXCONN];//�������ӵĿͻ��˵�ַ
	int nAddrLen;
	//����send������recv�������лỰ
	//����closesocket�����ر�SOCKET
}