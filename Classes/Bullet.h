#pragma once
#include "cocos2d.h"
#include "math.h"
#include "Monster.h"
#include "bloodProgress.h"
#include <vector>

class Bullet :public cocos2d::Node
{
private:
	//float speed;//�ӵ������ٶ�
	//int power;//һ�θɵ�����Ѫ
	//char* bulletname; //
	
	float speed;//�ӵ������ٶ�
	int power;//һ�θɵ�����Ѫ
	char* bulletname; //�����ʼͼƬ����
	int x, y;//��¼�ӵ���ʼ����
public:
	cocos2d::Sprite* bulletsprite;
	int ifexist;//��¼�ӵ��Ƿ񻹴���
	float distance;  //�ӵ���Ŀ�����
	//Monster* my_monster;
	//localPlay* my_map;
	ProgressView*  Monster_xue;//����Ѫ��  
	Hero* my_hero;
	Bullet();
	~Bullet();
	cocos2d::Sprite* GetSprite();
	void removeBullet(float delta);//�Ƴ��ӵ�
	void removeBulletFromOutside();
	void initBulletSprite(Hero* my_hero);
	void bulletMoveAnimation();  //�ƶ��ӵ�
	void StartListen();
	void cutMonsterBlood(float delta);//�ɵ�����Ѫ

	//װ������

	CREATE_FUNC(Bullet);
	
};