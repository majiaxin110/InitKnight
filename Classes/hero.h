#ifndef __HERO_H__  
#define __HERO_H__  

#include "cocos2d.h"  

class Hero :public cocos2d::Node
{
private:
	cocos2d::Sprite* cHeroSprite;
public:
	void initHeroSprite();
	CREATE_FUNC(Hero);
};

#endif // __HERO_H__  
