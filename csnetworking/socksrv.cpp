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
	ListCONN conList;		//保存所有有效的会话SOCKET
	//ListCONN::iterator itor;
	ListConErr conErrList;	//保存所有失效的会话SOCKET
	//ListConErr::iterator itor1;
	FD_SET rfds, wfds;
	u_long uNonBlock;

	//WSAStarup()初始化Winsock
	nRC = WSAStartup(0x0101, &wsaData);
	if (nRC)
	{
		//Winsock初始化错误
		cout << "Server's Winsock Initialize Error!\n";
		return;
	}
	if (wsaData.wVersion != 0x1010)
	{
		//版本支持不够
		//报告错误给用户，清除Winsock，返回
		cout << "Server's Winsock Version Error!\n";
		WSACleanup();
		return;
	}
	cout<< "Server's Winsock Initialized!\n";


	//socket（）创建一个监听SOCKET，判断是TCP还是UDP
//#ifdef TCP
	//创建流socket
	srvSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//#endif // TCP
//#ifndef TCP
	//创建数据报socket
//	srvSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
//#endif // !TCP
	if (srvSock == INVALID_SOCKET)
	{
		//创建失败
		cout << "Socket Create Error!\n";
		WSACleanup();
		return;
	}
	//创建成功
//#ifdef TCP
	cout << "TCP Socket Create Ok\n";
//#endif // TCP
//#ifndef TCP
//	cout << "UDP Socket Create Ok\n";
//#endif // !TCP

	//bind（）监听SOCKET
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
		//绑定失败
		cout << "Server Socket Bind Error!\n";
		closesocket(srvSock);
		WSACleanup();
		return;
	}
	//绑定成功
	cout << "Server Socket Bind Ok!\n";


	//listen（）设置等待连接状态
	nRC = listen(srvSock, MAXCONN);
	if (nRC == SOCKET_ERROR)
	{
		//连接失败
		cout << "Server Socket Listen Error!\n";
		closesocket(srvSock);
		WSACleanup();
		return;
	}
	//连接成功
	cout << "Server Socket Listen Ok!\n";


	//accept（）连接并生成会话SOCKET
	int nSockErr;
	int nNumConns = 0;	//当前请求连接数
	SOCKET sConns[MAXCONN];	//会话SOCKET数组
	sockaddr ConnAddrs[MAXCONN];//请求连接的客户端地址
	int nAddrLen;
	//调用send（）和recv（）进行会话
	//调用closesocket（）关闭SOCKET
}