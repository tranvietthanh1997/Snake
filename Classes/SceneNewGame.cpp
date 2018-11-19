#include "SceneNewGame.h"
#include "MenuScreen.h"
#include "cocos2d.h"
#include "Rock.h"
#include "Snake.h"

USING_NS_CC;
Snake *snake;
float xMovement;
int framesCount; 
float newPosX;

Scene* SceneNewGame::createScene()
{
	return SceneNewGame::create();
}

bool SceneNewGame::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Add button back
	auto closeItem1 = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		[](Ref *event) {
		Director::getInstance()->replaceScene(TransitionFlipX::create(0.5, MenuScreen::createScene()));
	});

	closeItem1->setPosition(visibleSize.width - closeItem1->getContentSize().width / 2, visibleSize.height - closeItem1->getContentSize().height / 2);

	auto menuImage = Menu::create(closeItem1, nullptr);
	menuImage->setPosition(Vec2::ZERO);
	addChild(menuImage);

	auto screenSize = Director::getInstance()->getVisibleSize();

	framesCount = 0;	

	snake = new Snake(this);
	snake->Init();
	
	//KeyBoard listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(SceneNewGame::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(SceneNewGame::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	int typeRock;
	for (int i = 0; i < MAX_ROCK; i++)
	{
		typeRock = 1;
		Rock* rock = new Rock(this, typeRock);
		rock->setType(typeRock);
		rock->setAlive(false);
		mRocks.push_back(rock);
	}
	
	scheduleUpdate();
	return true;	
}

void SceneNewGame::update(float delta)
{
	framesCount++;

	snake->Update();
	
	newPosX = snake->GetPosistion().x + (xMovement * 10.f);
	snake->setPosition(Vec2(newPosX, snake->GetPosistion().y));
	//log("X %f", snake->GetPosistion().x);
	
	//generating rock
	if (framesCount % ROCK_GENERATING_STEP == 0)
	{
		GenerateRock();
	}	
	
	//update rock
	for (int i = 0; i < mRocks.size(); i++)
	{
		Rock *r = mRocks.at(i);
		if (r->isAlive())
		{
			r->Update();			
		}
	}

	snake->Colission(mRocks);
}

void SceneNewGame::GenerateRock()
{
	for (int i = 0; i < mRocks.size(); i++)
	{
		Rock *r = mRocks.at(i);
		if (!r->isAlive())
		{
			r->setAlive(true);
			r->Init();
			break;
		}
	}
}

void SceneNewGame::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:	
		xMovement--;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:	
		xMovement++;
		break;
	}
}

void SceneNewGame::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:	
		xMovement++;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:	
		xMovement--;
		break;
	}
}
