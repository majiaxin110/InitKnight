#ifndef __LOCALPLAY_SCENE_H__
#define __LOCALPLAY_SCENE_H__

#include "cocos2d.h"

class localPlay : public cocos2d::Scene
{
public:
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(localPlay);
};

#endif // __LOCALPLAY_SCENE_H__
