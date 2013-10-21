//
//  GameScenePlayLayer.cpp
//  Ironman
//
//  Created by Ken on 13-10-10.
//
//

#include "GameScenePlayLayer.h"
#include "GameScene.h"
#define ANIME_RUN 0
#define ANIME_JUMP 0
#define PLAYER_SCALE 0.6f
bool GameScenePlayLayer::init()
{
	touchTime = 0;
	imManArmatureBrood = 100;
	
	monsterGroundAmount = 0;
    monsterSkyAmount = 0;

	this->IMCrouch();
	this->setTouchEnabled(true);
	actionNum = ACTION_CROUCH;
    
    return true;
}

void GameScenePlayLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

void GameScenePlayLayer::runJumpActionCallBack(CCNode* sender, void* data)
{
	imManArmature->stopAllActions();
    imManArmature->removeFromParentAndCleanup(false);
	if(0xbebabebb ==(unsigned int) data)
	{
		 this ->IMRunning();
	}
	else
	{
		this ->IMRunningStop();
	}
}

void GameScenePlayLayer::standJumpActionCallBack(CCNode* sender, void* data)
{
	imManArmature->stopAllActions();
    imManArmature->removeFromParentAndCleanup(false);
    this ->IMRunningStop();
}

void GameScenePlayLayer::menuCloseCallback(CCObject* pSender)
{
    CCActionInterval * splitCols = CCMoveTo::create(1.0,CCPointMake(imManArmature->getPosition().x+300, imManArmature->getPosition().y));
    imManArmature->runAction(splitCols);
}

bool GameScenePlayLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    m_tBeginPos = pTouch->getLocation();
	return true;
}

void GameScenePlayLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	touchTime++;	
}

void GameScenePlayLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
	if(touchTime>30)
	{
		touchTime = 0;
		return;
	}

    CCPoint touchLocation = pTouch->getLocation();
	
	if(touchTime<2)
	{
		if(actionNum != ACTION_RUN && actionNum != ACTION_RUN_STOP)
			return;

		imManArmature->stopAllActions();
		imManArmature->removeFromParentAndCleanup(false);
		if(actionNum == ACTION_RUN)
		{
			this ->IMRunAttack(touchLocation);
		}
		else if(actionNum == ACTION_RUN_STOP)
		{
			this ->IMStandAttack(touchLocation);
		}
		
		touchTime = 0;
		return;
	}

    float nMoveX = touchLocation.x - m_tBeginPos.x;
	float nMoveY = touchLocation.y - m_tBeginPos.y;
	int radian = 10;
	touchTime = 0;

	if(nMoveX>10 && fabs(tan(nMoveY/nMoveX))<fabs(sqrt(3)/radian))
	{
		if(actionNum == ACTION_RUN)
			return;
		imManArmature->stopAllActions();
		imManArmature->removeFromParentAndCleanup(false);
		this ->IMRunning();
	}
    
	if(nMoveX<-10 && fabs(tan(nMoveY/nMoveX))<fabs(sqrt(3)/radian))
	{
		if(actionNum == ACTION_RUN_STOP)
			return;
		imManArmature->stopAllActions();
		imManArmature->removeFromParentAndCleanup(false);
		this ->IMRunningStop();
	}
    
	if(nMoveY>10 && fabs(tan(nMoveY/nMoveX))>fabs(sqrt(3)/radian))
	{
		if(actionNum == ACTION_STAND_JUMP || actionNum == ACTION_RUN_JUMP || actionNum ==ACTION_CROUCH_JUMP)
			return;
        
        std::string armatureName = imManArmature->getName();
		imManArmature->stopAllActions();
		imManArmature->removeFromParentAndCleanup(false);
        
        if(0 == armatureName.compare("IMRun"))
        {
            this->IMRunJump();
            CCActionInterval * jumpAction = CCJumpTo::create(0.5,CCPointMake(imManArmature->getPosition().x,imManArmature->getPosition().y),150,1);
            CCCallFunc * callBack;
			if(nMoveX<0)
			{
				callBack = CCCallFuncND::create(this, callfuncND_selector(GameScenePlayLayer::runJumpActionCallBack), (void*)0xbebabeba);
			}
			else
			{
				callBack = CCCallFuncND::create(this, callfuncND_selector(GameScenePlayLayer::runJumpActionCallBack), (void*)0xbebabebb);
			}

				
            CCFiniteTimeAction*  action = CCSequence::create(jumpAction,callBack,NULL);
            imManArmature->runAction(action);

        }
        
        if(0 == armatureName.compare("IMRunStop"))
        {
            this ->IMStandJump();
            CCActionInterval * jumpAction = CCJumpTo::create(0.5,CCPointMake(imManArmature->getPosition().x,imManArmature->getPosition().y),150,1);
            CCCallFunc * callBack = CCCallFuncND::create(this, callfuncND_selector(GameScenePlayLayer::standJumpActionCallBack), (void*)0xbebabeba);
            CCFiniteTimeAction*  action = CCSequence::create(jumpAction,callBack,NULL);
            imManArmature->runAction(action);
        }
        
        if(0 == armatureName.compare("IMCrouch"))
        {
            this ->IMCrouchJump();
            CCActionInterval * jumpAction = CCJumpTo::create(0.5,CCPointMake(imManArmature->getPosition().x,imManArmature->getPosition().y),100,1);
            CCCallFunc * callBack = CCCallFuncND::create(this, callfuncND_selector(GameScenePlayLayer::standJumpActionCallBack), (void*)0xbebabeba);
            CCFiniteTimeAction*  action = CCSequence::create(jumpAction,callBack,NULL);
            imManArmature->runAction(action);
        }
	}
    
	if(nMoveY<-10 && fabs(tan(nMoveY/nMoveX))>fabs(sqrt(3)/radian))
	{
		if(actionNum == ACTION_CROUCH)
			return;
		imManArmature->stopAllActions();
		imManArmature->removeFromParentAndCleanup(false);
		this ->IMCrouch();
	}
}

