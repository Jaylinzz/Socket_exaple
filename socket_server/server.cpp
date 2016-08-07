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
	WSADATA            wsad;            //WSADATA����  
    SOCKET            Server;        //�������׽���  
    SOCKET            Client;        //�ͻ����׽���  
    SOCKADDR_IN        addrServ;        //��������ַ  
    int                retVal;        //����ֵ  
	char buffer[40]="";
	char buffer1[]="data from server!";
    //��ʼ���׽��ֶ�̬��  
    if (WSAStartup(MAKEWORD(2, 2), &wsad) != 0)  
    {  
        std::printf("��ʼ���׽��ֶ�̬��ʧ��!\n");  
        return 1;  
    }  
  
    //�����׽���  
    Server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
    if (INVALID_SOCKET == Server)  
    {  
        std::printf("�����׽���ʧ��!\n");  
        WSACleanup();//�ͷ��׽�����Դ;  
        return  -1;  
    }  
  
    //�������׽��ֵ�ַ   
    addrServ.sin_family = AF_INET;  
    addrServ.sin_port = htons(PORT);  
    //addrServ.sin_addr.s_addr= htonl(INADDR_ANY);  
	addrServ.sin_addr.s_addr=  inet_addr("192.168.0.110");  
    //���׽���  
    retVal = bind(Server, (struct sockaddr*)&addrServ, sizeof(SOCKADDR_IN));  
    if (SOCKET_ERROR == retVal)  
    {  
        std::printf("���׽���ʧ��!\n");  
        closesocket(Server);    //�ر��׽���  
        WSACleanup();            //�ͷ��׽�����Դ;  
        return -1;  
    }  
  
    //��ʼ����   
    retVal = listen(Server, 1);  
    if (SOCKET_ERROR == retVal)  
    {  
        std::printf("����ʧ��!\n");  
        closesocket(Server);    //�ر��׽���  
        WSACleanup();            //�ͷ��׽�����Դ;  
        return -1;  
    }  
    for (;;){  
        //���ܿͻ�������  
        sockaddr_in addrClient;  
        int addrClientlen = sizeof(addrClient);  
        Client = accept(Server, (struct sockaddr*)&addrClient, &addrClientlen);  
        std::printf("accept a socket\n");  
        if (INVALID_SOCKET == Client)  
        {  
            std::printf("���ܿͻ�������ʧ��!\n");  
            continue;  
        }  
        //���տͻ�������  
		
        int retrec=recv(Client, buffer, sizeof(buffer)-1,0);
		if(SOCKET_ERROR==retrec)
		{
		printf("��������ʧ��\n");
		 WSACleanup();
		return -1;
		}
		printf("%s\n",buffer);
		int retsend=send(Client,buffer1,sizeof(buffer1)-1,0);
		if(SOCKET_ERROR==retsend)
		{
		printf("��������ʧ��\n");
		 WSACleanup();
		return -1;
		}
    }  
    closesocket(Server);  
    WSACleanup();            //�ͷ��׽�����Դ;  
    return 0;  
}  