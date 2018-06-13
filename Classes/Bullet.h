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
	//float speed;//子弹飞行速度
	//int power;//一次干掉多少血
	//char* bulletname; //保存初始图片名称
public:
	int x, y;//记录子弹初始坐标
	int ifexist;//记录子弹是否还存在
	float speed;//子弹飞行速度
	int power;//一次干掉多少血
	char* bulletname; //保存初始图片名称
	CCSprite* bulletsprite;
	float distance;  //子弹和目标距离
	Monster* my_monster;
	CCNode* my_map;
	ProgressView*  Monster_xue;//怪物血条  
	localStatus* nowStatus;//当前状态层
	//Vector <Sprite *>vecBullet;//子弹容器 
	Hero* my_hero;
	Bullet();
	~Bullet();
	CCSprite* GetSprite();
	void removeBullet(float delta);//移除子弹
	void initBulletSprite(Hero* my_hero);
	void bulletMoveAnimation();  //移动子弹
	void StartListen(Monster* m_monster, CCNode* m_map);
	void cutMonsterBlood(float delta);//干掉怪物血
	void getBloodStatus(localStatus* nowStatus);




	//装备操作

	CREATE_FUNC(Bullet);
	
};