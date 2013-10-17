//
//  GameSceneSetLayer.cpp
//  Ironman
//
//  Created by Ken on 13-10-17.
//
//

#include "GameSceneSetLayer.h"

bool GameSceneSetLayer::init(int effectStatus, int volumn)
{
	if(UILayer::init()){
		
		GameScene* parentScene = GameScene::shareGameScene();
		parentScene->gameSceneMapLayer->stop();
		parentScene->playLayer->imManArmature->pauseSchedulerAndActions();
		
		this->addWidget(dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile("GameSceneSetMenu_1.json")));
		
		musicEffectSlider = dynamic_cast<UISlider*>(this->getWidgetByName("musicEffect"));
		musicVolumeSlider = dynamic_cast<UISlider*>(this->getWidgetByName("musicVolume"));
		UIButton* backGameBtn = dynamic_cast<UIButton*>(this->getWidgetByName("backGame"));
		UIButton* returnMainMenuBtn = dynamic_cast<UIButton*>(this->getWidgetByName("returnMainMenu"));
		
		musicEffectStatus = effectStatus;
		
		if(musicEffectStatus == 0){
			
			musicEffectSlider->setPercent(15);
		}else if(musicEffectStatus == 1){
			
			musicEffectSlider->setPercent(95);
		}
		musicVolumeSlider->setPercent(volumn);

		backGameBtn->addTouchEventListener(this, toucheventselector(GameSceneSetLayer::backGameBtn));
		returnMainMenuBtn->addTouchEventListener(this, toucheventselector(GameSceneSetLayer::returnMainMenuBtnFunc));
		musicEffectSlider->addEventListener(this, sliderpercentchangedselector(GameSceneSetLayer::musicEffectSliderCallFunc));
		musicVolumeSlider->addEventListener(this, sliderpercentchangedselector(GameSceneSetLayer::musicVolumeSliderCallFunc));
		
		return true;
	}
	
	return false;
}

void GameSceneSetLayer::musicEffectSliderCallFunc(cocos2d::CCObject *pSender, SliderEventType type)
{
	if(type == SLIDER_PERCENTCHANGED){
		
		if(musicEffectStatus == 0){
			
			musicEffectSlider->setPercent(95);
			musicEffectStatus=1;
		}else if(musicEffectStatus == 1){
			
			musicEffectSlider->setPercent(15);
			musicEffectStatus=0;
		}
	}
	
	GameScene::shareGameScene()->menuLayer->musicEffect = musicEffectStatus;
}

void GameSceneSetLayer::musicVolumeSliderCallFunc(cocos2d::CCObject *pSender, SliderEventType type)
{
	if(type == SLIDER_PERCENTCHANGED){
		
		if(musicVolumeSlider->getPercent()<8){
			musicVolumeSlider->setPercent(8);
		}else if(musicVolumeSlider->getPercent()>95){
			musicVolumeSlider->setPercent(95);
		}
	}
	
	GameScene::shareGameScene()->menuLayer->musicVolume = musicVolumeSlider->getPercent();
}

void GameSceneSetLayer::backGameBtn(cocos2d::CCObject *pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type){

	    GameScene::shareGameScene()->playLayer->imManArmature->resumeSchedulerAndActions();
	    GameScene::shareGameScene()->gameSceneMapLayer->move();
	
	    this->removeAllChildren();
	    this->removeFromParentAndCleanup(true);
	}
}

void GameSceneSetLayer::returnMainMenuBtnFunc(cocos2d::CCObject *pSender, TouchEventType type)
{
	MainMenuScene* mainMenuScene =  new MainMenuScene();
	mainMenuScene->init();
	
	CCTransitionFade* mainMenuSceneTransition =  CCTransitionFade::create(0.5, mainMenuScene, ccWHITE);
	CCDirector::sharedDirector()->replaceScene(mainMenuSceneTransition);
}