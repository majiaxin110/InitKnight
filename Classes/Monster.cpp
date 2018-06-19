#include "Monster.h"
#include "localPlayMainLayer.h"
USING_NS_CC;

Monster::Monster(void)
{
	IsRunning = false;//û�ڷŶ���  
	MonsterDirecton = TRUE;//�����˶�  
	IsAttack = false;
	Monster_xue = NULL; //�����ʼ��
	senseDistance = 200; //׷�پ���
}

Monster::~Monster(void)
{

}

Sprite* Monster::GetSprite()
{
	return m_MonsterSprite;
}

void Monster::InitMonsterSprite(char *name)  //����Ѫ���Ĺ���
{
	Monster_name.assign(name);
	log(Monster_name.c_str());
	this->m_MonsterSprite = Sprite::create((Monster_name + "/monsterwalk1.png"));
	if (Monster_name == "monster1")
		m_MonsterSprite->setFlippedX(MonsterDirecton);  //ͼƬ��ʼ����
	else
		m_MonsterSprite->setFlippedX(!MonsterDirecton);
	this->addChild(m_MonsterSprite);
	isDied = false;
}

void Monster::InitMonsterSprite(char *name, char *xue_back, char* xue_fore,float totalPro)  //��Ѫ���Ĺ���  ��������
{
	InitMonsterSprite(name);
	//���ù����Ѫ��   
	Monster_xue = new ProgressView();
	Monster_xue->setPosition(Vec2(m_MonsterSprite->getPositionX() + 25, m_MonsterSprite->getPositionY() + 50));//�����ڹ�����ͷ    																											  //Monster_xue->setScale(2.2f);    
	Monster_xue->initProgressView(xue_back, xue_fore);
	Monster_xue->setTotalProgress(totalPro);
	Monster_xue->setCurrentProgress(totalPro);
	this->addChild(Monster_xue);
}

void Monster::SetAnimation(const char *name_each, unsigned int num, bool run_directon)
{
	if (MonsterDirecton != run_directon)
	{
		MonsterDirecton = run_directon;
		m_MonsterSprite->setFlippedX(run_directon);//���ӣ�
	}
	if (IsRunning || IsAttack)
		return;
	Animation* animation = Animation::create();
	for (unsigned int i = 1; i <= num; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "%s%d.png", name_each, i);
		log(szName);
		animation->addSpriteFrameWithFile(szName); //���ض�����֡    
	}
	animation->setDelayPerUnit(2.8f / 14.0f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(-1); //����ѭ��  
							 //��������װ��һ������  
	Animate* act = Animate::create(animation);
	m_MonsterSprite->runAction(act);
	IsRunning = true;

}
void Monster::StopAnimation()
{
	if (!IsRunning)
		return;
	m_MonsterSprite->stopAllActions();//��ǰ����ֹͣ���ж���  
									  //�ָ�����ԭ���ĳ�ʼ����ͼ   
	this->removeChild(m_MonsterSprite, TRUE);//��ԭ���ľ���ɾ����  
	m_MonsterSprite = Sprite::create(Monster_name+"/monsterwalk1.png");//�ָ�����ԭ������ͼ����  
	m_MonsterSprite->setFlippedX(!MonsterDirecton);  //���ӣ�
	this->addChild(m_MonsterSprite);
	IsRunning = false;
	MonsterDirecton = !MonsterDirecton;  //ÿ��ͣ�¶������÷���
}
void Monster::AttackAnimation(const char *name_each, const unsigned int num, bool run_directon)
{
	if (IsAttack || IsRunning)
		return;
	Animation* animation = Animation::create();
	for (unsigned int i = 1; i <= num; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "%s%d.png", name_each, i);
		log(szName);
		animation->addSpriteFrameWithFile(szName); //���ض�����֡    
	}
	animation->setDelayPerUnit(2.0f / 14.0f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(1); //����ѭ��1��    
							//��������װ��һ������  
	Animate* act = Animate::create(animation);
	//�����ص��������������������AttackEnd()  
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Monster::AttackEnd));
	//������������
	ActionInterval* attackact = Sequence::create(act, callFunc, NULL);

	m_MonsterSprite->runAction(attackact);
	IsAttack = true;

}
void Monster::AttackEnd()
{
	//�ָ�����ԭ���ĳ�ʼ����ͼ   
	this->removeChild(m_MonsterSprite, TRUE);//��ԭ���ľ���ɾ����  
	m_MonsterSprite = Sprite::create((Monster_name+"/monsterwalk1.png").c_str());//�ָ�����ԭ������ͼ����  
	m_MonsterSprite->setFlippedX(!MonsterDirecton);  //��ת����
	this->addChild(m_MonsterSprite);
	IsAttack = false;
}

