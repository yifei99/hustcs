#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <istream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <iostream>
#include <winsock2.h>
#include <Windows.h>
#include <thread>
#include <conio.h>
#include  <WS2tcpip.h>
#include <regex>
#pragma comment(lib,"Ws2_32.lib")
#pragma warning(diable:4996)


void serverclient(SOCKET talksocket);
std::string fileposition("C:\\Users\\dell\\source\\repos\\计网\\file");

int main(void)
{

	//初始化winsock
	WSADATA wasdata;
	int nRc = WSAStartup(0x0202, &wasdata);//返回值
	std::cout << "Do you want to configure fileposition? (y/n)\n";
	std::cout << "Default fileposition :C:\\Users\\dell\\source\\repos\\计网\\file;\n";
	char a;
	scanf_s("%c", &a);
	while ((a != 'y') && (a != 'n') && (a != 'Y') && (a != 'N'))
	{
		scanf_s("%c", &a);
	}
	if (a == 'y' || a == 'Y')
	{
		std::cout << "input fileposition:";
		std::cin >> fileposition;

	}
	if (nRc)
	{
		std::cout << "WSAstartup error\n";
		return 0;
	}
	std::cout << "WSAstartup success\n";
	if (wasdata.wVersion != 0x0202)
	{
		std::cout << "Version error\n";
		WSACleanup();
		return 0;
	}
	std::cout << "Version pass\n";
	//创建一个监听socket
	SOCKET tcpsocket;//服务器监听socket
	tcpsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (tcpsocket == INVALID_SOCKET)
	{
		std::cout << "Get socket error\n";
		return 0;
	}
	std::cout << "get correct socket\n";
	//bind 监听socket

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	std::cout << "Do you want to configure port? (y/n)\n";
	std::cout << "Default port :80;\n";
	char configure;
	char configure1;
	int portnum = 80;
	char ipnum[20] = {"127.0.0.1"};
	scanf_s("%c", &configure);
	while ((configure != 'y') && (configure != 'n') && (configure != 'Y') && (configure != 'N'))
	{
		scanf_s("%c", &configure);
	}
	if (configure == 'y' || configure == 'Y')
	{
		std::cout << "input port:";
		std::cin >> portnum;

	}
	std::cout << "Do you want to configure IP? (y/n)\n";
	std::cout << "Default IP :127.0.0.1;\n";
	scanf_s("%c", &configure1);
	while ((configure1 != 'y') && (configure1 != 'n') && (configure1 != 'Y') && (configure1 != 'N'))
	{
		scanf_s("%c", &configure1);
	}
	if (configure1 == 'y' || configure1 == 'Y')
	{
		std::cout << "input ip:";
		std::cin >> ipnum;
	}
	addr.sin_port = htons(portnum);
	addr.sin_addr.S_un.S_addr = inet_addr(ipnum);
	bind(tcpsocket, (LPSOCKADDR)&addr, sizeof(addr));
	//监听socket，等待客户机的连接请求
	nRc = listen(tcpsocket, 5);//最多接收5个连接
	if (nRc == SOCKET_ERROR)
	{
		std::cout << "listen error\n";
		return 0;
	}
	std::cout << "listen correct\n";
	//accept接收客户机请求 连接并生成会话socket
	while (1)
	{
		int sockerror;
		int length = sizeof(sockaddr);
		sockaddr_in clientaddr;
		SOCKET talksocket = accept(tcpsocket, (sockaddr *)&clientaddr, &length);
		if (talksocket == INVALID_SOCKET)
		{
			std::cout << "accept error\n";
			sockerror = WSAGetLastError();
			return 0;
		}
		else
		{
			std::cout << "accept success\n";
			std::cout << "request IP addr:" << (int)clientaddr.sin_addr.S_un.S_un_b.s_b1 << "." << (int)clientaddr.sin_addr.S_un.S_un_b.s_b2 << "." << (int)clientaddr.sin_addr.S_un.S_un_b.s_b3 << "." << (int)clientaddr.sin_addr.S_un.S_un_b.s_b4;
			std::cout << "\nrequest Port:" << clientaddr.sin_port << "\n";
			std::thread talkthread(serverclient, talksocket);//开启一个新的线程来处理这一个客户的请求
			talkthread.detach();
		}
	}
	return 0;
}

