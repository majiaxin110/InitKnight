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

	this->statusShow = Label::createWithTTF("new", "fonts/Deng.ttf", 60);
	statusShow->setPosition(Vec2(visibleSize.width / 2, 40));
	this->addChild(statusShow,3);
	return true;
}

void ScoreScene::putBackImage(const char* backImage)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto imageBackground = ui::ImageView::create("loseBackground.png");
	imageBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(imageBackground,0);
}

void ScoreScene::getScore(int sc)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	playerScore = sc;
	auto scoreLabel = Label::createWithTTF(std::to_string(playerScore), "fonts/Deng.ttf", 50);
	scoreLabel->setTextColor(Color4B::ORANGE);
	scoreLabel->enableShadow(Color4B(200,200,200,90));
	scoreLabel->setPosition(Vec2(visibleSize.width / 2+40, visibleSize.height / 2+30));
	this->addChild(scoreLabel,1);

	uploadScore();
}

int ScoreScene::uploadScore()
{
	SOCKET clientsocket;
	SOCKADDR_IN serveraddr;
	SOCKADDR_IN clientaddr;
	char buf[1024];
	strcpy(buf, (std::to_string(playerScore)).c_str());
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 0), &wsa); //��ʼ��WS2_32.DLL  

									  //�����׽���
	if ((clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0)
	{
		statusShow->setString("socket failed");
		return -1;
	}

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9102);
	serveraddr.sin_addr.S_un.S_addr = inet_addr("118.25.141.206");//�������󷨺ã���

																  //��������  
	statusShow->setString("try to connect...");
	if (connect(clientsocket, (SOCKADDR *)&serveraddr, sizeof(serveraddr)) != 0)
	{
		statusShow->setString("connect failed");
		return -1;
	}
	statusShow->setString("connect success!");

	//��������  
	statusShow->setString("sending...");
	if (send(clientsocket, buf, strlen(buf) + 1, 0) <= 0)
	{
		printf("���ʹ���!\n");
	}

	/*��������  
	while (1) {
		if (recv(clientsocket, buf, 1024, 0) <= 0)
		{
			printf("�ر�����!\n");
			closesocket(clientsocket);
		}
		printf("�������Է���������Ϣ: %s\n", buf);
		break;
	}
	//�ر��׽���  */
	closesocket(clientsocket);
	WSACleanup();    //�ͷ�WS2_32.DLL  
	//system("pause");
	return true;
}
