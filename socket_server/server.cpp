#include <iostream>
#include <string>
#include <Windows.h>
//#include <Winsock2.h>
#include <fstream>
using namespace std;
#define PORT 18990
#define IP_ADDRESS "192.168.0.110"
#pragma comment(lib, "ws2_32.lib")
int main(){  
	WSADATA            wsad;            //WSADATA变量  
    SOCKET            Server;        //服务器套接字  
    SOCKET            Client;        //客户端套接字  
    SOCKADDR_IN        addrServ;        //服务器地址  
    int                retVal;        //返回值  
	char buffer[40]="";
	char buffer1[]="data from server!";
    //初始化套接字动态库  
    if (WSAStartup(MAKEWORD(2, 2), &wsad) != 0)  
    {  
        std::printf("初始化套接字动态库失败!\n");  
        return 1;  
    }  
  
    //创建套接字  
    Server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
    if (INVALID_SOCKET == Server)  
    {  
        std::printf("创建套接字失败!\n");  
        WSACleanup();//释放套接字资源;  
        return  -1;  
    }  
  
    //服务器套接字地址   
    addrServ.sin_family = AF_INET;  
    addrServ.sin_port = htons(PORT);  
    //addrServ.sin_addr.s_addr= htonl(INADDR_ANY);  
	addrServ.sin_addr.s_addr=  inet_addr("192.168.0.110");  
    //绑定套接字  
    retVal = bind(Server, (struct sockaddr*)&addrServ, sizeof(SOCKADDR_IN));  
    if (SOCKET_ERROR == retVal)  
    {  
        std::printf("绑定套接字失败!\n");  
        closesocket(Server);    //关闭套接字  
        WSACleanup();            //释放套接字资源;  
        return -1;  
    }  
  
    //开始监听   
    retVal = listen(Server, 1);  
    if (SOCKET_ERROR == retVal)  
    {  
        std::printf("监听失败!\n");  
        closesocket(Server);    //关闭套接字  
        WSACleanup();            //释放套接字资源;  
        return -1;  
    }  
    for (;;){  
        //接受客户端请求  
        sockaddr_in addrClient;  
        int addrClientlen = sizeof(addrClient);  
        Client = accept(Server, (struct sockaddr*)&addrClient, &addrClientlen);  
        std::printf("accept a socket\n");  
        if (INVALID_SOCKET == Client)  
        {  
            std::printf("接受客户端请求失败!\n");  
            continue;  
        }  
        //接收客户端数据  
		
        int retrec=recv(Client, buffer, sizeof(buffer)-1,0);
		if(SOCKET_ERROR==retrec)
		{
		printf("接收数据失败\n");
		 WSACleanup();
		return -1;
		}
		printf("%s\n",buffer);
		int retsend=send(Client,buffer1,sizeof(buffer1)-1,0);
		if(SOCKET_ERROR==retsend)
		{
		printf("发送数据失败\n");
		 WSACleanup();
		return -1;
		}
    }  
    closesocket(Server);  
    WSACleanup();            //释放套接字资源;  
    return 0;  
}  