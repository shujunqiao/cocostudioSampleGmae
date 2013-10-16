//
//  GameSceneMenuLayer.cpp
//  Ironman
//
//  Created by Ken on 13-10-14.
//
//

#include "GameSceneMenuLayer.h"

bool GameSceneMenuLayer::init(){
    
    if(UILayer::init()){
        
        this->addWidget(CCUIHELPER->createWidgetFromJsonFile("iphone/IronCityUI_1.json"));
        return true;
    }
    return false;
}