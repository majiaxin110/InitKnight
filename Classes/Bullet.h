#pragma once
#include "cocos2d.h"
#include "math.h"
#include "Monster.h"
#include "LocalPlayStatusLayer.h"
#include "bloodProgress.h"
USING_NS_CC;

class Bullet :public cocos2d::Node
{
private:
	//float speed;//�ӵ������ٶ�
	//int power;//һ�θɵ�����Ѫ
	//char* bulletname; //�����ʼͼƬ����
public:
	int x, y;//��¼�ӵ���ʼ����
	int ifexist;//��¼�ӵ��Ƿ񻹴���
	float speed;//�ӵ������ٶ�
	int power;//һ�θɵ�����Ѫ
	char* bulletname; //�����ʼͼƬ����
	CCSprite* bulletsprite;
	float distance;  //�ӵ���Ŀ�����
	Monster* my_monster;
	CCNode* my_map;
	ProgressView*  Monster_xue;//����Ѫ��  
	localStatus* nowStatus;//��ǰ״̬��
	//Vector <Sprite *>vecBullet;//�ӵ����� 
	Hero* my_hero;
	Bullet();
	~Bullet();
	CCSprite* GetSprite();
	void removeBullet(float delta);//�Ƴ��ӵ�
	void initBulletSprite(Hero* my_hero);
	void bulletMoveAnimation();  //�ƶ��ӵ�
	void StartListen(Monster* m_monster, CCNode* m_map);
	void cutMonsterBlood(float delta);//�ɵ�����Ѫ
	void getBloodStatus(localStatus* nowStatus);




	//װ������

	CREATE_FUNC(Bullet);
	
};