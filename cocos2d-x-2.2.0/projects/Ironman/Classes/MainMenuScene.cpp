//
//  MainMenuScene.cpp
//  Ironman
//
//  Created by Ken on 13-10-10.
//
//

#include "MainMenuScene.h"
#include "GameScene.h"

bool MainMenuScene::init()
{    
    CCLayer* menuLayer = CCLayer::create();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // Add backgrounbdPic
    CCSprite* backGroundPic = CCSprite::create("iphone/MainMenuSceneBK.png");
    backGroundPic->setAnchorPoint(ccp(0, 0));
    
    menuLayer->addChild(backGroundPic,0);
    
    //Add StartBtn
    CCSprite* start     = CCSprite::create("iphone/StartBtn.png");
    CCSprite* startPush = CCSprite::create("iphone/StartBtnPush.png");
    
    CCMenuItemSprite* startBtn = CCMenuItemSprite::create(start, startPush, menuLayer, menu_selector(MainMenuScene::startBtnCallFunc));
    
    //Add Menu
    CCMenu* mainMenu = CCMenu::create(startBtn, NULL);
    mainMenu->setAnchorPoint(ccp(0, 0));
    mainMenu->setPosition(ccp(size.width/2, size.height/5));

    menuLayer->addChild(mainMenu,1);
    this->addChild(menuLayer);
    return true;
}

void MainMenuScene::startBtnCallFunc(CCObject* pSender)
{
    GameScene* gameScene = new GameScene();
    gameScene->init();
    
    CCTransitionFade* gameScneTransition =  CCTransitionFade::create(0.5, gameScene, ccWHITE);
    CCDirector::sharedDirector()->replaceScene(gameScneTransition);
}