void serverclient(SOCKET talksocket)//进行会话的函数。
{
	int sendre;
	char* buf = (char*)malloc(1024 * sizeof(char));
	int len = 1024;
	int recharnum;
	recharnum = recv(talksocket, buf, len, 0);
	if (recharnum == SOCKET_ERROR)
	{
		recharnum = WSAGetLastError();
		std::cout << "thread falied!";
		std::cout << std::endl;
		return;
	}
	else
	{
		//对接受到的消息进行解析
		std::smatch strmatch;//正则表达式结果文本
		std::regex regulation("([A-Za-z]+) +(.*) +(HTTP/[0-9][.][0-9])");//正则表达式规则，，匹配请求报文的请求行
		std::string str(buf);//需要用正则表达式的原始文本

		    int matchnum = std::regex_search(str, strmatch, regulation);//分离 GET  url http_version
			std::cout << strmatch[1] << " " << strmatch[2] << " " << strmatch[3] << std::endl;
			std::string msg_get = strmatch[1];
			std::string msg_url = strmatch[2];
			std::smatch filetype;
			std::regex regulation2("\\..*");
			matchnum = regex_search(msg_url, filetype, regulation2);
			if (matchnum == 0)
			{
				std::cout << msg_get + msg_url + " NOT FOUND\n";
				char send4041[] = "NOT FOUND 404!";
				if ((sendre = send(talksocket, send4041, sizeof(send4041), 0) < 0)) {
					std::cout << "send error" << std::endl;
				};
				closesocket(talksocket);
				return;
			}
			else
			{
				std::ifstream f(fileposition + msg_url, std::ios::binary);
				if (!f)//没有找到文件
				{   
					std::cout << msg_url + " NOT FOUND\n";
					char send404[] = "NOT FOUND 404!";
						if ((sendre = send(talksocket, send404, sizeof(send404), 0) < 0)) {
							std::cout << "send error" << std::endl;
					};
					closesocket(talksocket);
					return;
				}
				else//如果找到了对应的文件
				{
					std::filebuf* tmp = f.rdbuf();
					int size = tmp->pubseekoff(0, f.end, f.in);
					tmp->pubseekpos(0, f.in);
					std::string Content_Type;
						if (filetype[0] == ".html") Content_Type = "text/html";
						else {
							if (filetype[0] == ".xml") Content_Type = "text/xml";
							else
							{
								if (filetype[0] == ".css") Content_Type = "text/css";
								else
								{
									if (filetype[0] == ".png") Content_Type = "image/png";
									else
									{
										if (filetype[0] == ".gif") Content_Type = "image/gif";
										else
										{
											if (filetype[0] == ".jpg") Content_Type = "image/jpg";
											else
											{
												if (filetype[0] == ".jpeg") Content_Type = "image/jpeg";
												else
												{
													if (filetype[0] == ".ico") Content_Type = "image/ico";
													else
													{
														Content_Type = "text/plain";
													}
												}
											}
										}
									}
								}
							}
						}
						char* buffer = new char[size];
						char* tail = buffer + size;
						tmp->sgetn(buffer, size);
						f.close();
						std::cout << "success return file " + msg_url;
						std::cout << std::endl;
						std::stringstream remsg;
						remsg << "HTTP/1.1 200 OK\r\n" << "Connection:close\r\n" << "Server:LiangyiFei\r\n" << "Content Length:" << size
							<< "\r\n" << "Content Type:" + Content_Type << "\r\n\r\n";
						std::string remsgstr = remsg.str();
						const char* remsgchar = remsgstr.c_str();
						int tmpsize = strlen(remsgchar);
						sendre = send(talksocket, remsgchar, tmpsize, 0);
						while (buffer < tail)
						{
							sendre = send(talksocket, buffer, size, 0);
							buffer = buffer + sendre;
							size = size - sendre;
						}
						closesocket(talksocket);
						return;
					}
				}


			}
	 return;
}
