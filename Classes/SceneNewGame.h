#pragma once
#include "cocos2d.h"
#include "Define.h"
#include "Rock.h"
class SceneNewGame : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float delta);
	CREATE_FUNC(SceneNewGame);
	void GenerateRock();

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void calculateScore();
private:
	std::vector<Rock*> mRocks;
};


