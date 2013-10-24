/**
 * Created with JetBrains WebStorm.
 * User: cocos
 * Date: 13-10-23
 * Time: 下午3:46
 * To change this template use File | Settings | File Templates.
 */
MonsterType = {
    MonsterGround_enum: 0,
    MonsterSky_enum: 1
};

var GameSceneMonster = cc.Layer.extend({
    MonsterAmature:null,
    MonsterAmatureBoundingBox:null,
    MonsterIndex:null,
    VisibleSize:null,
    VisiblePosition:null,
    init:function(){
        cc.ArmatureDataManager.getInstance().addArmatureFileInfo(Json_MonsterGroundMoving);
        cc.ArmatureDataManager.getInstance().addArmatureFileInfo(Json_MonsterSkyMoving);
        cc.ArmatureDataManager.getInstance().addArmatureFileInfo(Json_MonsterGroundAnimation);
        cc.ArmatureDataManager.getInstance().addArmatureFileInfo(Json_MonsterSkyAnimation);
        var r = this.random(0, 1);
        this.VisibleSize = cc.Director.getInstance().getVisibleSize();
        this.VisiblePosition  = cc.Director.getInstance().getVisibleOrigin();
        var height = this.random(0, this.VisiblePosition.y+200);
        var aPosition = cc.p(this.VisibleSize.width, height);

        switch (r)
        {
            case 0:
            {
                this.MonsterGroundMoving(cc.p(this.VisibleSize.width,20));
            }
                break;
            case 1:
            {
                this.MonsterSkyMoving(aPosition);
            }
                break;
            default:
                break;
        }

        return true;
    },
    MonsterGroundMoving:function(position){
        var pGameScene = GameScene.getScene();
        //console.log(pGameScene, pGameScene.playLayer);
        var armature = null;
        armature = cc.Armature.create("MonsterGroundMoving");
        armature.getAnimation().playByIndex(0);
        armature.getAnimation().setSpeedScale(1.5);
        armature.setScale(1.0);
        armature.setAnchorPoint(cc.p(0.5,0));
        armature.setPosition(position);
        this.addChild(armature);
        this.MonsterAmature = armature;
        this.MonsterIndex = MonsterType.MonsterGround_enum;
        var movePoint = cc.p(pGameScene.playLayer.imManArmature.getPosition().x-100,
            pGameScene.playLayer.imManArmature.getPosition().y);
        var jumpAction = cc.JumpTo.create(3.0, movePoint, 50, 3);
        var callBack = cc.CallFunc.create(this, this.JumpActionCallBack);
        var  action = cc.Sequence.create(jumpAction, callBack);
        this.MonsterAmature.runAction(action);
    },
    MonsterSkyMoving:function(position){
        var pGameScene = GameScene.getScene();
        var armature = null;
        armature = cc.Armature.create("MonsterSkyMoving");
        armature.getAnimation().playByIndex(0);
        armature.getAnimation().setSpeedScale(1.5);
        armature.setScale(1.0);
        armature.setAnchorPoint(cc.p(0.5,0));
        armature.setPosition(position);
        this.addChild(armature);
        this.MonsterAmature = armature;
        this.MonsterIndex = MonsterType.MonsterSky_enum;
        var movePoint = cc.p(pGameScene.playLayer.imManArmature.getPosition().x-100,
            pGameScene.playLayer.imManArmature.getPosition().y);
        var jumpAction = cc.JumpTo.create(3.0,movePoint,0,1);
        console.log("add action");
        var callBack = cc.CallFunc.create(this, this.JumpActionCallBack);
        var  action = cc.Sequence.create(jumpAction, callBack);
        this.MonsterAmature.runAction(action);
        console.log("run action.");
    },
    MonsterGroundDestroyAction:function(position){
        var armature = null;
        armature = cc.Armature.create("MonsterGroundAnimation");
        armature.getAnimation().playByIndex(0);
        armature.getAnimation().setSpeedScale(1.5);
        armature.setScale(1.0);
        armature.setAnchorPoint(cc.p(0.5,0));
        armature.setPosition(position);
        this.addChild(armature);
        this.MonsterAmature = armature;
        this.MonsterAmature.getAnimation().setMovementEventCallFunc(this.DestroyActionActionEnded, this);
    },
    MonsterSkyDestroyAction:function(position){
        var armature = null;
        armature = cc.Armature.create("MonsterSkyAnimation");
        armature.getAnimation().playByIndex(0);
        armature.getAnimation().setSpeedScale(1.5);
        armature.setScale(1.0);
        armature.setAnchorPoint(cc.p(0.5,0));
        armature.setPosition(position);
        this.addChild(armature);
        this.MonsterAmature = armature;
        this.MonsterAmature.getAnimation().setMovementEventCallFunc(this.DestroyActionActionEnded, this);
    },
    MonsterDestroyAction:function(armature, movementType, movementID){
        if (movementType == CC_MovementEventType_COMPLETE || movementType == CC_MovementEventType_LOOP_COMPLETE)
        {
            this.init();
        }
    },
    random:function(start, end){
        var i = cc.RANDOM_0_1()*(end-start+1)+start;
        return i | 0;
    },
    JumpActionCallBack:function(sender, data){
        var pGameScene = GameScene.getScene();
        switch (this.MonsterIndex)
        {
            case MonsterType.MonsterGround_enum:
            {
                var movePoint = cc.p(pGameScene.playLayer.imManArmature.getPosition().x-100,
                    pGameScene.playLayer.imManArmature.getPosition().y);
                var jumpAction = cc.JumpTo.create(3.0,movePoint,50,3);
                var  action = cc.Sequence.create(jumpAction, this.JumpActionCallBack, null);
                this.MonsterAmature.runAction(action);
            }
                break;
            case MonsterType.MonsterSky_enum:
            {
                var movePoint = cc.p(pGameScene.playLayer.imManArmature.getPosition().x-100,
                    pGameScene.playLayer.imManArmature.getPosition().y);
                var jumpAction = cc.JumpTo.create(3.0, movePoint, 0, 1);
                var  action = cc.Sequence.create(jumpAction, this.JumpActionCallBack, null);
                this.MonsterAmature.runAction(action);
            }
                break;
            default:
                break;
        }
    },
    draw:function(){
//        CCRect playerBoundingBoxCopy = GameScene::shareGameScene()->playLayer->playerBoundingBox;
//        float playerBoundingBoxX = playerBoundingBoxCopy.origin.x;
//        float playerBoundingBoxY = playerBoundingBoxCopy.origin.y;
//        float playerBoundingBoxWidth = playerBoundingBoxCopy.size.width;
//        float playerBoundingBoxHeight = playerBoundingBoxCopy.size.height;
//        CCPoint point1 = CCPointMake(playerBoundingBoxX,playerBoundingBoxY);
//        CCPoint point2 = CCPointMake(playerBoundingBoxX+playerBoundingBoxWidth,playerBoundingBoxY);
//        CCPoint point3 = CCPointMake(playerBoundingBoxX+playerBoundingBoxWidth,playerBoundingBoxY+playerBoundingBoxHeight);
//        CCPoint point4 = CCPointMake(playerBoundingBoxX,playerBoundingBoxY+playerBoundingBoxHeight);
//
//        //ª≠“ª∏ˆ∂‡±ﬂ–Œ
//        ccDrawColor4B(255, 255, 0, 255);
//        glLineWidth(1);
//        CCPoint vertices1[] = { point1, point2, point3, point4};
//        ccDrawPoly( vertices1, 4, true// «∑Ò∑‚±’
//        );
//
//        float MonsterAmatureBoundingBoxX = MonsterAmatureBoundingBox.origin.x;
//        float MonsterAmatureBoundingBoxY = MonsterAmatureBoundingBox.origin.y;
//        float MonsterAmatureBoundingBoxWidth = MonsterAmatureBoundingBox.size.width;
//        float MonsterAmatureBoundingBoxHeight = MonsterAmatureBoundingBox.size.height;
//
//        CCPoint point5 = CCPointMake(MonsterAmatureBoundingBoxX,MonsterAmatureBoundingBoxY);
//        CCPoint point6 = CCPointMake(MonsterAmatureBoundingBoxX+MonsterAmatureBoundingBoxWidth,MonsterAmatureBoundingBoxY);
//        CCPoint point7 = CCPointMake(MonsterAmatureBoundingBoxX+MonsterAmatureBoundingBoxWidth,MonsterAmatureBoundingBoxY+MonsterAmatureBoundingBoxHeight);
//        CCPoint point8 = CCPointMake(MonsterAmatureBoundingBoxX,MonsterAmatureBoundingBoxY+MonsterAmatureBoundingBoxHeight);
//
//        CCPoint vertices2[] = { point5, point6, point7, point8};
//        ccDrawPoly( vertices2, 4, true// «∑Ò∑‚±’
//        );
    },
    DestroyActionActionEnded:function(){
        console.log("Monster action event.");
        this.MonsterAmature.stopAllActions();
        //this.MonsterAmature.removeFromParent(false);
        this.MonsterAmature.removeAllChildren(true);

        switch (this.MonsterIndex)
        {
            case MonsterType.MonsterGround_enum:
            {
                this.MonsterGroundDestroyAction(this.MonsterAmature.getPosition());
            }
                break;
            case MonsterType.MonsterSky_enum:
            {
                this.MonsterSkyDestroyAction(this.MonsterAmature.getPosition());
            }
                break;
            default:
                break;
        }
    }
});