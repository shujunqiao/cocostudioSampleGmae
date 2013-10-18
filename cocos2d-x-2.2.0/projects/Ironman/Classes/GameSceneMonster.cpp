//
//  GameSceneMonster.cpp
//  Ironman
//
//  Created by Ken on 13-10-10.
//
//

#include "GameSceneMonster.h"
#include "GameScene.h"

bool GameSceneMonster::init()
{
	 int r = random(0, 1);
	  VisibleSize = CCDirector::sharedDirector()->getVisibleSize();
	  VisiblePosition  = CCDirector::sharedDirector()->getVisibleOrigin();
	  float height = ((float)random(0,VisiblePosition.y+200));
	  CCPoint aPosition = CCPointMake(VisibleSize.width,height);
	 switch (r)
	 {
		case 0:
		{
			MonsterGroundMoving(CCPointMake(VisibleSize.width,20));
		}
			break;
		case 1:
		{
			MonsterSkyMoving(aPosition);
		}
			break;
			/*
			case 1:
		{

		}
			break;
			*/
	 default:
		 break;
	 }

    return true;
}
void GameSceneMonster::MonsterGroundMoving(CCPoint position)
{
	CCArmature *armature = NULL;
	armature = cocos2d::extension::CCArmature::create("MonsterGroundMoving");
	armature->getAnimation()->playByIndex(0);
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(1.0f);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(position);
	//amaturePosition = armature->getPosition();
	addChild(armature);
	MonsterGroundAmature = armature;
	MonsterIndex = MonsterGround_enum;
	CCActionInterval * jumpAction = CCJumpTo::create(1.0,GameScene::shareGameScene()->playLayer->getPosition(),50,3);
	CCCallFunc * callBack = CCCallFuncND::create(this, callfuncND_selector(GameSceneMonster::JumpActionCallBack), (void*)0xbebabeba);
	CCFiniteTimeAction*  action = CCSequence::create(jumpAction,callBack,NULL);
    MonsterGroundAmature->runAction(action);
	this->scheduleUpdate();
}
void GameSceneMonster::MonsterSkyMoving(CCPoint position)
{
	CCArmature *armature = NULL;
	armature = cocos2d::extension::CCArmature::create("MonsterSkyMoving");
	armature->getAnimation()->playByIndex(0);
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(1.0f);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(position);
	addChild(armature);
	MonsterSkyAmature = armature;
	MonsterIndex = MonsterSky_enum;
	CCActionInterval * jumpAction = CCJumpTo::create(1.0,GameScene::shareGameScene()->playLayer->getPosition(),0,1);
	CCCallFunc * callBack = CCCallFuncND::create(this, callfuncND_selector(GameSceneMonster::JumpActionCallBack), (void*)0xbebabeba);
	CCFiniteTimeAction*  action = CCSequence::create(jumpAction,callBack,NULL);
    MonsterSkyAmature->runAction(action);
	this->scheduleUpdate();
}
void GameSceneMonster::MonsterGroundDestroyAction(CCPoint position)
{
	this->unscheduleUpdate();  
	CCArmature *armature = NULL;
	armature = cocos2d::extension::CCArmature::create("MonsterGroundAnimation");
	armature->getAnimation()->playByIndex(0);
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(1.0f);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(position);
	addChild(armature);
	MonsterGroundAmature = armature;
}
void GameSceneMonster::MonsterSkyDestroyAction(CCPoint position)
{
	this->unscheduleUpdate();  
	CCArmature *armature = NULL;
	armature = cocos2d::extension::CCArmature::create("MonsterSkyAnimation");
	armature->getAnimation()->playByIndex(0);
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(1.0f);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(position);
	addChild(armature);
	MonsterSkyAmature = armature;
}
void GameSceneMonster::MonsterDestroyAction()
{
	switch (MonsterIndex)
	 {
		case MonsterGround_enum:
		{
			MonsterGroundAmature->removeAllChildrenWithCleanup(false);
			MonsterGroundDestroyAction(MonsterGroundAmature->getPosition());
		}
			break;
		case MonsterSky_enum:
		{
			MonsterSkyAmature->removeAllChildrenWithCleanup(false);
			MonsterSkyDestroyAction(MonsterSkyAmature->getPosition());
		}
			break;
			/*
			case 1:
		{

		}
			break;
			*/
	 default:
		 break;
	 }
}
int GameSceneMonster::random(int start, int end)
{
	float i = CCRANDOM_0_1()*(end-start+1)+start;
	return (int)i;
}
void GameSceneMonster::JumpActionCallBack(CCNode* sender, void* data)
{
	 MonsterDestroyAction();
	 GameSceneMonster::init();
}
void GameSceneMonster::update(float dt)
{
	CCArmature * aAmature;
	switch (MonsterIndex)
	 {
		case MonsterGround_enum:
		{
			aAmature = MonsterGroundAmature;
		}
			break;
		case MonsterSky_enum:
		{
			aAmature = MonsterSkyAmature;
		}
			break;
			/*
			case 1:
		{

		}
			break;
			*/
	 default:
		 break;
	 }

	if (GameScene::shareGameScene()->playLayer->boundingBox().intersectsRect(aAmature->boundingBox()))
	{
		aAmature->stopAllActions();
		MonsterDestroyAction();
	    GameSceneMonster::init();
		this->unscheduleUpdate();  
	}
}