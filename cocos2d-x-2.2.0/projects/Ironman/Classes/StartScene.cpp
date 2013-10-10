#include "StartScene.h"

USING_NS_CC;

#define ANIME_RUN 0
#define ANIME_JUMP 0

CCScene* StartScene::initStartScene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    StartScene *layer = StartScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    StartScene::registerWithTouchDispatcher();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/*
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("ImCrouch.ExportJson", this, schedule_selector(StartScene::dataLoaded));
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("IMRun.ExportJson", this, schedule_selector(StartScene::dataLoaded));
	*/
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("ImCrouch.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("IMRun.ExportJson");
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("IMJump.ExportJson");
	
	touchTime = 0;
	this->ImCrouch();
	actionNum = ACTION_CROUCH;

    return true;
}
void StartScene::dataLoaded(float t)
{

}

void StartScene::ImCrouch()
{
	CCArmature *armature = NULL;
	armature = cocos2d::extension::CCArmature::create("ImCrouch");
	armature->getAnimation()->play("crouch");
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(0.6f);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(ccp(50, 50));
	amaturePosition = armature->getPosition();
	addChild(armature);
	imManArmature = armature;
	actionNum = ACTION_CROUCH;
}

void StartScene::IMRun()
{
	CCArmature *armature = NULL;
	armature = CCArmature::create("IMRun");
	armature->getAnimation()->playByIndex(ANIME_RUN,-1,-1,1,10000);
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(0.6f);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(ccp(50, 50));
	amaturePosition = armature->getPosition();
	addChild(armature);
	imManArmature = armature;
	actionNum = ACTION_RUN;
}
void StartScene::IMJump()
{
	CCArmature *armature = NULL;
	armature = CCArmature::create("IMJump");
	armature->getAnimation()->playByIndex(ANIME_JUMP,-1,-1,1,10000);
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(0.6f);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(ccp(50, 50));
	amaturePosition = armature->getPosition();
	addChild(armature);
	imManArmature = armature;
	actionNum = ACTION_JUMP;
}
void StartScene::ImStand()
{//RunningStand
	CCArmature *armature = NULL;
	armature = CCArmature::create("IMRun");
	armature->getAnimation()->play("RunningStand");
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(0.6f);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(ccp(50, 50));
	amaturePosition = armature->getPosition();
	addChild(armature);
	imManArmature = armature;
	actionNum = ACTION_RNNING_STAND;
}


void StartScene::jumpActionCallBack(CCNode* sender, void* data)
{
	imManArmature->stopAllActions();
		imManArmature->removeFromParentAndCleanup(false);
		this ->IMRun();
}
void StartScene::menuCloseCallback(CCObject* pSender)
{
		CCActionInterval * splitCols = CCMoveTo::create(1.0,CCPointMake(imManArmature->getPosition().x+300,imManArmature->getPosition().y));
		imManArmature->runAction(splitCols);
}


void StartScene::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void StartScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
     CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
   
    m_tBeginPos = touch->getLocation();    
	
}

void StartScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	touchTime++;
	
}

void StartScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCLog("touchTime == %d",touchTime);
	if(touchTime>30)
	{
		touchTime = 0;
		return;
	}
	
		touchTime = 0;
	
    
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
 
    CCPoint touchLocation = touch->getLocation();    
    float nMoveX = touchLocation.x - m_tBeginPos.x;
	float nMoveY = touchLocation.y - m_tBeginPos.y;
	CCLog("m_tBeginPos.x = %f",m_tBeginPos.x);
	CCLog("touchLocation.x = %f",touchLocation.x);
	CCLog("nMoveX = %f ,nMoveY = %f",nMoveX,nMoveY);
	CCLog("tan1 = %f",tan(nMoveY/nMoveX));
	CCLog("tan2 = %f",fabs(sqrt(3)/10));
	int radian = 10;
	
	if(nMoveX>10 && fabs(tan(nMoveY/nMoveX))<fabs(sqrt(3)/radian))
	{
		if(actionNum == ACTION_RUN)
			return;
		imManArmature->stopAllActions();
		imManArmature->removeFromParentAndCleanup(false);
		this ->IMRun();
	}
	if(nMoveX<-10 && fabs(tan(nMoveY/nMoveX))<fabs(sqrt(3)/radian))
	{
		if(actionNum == ACTION_RNNING_STAND)
			return;
		imManArmature->stopAllActions();
		imManArmature->removeFromParentAndCleanup(false);
		this ->ImStand();
	}
	if(nMoveY>10 && fabs(tan(nMoveY/nMoveX))>fabs(sqrt(3)/radian))
	{
		if(actionNum == ACTION_JUMP)
			return;
		imManArmature->stopAllActions();
		imManArmature->removeFromParentAndCleanup(false);
		this ->IMJump();
		CCActionInterval * jumpAction = CCJumpTo::create(0.5,CCPointMake(imManArmature->getPosition().x,imManArmature->getPosition().y),100,1);
		CCCallFunc * callBack = CCCallFuncND::create(this, callfuncND_selector(StartScene::jumpActionCallBack), (void*)0xbebabeba);
	    CCFiniteTimeAction*  action = CCSequence::create(jumpAction,callBack,NULL);

		imManArmature->runAction(action);
	}
	if(nMoveY<-10 && fabs(tan(nMoveY/nMoveX))>fabs(sqrt(3)/radian))
	{
		if(actionNum == ACTION_CROUCH)
			return;
		imManArmature->stopAllActions();
		imManArmature->removeFromParentAndCleanup(false);
		this ->ImCrouch();
	}
}

void StartScene::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
  //  ccTouchesEnded(pTouches, pEvent);
}