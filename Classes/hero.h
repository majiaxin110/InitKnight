#ifndef __HERO_H__  
#define __HERO_H__  

#include "cocos2d.h"  

class Hero :public cocos2d::Node
{
private:
	cocos2d::Sprite* cHeroSprite;
	float moveSpeed;//可移动的速度
	int attackPower;//攻击值
public:
	bool isMoving;//是否正在移动
	bool isAttacking;//是否正在攻击
	bool heroDirection;//左右朝向，0向右，1向左

	Hero();

	float getMoveSpeed();
	void setMoveSpeed(float currentSpeed);
	void initHeroSprite();
	void setRunAnimation(bool runDirection = 0);
	void setAttackAnimation();
	void setUpAnimation();
	void stopAllAnimation();
	CREATE_FUNC(Hero);
};

#endif // __HERO_H__  
