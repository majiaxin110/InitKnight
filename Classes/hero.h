#ifndef __HERO_H__  
#define __HERO_H__  

#include "cocos2d.h"  

class Hero :public cocos2d::Node
{
private:
	//cocos2d::Sprite* cHeroSprite;
	float moveSpeed;//可移动的速度
	int attackPower;//攻击值
	bool attackMode;//攻击类型，0剑1火枪
public:
	cocos2d::Sprite* cHeroSprite;//我把这个放到public方便monster读取
	bool isMoving;//是否正在移动
	bool isAttacking;//是否正在攻击
	bool heroDirection;//左右朝向，0向右，1向左

	Hero();

	float getMoveSpeed();
	void setMoveSpeed(float currentSpeed);

	void changeAttackMode();
	void initHeroSprite();
	void setRunAnimation(bool runDirection = 0);
	//void setAttackAnimation();
	void setAttackAnimation();
	void AttackEnd();  //分成两个否则攻击瞬间就过去了判断不出来掉血
	void setUpAnimation();
	void stopAllAnimation();
	CREATE_FUNC(Hero);
};

#endif // __HERO_H__  
