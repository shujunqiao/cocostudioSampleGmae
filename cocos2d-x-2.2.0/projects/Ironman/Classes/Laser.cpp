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
    
    laserAmatureBoundingBox = CCRectMake(-5, -5, 90, 10);
    
    _idx = idx;
    int speed = 3;
    dir_x = cos(direction) * speed;
	dir_y = -sin(direction) * speed;
	return true;
}

void Laser::draw()
{
    CCRect playerBoundingBoxCopy = laserAmatureBoundingBox;
	float playerBoundingBoxX = playerBoundingBoxCopy.origin.x;
	float playerBoundingBoxY = playerBoundingBoxCopy.origin.y;
	float playerBoundingBoxWidth = playerBoundingBoxCopy.size.width;
	float playerBoundingBoxHeight = playerBoundingBoxCopy.size.height;
	CCPoint point1 = CCPointMake(playerBoundingBoxX,playerBoundingBoxY);
	CCPoint point2 = CCPointMake(playerBoundingBoxX+playerBoundingBoxWidth,playerBoundingBoxY);
	CCPoint point3 = CCPointMake(playerBoundingBoxX+playerBoundingBoxWidth,playerBoundingBoxY+playerBoundingBoxHeight);
	CCPoint point4 = CCPointMake(playerBoundingBoxX,playerBoundingBoxY+playerBoundingBoxHeight);
    
    ccDrawColor4B(255, 255, 0, 255);
    glLineWidth(1);
    CCPoint vertices1[] = { point1, point2, point3, point4};
    ccDrawPoly( vertices1, 4, true);
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
    
    if (GameScene::shareGameScene()->gameSceneMonster->MonsterAmatureBoundingBox.intersectsRect(laserAmatureBoundingBox))
	{
        //delete self.
		releaseLaser();
        //add score.
        int type = GameScene::shareGameScene()->gameSceneMonster->MonsterIndex;
        if (type == MonsterSky_enum) {
            GameScene::shareGameScene()->playLayer->monsterSkyAmount ++;
        }
        else{
            GameScene::shareGameScene()->playLayer->monsterGroundAmount ++;
        }
        //delete monster.
        GameScene::shareGameScene()->gameSceneMonster->MonsterDestroyAction();
        
        return;
	}
    
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
    attackTime = 0;
    for (int i=0; i<LASER_NUM_MAX; i++)
        if (lasers[i] == NULL)
    //this->scheduleUpdate();
    return true;
}

void LaserManager::addLaser(CCPoint pos, float dir)
{
    if (attackTime > 0) {
        return;
    }
    CCLog("Laser manager addLaser. %d", topNum);
    int idx = getIndex();
    Laser* laser = new Laser();
    laser->init(idx, pos, dir);
    this->addChild(laser);
	
    lasers[idx] = laser;
    if (idx >= topNum) {
        topNum++;
    }
    
    attackTime = 60;
}
void LaserManager::update(float dt)
{
    if (attackTime > 0) {
        attackTime --;
    }
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
