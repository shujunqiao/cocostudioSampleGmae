//
//  GameSceneMenuLayer.cpp
//  Ironman
//
//  Created by Ken on 13-10-14.
//
//

#include "GameSceneMenuLayer.h"

bool GameSceneMenuLayer::init(){
    
    this->addWidget(CCUIHELPER->createWidgetFromJsonFile("IronCityUI_1.json"));
    
    return true;
}