void Monster::FollowRun(Hero* m_hero, Node* m_map)
{
	//�õ�����x�ľ���,�ǵù��������Ҫ���ϵ�ͼ��  
	float x = m_hero->getPositionX() - (this->getPositionX() + m_map->getPositionX());
	//�õ�����y�ľ��룬�ǵù��������Ҫ���ϵ�ͼ��  
	float y = m_hero->getPositionY() - (this->getPositionY() + m_map->getPositionY());

	//�ȼ�������Ӣ�۵ľ���  
	dis = sqrt(pow(x, 2) + pow(y, 2));

	if (dis >= senseDistance)//��������Ӣ�۾��볬��100
		return;
	if (dis <= 64)//�ڹ��﹥����Χ�ڣ�����ֹͣ�ƶ�  
	{
		this->StopAnimation();//ֹͣ�ܶ�
		JudgeAttack();//�ض���������
		return;
	}
	std::string aniName(Monster_name);
	aniName = aniName + "/monsterwalk";

	if (x<-64)//�жϹ���������Ӣ�۵ľ���  
	{

		MonsterDirecton = true;
		m_MonsterSprite->setFlippedX(MonsterDirecton);//���÷���  ���ӣ�
		if (IsAttack)
			return;
		this->setPosition(this->getPositionX() - 0.8, this->getPositionY());//������Ӣ���ƶ�  
		this->SetAnimation(aniName.c_str(), 6, MonsterDirecton);//���Ŷ���  

	}
	else if (x>64)
	{

		MonsterDirecton = false;
		m_MonsterSprite->setFlippedX(MonsterDirecton);//���÷���  ���ӣ�
		if (IsAttack)
			return;
		this->setPosition(this->getPositionX() + 0.8, this->getPositionY());
		
		this->SetAnimation(aniName.c_str(), 6, MonsterDirecton);//���Ŷ���  
	}
	else if (x <= 64)//����M���˺�Ӣ�������64����ʱ����ʼ�ƶ�����������  
	{

		if (m_hero->getPositionY()>this->getPositionY())
		{
			m_MonsterSprite->setFlippedX(MonsterDirecton);//���÷���  ���ӣ�
			if (IsAttack)
				return;
			this->setPosition(this->getPositionX(), this->getPositionY() + 0.8);
			this->SetAnimation(aniName.c_str(), 6, MonsterDirecton);//���Ŷ���  
		}
		else if (m_hero->getPositionY()<this->getPositionY())
		{
			m_MonsterSprite->setFlippedX(MonsterDirecton);//���÷���  ���ӣ�
			if (IsAttack)
				return;
			this->setPosition(this->getPositionX(), this->getPositionY() - 0.8);
			this->SetAnimation(aniName.c_str(), 6, MonsterDirecton);//���Ŷ���  //knightAnime/run_%d.png
		}
	}

}
void Monster::JudgeAttack()//�ж�����
{
	srand((UINT)GetCurrentTime());
	int x = rand() % 100;
	if (x > 64)
	{
		m_MonsterSprite->setFlippedX(!MonsterDirecton);
		std::string aniName(Monster_name);
		aniName = aniName + "/monsterattack";
		this->AttackAnimation(aniName.c_str(), 6, MonsterDirecton);
	}
	//this->schedule(schedule_selector(Monster::cutHeroBlood), 1.0f); 
	//this->schedule(schedule_selector(Monster::updateMonster), 2.0f);
	//}

}

void Monster::cutHeroBlood(float delta)
{
	if (IsAttack == 1)  //���������ڹ���
		nowStatus->cutHeroBlood(0.7);  //�ɵ�Ѫ
}

void Monster::heroCutMonsterBlood(float delta)//Ӣ�۸ɵ�����Ѫ
{
	float x = my_hero->getPositionX() - (this->getPositionX() + my_map->getPositionX());
	//�õ�����y�ľ��룬�ǵù��������Ҫ���ϵ�ͼ��  
	float y = my_hero->getPositionY() - (this->getPositionY() + my_map->getPositionY());

	//�ȼ�������Ӣ�۵ľ���  
	dis = sqrt(pow(x, 2) + pow(y, 2));
	if (my_hero->isAttacking == true && !my_hero->getAttackMode() && dis<64)
		if (this->getHurt(5))
			isDied = true;
}

void  Monster::MonsterSeeRun()
{
	if (dis < senseDistance)
		return;
	this->SetAnimation((Monster_name+"/monsterwalk").c_str(), 6, MonsterDirecton);//���Ŷ���  
	MoveBy *moveby1;
	if (MonsterDirecton == true)
	{
		moveby1 = MoveBy::create(4, Vec2(-100, 0));
	}
	else
		moveby1 = MoveBy::create(4, Vec2(100, 0));
	//�����ص�������Ѳ��·�����  
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Monster::StopAnimation));
	//������������  
	ActionInterval* xunluo = Sequence::create(moveby1, callFunc, NULL);
	this->runAction(xunluo);
}
//��������  

void Monster::StartListen(Hero* m_hero, Node* m_map)
{
	my_hero = m_hero;
	my_map = m_map;
	//nowStatus = nowStatus1;  ���ڵ��������� 
	this->schedule(schedule_selector(Monster::updateMonster), 1.0f);//ÿ��2��������  
	this->scheduleUpdate();//Ӣ��һ��������ӷ�Χ������׷��Ӣ�۴�  
	this->schedule(schedule_selector(Monster::cutHeroBlood), 0.2f); //0.2f�ж�һ��
	this->schedule(schedule_selector(Monster::heroCutMonsterBlood), 0.05f);
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
	if (dis >= senseDistance)
	{
		if (!IsRunning)
			MonsterSeeRun();
	}
}

void Monster::update(float delta)
{
	if (dis < senseDistance)//��Ӣ�������Ŀ��ӷ�Χ�ڣ�����׷��Ӣ��  
		FollowRun(my_hero, my_map);
}

void Monster::getBloodStatus(localStatus* nowStatus1)
{
	nowStatus = nowStatus1;  //��mainlayer�г�ʼ��ʱ��ȡ
}

bool Monster::getHurt(float delta)
{
	return Monster_xue->cutBlood(delta);
}

float Monster::getSense()
{
	return senseDistance;
}

void Monster::setSense(float sens)
{
	senseDistance = sens;
}
