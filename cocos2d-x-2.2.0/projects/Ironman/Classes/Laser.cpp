//
//  Laser.cpp
//  Ironman
//
//  Created by Ken on 13-10-18.
//
//

#include "Laser.h"

bool Laser::init(CCPoint position, float direction)
{
	this->create("iphone/laser.png");
	this->setPosition(position);
	this->setAnchorPoint(ccp(0, 0));
	this->setRotation(direction);
	
	return true;
}

void Laser::releaseLaser()
{
	this->removeFromParentAndCleanup(true);
}

bool Laser::ifOutSideWall()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	float laserX = this->getPosition().x;
	float laserY = this->getPosition().y;
	
	if(laserX < 0.0f || laserX > winSize.width || laserY < 0.0f || laserY > winSize.height){
		return true;
	}
	

	return false;
}