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
    
	int animationTag;
	void dataLoaded(float t);
	CCArmature *armature;
	CCPoint amaturePosition;

    // implement the "static node()" method manually
    CREATE_FUNC(StartScene);
};

#endif // __StartScene_SCENE_H__
