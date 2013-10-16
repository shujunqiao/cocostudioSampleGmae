//
//  GameSceneOverLayer.h
//  Ironman
//
//  Created by Ken on 13-10-15.
//
//

#ifndef Ironman_GameSceneOverLayer_h
#define Ironman_GameSceneOverLayer_h
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameScene.h"
USING_NS_CC;

using namespace extension;

class GameScene;
class GameSceneOverLayer : public UILayer
{
    
public:
    
    bool init(GameScene* gameScene);
    
protected:
    
	GameScene* parentScene;
    UIButton* playAgainBtn;
    UITextField* monsterSkyAmount;
    UITextField* monsterGroundAmount;
    UILabelAtlas* distanceScore;
    UILabelAtlas* finalScore;
    
    void calculateFinalScore(const char* monsterSkyAmountValue,const char* monsterGroundAmountValue, const char* distanceScoreValue);
	virtual void playAgainBtnCallback(CCObject* sender);

};


#endif