void GameScenePlayLayer::IMCrouch()
{
	CCArmature *armature = NULL;
	armature = cocos2d::extension::CCArmature::create("IMCrouch");
	armature->getAnimation()->play("crouch");
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(PLAYER_SCALE);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(ccp(50, 50));
	amaturePosition = armature->getPosition();
	addChild(armature);
	imManArmature = armature;
	actionNum = ACTION_CROUCH;
	GameScene::shareGameScene()->gameSceneMapLayer->stop();
}

void GameScenePlayLayer::IMRunning()
{
	CCArmature *armature = NULL;
	armature = CCArmature::create("IMRun");
	armature->getAnimation()->play("Running");
	armature->getAnimation()->setSpeedScale(2.0f);
	armature->setScale(PLAYER_SCALE);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(ccp(50, 50));
	amaturePosition = armature->getPosition();
	addChild(armature);
	imManArmature = armature;
	actionNum = ACTION_RUN;
	GameScene::shareGameScene()->gameSceneMapLayer->move();
}

void GameScenePlayLayer::IMStandJump()
{
	CCArmature *armature = NULL;
	armature = CCArmature::create("IMStandJump");
	armature->getAnimation()->play("StandJump");
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(PLAYER_SCALE);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(ccp(50, 50));
	amaturePosition = armature->getPosition();
	addChild(armature);
	imManArmature = armature;
	actionNum = ACTION_STAND_JUMP;
	GameScene::shareGameScene()->gameSceneMapLayer->stop();
}

void GameScenePlayLayer::IMRunJump()
{
    
 	CCArmature *armature = NULL;
	armature = CCArmature::create("IMRunJump");
	armature->getAnimation()->play("RuningJump");
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(PLAYER_SCALE);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(ccp(50, 50));
	amaturePosition = armature->getPosition();
	addChild(armature);
	imManArmature = armature;
	actionNum = ACTION_RUN_JUMP;
	GameScene::shareGameScene()->gameSceneMapLayer->move();
}

void GameScenePlayLayer::IMCrouchJump()
{
 	CCArmature *armature = NULL;
	armature = CCArmature::create("IMCrouchJump");
	armature->getAnimation()->play("CrouchJump");
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(PLAYER_SCALE);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(ccp(50, 50));
	amaturePosition = armature->getPosition();
	addChild(armature);
	imManArmature = armature;
	actionNum = ACTION_CROUCH_JUMP;
	GameScene::shareGameScene()->gameSceneMapLayer->move();
}

