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
	this->unscheduleUpdate();  
	CCArmature *armature = NULL;
	armature = cocos2d::extension::CCArmature::create("MonsterGroundAnimation");
	armature->getAnimation()->playByIndex(0);
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(1.0f);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(position);
	addChild(armature);
	MonsterAmature = armature;
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
	MonsterAmature = armature;
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
		
	
//	CCLog("%f,%f,%f,%f",GameScene::shareGameScene()->playLayer->imManArmature->boundingBox().origin.x,GameScene::shareGameScene()->playLayer->imManArmature->boundingBox().origin.y,GameScene::shareGameScene()->playLayer->imManArmature->boundingBox().size.width,GameScene::shareGameScene()->playLayer->imManArmature->boundingBox().size.height);
	//CCLog("%f,%f,%f,%f",MonsterAmature->boundingBox().origin.x,MonsterAmature->boundingBox().origin.y,MonsterAmature->boundingBox().size.width,MonsterAmature->boundingBox().size.height);
	CCArmature * imManArmatureCopy = GameScene::shareGameScene()->playLayer->imManArmature;
	CCRect imManArmatureBounding= CCRectMake(imManArmatureCopy->getPosition().x-imManArmatureCopy->getContentSize().width/2,imManArmatureCopy->getPosition().y,imManArmatureCopy->getContentSize().width,imManArmatureCopy->getContentSize().height);
	CCRect MonsterAmatureBounding = CCRectMake(MonsterAmature->getPosition().x-MonsterAmature->getContentSize().width/2,MonsterAmature->getPosition().y,MonsterAmature->getContentSize().width,MonsterAmature->getContentSize().height);
	/*
	CCLog("imManArmatureBounding = %f,%f,%f,%f",imManArmatureCopy->getPosition().x-imManArmatureCopy->getContentSize().width/2,imManArmatureCopy->getPosition().y,imManArmatureCopy->getContentSize().width,imManArmatureCopy->getContentSize().height);
	CCLog("MonsterAmatureBounding = %f,%f,%f,%f",MonsterAmature->getPosition().x-MonsterAmature->getContentSize().width/2,MonsterAmature->getPosition().y,MonsterAmature->getContentSize().width,MonsterAmature->getContentSize().height);
	*/
	
	if (imManArmatureBounding.intersectsRect(MonsterAmatureBounding))
	{
		
		MonsterDestroyAction();
		GameScene::shareGameScene()->playLayer->imManArmatureBrood-=20;
		if(GameScene::shareGameScene()->playLayer->imManArmatureBrood<1)
		{
			GameScene::shareGameScene()->menuLayer->setBroodBarPercent(0);
			GameScene::shareGameScene()->playLayer->IMDeath();
			return;
		}

		GameScene::shareGameScene()->menuLayer->setBroodBarPercent(GameScene::shareGameScene()->playLayer->imManArmatureBrood);
	    GameSceneMonster::init();
	}
}

void GameSceneMonster::draw()
{
	/*
	CCPoint point1 = CCPointMake(GameScene::shareGameScene()->playLayer->imManArmature->boundingBox().origin.x,GameScene::shareGameScene()->playLayer->imManArmature->boundingBox().origin.y);
	CCPoint point2 = CCPointMake(GameScene::shareGameScene()->playLayer->imManArmature->boundingBox().origin.x+GameScene::shareGameScene()->playLayer->imManArmature->boundingBox().size.width,GameScene::shareGameScene()->playLayer->imManArmature->boundingBox().origin.y);
	CCPoint point3 = CCPointMake(GameScene::shareGameScene()->playLayer->imManArmature->boundingBox().origin.x+GameScene::shareGameScene()->playLayer->imManArmature->boundingBox().size.width,GameScene::shareGameScene()->playLayer->imManArmature->boundingBox().origin.y+GameScene::shareGameScene()->playLayer->imManArmature->boundingBox().size.height);
	CCPoint point4 = CCPointMake(GameScene::shareGameScene()->playLayer->imManArmature->boundingBox().origin.x+GameScene::shareGameScene()->playLayer->imManArmature->boundingBox().size.width,GameScene::shareGameScene()->playLayer->imManArmature->boundingBox().origin.y);
	CCLog("(%f,%f),(%f,%f),(%f,%f),(%f,%f),",point1.x,point1.y,point2.x,point2.y,point3.x,point3.y,point4.x,point4.y);
	*/
	CCArmature * imManArmatureCopy = GameScene::shareGameScene()->playLayer->imManArmature;
	CCPoint point1 = CCPointMake(imManArmatureCopy->getPosition().x-imManArmatureCopy->getContentSize().width/2,imManArmatureCopy->getPosition().y);
		CCPoint point2 = CCPointMake(imManArmatureCopy->getPosition().x+imManArmatureCopy->getContentSize().width/2,imManArmatureCopy->getPosition().y);
		CCPoint point3 = CCPointMake(imManArmatureCopy->getPosition().x+imManArmatureCopy->getContentSize().width/2,imManArmatureCopy->getPosition().y+imManArmatureCopy->getContentSize().height);
		CCPoint point4 = CCPointMake(imManArmatureCopy->getPosition().x-imManArmatureCopy->getContentSize().width/2,imManArmatureCopy->getPosition().y+imManArmatureCopy->getContentSize().height);

	    //画一个多边形  
    ccDrawColor4B(255, 255, 0, 255);  
    glLineWidth(1);  
    CCPoint vertices1[] = { point1, point2, point3, point4};  
    ccDrawPoly( vertices1, 4, true//是否封闭  
        ); 


	CCPoint point5 = CCPointMake(MonsterAmature->getPosition().x-MonsterAmature->getContentSize().width/2,MonsterAmature->getPosition().y);
		CCPoint point6 = CCPointMake(MonsterAmature->getPosition().x+MonsterAmature->getContentSize().width/2,MonsterAmature->getPosition().y);
		CCPoint point7 = CCPointMake(MonsterAmature->getPosition().x+MonsterAmature->getContentSize().width/2,MonsterAmature->getPosition().y+MonsterAmature->getContentSize().height);
		CCPoint point8 = CCPointMake(MonsterAmature->getPosition().x-MonsterAmature->getContentSize().width/2,MonsterAmature->getPosition().y+MonsterAmature->getContentSize().height);

	 CCPoint vertices2[] = { point5, point6, point7, point8};  
    ccDrawPoly( vertices2, 4, true//是否封闭  
        ); 

}
