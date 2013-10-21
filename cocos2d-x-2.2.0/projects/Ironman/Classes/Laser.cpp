//
//  Laser.cpp
//  Ironman
//
//  Created by Ken on 13-10-18.
//
//

#include "Laser.h"

bool Laser::init(int idx, CCPoint position, float direction)
{
    this->initWithFile("laser.png");
	this->setPosition(position);
	this->setAnchorPoint(ccp(0, 0));
	this->setRotation(direction*180/3.14159);
    
    _idx = idx;
    int speed = 3;
    dir_x = cos(direction) * speed;
	dir_y = -sin(direction) * speed;
	return true;
}

void Laser::releaseLaser()
{
	//this->removeFromParentAndCleanup(true);
    ((LaserManager*) (this->getParent()))->removeLaser(_idx);
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

void Laser::update()
{
    if (ifOutSideWall()) {
        releaseLaser();
        return;
    }
    
    //if (<#condition#>) {
    //    releaseLaser();
    //}
    CCPoint pos = this->getPosition();
    //CCLog("pos: %f, %f", pos.x, pos.y);
    pos.x += dir_x;
    pos.y += dir_y;
    this->setPosition(pos);
}

/************************LaserManager************************/
bool LaserManager::init()
{
    CCLog("LaserManager init.");
    topNum = 0;
    for (int i=0; i<LASER_NUM_MAX; i++)
        if (lasers[i] == NULL)
    //this->scheduleUpdate();
    return true;
}

void LaserManager::addLaser(CCPoint pos, float dir)
{
    CCLog("Laser manager addLaser. %d", topNum);
    int idx = getIndex();
    Laser* laser = new Laser();
    laser->init(idx, pos, dir);
    this->addChild(laser);
	
    lasers[idx] = laser;
    if (idx >= topNum) {
        topNum++;
    }
}
void LaserManager::update(float dt)
{
    for (int i=0; i<topNum; i++) {
        if (lasers[i] != NULL) {
            lasers[i]->update();
        }
    }
}
void LaserManager::removeLaser(int idx)
{
    lasers[idx]->removeFromParentAndCleanup(true);
    lasers[idx] = NULL;
}
int LaserManager::getIndex()
{
    for (int i=0; i<topNum; i++) {
        if (lasers[i] == NULL) {
            return i;
        }
    }
    
    return topNum;
}