void GameScenePlayLayer::IMRunningStop()
{
	CCArmature *armature = NULL;
	armature = CCArmature::create("IMRunStop");
	armature->getAnimation()->play("RunningStop");
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(PLAYER_SCALE);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(ccp(100, 50));
	amaturePosition = armature->getPosition();
	addChild(armature);
	imManArmature = armature;
	actionNum = ACTION_RUN_STOP;
	GameScene::shareGameScene()->gameSceneMapLayer->stop();
}

float GameScenePlayLayer::getAngle(CCPoint touch)
{
    //touch = ccp(240, 290);
    CCPoint posOrg = ccp(140, 190);
    if(touch.x == posOrg.x)
        return -1.57;
    if (touch.y == posOrg.y) {
        if (touch.x > posOrg.x) {
            return 0;
        }
        if (touch.x < posOrg.x) {
            return 3.14;
        }
    }
    float tan = (touch.y - posOrg.y)/(touch.x - posOrg.x);
    double angle = atan(tan);
    CCLog("tan: %f, %f", tan, angle);
    return -angle;
}
CCPoint GameScenePlayLayer::getPosHand(float angle)
{
    CCPoint posOrg = ccp(140, 190);
    CCPoint posH;
    float length = 56.0;
    posH.x = posOrg.x + length * cos(angle);
    posH.y = posOrg.y + length * sin(angle);
    
    return posH;
}

void GameScenePlayLayer::IMRunAttack(CCPoint touch)
{
    float angle = getAngle(touch);
    CCPoint posHand = getPosHand(angle);
    CCArmature *armature = NULL;
    armature = CCArmature::create("LaserRunAttack");
    armature->getAnimation()->play("RunningAttack");
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setScale(PLAYER_SCALE);
	armature->setPosition(ccp(100, 50));
    CCBone* leftArmBone = armature->getBone("LeftTopArmAttack");
    leftArmBone->setRotation(getAngle(touch));
    amaturePosition = armature->getPosition();
	addChild(armature);
    CCPoint pArm = leftArmBone->getPosition();
    //CCLog("arm pos: %f, %f, %f, %f.", posHand.x, posHand.y, amaturePosition.x, amaturePosition.y);
	imManArmature = armature;
	actionNum = ACTION_RUN_ATTACK;
    armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(GameScenePlayLayer::setAttackEvent));
	//LaserManager::shareGameScene()->gameSceneMapLayer->attack();
}

void GameScenePlayLayer::IMStandAttack(CCPoint touch)
{
    
}
void GameScenePlayLayer::IMDeath()
{
	this->setTouchEnabled(false);
	imManArmature->removeFromParentAndCleanup(true);
	CCArmature *armature = NULL;
	armature = CCArmature::create("IMDead");
	armature->getAnimation()->playByIndex(0.0f, 1.0f, 1.0f,0.0f, 1.0f);
	armature->getAnimation()->setSpeedScale(1.0f);
	armature->setScale(PLAYER_SCALE);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(ccp(100, 50));
	amaturePosition = armature->getPosition();
	addChild(armature);
	imManArmature = armature;
	actionNum = ACTION_DEATH;
	armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(GameScenePlayLayer::Dead));
	
}
void GameScenePlayLayer::setAttackEvent(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID)
{
	   std::string id = movementID;
    
    CCLog("setAttackEvent %d.", movementType);
    if (movementType == LOOP_COMPLETE)
    {
        CCLog("setAttackEvent end");
        armature->removeFromParentAndCleanup(true);
        //        if (id.compare("LOOP_COMPLETE") == 0)
        //        {
        //            CCActionInterval *actionToRight = CCMoveTo::create(2, ccp(VisibleRect::right().x - 50, VisibleRect::right().y));
        //            armature->stopAllActions();
        //            armature->runAction(CCSequence::create(actionToRight,  CCCallFunc::create(this, callfunc_selector(TestAnimationEvent::callback1)), NULL));
        //            armature->getAnimation()->play("Walk");
        //        }
    }

}
void GameScenePlayLayer::Dead(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID)
{
 	GameScene::shareGameScene()->gameOver();
}

int GameScenePlayLayer::getMonsterGroundAmount()
{
	
	return monsterGroundAmount;
}

int GameScenePlayLayer::getMonsterSkyAmount()
{
	return monsterSkyAmount;
}
