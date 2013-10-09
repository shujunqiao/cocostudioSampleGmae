#ifndef __StartScene_SCENE_H__
#define __StartScene_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
using namespace extension;
class StartScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
	void dataLoaded(float t);
	void ImCrouch();
	void IMRun();
	void IMJump();
	void jumpActionCallBack(CCNode* sender, void* data);
	CCArmature *imManArmature;
	CCPoint amaturePosition;

	CCPoint m_tBeginPos;
	CCPoint s_tCurPos;
	
    virtual void registerWithTouchDispatcher(void);
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	
	int actionNum;
	int touchTime;
	enum
	{
		ACTION_CROUCH = 0,
		 ACTION_RUN,
		ACTION_JUMP,
	};

    // implement the "static node()" method manually
    CREATE_FUNC(StartScene);
};

#endif // __StartScene_SCENE_H__
