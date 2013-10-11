//
//  GameScene.h
//  Ironman
//
//  Created by Ken on 13-10-10.
//
//

#ifndef Ironman_GameScene_h
#define Ironman_GameScene_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameScenePlayLayer.h"
USING_NS_CC;

using namespace extension;
class GameScene : public cocos2d::CCScene
{
public:
    
    bool init();
    
    GameScenePlayLayer* playLayer;
};

#endif
