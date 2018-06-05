/*#pragma once
#include "cocos2d.h"

class Monster :public cocos2d::Node
{
private:
	cocos2d::Sprite* monsterSprite;
	float moveSpeed;//可移动的速度
	int attackPower;//攻击值
	int blood;//血量
public:
	bool isMoving;//是否正在移动
	bool isAttacking;//是否正在攻击
	bool heroDirection;//左右朝向，0向右，1向左

	Monster();

	float getMoveSpeed();
	void initMonsterSprite();
	void setRunAnimation(bool runDirection = 0);
	void setAttackAnimation();
	void setUpAnimation();
	void stopAllAnimation();
	CREATE_FUNC(Monster);
};*/
