//
//  GameSceneOverLayer.cpp
//  Ironman
//
//  Created by Ken on 13-10-15.
//
//

#include "GameSceneOverLayer.h"

bool GameSceneOverLayer::init()
{
    if(UILayer::init()){
        
		parentScene = GameScene::shareGameScene();
        this->addWidget(dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("iphone/GameSceneOverLayer_1.json")));
        
        UIButton*    playAgainBtn        = dynamic_cast<UIButton*>(this->getWidgetByName("playAgain"));
        UITextField* monsterGroundAmount = dynamic_cast<UITextField*>(this->getWidgetByName("monsterGroundLabel"));
        UITextField* monsterSkyAmount    = dynamic_cast<UITextField*>(this->getWidgetByName("monsterSkyLabel"));
        UILabelAtlas* distanceScore      = dynamic_cast<UILabelAtlas*>(this->getWidgetByName("distanceScore"));
        finalScore = dynamic_cast<UILabelAtlas*>(this->getWidgetByName("finalScore"));
        
        playAgainBtn->addTouchEventListener(this, toucheventselector(GameSceneOverLayer::playAgainBtnCallback));
        monsterGroundAmount->setText(parentScene->playLayer->getMonsterGroundAmount());
        monsterSkyAmount->setText(parentScene->playLayer->getMonsterSkyAmount());
        distanceScore->setStringValue(parentScene->menuLayer->getDistanceScore());
        
        return true;
    }
	
    return false;
}

void GameSceneOverLayer::calculateFinalScore(const char* monsterSkyAmountValue,const char* monsterGroundAmountValue, const char* distanceScoreValue)
{
    int score = (int)monsterSkyAmountValue + (int)monsterGroundAmountValue + (int)distanceScoreValue * 3;
    
    finalScore->setStringValue((const char*)score);
}

void GameSceneOverLayer::playAgainBtnCallback(CCObject *pSender, TouchEventType type)
{
	if(TOUCH_EVENT_BEGAN == type){
	    GameScene* againScene = new GameScene();
        againScene->init();
		
        CCTransitionFade* playAgainTransition =  CCTransitionFade::create(0.5, againScene, ccWHITE);
        CCDirector::sharedDirector()->replaceScene(playAgainTransition);
	}
}
