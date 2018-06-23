#pragma once
#include "cocos2d.h"
USING_NS_CC;

enum DataType
{
	POSITION
};

struct GameData
{
	int dataSize;
	DataType dataType;
	Vec2 position;
};

struct receiveTemp
{
	Vec2 receivePosition;
};
