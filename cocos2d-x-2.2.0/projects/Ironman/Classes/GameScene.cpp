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
	menuLayer = new GameSceneMenuLayer();
    menuLayer->init(100, "0", this);
    menuLayer->setAnchorPoint(ccp(0, 0));
    menuLayer->setPosition(ccp(0, 0));
    menuLayer->setScale(0.5);
    this->addChild(menuLayer,1);
    
    playLayer = new GameScenePlayLayer();
    playLayer->init();
    this->addChild(playLayer, 0);
    
    return true;
}

GameSceneMenuLayer* GameScene::getMenuLayer()
{
	return menuLayer;
}

GameScenePlayLayer* GameScene::getPlayLayer()
{
	return playLayer;
}

void GameScene::gameOver()
{
	GameSceneOverLayer* overLayer = new GameSceneOverLayer();
	overLayer->init(this);
	
	playLayer->stopAllActions();
	playLayer->unscheduleUpdate();
	menuLayer->unscheduleUpdate();
	
	this->addChild(overLayer);
}