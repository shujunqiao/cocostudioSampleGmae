//
//  Laser.h
//  Ironman
//
//  Created by Ken on 13-10-18.
//
//

#ifndef Ironman_Laser_h
#define Ironman_Laser_h
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameScene.h"
USING_NS_CC;

class Laser : public CCSprite
{
public:
	
	bool init(CCPoint position, float direction);
    void releaseLaser();
	bool ifOutSideWall();
};



#endif
