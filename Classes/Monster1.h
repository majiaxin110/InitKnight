#pragma once
#include "cocos2d.h"  

class Monster1 :public cocos2d::Node
{
private:
	cocos2d::Sprite* monster1Sprite;
	float moveSpeed;//�ƶ����ٶ�
	int attackPower;//����ֵ
	int blood;//Ѫ��
public:
	bool isMoving;//�Ƿ������ƶ�
	bool isAttacking;//�Ƿ����ڹ���
	bool monster1Direction;//���ҳ���0���ң�1����
	
	Monster1();

	float getMoveSpeed();
	void initMonster1Sprite();
	void startAnimation();
	void patrol();
	/*void setRunAnimation(bool runDirection = 0);
	void setAttackAnimation();
	void setUpAnimation();
	void stopAllAnimation();*/
	CREATE_FUNC(Monster1);
};


