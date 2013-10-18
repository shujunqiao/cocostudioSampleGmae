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
	gameSceneMapLayer->init();
	gameSceneMapLayer->setMovedSpeed(3);
    gameSceneMapLayer->setPosition(ccp(0, 0));
    this->addChild(gameSceneMapLayer,0);

	menuLayer = new GameSceneMenuLayer();
    menuLayer->init(100, "0");
    menuLayer->setAnchorPoint(ccp(0, 0));
    menuLayer->setPosition(ccp(0, 0));
    menuLayer->setScale(0.5);
    this->addChild(menuLayer,1);
    
    playLayer = new GameScenePlayLayer();
    playLayer->init();
    this->addChild(playLayer, 0);
    
	gameSceneMonster = new GameSceneMonster();
    gameSceneMonster->init();
    this->addChild(gameSceneMonster, 0);

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

void GameScene::gameOver()
{
	GameSceneOverLayer* overLayer = new GameSceneOverLayer();
	overLayer->init();
	
	playLayer->stopAllActions();
	playLayer->unscheduleUpdate();
	menuLayer->unscheduleUpdate();
	
	this->addChild(overLayer);
}