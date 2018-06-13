#include "Monster.h"

USING_NS_CC;
Monster::Monster(void)
{
	IsRunning = false;//û�ڷŶ���  
	MonsterDirecton = TRUE;//�����˶�  
	Monster_name = NULL;
	IsAttack = false;
	Monster_xue = NULL; //�����ʼ��
}

Monster::~Monster(void)
{

}
CCSprite* Monster::GetSprite()
{
	return m_MonsterSprite;
}
void  Monster::InitMonsterSprite(char *name)  //����Ѫ���Ĺ���
{
	Monster_name = name;
	this->m_MonsterSprite = CCSprite::create(name);
	m_MonsterSprite->setFlipX(MonsterDirecton);  //ͼƬ��ʼ����
	this->addChild(m_MonsterSprite);
}
void Monster::InitMonsterSprite(char *name, char *xue_back, char* xue_fore)  //��Ѫ���Ĺ���  ��������
{
	InitMonsterSprite(name);
	//���ù����Ѫ��   
	Monster_xue = new ProgressView();
	Monster_xue->setPosition(ccp(m_MonsterSprite->getPositionX() + 25, m_MonsterSprite->getPositionY() + 50));//�����ڹ�����ͷ    																											  //Monster_xue->setScale(2.2f);    
	Monster_xue->initProgressView(xue_back, xue_fore);
	Monster_xue->setTotalProgress(300.0f);
	Monster_xue->setCurrentProgress(300.0f);
	this->addChild(Monster_xue);
}
void  Monster::SetAnimation(const char *name_each, unsigned int num, bool run_directon)
{
	if (MonsterDirecton != run_directon)
	{
		MonsterDirecton = run_directon;
		m_MonsterSprite->setFlipX(run_directon);//���ӣ�
	}
	if (IsRunning || IsAttack)
		return;
	CCAnimation* animation = CCAnimation::create();
	for (int i = 1; i <= num; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "%s%d.png", name_each, i);
		animation->addSpriteFrameWithFileName(szName); //���ض�����֡    
	}
	animation->setDelayPerUnit(2.8f / 14.0f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(-1); //����ѭ��  
							 //��������װ��һ������  
	CCAnimate* act = CCAnimate::create(animation);
	m_MonsterSprite->runAction(act);
	IsRunning = true;

}
void  Monster::StopAnimation()
{
	if (!IsRunning)
		return;
	m_MonsterSprite->stopAllActions();//��ǰ����ֹͣ���ж���  
									  //�ָ�����ԭ���ĳ�ʼ����ͼ   
	this->removeChild(m_MonsterSprite, TRUE);//��ԭ���ľ���ɾ����  
	m_MonsterSprite = CCSprite::create(Monster_name);//�ָ�����ԭ������ͼ����  
	m_MonsterSprite->setFlipX(!MonsterDirecton);  //���ӣ�
	this->addChild(m_MonsterSprite);
	IsRunning = false;
	MonsterDirecton = !MonsterDirecton;  //ÿ��ͣ�¶������÷���
}
void  Monster::AttackAnimation(const char *name_each, const unsigned int num, bool run_directon)
{
	if (IsAttack || IsRunning)
		return;
	CCAnimation* animation = CCAnimation::create();
	for (int i = 1; i <= num; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "%s%d.png", name_each, i);
		animation->addSpriteFrameWithFileName(szName); //���ض�����֡    
	}
	animation->setDelayPerUnit(2.0f / 14.0f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(1); //����ѭ��1��    
							//��������װ��һ������  
	CCAnimate* act = CCAnimate::create(animation);
	//�����ص��������������������AttackEnd()  
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Monster::AttackEnd));
	//������������  
	CCActionInterval* attackact = CCSequence::create(act, callFunc, NULL);

	m_MonsterSprite->runAction(attackact);
	IsAttack = true;

}
void Monster::AttackEnd()
{
	//�ָ�����ԭ���ĳ�ʼ����ͼ   
	this->removeChild(m_MonsterSprite, TRUE);//��ԭ���ľ���ɾ����  
	m_MonsterSprite = CCSprite::create(Monster_name);//�ָ�����ԭ������ͼ����  
	m_MonsterSprite->setFlipX(!MonsterDirecton);  //���ӣ�
	this->addChild(m_MonsterSprite);
	IsAttack = false;
}

