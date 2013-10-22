//
//  GameScene.cpp
//  Ironman
//
//  Created by Ken on 13-10-10.
//
//

#include "GameScene.h"

bool GameScene::init()
{
	gameSceneMapLayer = new GameSceneMapLayer();
	
	if(gameSceneMapLayer && gameSceneMapLayer->init()){
		
		gameSceneMapLayer->autorelease();
	}else{
		
		CC_SAFE_DELETE(gameSceneMapLayer);
	}
	
	gameSceneMapLayer->setMovedSpeed(3);
    gameSceneMapLayer->setPosition(ccp(0, 0));
    this->addChild(gameSceneMapLayer, 0);

	menuLayer = new GameSceneMenuLayer();
	
	if(menuLayer && menuLayer->init(100, "0")){
		
		menuLayer->autorelease();
	}else{
		
		CC_SAFE_DELETE(menuLayer);
	}
	
    menuLayer->setAnchorPoint(ccp(0, 0));
    menuLayer->setPosition(ccp(0, 0));
    menuLayer->setScale(0.5);
    this->addChild(menuLayer, 0);
    
    playLayer = new GameScenePlayLayer();
	
	if(playLayer && playLayer->init()){
		
		playLayer->autorelease();
	}else{
		
		CC_SAFE_DELETE(playLayer);
	}
	
    this->addChild(playLayer, 0);
    
	gameSceneMonster = new GameSceneMonster();
    gameSceneMonster->init();
    this->addChild(gameSceneMonster, 0);
    
    laser = LaserManager::create();
    laser->scheduleUpdate();
    this->addChild(laser);
	this->scheduleUpdate();

    return true;
}

static GameScene *_sharedGameScene = NULL;

GameScene* GameScene::shareGameScene()
{
    if (!_sharedGameScene) {
        _sharedGameScene = new GameScene();
        if (!_sharedGameScene->init())
        {
            CC_SAFE_DELETE(_sharedGameScene);
        }
    }
    return _sharedGameScene;
}
GameScene* GameScene::newGameScene()
{
     _sharedGameScene = new GameScene();
    if (!_sharedGameScene->init())
    {
		CC_SAFE_DELETE(_sharedGameScene);
    }
    
    return _sharedGameScene;
}
void GameScene::gameOver()
{
	GameSceneOverLayer* overLayer = new GameSceneOverLayer();
	overLayer->init();
	
	playLayer->stopAllActions();
	playLayer->unscheduleUpdate();
	gameSceneMonster->stopAllActions();
	gameSceneMonster->unscheduleUpdate();

	menuLayer->unscheduleUpdate();

	this->addChild(overLayer, 0);
}

