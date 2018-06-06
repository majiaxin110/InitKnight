#pragma once
#include "cocos2d.h"  

USING_NS_CC;

class Monster :public cocos2d::CCNode
{
public:
	Monster(void);
	~Monster(void);
	//根据图片名创建怪物，不带血条  
	void InitMonsterSprite(char *name);
	//带血条的怪物   
	//void InitMonsterSprite(char *name, char *xue_back, char* xue_fore);
	//设置动画,num为图片数目，run_directon为精灵脸朝向，false朝右,name_each为name_png中每一小张图片的公共名称部分  
	void SetAnimation(const char *name_each, const unsigned int num, bool run_directon);
	//停止动画  
	void StopAnimation();
	//攻击动画  
	void AttackAnimation(const char *name_each, const unsigned int num, bool run_directon);
	//攻击动画结束  
	void AttackEnd();
	//返回英雄  
	CCSprite* GetSprite();
	//判断是否在跑动画  
	bool IsRunning;
	//判断是否在攻击动画  
	bool IsAttack;
	//英雄运动的方向  
	bool MonsterDirecton;
	CREATE_FUNC(Monster);
private:
	CCSprite* m_MonsterSprite;//怪物精灵  
	char *Monster_name;//用来保存初始状态的精灵图片名称  
	//ProgressView*  Monster_xue;//怪物血条  

};



