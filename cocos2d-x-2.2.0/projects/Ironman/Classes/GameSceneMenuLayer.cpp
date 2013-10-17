//
//  GameSceneMenuLayer.cpp
//  Ironman
//
//  Created by Ken on 13-10-14.
//
//

#include "GameSceneMenuLayer.h"

bool GameSceneMenuLayer::init(int broodBarPercent,const char *value)
{
    if(UILayer::init()){
        
        parentScene = GameScene::shareGameScene();
        this->addWidget(dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("iphone/IronCityUI_1.json")));
        
        settingBtn    = dynamic_cast<UIButton*>(this->getWidgetByName("Setting"));
        broodBar      = dynamic_cast<UILoadingBar*>(this->getWidgetByName("BroodBar"));
        distanceScore = dynamic_cast<UILabelAtlas*>(this->getWidgetByName("DistanceScore"));
        
        settingBtn->addTouchEventListener(this, toucheventselector(GameSceneMenuLayer::settingBtnCallback));
        this->setBroodBarPercent(broodBarPercent);
        this->setDistanceScore(value);
		
		musicEffect = 0;
		musicVolume = 50;
        
        return true;
    }
    return false;
}

void GameSceneMenuLayer::settingBtnCallback(CCObject *pSender, TouchEventType type)
{
	if(TOUCH_EVENT_BEGAN == type){
		
		GameSceneSetLayer* gameSetLayer = new GameSceneSetLayer();
		gameSetLayer->init(musicEffect, musicVolume);
		gameSetLayer->setAnchorPoint(ccp(0, 0));
		gameSetLayer->setPosition(ccp(0, 0));
		
		parentScene->addChild(gameSetLayer,4);
	}
	
}

void GameSceneMenuLayer::setBroodBarPercent(int percent)
{
    broodBar->setPercent(percent);
}

void GameSceneMenuLayer::setDistanceScore(const char *value)
{
    distanceScore->setStringValue(value);
}

const char* GameSceneMenuLayer::getDistanceScore()
{
    return distanceScore->getStringValue();
}