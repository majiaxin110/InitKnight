#include "hero.h"

USING_NS_CC;

Hero::Hero()
{
	isMoving = false;
	heroDirection = 0;
	cHeroSprite = nullptr;
}

void Hero::initHeroSprite()
{
	this->cHeroSprite = Sprite::create("playerHero.png");
	this->addChild(cHeroSprite);
}

void Hero::keyPressedDo(cocos2d::EventKeyboard::KeyCode keyCode)
{
	int deltaX = 0, deltaY = 0;
	switch (keyCode) 
	{
	case EventKeyboard::KeyCode::KEY_W:
		deltaY = 3;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		deltaX = -3;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		deltaY = -3;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		deltaX = 3;
		break;
	default:
		deltaY = deltaX = 0;
		break;
	}
	this->runAction(MoveBy::create(0.2f, Vec2(deltaX, deltaY)));	//给我动起来
}