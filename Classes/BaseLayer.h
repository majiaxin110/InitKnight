#pragma once
#include "cocos2d.h"
#include <vector>
#include "Bullet.h"
#include "ipconfig.h"
#include <string>
USING_NS_CC;



enum DataType
{
	POSITION,
	ATTACK,
};

struct GameData
{
	int dataSize;
	DataType dataType;
	Vec2 position;
	int heroface;
	bool bulAttack;
	float hero2Blood;
	float heroBlood;
};

struct receiveTemp
{
	Vec2 receivePosition;
	int heroface;
	bool isNeedBullet;
	float hero2Progress;
	float heroProgress;
};