void Monster::FollowRun(Hero* m_hero, CCNode* m_map)
{
	//�õ�����x�ľ���,�ǵù��������Ҫ���ϵ�ͼ��  
	float x = m_hero->getPositionX() - (this->getPositionX() + m_map->getPositionX());
	//�õ�����y�ľ��룬�ǵù��������Ҫ���ϵ�ͼ��  
	float y = m_hero->getPositionY() - (this->getPositionY() + m_map->getPositionY());

	//�ȼ�������Ӣ�۵ľ���  
	dis = sqrt(pow(x, 2) + pow(y, 2));

	if (dis >= 100)//��������Ӣ�۾��볬��150
		return;
	if (dis <= 64)//�ڹ��﹥����Χ�ڣ�����ֹͣ�ƶ�  
	{
		this->StopAnimation();//ֹͣ�ܶ�  
		JudegeAttack();//�ض��������� 
		return;
	}

	if (x<-64)//�жϹ���������Ӣ�۵ľ���  
	{

		MonsterDirecton = true;
		m_MonsterSprite->setFlipX(MonsterDirecton);//���÷���  ���ӣ�
		if (IsAttack)
			return;
		this->setPosition(this->getPositionX() - 1, this->getPositionY());//������Ӣ���ƶ�  
		this->SetAnimation("monster1/monsterwalk", 6, MonsterDirecton);//���Ŷ���  

	}
	else if (x>64)
	{

		MonsterDirecton = false;
		m_MonsterSprite->setFlipX(MonsterDirecton);//���÷���  ���ӣ�
		if (IsAttack)
			return;
		this->setPosition(this->getPositionX() + 1, this->getPositionY());
		this->SetAnimation("monster1/monsterwalk", 6, MonsterDirecton);//���Ŷ���  
	}
	else if (x <= 64)//����M���˺�Ӣ�������64����ʱ����ʼ�ƶ�����������  
	{

		if (m_hero->getPositionY()>this->getPositionY())
		{
			m_MonsterSprite->setFlipX(MonsterDirecton);//���÷���  ���ӣ�
			if (IsAttack)
				return;
			this->setPosition(this->getPositionX(), this->getPositionY() + 1);
			this->SetAnimation("monster1/monsterwalk", 6, MonsterDirecton);//���Ŷ���  
		}
		else if (m_hero->getPositionY()<this->getPositionY())
		{
			m_MonsterSprite->setFlipX(MonsterDirecton);//���÷���  ���ӣ�
			if (IsAttack)
				return;
			this->setPosition(this->getPositionX(), this->getPositionY() - 1);
			this->SetAnimation("monster1/monsterwalk", 6, MonsterDirecton);//���Ŷ���  //knightAnime/run_%d.png
		}
	}

}
void Monster::JudegeAttack()//�ض�����
{
	//srand((UINT)GetCurrentTime());
	//int x = rand() % 100;
	//if (x>98)
	//{
	m_MonsterSprite->setFlipX(!MonsterDirecton);
	this->AttackAnimation("monster1/monsterattack", 6, MonsterDirecton);
	//this->schedule(schedule_selector(Monster::cutHeroBlood), 1.0f); 
	//this->schedule(schedule_selector(Monster::updateMonster), 2.0f);
	//}

}

void Monster::cutHeroBlood(float delta)
{
	if (IsAttack == 1)  //���������ڹ���
		nowStatus->cutHeroBlood(1);  //�ɵ�Ѫ
}

void Monster::cutMonsterBlood(float delta)//�ɵ�����Ѫ
{
	float x = my_hero->getPositionX() - (this->getPositionX() + my_map->getPositionX());
	//�õ�����y�ľ��룬�ǵù��������Ҫ���ϵ�ͼ��  
	float y = my_hero->getPositionY() - (this->getPositionY() + my_map->getPositionY());

	//�ȼ�������Ӣ�۵ľ���  
	dis = sqrt(pow(x, 2) + pow(y, 2));
	if (my_hero->isAttacking == true)
		if (dis < 64)
			Monster_xue->cutBlood(3);
}

void  Monster::MonsterSeeRun()
{
	if (dis<100)
		return;
	this->SetAnimation("monster1/monsterwalk", 6, MonsterDirecton);//���Ŷ���  
	CCMoveBy *moveby1;
	if (MonsterDirecton == true)
	{
		moveby1 = CCMoveBy::create(4, ccp(-100, 0));

	}
	else
		moveby1 = CCMoveBy::create(4, ccp(100, 0));
	//�����ص�������Ѳ��·�����  
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Monster::StopAnimation));
	//������������  
	CCActionInterval* xunluo = CCSequence::create(moveby1, callFunc, NULL);
	this->runAction(xunluo);
}
//��������  

void Monster::StartListen(Hero* m_hero, CCNode* m_map)
{
	my_hero = m_hero;
	my_map = m_map;
	//nowStatus = nowStatus1;  ���ڵ��������� 
	this->schedule(schedule_selector(Monster::updateMonster), 2.0f);//ÿ��2��������  
	this->scheduleUpdate();//Ӣ��һ��������ӷ�Χ������׷��Ӣ�۴�  
	this->schedule(schedule_selector(Monster::cutHeroBlood), 0.2f); //0.2f�ж�һ��
	this->schedule(schedule_selector(Monster::cutMonsterBlood), 0.05f);
}
//��������,ÿ��2������  
void Monster::updateMonster(float delta)
{
	//�õ�����x�ľ���,�ǵù��������Ҫ���ϵ�ͼ��  
	float x = my_hero->getPositionX() - (this->getPositionX() + my_map->getPositionX());
	//�õ�����y�ľ��룬�ǵù��������Ҫ���ϵ�ͼ��  
	float y = my_hero->getPositionY() - (this->getPositionY() + my_map->getPositionY());
	//�ȼ�������Ӣ�۵ľ���  
	dis = sqrt(pow(x, 2) + pow(y, 2));
	if (dis >= 100)
	{
		if (!IsRunning)
			MonsterSeeRun();
	}
}

void Monster::update(float delta)
{
	if (dis<100)///��Ӣ�������Ŀ��ӷ�Χ�ڣ�����׷��Ӣ��  
		FollowRun(my_hero, my_map);
}

void Monster::getBloodStatus(localStatus* nowStatus1)
{
	nowStatus = nowStatus1;  //��mainlayer�г�ʼ��ʱ��ȡ
}