#include "hero.h"
#include "localPlayScene.h"

USING_NS_CC;

Hero::Hero()
{
	isMoving = false;
	heroDirection = 0;
	cHeroSprite = nullptr;
	moveSpeed = 1.5f;
}

void Hero::initHeroSprite()
{
	this->cHeroSprite = Sprite::create("ninja.png");
	this->addChild(cHeroSprite);
}

float Hero::getMoveSpeed()
{
	return moveSpeed;
}

bool isCollid(Vec2 pos)
{
//	cocos2d::TMXLayer *blockBarriers = static_cast<localPlay*>(this->getParent())->barriers;
	return false;
}

