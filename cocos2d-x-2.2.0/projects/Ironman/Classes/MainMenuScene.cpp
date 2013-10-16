//
//  MainMenuScene.cpp
//  Ironman
//
//  Created by Ken on 13-10-10.
//
//

#include "MainMenuScene.h"
#include "GameScene.h"

bool MainMenuScene::init()
{    
    CCLayer* menuLayer = CCLayer::create();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // Add backgrounbdPic
    CCSprite* backGroundPic = CCSprite::create("iphone/MainMenuSceneBK.png");
    backGroundPic->setAnchorPoint(ccp(0, 0));
    
    menuLayer->addChild(backGroundPic,0);
    
    //Add StartBtn
    CCSprite* start     = CCSprite::create("iphone/StartBtn.png");
    CCSprite* startPush = CCSprite::create("iphone/StartBtnPush.png");
    
    CCMenuItemSprite * startBtn = CCMenuItemSprite::create(start, startPush, this, menu_selector(MainMenuScene::startBtnCallFunc));
    
    //Add Menu
    mainMenu = CCMenu::create(startBtn, NULL);
    mainMenu->setAnchorPoint(ccp(0, 0));
    mainMenu->setPosition(ccp(size.width/2, size.height/5));

    menuLayer->addChild(mainMenu,1);
    this->addChild(menuLayer);
    return true;
}

void MainMenuScene::startBtnCallFunc(CCObject* pSender)
{
	CCMenuItemSprite *  startBtn = (CCMenuItemSprite *  )pSender;
	startBtn->setOpacity(0);
	mainMenu->setEnabled(false);

	CCSprite * activity = CCSprite::create("loading.png");
	activity->setPosition(ccp(240,65));
	addChild(activity);
	
	CCRotateBy * rotateAction = CCRotateBy::create(0.5f,180.0f);
	activity->runAction(CCRepeatForever::create(rotateAction));
	
	loadingCount = 0;
	dataLoaded(loadingCount);

   
}
void MainMenuScene::dataLoaded(float percent)
{
	
	switch (loadingCount)
	{
		case 0:
		{
			CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("iphone/IMCrouch.ExportJson",this, schedule_selector(MainMenuScene::dataLoaded));
		}
		break;
		case 1:
		{
			CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("iphone/IMRun.ExportJson",this, schedule_selector(MainMenuScene::dataLoaded));
		}
		break;
		case 2:
		{
			CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("iphone/IMRunJump.ExportJson",this, schedule_selector(MainMenuScene::dataLoaded));
		}
		break;
		case 3:
		{
			CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("iphone/IMStandJump.ExportJson",this, schedule_selector(MainMenuScene::dataLoaded));
		}
		break;
		case 4:
		{
			CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("iphone/IMCrouchJump.ExportJson",this, schedule_selector(MainMenuScene::dataLoaded));
		}
		break;
		case 5:
		{
			CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("iphone/IMRunStop.ExportJson",this, schedule_selector(MainMenuScene::dataLoaded));
		}
		break;
		case 6:
		{
			CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("iphone/LaserRunAttack.ExportJson",this, schedule_selector(MainMenuScene::dataLoaded));
		}
		break;
		case 7:
		{
			CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("iphone/LaserStandAttack.ExportJson",this, schedule_selector(MainMenuScene::dataLoaded));
		}
		break;

	default:
		{
			GameScene* gameScene = new GameScene();
			gameScene->init();
    
			CCTransitionFade* gameSceneTransition =  CCTransitionFade::create(0.5, gameScene, ccWHITE);
			CCDirector::sharedDirector()->replaceScene(gameSceneTransition);
		}
		break;
	}	
	loadingCount++;
	
}