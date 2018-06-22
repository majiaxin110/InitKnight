#include "ScoreScene.h"
#include "ui/CocosGUI.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <WinSock2.h>  

USING_NS_CC;

Scene* ScoreScene::createScene()
{
	return ScoreScene::create();
}

bool ScoreScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();

	return true;
}

void ScoreScene::putBackImage(const char* backImage)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto imageBackground = ui::ImageView::create(backImage);
	imageBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(imageBackground,0);
}

void ScoreScene::setScore(int sc)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	playerScore = sc;
	//playerName.assign(str);
	auto scoreLabel = Label::createWithTTF(std::to_string(playerScore), "fonts/Deng.ttf", 50);
	scoreLabel->setTextColor(Color4B::ORANGE);
	scoreLabel->enableShadow(Color4B(200,200,200,90));
	scoreLabel->setPosition(Vec2(visibleSize.width / 2+85, visibleSize.height / 2-90));
	this->addChild(scoreLabel,1);
}

int ScoreScene::getPlayerScore()
{
	return playerScore;
}

cocos2d::Label * ScoreScene::getStatusShow()
{
	return statusShow;
}

/*void uploadScore(std::string name, int score)
{
	std::string pName[5];
	std::string pScore[5];

	log("current name and score :%s %d", name.c_str(), score);

	SOCKET clientsocket;
	SOCKADDR_IN serveraddr;
	SOCKADDR_IN clientaddr;
	char buf[1024];
	strcpy(buf, (std::to_string(score).c_str()));
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 0), &wsa); //初始化WS2_32.DLL  

									  //创建套接字
	if ((clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0)
	{
		log("socket failed");
		//scene->getStatusShow()->setString("socket failed");
		//return -1;
	}

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9102);
	serveraddr.sin_addr.S_un.S_addr = inet_addr("118.25.141.206");//服务器大法好！！

																  //请求连接  
	//scene->getStatusShow()->setString("try to connect...");
	log("try to connect..");
	if (connect(clientsocket, (SOCKADDR *)&serveraddr, sizeof(serveraddr)) != 0)
	{
		//scene->getStatusShow()->setString("connect failed");
		log("connect failed");
		//return -1;
		return;
	}
	//scene->getStatusShow()->setString("connect success!");

	//发送数据
	//scene->getStatusShow()->setString("sending...");
	log("sending..");
	if (send(clientsocket, name.c_str(), name.size() + 1, 0) <= 0)
	{
		log("error send name !");
		return;
	}

	if (send(clientsocket, std::to_string(score).c_str(), std::to_string(score).size() + 1, 0) <= 0)
	{
		log("error send score");
		return;
	}
	
	for(int i=0;i<5;i++)
	{
		if (recv(clientsocket, buf, 1024, 0) <= 0)
		{
			log("close connection\n");
			closesocket(clientsocket);
		}
		log("receive name: %s", buf);

		pName[i].assign(buf);

		if (recv(clientsocket, buf, 1024, 0) <= 0)
		{
			log("close connection !");
			closesocket(clientsocket);
		}
		log("receive score : %s", buf);

		pScore[i].assign(buf);
	}

	//关闭套接字  
	closesocket(clientsocket);
	WSACleanup();    //释放WS2_32.DLL  
	//system("pause");
	//return true;
	return;
}

void ScoreScene::onExit()
{
//	scoThread->join();
//	CC_SAFE_DELETE(scoThread);
}*/