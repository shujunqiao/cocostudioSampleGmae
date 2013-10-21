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
		UILabel* monsterGroundAmount = dynamic_cast<UILabel*>(this->getWidgetByName("monsterGroundLabel"));
        UILabel* monsterSkyAmount    = dynamic_cast<UILabel*>(this->getWidgetByName("monsterSkyLabel"));
        UILabelAtlas* distanceScore      = dynamic_cast<UILabelAtlas*>(this->getWidgetByName("distanceScore"));
        finalScore = dynamic_cast<UILabelAtlas*>(this->getWidgetByName("finalScore"));
        
        playAgainBtn->addTouchEventListener(this, toucheventselector(GameSceneOverLayer::playAgainBtnCallback));

		int monsterGroundCount= parentScene->playLayer->getMonsterGroundAmount();
		ostringstream oss1;
        oss1<<monsterGroundCount;
	    string str1 = oss1.str();
	    const char * charStr1= str1.c_str();
        monsterGroundAmount->setText(charStr1);

		int monsterSkyCount= parentScene->playLayer->getMonsterSkyAmount();
		ostringstream oss2;
        oss2<<monsterGroundCount;
	    string str2= oss2.str();
	    const char * charStr2= str2.c_str();
        monsterSkyAmount->setText(charStr2);

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
		
	    GameScene* againScene = GameScene::newGameScene();
    
        CCTransitionFade* playAgainTransition =  CCTransitionFade::create(0.5, againScene, ccWHITE);
        CCDirector::sharedDirector()->replaceScene(playAgainTransition);
	}
}
