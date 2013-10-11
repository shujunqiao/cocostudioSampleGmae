//
//  MainMenuScene.h
//  Ironman
//
//  Created by Ken on 13-10-10.
//
//

#ifndef Ironman_MainMenuScene_h
#define Ironman_MainMenuScene_h

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;

using namespace extension;

class MainMenuScene : public cocos2d::CCScene
{
public:
    
    bool init();
    
    void startBtnCallFunc(CCObject* pSender);
};

#endif
