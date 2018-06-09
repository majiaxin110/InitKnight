#ifndef __HERO_H__  
#define __HERO_H__  

#include "cocos2d.h"  

class Hero :public cocos2d::Node
{
private:
	
	float moveSpeed;//���ƶ����ٶ�
	int attackPower;//����ֵ
	int blood;//Ѫ��
public:
	cocos2d::Sprite* cHeroSprite;
	bool isMoving;//�Ƿ������ƶ�
	bool isAttacking;//�Ƿ����ڹ���
	bool heroDirection;//���ҳ���0���ң�1����

	Hero();

	float getMoveSpeed();
	void initHeroSprite();
	void setRunAnimation(bool runDirection = 0);
	void setAttackAnimation();
	void setUpAnimation();
	void stopAllAnimation();
	void AttackEnd();
	CREATE_FUNC(Hero);
};

#endif // __HERO_H__  
