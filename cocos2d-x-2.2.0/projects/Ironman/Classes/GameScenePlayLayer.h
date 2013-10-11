//
//  GameScenePlayLayer.h
//  Ironman
//
//  Created by Ken on 13-10-10.
//
//

#ifndef Ironman_GameScenePlayLayer_h
#define Ironman_GameScenePlayLayer_h
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;

using namespace extension;

class GameScenePlayLayer : public cocos2d::CCLayer
{
  public:
    
    bool init();
    
	void ImCrouch();
	void IMRun();
	void IMJump();
	void jumpActionCallBack(CCNode* sender, void* data);
	void ImStand();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    virtual void registerWithTouchDispatcher(void);
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);    
    
	int actionNum;
	int touchTime;
	CCArmature *imManArmature;
	CCPoint amaturePosition;

    CCPoint m_tBeginPos;
	CCPoint s_tCurPos;
    
	enum
	{
		ACTION_CROUCH = 0,
		ACTION_RUN,
		ACTION_JUMP,
		ACTION_RNNING_STAND,
	};
    
    CREATE_FUNC(GameScenePlayLayer);
};

#endif
