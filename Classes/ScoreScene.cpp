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