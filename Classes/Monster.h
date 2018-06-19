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
	bool isDied;
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
	//���ع���sprite  
	Sprite* GetSprite();
	//�ж��Ƿ����ܶ���  
	bool IsRunning;
	//�ж��Ƿ��ڹ�������  
	bool IsAttack;
	//Ӣ���˶��ķ���  
	bool MonsterDirecton;

	void FollowRun(Hero* m_hero, Node* m_map);
	//�ж��Ƿ񹥻�  
	void JudgeAttack();
	//����Ѳ��·��  
	void MonsterSeeRun();

	//������������Ӣ��  
	void StartListen(Hero* m_hero, Node* m_map);
	//��������,ÿ��2�����£�����Ӣ�������ľ���  
	void updateMonster(float delta);
	//���º��������Ӣ���ڿ��ӷ�Χ�ڣ����ϴ���  
	void update(float delta);
	void getBloodStatus(localStatus* nowStatus);
	void cutHeroBlood(float delta);//�ɵ�Ӣ��Ѫ
	void heroCutMonsterBlood(float delta);//�ɵ�����Ѫ
	bool getHurt(float delta);

	float getSense();
	void setSense(float sens);

	ProgressView*  Monster_xue;//����Ѫ��  
	localStatus* nowStatus;//��ǰ״̬��

	CREATE_FUNC(Monster);

private:
	Sprite* m_MonsterSprite;//���ﾫ��  
	char *Monster_name;//���������ʼ״̬�ľ���ͼƬ����  

	Hero* my_hero;//��ǰӢ��  
	Node* my_map;//��ǰ��ͼ  
	float dis;//��ǰ�����Ӣ�۵ľ���  

	float sense;//����֪̽Ӣ�۾���

	float power;//���﹥������
};
