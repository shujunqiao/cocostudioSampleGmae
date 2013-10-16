//
//  GameSceneMenuLayer.cpp
//  Ironman
//
//  Created by Ken on 13-10-14.
//
//

#include "GameSceneMenuLayer.h"

bool GameSceneMenuLayer::init(int broodBarPercent,const char *value, GameScene* gameScene)
{
    if(UILayer::init()){
        
        parentScene = gameScene;
        this->addWidget(dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("iphone/IronCityUI_1.json")));
        
        settingBtn    = dynamic_cast<UIButton*>(this->getWidgetByName("Setting"));
        broodBar      = dynamic_cast<UILoadingBar*>(this->getWidgetByName("BroodBar"));
        distanceScore = dynamic_cast<UILabelAtlas*>(this->getWidgetByName("DistanceScore"));
        
        settingBtn->addReleaseEvent(this, coco_releaseselector(GameSceneMenuLayer::settingBtnCallback));
        this->setBroodBarPercent(broodBarPercent);
        this->setDistanceScore(value);
        
        return true;
    }
    return false;
}

void GameSceneMenuLayer::settingBtnCallback(CCObject* sender)
{
    parentScene->gameOver();
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