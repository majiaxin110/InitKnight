#ifndef __HERO_H__  
#define __HERO_H__  

#include "cocos2d.h"  

class Hero :public cocos2d::Node
{
private:
	cocos2d::Sprite* cHeroSprite;
	float moveSpeed;//可移动的速度
public:
	bool isMoving;//是否正在移动
	bool heroDirection;//左右朝向，0向右，1向左

	Hero();

	float getMoveSpeed();
	void initHeroSprite();
	void setRunAnimation(bool runDirection = 0);
	void stopAllAnimation();
	CREATE_FUNC(Hero);
};

#endif // __HERO_H__  
