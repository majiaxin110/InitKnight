#include "hero.h"

USING_NS_CC;

void Hero::initHeroSprite()
{
	this->cHeroSprite = Sprite::create("playerHero.png");
	this->addChild(cHeroSprite);
}