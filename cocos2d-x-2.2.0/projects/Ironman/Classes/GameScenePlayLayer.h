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
    
	void IMCrouch();
	void IMRunning();
    void IMRunJump();
	void IMStandJump();
	void IMCrouchJump();
	void IMRunningStop();
    void IMRunAttack(CCPoint touch);
    void IMStandAttack(CCPoint touch);
	void IMDeath();
    
    float getAngle(CCPoint touch);
    CCPoint getPosHand(float angle);
    void setAttackEvent(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID);
    void Dead(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID);
    
 	void runJumpActionCallBack(CCNode* sender, void* data);
 	void standJumpActionCallBack(CCNode* sender, void* data);
    void menuCloseCallback(CCObject* pSender);
    
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	int getMonsterGroundAmount();
	int getMonsterSkyAmount();
    
	int actionNum;
	int touchTime;
    int monsterGroundAmount;
    int monsterSkyAmount;
	CCArmature *imManArmature;
	int imManArmatureBrood;
	CCPoint amaturePosition;

    CCPoint m_tBeginPos;
	CCPoint s_tCurPos;
	enum
	{
		ACTION_CROUCH = 0,
		ACTION_RUN,
		ACTION_STAND_JUMP,
        ACTION_RUN_JUMP,
        ACTION_CROUCH_JUMP,
		ACTION_RUN_STOP,
        ACTION_RUN_ATTACK,
        ACTION_STAND_ATTACK,
		ACTION_DEATH
	};
 
    CREATE_FUNC(GameScenePlayLayer);
};

#endif
