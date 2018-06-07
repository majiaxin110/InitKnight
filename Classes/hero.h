#ifndef __HERO_H__  
#define __HERO_H__  

#include "cocos2d.h"  

class Hero :public cocos2d::Node
{
private:
	cocos2d::Sprite* cHeroSprite;
	float moveSpeed;//���ƶ����ٶ�
	int attackPower;//����ֵ
public:
	bool isMoving;//�Ƿ������ƶ�
	bool isAttacking;//�Ƿ����ڹ���
	bool heroDirection;//���ҳ���0���ң�1����

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
