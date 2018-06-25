#pragma once
#include "cocos2d.h"
#include "math.h"
#include "Monster.h"
#include "bloodProgress.h"
#include <vector>

class Bullet :public cocos2d::Node
{
private:
	float speed;//子弹飞行速度
	int power;//一次干掉多少血
	char* bulletname; //保存初始图片名称
	int x, y;//记录子弹初始坐标
public:
	cocos2d::Sprite* bulletsprite;
	int ifexist;//记录子弹是否还存在
	float distance;  //子弹和目标距离
	int heroFaceinBullet;
	//Monster* my_monster;
	//localPlay* my_map;
	ProgressView*  Monster_xue;//怪物血条  
	Hero* my_hero;
	Bullet();
	~Bullet();
	cocos2d::Sprite* GetSprite();
	void removeBullet(float delta);//移除子弹
	void removeBulletFromOutside();//外部移除
	void initBulletSprite(Hero* my_hero);
	void initBulletSprite(Vec2 pos,int face);
	void bulletMoveAnimation();  //移动子弹
	void StartListen();
	//装备操作

	CREATE_FUNC(Bullet);
	
};