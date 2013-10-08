#include "StartScene.h"

USING_NS_CC;

CCScene* StartScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    StartScene *layer = StartScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(StartScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "StartScene" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
	animationTag = 0;
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("IMRun.ExportJson", this, schedule_selector(StartScene::dataLoaded));
    

    return true;
}
void StartScene::dataLoaded(float t)
{
	armature = NULL;
	armature = CCArmature::create("IMRun");
	armature->getAnimation()->playByIndex(animationTag);
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setScale(0.6f);
	armature->setPosition(ccp(130, 100));
	amaturePosition = armature->getPosition();
	addChild(armature);
}

void StartScene::menuCloseCallback(CCObject* pSender)
{
	animationTag++;
	if(animationTag == 3)
	{
		animationTag = 0;
	}
	armature->getAnimation()->playByIndex(animationTag);
	if(animationTag == 0)
	{
		armature->setPosition(amaturePosition);
	}
	if(animationTag == 1)
	{
		
		CCActionInterval * splitCols = CCMoveTo::create(1.0,CCPointMake(armature->getPosition().x+300,armature->getPosition().y));

		armature->runAction(splitCols);
	}
	/*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
	*/
}
