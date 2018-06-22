#pragma once  
#include "cocos2d.h"  
#include "bloodProgress.h"
#include <vector>
#include <string>

USING_NS_CC;

class localStatus : public cocos2d::Layer
{
private:
	std::vector<ProgressView*> cBloodProgress;
	Label* pointLabel;
	int playerPoint;
	std::string playerName;
public:
	virtual bool init();

	bool cutHeroBlood(float amount);
	void addHeroBlood(float amount);

	void addPoint(int add);//���ӵ÷�
	void setPlayerName(const char* str);

	//��NPC�Ի���ͼ��
	void showOldNPCDialog();
	void removeOldNPCDialog();
	void showPaojieDialog();
	void removePaoNPCDialog();

	void changeToLoseScene();
	void changeToWinScene();

	CREATE_FUNC(localStatus);
};  
