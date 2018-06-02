#ifndef __LOCALPLAY_SCENE_H__
#define __LOCALPLAY_SCENE_H__

#include "cocos2d.h"
#include "hero.h"
#include <map>

class localPlay : public cocos2d::Scene
{
private:
	cocos2d::TMXTiledMap *tileMap;
	cocos2d::TMXLayer *barriers;//�ϰ���
	cocos2d::Sprite *player;
	Hero* hero;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyStatus; //���̸������������µ�״̬
public:
	

	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onEnter();

	cocos2d::EventKeyboard::KeyCode whichPressed(); //�ĸ�����ǰ�ǰ���״̬
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 pos); //ת����Ƭ����
	bool isCollid(cocos2d::Vec2 pos);//����Ƿ����ͼǽ����ײ
	void setHero(cocos2d::EventKeyboard::KeyCode keyCode);//����hero
	void update(float delta) override;

	// implement the "static create()" method manually
	CREATE_FUNC(localPlay);
};

#endif // __LOCALPLAY_SCENE_H_
