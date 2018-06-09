#pragma once
#include "cocos2d.h" 
#include "LocalPlayStatusLayer.h"
#include "bloodProgress.h"
#include "hero.h"

USING_NS_CC;

class Monster :public cocos2d::CCNode
{
public:
	Monster(void);
	~Monster(void);
	//����ͼƬ�������������Ѫ��  
	void InitMonsterSprite(char *name);
	//��Ѫ���Ĺ���   
	void InitMonsterSprite(char *name, char *xue_back, char* xue_fore);
	//���ö���,numΪͼƬ��Ŀ��run_directonΪ����������false����,name_eachΪname_png��ÿһС��ͼƬ�Ĺ������Ʋ���  
	void SetAnimation(const char *name_each, const unsigned int num, bool run_directon);
	//ֹͣ����  
	void StopAnimation();
	//��������  
	void AttackAnimation(const char *name_each, const unsigned int num, bool run_directon);
	//������������  
	void AttackEnd();
	//����Ӣ��  
	CCSprite* GetSprite();
	//�ж��Ƿ����ܶ���  
	bool IsRunning;
	//�ж��Ƿ��ڹ�������  
	bool IsAttack;
	//Ӣ���˶��ķ���  
	bool MonsterDirecton;

	void FollowRun(Hero* m_hero, CCNode* m_map);
	//�ж��Ƿ񹥻�  
	void JudegeAttack();
	//����Ѳ��·��  
	void MonsterSeeRun();

	//������������Ӣ��  
	void StartListen(Hero* m_hero, CCNode* m_map);
	//��������,ÿ��2�����£�����Ӣ�������ľ���  
	void updateMonster(float delta);
	//���º��������Ӣ���ڿ��ӷ�Χ�ڣ����ϴ���  
	void update(float delta);
	void getBloodStatus(localStatus* nowStatus);
	void cutHeroBlood(float delta);//�ɵ�Ӣ��Ѫ
	void cutMonsterBlood(float delta);//�ɵ�����Ѫ

	CREATE_FUNC(Monster);

private:
	CCSprite* m_MonsterSprite;//���ﾫ��  
	char *Monster_name;//���������ʼ״̬�ľ���ͼƬ����  
	ProgressView*  Monster_xue;//����Ѫ��  
	localStatus* nowStatus;//��ǰ״̬��
	Hero* my_hero;//��ǰӢ��  
	CCNode* my_map;//��ǰ��ͼ  
	float   dis;//��ǰ�����Ӣ�۵ľ���  


};



