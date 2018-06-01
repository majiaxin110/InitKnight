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