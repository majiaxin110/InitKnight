/*#include "Monster.h"
#include "hero.h"
#include "localPlayScene.h"


USING_NS_CC;

Monster::Monster()
{

	isMoving = false;
	isAttacking = false;
	attackPower = 1;
	blood = 100;
	heroDirection = 0;
	monsterSprite = nullptr;
	moveSpeed = 2.5f;
}

void Monster::initMonsterSprite()  //��������
{
	this->monsterSprite = Sprite::create("carman1.png");
	this->addChild(monsterSprite);
}

float Monster::getMoveSpeed()
{
	return moveSpeed;
}

/*void Monster::setRunAnimation(bool runDriection)
{

}

void Hero::setRunAnimation(bool runDirection)
{
//��ת������
if (heroDirection != runDirection)
{
heroDirection = runDirection;
cHeroSprite->setFlippedX(runDirection);
}
if (isMoving || cHeroSprite->getNumberOfRunningActions() > 0)
return;
Animation *animation = Animation::create();
log("run move anime");
for (int i = 1; i <= 4; i++)
{
__String *frameName = __String::createWithFormat("knightAnime/run_%d.png", i);
//SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
animation->addSpriteFrameWithFile(frameName->getCString());
}
animation->setLoops(-1);
animation->setDelayPerUnit(0.1f);
Animate *action = Animate::create(animation);
action->setTag(101);
cHeroSprite->runAction(RepeatForever::create(action));

isMoving = true;
}

void Hero::setAttackAnimation()
{
if (isAttacking || cHeroSprite->getNumberOfRunningActions() > 0)
return;
isAttacking = true;
Animation *animation = Animation::create();
log("run attack anime");
for (int i = 1; i <= 4; i++)
{
__String *frameName = __String::createWithFormat("knightAnime/attackKnife_%d.png", i);
//SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
animation->addSpriteFrameWithFile(frameName->getCString());
}
animation->setLoops(1);
animation->setDelayPerUnit(0.1f);
Animate *action = Animate::create(animation);
action->setTag(102);
cHeroSprite->runAction(action);
isAttacking = false;
}

void Hero::setUpAnimation()
{
if (isAttacking)
return;
isAttacking = true;
Animation *animation = Animation::create();
log("run up anime");
for (int i = 1; i <= 5; i++)
{
__String *frameName = __String::createWithFormat("knightAnime/up_%d.png", i);
//SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
animation->addSpriteFrameWithFile(frameName->getCString());
}
animation->setLoops(1);
animation->setDelayPerUnit(0.1f);
Animate *action = Animate::create(animation);
action->setTag(103);
cHeroSprite->runAction(action);
isAttacking = false;
}
void Hero::stopAllAnimation()
{
if (!isMoving)
return;
cHeroSprite->stopActionByTag(101);
this->removeChild(cHeroSprite, TRUE);//��ԭ���ľ���ɾ����
cHeroSprite = Sprite::create("knight.png");//�ָ�����ԭ������ͼ����
cHeroSprite->setFlippedX(heroDirection);
this->addChild(cHeroSprite);
isMoving = false;
}
*/