void GameScene::update(float dt)
{
	CCArmature * imManArmature = playLayer->imManArmature;
	int actionNum = playLayer->actionNum;
	if(actionNum ==playLayer->ACTION_RUN)
	{
		playLayer->playerBoundingBox = CCRectMake(imManArmature->getPosition().x-imManArmature->getContentSize().width/2+46,imManArmature->getPosition().y,imManArmature->getContentSize().width-90,imManArmature->getContentSize().height-50);
	}
	else if(actionNum == playLayer->ACTION_STAND_JUMP)
	{
		playLayer->playerBoundingBox = CCRectMake(imManArmature->getPosition().x-imManArmature->getContentSize().width/2+30,imManArmature->getPosition().y,imManArmature->getContentSize().width-50,imManArmature->getContentSize().height-50);
	}
	else if(actionNum == playLayer->ACTION_RUN_JUMP)
	{
		playLayer->playerBoundingBox = CCRectMake(imManArmature->getPosition().x-imManArmature->getContentSize().width/2+33,imManArmature->getPosition().y,imManArmature->getContentSize().width-70,imManArmature->getContentSize().height-50);
	}
	else if(actionNum == playLayer->ACTION_RUN_STOP)
	{
		playLayer->playerBoundingBox = CCRectMake(imManArmature->getPosition().x-imManArmature->getContentSize().width/2+40,imManArmature->getPosition().y,imManArmature->getContentSize().width-110,imManArmature->getContentSize().height-45);
	}
	else if(actionNum == playLayer->ACTION_RUN_ATTACK)
	{
		playLayer->playerBoundingBox = CCRectMake(imManArmature->getPosition().x-imManArmature->getContentSize().width/2,imManArmature->getPosition().y,imManArmature->getContentSize().width,imManArmature->getContentSize().height);

	}
	else if(actionNum == playLayer->ACTION_STAND_ATTACK)
	{
		playLayer->playerBoundingBox = CCRectMake(imManArmature->getPosition().x-imManArmature->getContentSize().width/2,imManArmature->getPosition().y,imManArmature->getContentSize().width,imManArmature->getContentSize().height);

	}
	else if(actionNum == playLayer->ACTION_DEATH)
	{
		playLayer->playerBoundingBox = CCRectMake(imManArmature->getPosition().x-imManArmature->getContentSize().width/2,imManArmature->getPosition().y,imManArmature->getContentSize().width,imManArmature->getContentSize().height);
	}

	if(gameSceneMonster->MonsterIndex == MonsterGround_enum)
	{
		gameSceneMonster->MonsterAmatureBoundingBox = CCRectMake(gameSceneMonster->MonsterAmature->getPosition().x-gameSceneMonster->MonsterAmature->getContentSize().width/2+25,gameSceneMonster->MonsterAmature->getPosition().y+21,gameSceneMonster->MonsterAmature->getContentSize().width-50,gameSceneMonster->MonsterAmature->getContentSize().height-48);
	}
	else if(gameSceneMonster->MonsterIndex == MonsterSky_enum)
	{
		gameSceneMonster->MonsterAmatureBoundingBox = CCRectMake(gameSceneMonster->MonsterAmature->getPosition().x-gameSceneMonster->MonsterAmature->getContentSize().width/2+25,gameSceneMonster->MonsterAmature->getPosition().y+21,gameSceneMonster->MonsterAmature->getContentSize().width-50,gameSceneMonster->MonsterAmature->getContentSize().height-48);
	}

	if (playLayer->playerBoundingBox.intersectsRect(gameSceneMonster->MonsterAmatureBoundingBox))
	{
		this->unscheduleUpdate();
		gameSceneMonster->MonsterDestroyAction();
		playLayer->imManArmatureBrood-=1;
		if(playLayer->imManArmatureBrood<1)
		{
			GameScene::shareGameScene()->menuLayer->setBroodBarPercent(0);
			this->unscheduleUpdate();
			playLayer->IMDeath();
			return;
		}

		GameScene::shareGameScene()->menuLayer->setBroodBarPercent(playLayer->imManArmatureBrood);
	//	this->unscheduleUpdate();
	}
}
/*
void GameScene::draw()
{
	CCRect playerBoundingBoxCopy = playLayer->playerBoundingBox;
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

	CCRect MonsterAmatureBoundingBoxCopy = gameSceneMonster->MonsterAmatureBoundingBox;
	float MonsterAmatureBoundingBoxX = MonsterAmatureBoundingBoxCopy.origin.x;
	float MonsterAmatureBoundingBoxY = MonsterAmatureBoundingBoxCopy.origin.y;
	float MonsterAmatureBoundingBoxWidth = MonsterAmatureBoundingBoxCopy.size.width;
	float MonsterAmatureBoundingBoxHeight = MonsterAmatureBoundingBoxCopy.size.height;

	CCPoint point5 = CCPointMake(MonsterAmatureBoundingBoxX,MonsterAmatureBoundingBoxY);
	CCPoint point6 = CCPointMake(MonsterAmatureBoundingBoxX+MonsterAmatureBoundingBoxWidth,MonsterAmatureBoundingBoxY);
	CCPoint point7 = CCPointMake(MonsterAmatureBoundingBoxX+MonsterAmatureBoundingBoxWidth,MonsterAmatureBoundingBoxY+MonsterAmatureBoundingBoxHeight);
	CCPoint point8 = CCPointMake(MonsterAmatureBoundingBoxX,MonsterAmatureBoundingBoxY+MonsterAmatureBoundingBoxHeight);

	CCPoint vertices2[] = { point5, point6, point7, point8};  
    ccDrawPoly( vertices2, 4, true//是否封闭  
        ); 
}
*/