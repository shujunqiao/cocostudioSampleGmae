//
//  GameScenePlayLayer.cpp
//  Ironman
//
//  Created by Ken on 13-10-10.
//
//

#include "GameScenePlayLayer.h"
#include "GameScene.h"
#include "Laser.h"
#define ANIME_RUN 0
#define ANIME_JUMP 0
#define PLAYER_SCALE 0.6f
bool GameScenePlayLayer::init()
{
	touchTime = 0;
	isAttack = false;
	imManArmatureBrood = 100;
	
	monsterGroundAmount = 0;
    monsterSkyAmount = 0;
    
    _attackPos = CCPoint(0.0f, 0.0f);
    _attackDir = 0.0f;

	this->IMRunningStop();
	this->setTouchEnabled(true);
	actionNum = ACTION_RUN_STOP;
    
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
	if(isAttack)
		return;

	if(touchTime>30)
	{
		touchTime = 0;
		return;
	}

    CCPoint touchLocation  = pTouch->getLocation();
	CCPoint setBtnLocation = GameScene::shareGameScene()->menuLayer->settingBtn->getPosition();
	CCSize  setBtnSize = GameScene::shareGameScene()->menuLayer->settingBtn->getSize();
	
	if(touchTime<2 && checkIfTouchNotInSetBtnArea(touchLocation, setBtnLocation, setBtnSize))
	{
		if(actionNum != ACTION_RUN && actionNum != ACTION_RUN_STOP)
			return;
		isAttack = true;
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
		if(actionNum == ACTION_STAND_JUMP || actionNum == ACTION_RUN_JUMP)
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
	}
    
	if(nMoveY<-10 && fabs(tan(nMoveY/nMoveX))>fabs(sqrt(3)/radian))
	{
		;
	}
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

void GameScenePlayLayer::IMRunAttack(CCPoint touch)
{
    float angle = getAngle(touch);
    CCPoint posHand = getPosHand(angle);
    
    CCArmature *armature = NULL;
    armature = CCArmature::create("LaserRunAttack");
    armature->getAnimation()->play("RunningAttack");
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setScale(PLAYER_SCALE);
	armature->setPosition(ccp(50, 50));
    //CCBone* leftArmBone = armature->getBone("LeftTopArmAttack");
    //leftArmBone->setRotation(getAngle(touch));
    amaturePosition = armature->getPosition();
	addChild(armature);
    //CCPoint pArm = leftArmBone->getPosition();
    //CCLog("arm pos: %f, %f, %f, %f.", posHand.x, posHand.y, amaturePosition.x, amaturePosition.y);
	imManArmature = armature;
	//actionNum = ACTION_RUN_ATTACK;
	 armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(GameScenePlayLayer::setAttackEvent));
	//LaserManager::shareGameScene()->gameSceneMapLayer->attack();
    
    _attackPos = posHand;
    _attackDir = angle;
}

void GameScenePlayLayer::IMStandAttack(CCPoint touch)
{
    CCPoint posHand = getPosHand(0.1);
    _attackPos = posHand;
    float angle = getAngle(touch);
    
    CCArmature *armature = NULL;
    armature = CCArmature::create("LaserStandAttack");
    armature->getAnimation()->play("StandAttack");
    armature->getAnimation()->setSpeedScale(0.5);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setScale(PLAYER_SCALE);
	armature->setPosition(ccp(70, 50));
    addChild(armature);
    imManArmature = armature;
    armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(GameScenePlayLayer::setAttackEvent));
	
    _attackDir = angle;
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

float GameScenePlayLayer::getAngle(CCPoint touch)
{
    //touch = ccp(240, 290);
    //CCPoint posOrg = ccp(108, 105);
    CCPoint posOrg = ccp(135, 112);
    if(touch.x <= posOrg.x)
        return -1.57;   //up max->90 degree。
    if (touch.y == posOrg.y) {
        if (touch.x > posOrg.x) {
            return 0;
        }
    }
    
    float tan = (touch.y - posOrg.y)/(touch.x - posOrg.x);
    if (tan < -1) {
        tan = -1;    //down max->45 degree。
    }
    double angle = atan(tan);
    CCLog("tan: %f, %f", tan, angle);
    return -angle;
}
CCPoint GameScenePlayLayer::getPosHand(float angle)
{
    CCPoint posH = ccp(135, 112);
    
    return posH;
}
void GameScenePlayLayer::setAttackEvent(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID)
{
    std::string id = movementID;
    
    //CCLog("setAttackEvent %d.", movementType);
    if (movementType == COMPLETE)
    {
        //CCLog("setAttackEvent end");
        CCLog("attack dir: %f, pos(%f, %f).", _attackDir, _attackPos.x, _attackPos.y);
        GameScene::shareGameScene()->laser->addLaser(_attackPos, _attackDir);
        isAttack = false;
		imManArmature->stopAllActions();
		imManArmature->removeFromParentAndCleanup(false);
		if(actionNum == ACTION_RUN)
		{
			this ->IMRunning();
		}
		else if(actionNum == ACTION_RUN_STOP)
		{
			this ->IMRunningStop();
		}
    }

}

bool GameScenePlayLayer::checkIfTouchNotInSetBtnArea(CCPoint touchPosition, CCSize setBtnSize, CCPoint setBtnPosition)
{
	if(touchPosition.x < setBtnPosition.x-(setBtnSize.width/2)  ||
	   touchPosition.x > setBtnPosition.x+(setBtnSize.width/2)  ||
	   touchPosition.y < setBtnPosition.y-(setBtnSize.height/2) ||
	   touchPosition.y > setBtnPosition.y+(setBtnSize.height/2)){
		return true;
	}else{
		return false;
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
