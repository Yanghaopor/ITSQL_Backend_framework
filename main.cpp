#include "InTypeSendSQL.h"
#include "iostream"
#include "fstream"
#include "stdio.h"
#include "stdlib.h"
#include "iomanip"
#include "stream.h"
//默认端口为"127.0.0.1"


//主函数构造器 
//网络连接器
static void OpenNet();
//用户线程(Intel,用户套口)
static void HandleClient(IntelNet::InteS& server, SOCKET clientSocket);

//主函数入口
int main(void) {
	
	system("chcp 65001");
	//初始文件
	ReadFilePrject(&PIIEG, "./Saver/jpeg.txt"); //图片
	ReadFilePrject(&VIDEO, "./Saver/video.txt"); //视频
	ReadFilePrject(&JavaSc, "./Saver/js.txt"); //脚本
	for (auto& pair : VIDEO) {
		std::cout << pair.Name << std::endl;
		std::cout << pair.URL << std::endl;
		std::cout << pair.Type << std::endl;
		std::cout << pair.Tag << std::endl;
	}

	OpenNet();
	return 0;
}


//网络连接器
void OpenNet() {
	IntelNet::InteS* NetSet = new IntelNet::InteS; //网络变量
	NetSet->OpenIntOP(); //打开网络权限
	NetSet->OSset.agreement = true; //网络协议
	NetSet->OSset.Namber = 10; //接收人数
	NetSet->OSset.port = 80; //端口设置
	NetSet->MkIntNet(); //开始创建网络

	SOCKET UserMod; //创建字套存储
	sockaddr_in userADD; //新增用户
	int clientAddrSize = sizeof(userADD);//存储用户大小
	
	//为每个用户创建链接
	while (true) {
		UserMod = accept(NetSet->GetScok(), (struct sockaddr*)&userADD, &clientAddrSize);
		//为每个用户创建线程
		std::thread ThreadNet(HandleClient, std::ref(*NetSet), UserMod);
		ThreadNet.detach();
	}
	delete NetSet;
}

// 处理客户端连接的函数
void HandleClient(IntelNet::InteS& server, SOCKET clientSocket) {
	std::cout << "用户链接" << std::endl;
	//创建介绍字符
	char buffer[4096] = { 0 };
	int len = recv(clientSocket, buffer, sizeof(buffer), NULL);
	if (len > 0) {
		//链接后执行
		std::cout << buffer << std::endl;
		std::vector<std::string>Name = IntelNet::GetNAME(buffer,"ID");
		std::vector<std::string>Data = IntelNet::GetData(buffer, "ID");
		//查看请求
		//数据请求发送(图片)
		for (auto& name : Name) {
			for (auto& data : Data) {
				for (auto& piieg : PIIEG) {
					if (data == piieg.Name) {
						//流文件传输解决图片
						std::cout << "To detect the image pull up application:" << piieg.Name << ":" << data << std::endl;
						std::vector<char>FileeData = IntelNet::ReadFile(piieg.URL);
						IntelNet::OrCreaPost(piieg.Type, FileeData.size());
						send(clientSocket, FileeData.data(), FileeData.size(), NULL);
						std::wcout << "image send down" << std::endl;
					}
				}

				//数据请求发送(视频)
				for (auto& video : VIDEO) {
					if (data == video.Name) {
						std::cout << "To detect the VIDEO pull up application:" << video.Name << ":" << data << std::endl;
						//重新定向解决视频
						std::string SendVideo = IntelNet::URLtoHTTP(video.URL);
						send(clientSocket, SendVideo.c_str(), SendVideo.size(), NULL);

						std::wcout << "VIDEO send down" << std::endl;
					}
				}

				//数据请求发送(js脚本)
				for (auto& js : JavaSc) {
					if (data == js.Name) {
						std::cout << "To detect the For pull up application:" << js.Name << ":" << data << std::endl;
						//重新读取发送脚本
						std::vector<char>ReadFilles = IntelNet::ReadFile(js.URL);
						IntelNet::OrCreaPost(js.Type, ReadFilles.size());
						send(clientSocket, ReadFilles.data(), ReadFilles.size(), NULL);
						std::wcout << "JS send down" << std::endl;
					}
				}

				//移动视频传输
				if (data == "KE1") {
					std::string Jsc; //预载脚本
					std::cout << "KE1" << std::endl;
					for (auto& video : VIDEO) {
						//编辑脚本
						std::cout << "KE1" << std::endl;
						Jsc += "<div class=\"videoDiv\"><video class=\"videoMEN\" controls><source src=\"http://127.0.0.1:80/Pige102.jpg?IDVED=" + video.Name + "&\" type=\"video/mp4\"></video></div>";
					}
					//传输脚本
					Jsc = IntelNet::XOREncrypt(Jsc, 65);
					Jsc = IntelNet::CreaPost("text/plain", Jsc.c_str(), Jsc.size());
					send(clientSocket, Jsc.c_str(), Jsc.size(), NULL);
					std::cout << Jsc << std::endl;
				}


				//前端请求数据(视频)
				if (data == "V1-1" && name == "PL") {
					std::string Jsc; //预载脚本
					std::cout << "PL2" << std::endl;
					std::cout << "KE1" << std::endl;
					Jsc = "<div class=\"videoDiv\"><video class=\"videoMEN\" controls><source src=\"http://127.0.0.1:80/Pige102.jpg?IDVED=V1&\" type=\"video/mp4\"></video></div>";
					//传输脚本
					Jsc = IntelNet::XOREncrypt(Jsc, 65);
					Jsc = IntelNet::CreaPost("text/plain", Jsc.c_str(), Jsc.size());
					send(clientSocket, Jsc.c_str(), Jsc.size(), NULL);
					std::cout << Jsc << std::endl;
				}

				//数据请求发送(HTML)
				for (auto& html : HTTP) {
					if (data == html.Name) {
						std::cout << "To detect the For pull up application:" << html.Name << ":" << data << std::endl;
						//重新读取发送html
						std::vector<char>ReadFilles = IntelNet::ReadFile(html.URL);
						IntelNet::OrCreaPost(html.Type, ReadFilles.size());
						send(clientSocket, ReadFilles.data(), ReadFilles.size(), NULL);
						std::wcout << "JS send down" << std::endl;
					}
				}

			}
		}

	}
	// 关闭客户端连接
	std::cout << "链接结束" << std::endl;
	closesocket(clientSocket);
}
