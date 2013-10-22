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
	armature->setPosition(position);
	addChild(armature);
	MonsterAmature = armature;
	MonsterIndex = MonsterGround_enum;
	CCPoint movePoint = CCPointMake(GameScene::shareGameScene()->playLayer->imManArmature->getPosition().x-100,GameScene::shareGameScene()->playLayer->imManArmature->getPosition().y);
	CCActionInterval * jumpAction = CCJumpTo::create(3.0,movePoint,50,3);
	CCCallFunc * callBack = CCCallFuncND::create(this, callfuncND_selector(GameSceneMonster::JumpActionCallBack), (void*)0xbebabeba);
	CCFiniteTimeAction*  action = CCSequence::create(jumpAction,callBack,NULL);
    MonsterAmature->runAction(action);
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
	armature->setPosition(position);
	addChild(armature);
	MonsterAmature = armature;
	MonsterIndex = MonsterSky_enum;
	CCPoint movePoint = CCPointMake(GameScene::shareGameScene()->playLayer->imManArmature->getPosition().x-100,GameScene::shareGameScene()->playLayer->imManArmature->getPosition().y);
	CCActionInterval * jumpAction = CCJumpTo::create(3.0,movePoint,0,1);
	CCCallFunc * callBack = CCCallFuncND::create(this, callfuncND_selector(GameSceneMonster::JumpActionCallBack), (void*)0xbebabeba);
	CCFiniteTimeAction*  action = CCSequence::create(jumpAction,callBack,NULL);
    MonsterAmature->runAction(action);
	this->scheduleUpdate();
}
void GameSceneMonster::MonsterGroundDestroyAction(CCPoint position)
{  
	CCArmature *armature = NULL;
	armature = cocos2d::extension::CCArmature::create("MonsterGroundAnimation");
	armature->getAnimation()->playByIndex(0);
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(1.0f);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(position);
	addChild(armature);
	MonsterAmature = armature;
	MonsterAmature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(GameSceneMonster::DestroyActionActionEnded));
}
void GameSceneMonster::MonsterSkyDestroyAction(CCPoint position)
{
	CCArmature *armature = NULL;
	armature = cocos2d::extension::CCArmature::create("MonsterSkyAnimation");
	armature->getAnimation()->playByIndex(0);
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(1.0f);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(position);
	addChild(armature);
	MonsterAmature = armature;
	MonsterAmature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(GameSceneMonster::DestroyActionActionEnded));
}
void GameSceneMonster::DestroyActionActionEnded(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID)
{

	std::string id = movementID;
    if (movementType == COMPLETE || movementType == LOOP_COMPLETE)
    {
		this->unscheduleUpdate();
		GameSceneMonster::init();
    }
	
}
void GameSceneMonster::MonsterDestroyAction()
{
	MonsterAmature->stopAllActions();
	MonsterAmature->removeAllChildrenWithCleanup(false);

	switch (MonsterIndex)
	 {
		case MonsterGround_enum:
		{
			MonsterGroundDestroyAction(MonsterAmature->getPosition());
		}
			break;
		case MonsterSky_enum:
		{
			MonsterSkyDestroyAction(MonsterAmature->getPosition());
		}
			break;
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
	this->unscheduleUpdate(); 
	 MonsterDestroyAction();
	 GameSceneMonster::init();
}
void GameSceneMonster::update(float dt)
{
	CCArmature * imManArmature = GameScene::shareGameScene()->playLayer->imManArmature;
	int actionNum = GameScene::shareGameScene()->playLayer->actionNum;
	if(actionNum == GameScene::shareGameScene()->playLayer->ACTION_RUN)
	{
		GameScene::shareGameScene()->playLayer->playerBoundingBox = CCRectMake(imManArmature->getPosition().x-imManArmature->getContentSize().width/2,imManArmature->getPosition().y,imManArmature->getContentSize().width,imManArmature->getContentSize().height);
	}
	else if(actionNum == GameScene::shareGameScene()->playLayer->ACTION_STAND_JUMP)
	{
		GameScene::shareGameScene()->playLayer->playerBoundingBox = CCRectMake(imManArmature->getPosition().x-imManArmature->getContentSize().width/2,imManArmature->getPosition().y,imManArmature->getContentSize().width,imManArmature->getContentSize().height);
	}
	else if(actionNum == GameScene::shareGameScene()->playLayer->ACTION_RUN_JUMP)
	{
		GameScene::shareGameScene()->playLayer->playerBoundingBox = CCRectMake(imManArmature->getPosition().x-imManArmature->getContentSize().width/2,imManArmature->getPosition().y,imManArmature->getContentSize().width,imManArmature->getContentSize().height);
	}
	else if(actionNum == GameScene::shareGameScene()->playLayer->ACTION_RUN_STOP)
	{
		GameScene::shareGameScene()->playLayer->playerBoundingBox = CCRectMake(imManArmature->getPosition().x-imManArmature->getContentSize().width/2+40,imManArmature->getPosition().y,imManArmature->getContentSize().width-110,imManArmature->getContentSize().height-45);
	}
	else if(actionNum == GameScene::shareGameScene()->playLayer->ACTION_RUN_ATTACK)
	{
		GameScene::shareGameScene()->playLayer->playerBoundingBox = CCRectMake(imManArmature->getPosition().x-imManArmature->getContentSize().width/2,imManArmature->getPosition().y,imManArmature->getContentSize().width,imManArmature->getContentSize().height);

	}
	else if(actionNum == GameScene::shareGameScene()->playLayer->ACTION_STAND_ATTACK)
	{
		GameScene::shareGameScene()->playLayer->playerBoundingBox = CCRectMake(imManArmature->getPosition().x-imManArmature->getContentSize().width/2,imManArmature->getPosition().y,imManArmature->getContentSize().width,imManArmature->getContentSize().height);

	}
	else if(actionNum == GameScene::shareGameScene()->playLayer->ACTION_DEATH)
	{
		GameScene::shareGameScene()->playLayer->playerBoundingBox = CCRectMake(imManArmature->getPosition().x-imManArmature->getContentSize().width/2,imManArmature->getPosition().y,imManArmature->getContentSize().width,imManArmature->getContentSize().height);
	}

	if(MonsterIndex == MonsterGround_enum)
	{
		MonsterAmatureBoundingBox = CCRectMake(MonsterAmature->getPosition().x-MonsterAmature->getContentSize().width/2+25,MonsterAmature->getPosition().y+21,MonsterAmature->getContentSize().width-50,MonsterAmature->getContentSize().height-48);
	}
	else if(MonsterIndex == MonsterSky_enum)
	{
		MonsterAmatureBoundingBox = CCRectMake(MonsterAmature->getPosition().x-MonsterAmature->getContentSize().width/2+25,MonsterAmature->getPosition().y+21,MonsterAmature->getContentSize().width-50,MonsterAmature->getContentSize().height-48);
	}


	if (GameScene::shareGameScene()->playLayer->playerBoundingBox.intersectsRect(MonsterAmatureBoundingBox))
	{
		MonsterDestroyAction();
		GameScene::shareGameScene()->playLayer->imManArmatureBrood-=1;
		if(GameScene::shareGameScene()->playLayer->imManArmatureBrood<1)
		{
			GameScene::shareGameScene()->menuLayer->setBroodBarPercent(0);
			this->unscheduleUpdate();
			GameScene::shareGameScene()->playLayer->IMDeath();
			return;
		}

		GameScene::shareGameScene()->menuLayer->setBroodBarPercent(GameScene::shareGameScene()->playLayer->imManArmatureBrood);
	
	}
}

void GameSceneMonster::draw()
{
	CCRect playerBoundingBoxCopy = GameScene::shareGameScene()->playLayer->playerBoundingBox;
	float playerBoundingBoxX = playerBoundingBoxCopy.origin.x;
	float playerBoundingBoxY = playerBoundingBoxCopy.origin.y;
	float playerBoundingBoxWidth = playerBoundingBoxCopy.size.width;
	float playerBoundingBoxHeight = playerBoundingBoxCopy.size.height;
	CCPoint point1 = CCPointMake(playerBoundingBoxX,playerBoundingBoxY);
	CCPoint point2 = CCPointMake(playerBoundingBoxX+playerBoundingBoxWidth,playerBoundingBoxY);
	CCPoint point3 = CCPointMake(playerBoundingBoxX+playerBoundingBoxWidth,playerBoundingBoxY+playerBoundingBoxHeight);
	CCPoint point4 = CCPointMake(playerBoundingBoxX,playerBoundingBoxY+playerBoundingBoxHeight);

	    //画一个多边形  
    ccDrawColor4B(255, 255, 0, 255);  
    glLineWidth(1);  
    CCPoint vertices1[] = { point1, point2, point3, point4};  
    ccDrawPoly( vertices1, 4, true//是否封闭  
        ); 

	float MonsterAmatureBoundingBoxX = MonsterAmatureBoundingBox.origin.x;
	float MonsterAmatureBoundingBoxY = MonsterAmatureBoundingBox.origin.y;
	float MonsterAmatureBoundingBoxWidth = MonsterAmatureBoundingBox.size.width;
	float MonsterAmatureBoundingBoxHeight = MonsterAmatureBoundingBox.size.height;

	CCPoint point5 = CCPointMake(MonsterAmatureBoundingBoxX,MonsterAmatureBoundingBoxY);
	CCPoint point6 = CCPointMake(MonsterAmatureBoundingBoxX+MonsterAmatureBoundingBoxWidth,MonsterAmatureBoundingBoxY);
	CCPoint point7 = CCPointMake(MonsterAmatureBoundingBoxX+MonsterAmatureBoundingBoxWidth,MonsterAmatureBoundingBoxY+MonsterAmatureBoundingBoxHeight);
	CCPoint point8 = CCPointMake(MonsterAmatureBoundingBoxX,MonsterAmatureBoundingBoxY+MonsterAmatureBoundingBoxHeight);

	CCPoint vertices2[] = { point5, point6, point7, point8};  
    ccDrawPoly( vertices2, 4, true//是否封闭  
        ); 

}
