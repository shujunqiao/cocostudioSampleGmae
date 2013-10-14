//
//  GameScenePlayLayer.cpp
//  Ironman
//
//  Created by Ken on 13-10-10.
//
//

#include "GameScenePlayLayer.h"
#define ANIME_RUN 0
#define ANIME_JUMP 0
#define PTM_RATIO 32.0
bool GameScenePlayLayer::init(){
       
    GameScenePlayLayer::registerWithTouchDispatcher();
//    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("IMCrouch.ExportJson");
    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("IMRun.ExportJson");
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("IMRunJump.ExportJson");
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("IMStandJump.ExportJson");
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("IMCrouchJump.ExportJson");
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("IMRunStop.ExportJson");
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("LaserRunAttack.ExportJson");
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("LaserStandAttack.ExportJson");

	touchTime = 0;
	this->IMCrouch();
	actionNum = ACTION_CROUCH;
    
/*
	//创建这个刚体世界
  b2Vec2 gravity = b2Vec2(0.0f,-10.0f);
  m_pworld = new b2World(gravity);

  //创建4个物体
  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(0,0);
  m_pgroundBody = m_pworld->CreateBody(&groundBodyDef);
  b2EdgeShape groundEdge;
  b2FixtureDef boxShapeDef;
  
  boxShapeDef.shape = &groundEdge;
  //底边
  groundEdge.Set(b2Vec2(0,0),b2Vec2(visibleSize.width/PTM_RATIO,0));
  m_pgroundBody->CreateFixture(&boxShapeDef);
  //左边
   groundEdge.Set(b2Vec2(0,0),b2Vec2(0,visibleSize.height/PTM_RATIO));
   m_pgroundBody->CreateFixture(&boxShapeDef);
  //上边
   groundEdge.Set(b2Vec2(0, visibleSize.height/PTM_RATIO), 
    b2Vec2(visibleSize.width/PTM_RATIO, visibleSize.height/PTM_RATIO));
   m_pgroundBody->CreateFixture(&boxShapeDef);
  //右边
   groundEdge.Set(b2Vec2(visibleSize.width/PTM_RATIO, 
    visibleSize.height/PTM_RATIO), b2Vec2(visibleSize.width/PTM_RATIO, 0));
   m_pgroundBody->CreateFixture(&boxShapeDef);

  //creat a ball body and shape
  b2BodyDef ballBodyDef;
  //动态物体
  ballBodyDef.type = b2_dynamicBody;
  ballBodyDef.position.Set(100/PTM_RATIO, 100/PTM_RATIO);
  //!!这里很重要：设置userData
  ballBodyDef.userData = (void*)imManArmature;
  m_pbody = m_pworld->CreateBody(&ballBodyDef);

  //圆形
  b2CircleShape circle;
  circle.m_radius = 26.0/PTM_RATIO;
  //给这个动态物体创建一个固定装置
  //即：将一个密度为1，摩擦系数为0.2，弹性为0.8的圆形，
  //固定在这个刚体之上
  b2FixtureDef ballShapeDef;
  ballShapeDef.shape = &circle;
  ballShapeDef.density = 1.0f;
  ballShapeDef.friction = 0.2f;
  ballShapeDef.restitution = 0.8f;
  m_pBallFixture = m_pbody->CreateFixture(&ballShapeDef);
  
  this->schedule(schedule_selector(GameScenePlayLayer::tick), 0, 0, 0);
  */
    return true;
}
void GameScenePlayLayer::tick(float dt)
{
	_world->Step(dt, 10, 10);    
    for(b2Body *b = _world->GetBodyList(); b; b=b->GetNext())
	{    
        if (b->GetUserData() != NULL) 
		{
			imManArmature = (CCArmature *)b->GetUserData();                        
            imManArmature->setPosition(ccp(b->GetPosition().x * PTM_RATIO,
                                    b->GetPosition().y * PTM_RATIO));
            imManArmature->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
        }        
    }
}
void GameScenePlayLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void GameScenePlayLayer::runJumpActionCallBack(CCNode* sender, void* data)
{
	imManArmature->stopAllActions();
    imManArmature->removeFromParentAndCleanup(false);
    this ->IMRunning();
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

void GameScenePlayLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    
    m_tBeginPos = touch->getLocation();
}

void GameScenePlayLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	touchTime++;	
}

void GameScenePlayLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
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
            CCActionInterval * jumpAction = CCJumpTo::create(0.5,CCPointMake(imManArmature->getPosition().x,imManArmature->getPosition().y),100,1);
            CCCallFunc * callBack = CCCallFuncND::create(this, callfuncND_selector(GameScenePlayLayer::runJumpActionCallBack), (void*)0xbebabeba);
            CCFiniteTimeAction*  action = CCSequence::create(jumpAction,callBack,NULL);
            imManArmature->runAction(action);

        }
        
        if(0 == armatureName.compare("IMRunStop"))
        {
            this ->IMStandJump();
            CCActionInterval * jumpAction = CCJumpTo::create(0.5,CCPointMake(imManArmature->getPosition().x,imManArmature->getPosition().y),100,1);
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

void GameScenePlayLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    //  ccTouchesEnded(pTouches, pEvent);
}


void GameScenePlayLayer::IMCrouch()
{
	CCArmature *armature = NULL;
	armature = cocos2d::extension::CCArmature::create("IMCrouch");
	armature->getAnimation()->play("crouch");
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(0.6f);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(ccp(50, 50));
	amaturePosition = armature->getPosition();
	addChild(armature);
	imManArmature = armature;
	actionNum = ACTION_CROUCH;

	
	 CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	// Create a world
	b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
	bool doSleep = true;
	_world = new b2World(gravity);
 
	// Create edges around the entire screen
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0,0);
	_groundBody = _world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	b2FixtureDef groundBoxDef;
	groundBoxDef.shape = &groundBox;
	groundBox.Set(&b2Vec2(0,winSize.width/PTM_RATIO),4);
	_bottomFixture = _groundBody->CreateFixture(&groundBoxDef);
	/*
	groundBox.Set(&b2Vec2(0,winSize.height/PTM_RATIO),1);
	_groundBody->CreateFixture(&groundBoxDef);
	groundBox.Set(&b2Vec2(winSize.height/PTM_RATIO, winSize.width/PTM_RATIO),1);
	_groundBody->CreateFixture(&groundBoxDef);
	groundBox.Set(&b2Vec2(winSize.width/PTM_RATIO, winSize.height/PTM_RATIO),1);
	_groundBody->CreateFixture(&groundBoxDef);
  */

	// Create ball body 
	b2BodyDef ballBodyDef;
	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.position.Set(100/PTM_RATIO, 100/PTM_RATIO);
	ballBodyDef.userData = armature;
	b2Body * ballBody = _world->CreateBody(&ballBodyDef);
 
	// Create circle shape
	b2CircleShape circle;
	circle.m_radius = 26.0/PTM_RATIO;
 
	// Create shape definition and add to body
	b2FixtureDef ballShapeDef;
	ballShapeDef.shape = &circle;
	ballShapeDef.density = 1.0f;
	ballShapeDef.friction = 0.f;
	ballShapeDef.restitution = 1.0f;
	_ballFixture = ballBody->CreateFixture(&ballShapeDef);


	b2Vec2 force = b2Vec2(10, 10);
	ballBody->ApplyLinearImpulse(force, ballBodyDef.position);

	this->schedule(schedule_selector(GameScenePlayLayer::tick), 0, 0, 0);
}

void GameScenePlayLayer::IMRunning()
{
	CCArmature *armature = NULL;
	armature = CCArmature::create("IMRun");
	armature->getAnimation()->play("Running");
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(0.6f);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(ccp(50, 50));
	amaturePosition = armature->getPosition();
	addChild(armature);
	imManArmature = armature;
	actionNum = ACTION_RUN;
}

void GameScenePlayLayer::IMStandJump()
{
	CCArmature *armature = NULL;
	armature = CCArmature::create("IMStandJump");
	armature->getAnimation()->play("StandJump");
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(0.6f);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(ccp(50, 50));
	amaturePosition = armature->getPosition();
	addChild(armature);
	imManArmature = armature;
	actionNum = ACTION_STAND_JUMP;
}

void GameScenePlayLayer::IMRunJump()
{
    
 	CCArmature *armature = NULL;
	armature = CCArmature::create("IMRunJump");
	armature->getAnimation()->play("RuningJump");
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(0.6f);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(ccp(50, 50));
	amaturePosition = armature->getPosition();
	addChild(armature);
	imManArmature = armature;
	actionNum = ACTION_RUN_JUMP;
}

void GameScenePlayLayer::IMCrouchJump()
{
    
 	CCArmature *armature = NULL;
	armature = CCArmature::create("IMCrouchJump");
	armature->getAnimation()->play("CrouchJump");
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(0.6f);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(ccp(50, 50));
	amaturePosition = armature->getPosition();
	addChild(armature);
	imManArmature = armature;
	actionNum = ACTION_CROUCH_JUMP;
}

void GameScenePlayLayer::IMRunningStop()
{
	CCArmature *armature = NULL;
	armature = CCArmature::create("IMRunStop");
	armature->getAnimation()->play("RunningStop");
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(0.6f);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(ccp(50, 50));
	amaturePosition = armature->getPosition();
	addChild(armature);
	imManArmature = armature;
	actionNum = ACTION_RUN_STOP;
}
