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
	this->cHeroSprite = Sprite::create("knight.png");
	this->addChild(cHeroSprite);
}

float Hero::getMoveSpeed()
{
	return moveSpeed;
}

void Hero::setRunAnimation(bool runDirection)
{
	//翻转吧朋友
	if (heroDirection != runDirection)
	{
		heroDirection = runDirection;
		cHeroSprite->setFlippedX(runDirection);
	}
	if (isMoving)
		return;
	Animation *animation = Animation::create();
	log("run anime");
	for (int i = 1; i <= 4; i++)
	{
		__String *frameName = __String::createWithFormat("knightAnime/run_%d.png", i);
		//SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		animation->addSpriteFrameWithFile(frameName->getCString());
	}
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);
	Animate *action = Animate::create(animation);
	cHeroSprite->runAction(RepeatForever::create(action));

	isMoving = true;
}

void Hero::stopAllAnimation()
{
	if (!isMoving)
		return;
	cHeroSprite->stopAllActions();
	this->removeChild(cHeroSprite, TRUE);//把原来的精灵删除掉  
	cHeroSprite = Sprite::create("knight.png");//恢复精灵原来的贴图样子  
	cHeroSprite->setFlippedX(heroDirection);
	this->addChild(cHeroSprite);
	isMoving = false;
	isMoving = false;
}