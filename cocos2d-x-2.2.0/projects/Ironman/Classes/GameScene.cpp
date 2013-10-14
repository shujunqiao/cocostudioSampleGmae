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
    GameSceneMenuLayer* menuLayer = new GameSceneMenuLayer();
    menuLayer->init();
    this->addChild(menuLayer,1);
    
    playLayer = new GameScenePlayLayer();
    playLayer->init();
    this->addChild(playLayer, 0);
    
    return true;
}
