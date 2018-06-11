#ifndef __HERO_H__  
#define __HERO_H__  

#include "cocos2d.h"  

class Hero :public cocos2d::Node
{
private:
	//cocos2d::Sprite* cHeroSprite;
	float moveSpeed;//���ƶ����ٶ�
	int attackPower;//����ֵ
	bool attackMode;//�������ͣ�0��1��ǹ
public:
	cocos2d::Sprite* cHeroSprite;//�Ұ�����ŵ�public����monster��ȡ
	bool isMoving;//�Ƿ������ƶ�
	bool isAttacking;//�Ƿ����ڹ���
	bool heroDirection;//���ҳ���0���ң�1����

	Hero();

	float getMoveSpeed();
	void setMoveSpeed(float currentSpeed);

	void changeAttackMode();
	void initHeroSprite();
	void setRunAnimation(bool runDirection = 0);
	//void setAttackAnimation();
	void setAttackAnimation();
	void AttackEnd();  //�ֳ��������򹥻�˲��͹�ȥ���жϲ�������Ѫ
	void setUpAnimation();
	void stopAllAnimation();
	CREATE_FUNC(Hero);
};

#endif // __HERO_H__  
