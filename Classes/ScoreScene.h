#ifndef __SCORE_SCENE_H__
#define __SCORE_SCENE_H__

#include "cocos2d.h"
#include <string>
#include <thread>

class ScoreScene : public cocos2d::Scene
{
private:
	int playerScore;
	//std::string playerName;
	cocos2d::Label* statusShow;
	//std::thread* scoThread;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	//virtual void onEnter();
	//virtual void onExit();

	void putBackImage(const char* source);
	void setScore(int sc);
	
	//const std::string& getPlayerName();
	int getPlayerScore();
	cocos2d::Label* getStatusShow();

	//int uploadScore();
	// implement the "static create()" method maddnually
	CREATE_FUNC(ScoreScene);
};

#endif // __Lose_SCENE_H__
