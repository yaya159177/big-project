﻿#include "Client.h"
#include <ctime>
#include <thread>
#include <algorithm>
#include "cocos2d.h"

USING_NS_CC;

Client* Client::client = new Client();

bool Client::init()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))//³É¹¦·µ»Ø0  
	{
		return FALSE;
	}

	SOCKET sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sHost)
	{
		closesocket(sHost);
		WSACleanup();
		return FALSE;
	}

	//3 ×¼±¸Í¨ÐÅµØÖ·  
	SOCKADDR_IN addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(PORT);
	addrServer.sin_addr.s_addr = inet_addr("192.168.0.3");

	return true;
}

BOOL Client::ConnectServer()
{
	if (SOCKET_ERROR == connect(sHost, (const sockaddr*)&addrServer, sizeof(addrServer)))
	{
		//cout <<clock()-start;
		closesocket(sHost);
		WSACleanup();
		system("pause");
		return FALSE;
	}

	return TRUE;
}

string Client::recv_Cli()
{
	char recvBuf[BUFLEN + 1];
	ZeroMemory(recvBuf, sizeof(recvBuf));
	if (SOCKET_ERROR == recv(sHost, recvBuf, sizeof(recvBuf), 0))
	{
		//closesocket(sHost);
		//WSACleanup();
		return FALSE;
	}
	recvBuf[BUFLEN] = '\0';

	return string(recvBuf);
}

BOOL Client::send_Cli(string sendBuf)
{
	clock_t start = clock();
	while (true)
	{
		if (SOCKET_ERROR == send(sHost, sendBuf.c_str(), sendBuf.length(), 0))
		{
			//closesocket(sHost);
			//WSACleanup();
			if (clock() - start > TIMEOUTERROR)
			{
				log("send message %s fail,time out", sendBuf.c_str());
				break;
			}
			Sleep(WAITTIME);
			continue;
		}
		//information.clearSendBuf();
		break;
	}
	return TRUE;
}

Client::Client()
{
	if (!init())
	{
		log("init Client false!");
	}

	if (!ConnectServer())
	{
		log("can't connect Server!");
	}
}

Client* Client::getInstance()
{
	return client;
}

void Client::SendThread(string sendBuf)
{
	while (true)
	{
		send_Cli(sendBuf);
		Sleep(TIME_LAG);
	}
}

void Client::RecvThread()
{
	while (true)
	{
		recv_Cli();
		Sleep(TIME_LAG);
	}
}
