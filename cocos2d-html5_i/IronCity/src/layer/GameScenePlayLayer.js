/*
var GameScenePlayLayer = ACTION ({
    CROUCH = 0;

});*/
var GameScenePlayLayer = cc.Layer.extend({
    isMouseDown:false,
    actionNum:null,
    imManArmature:null,
    armaturePosition:null,
    m_tBeginPos:null,
    isAttack:false,

    monsterGroundAmount:0,
    monsterSkyAmount:0,

    ACTION_CROUCH:0,
    ACTION_RUN:1,
    ACTION_STAND_JUMP:2,
    ACTION_RUN_JUMP:3,
    ACTION_CROUCH_JUMP:4,
    ACTION_RUN_STOP:5,

    init:function () {
        this._super();
        this.setTouchEnabled(true);
        //this.setTouchMode(cc.TOUCH_ONE_BY_ONE);
        var size = cc.Director.getInstance().getWinSize();

        //cc.ArmatureDataManager.getInstance().addArmatureFileInfo(Json_IMCrouch);
        //cc.ArmatureDataManager.getInstance().addArmatureFileInfo(Json_IMCrouchJump);
        cc.ArmatureDataManager.getInstance().addArmatureFileInfo(Json_IMRun);
        cc.ArmatureDataManager.getInstance().addArmatureFileInfo(Json_IMRunJump);
        cc.ArmatureDataManager.getInstance().addArmatureFileInfo(Json_IMRunStop);
        cc.ArmatureDataManager.getInstance().addArmatureFileInfo(Json_IMStandJump);
        cc.ArmatureDataManager.getInstance().addArmatureFileInfo(Json_LaserRunAttack);
        cc.ArmatureDataManager.getInstance().addArmatureFileInfo(Json_LaserStandAttack);
        cc.ArmatureDataManager.getInstance().addArmatureFileInfo(Json_IMDead);

        this.touchTime = 0;
        this.isAttack = false;
        this.IMRunningStop();
        this.actionNum = this.ACTION_RUN_STOP;
    },

    runJumpActionCallBack:function(){

        this.imManArmature.stopAllActions();
        this.imManArmature.removeFromParent(false);
        this.IMRunning();
    },

    standJumpActionCallBack:function(){

        this.imManArmature.stopAllActions();
        this.imManArmature.removeFromParent(false);
        this.IMRunningStop();
    },
    registerWithTouchDispatcher:function(){
        cc.registerTargetedDelegate(0, false, this);
    },
    menuCloseCallback:function(){

        var splitCols = cc.MoveTo.create(1.0 ,cc.p(this.imManArmature.getPosition().x+300, this.imManArmature.getPosition().y));
        this.imManArmature.runAction(splitCols);
    },
//    onTouchBegan:function(sender){
//        console.log("Touch Began.");
//    },
    onTouchBegan:function (touches, event) {
        this.m_tBeginPos = touches.getLocation();
        //console.log("m_tBeginPos", this.m_tBeginPos);

        return true;
    },

    onTouchMoved:function (touches, event) {
        this.touchTime++;
    },

    onTouchEnded:function (touches, event) {
        //console.log("onTouchesEnded", this.touchTime, touches);
        if(this.isAttack){
            return;
        }
        if(this.touchTime>30)
        {
            this.touchTime = 0;
            return;
        }

        var touchLocation = touches.getLocation();
        var nMoveX = touchLocation.x - this.m_tBeginPos.x;
        var nMoveY = touchLocation.y - this.m_tBeginPos.y;
//        cc.log("m_tBeginPos.x = " + this.m_tBeginPos.x);
//        cc.log("touchLocation.x = " + touchLocation.x);
//        cc.log("nMoveX = %f ,nMoveY = " + nMoveX,nMoveY);
//        cc.log("tan1 = " + Math.tan(nMoveY/nMoveX));
//        cc.log("tan2 = " + Math.abs(Math.sqrt(3)/10));
        var radian = 10;
        //console.log("nMoveX: ", nMoveX, "nMoveY: ", nMoveY);

        if(this.touchTime<3 )//&& checkIfTouchNotInSetBtnArea(touchLocation,setBtnSize, setBtnLocation))
        {
            if(this.actionNum != this.ACTION_RUN && this.actionNum != this.ACTION_RUN_STOP)
                return;
            this.isAttack = true;
            this.imManArmature.stopAllActions();
            this.imManArmature.removeFromParent(false);
            if(this.actionNum == this.ACTION_RUN)
            {
                this.IMRunAttack(touchLocation);
            }
            else if(this.actionNum == this.ACTION_RUN_STOP)
            {
                this.IMStandAttack(touchLocation);
            }

            this.touchTime = 0;
            return;
        }

        this.touchTime = 0;

        if(nMoveX>10 && Math.abs(Math.tan(nMoveY/nMoveX))<Math.abs(Math.sqrt(3)/radian))
        {
            if(this.actionNum == this.ACTION_RUN)
                return;
            this.imManArmature.stopAllActions();
            this.imManArmature.removeFromParent(false);
            this.IMRunning();
        }else if(nMoveX<-10 && Math.abs(Math.tan(nMoveY/nMoveX))<Math.abs(Math.sqrt(3)/radian))
        {
            if(this.actionNum == this.ACTION_RUN_STOP)
                return;

            this.imManArmature.stopAllActions();
            this.imManArmature.removeFromParent(false);
            this.IMRunningStop();
        }else if(nMoveY>10 && Math.abs(Math.tan(nMoveY/nMoveX))>Math.abs(Math.sqrt(3)/radian))
        {
            if(this.actionNum == this.ACTION_STAND_JUMP ||
               this.actionNum == this.ACTION_RUN_JUMP ||
               this.actionNum == this.ACTION_CROUCH_JUMP)
               return;

            var armatureName = this.imManArmature.getName();
            this.imManArmature.stopAllActions();
            this.imManArmature.removeFromParent(false);

            if(armatureName == "IMRun")
            {
                this.IMRunJump();
                var jumpAction = cc.JumpTo.create(0.5,cc.p(this.imManArmature.getPosition().x,this.imManArmature.getPosition().y),100,1);
                var callBack = cc.CallFunc.create(function(){this.runJumpActionCallBack()}, this);
                var action = cc.Sequence.create(jumpAction,callBack);
                this.imManArmature.runAction(action);
            }else if(armatureName == "IMRunStop")
            {
                this.IMStandJump();
                var jumpAction = cc.JumpTo.create(0.5,cc.p(this.imManArmature.getPosition().x,this.imManArmature.getPosition().y),100,1);
                var callBack = cc.CallFunc.create(function(){this.standJumpActionCallBack()},this);
                var action = cc.Sequence.create(jumpAction,callBack);
                this.imManArmature.runAction(action);
            }
        }else if(nMoveY<-10 && Math.abs(Math.tan(nMoveY/nMoveX))>Math.abs(Math.sqrt(3)/radian))
        {
            if(this.actionNum == this.ACTION_CROUCH)
                return;
            this.imManArmature.stopAllActions();
            this.imManArmature.removeFromParent(false);
            this.IMRunningStop();
        }
    },

//    onTouchesCancelled:function (touches, event) {
//        console.log("onTouchesCancelled");
//    },


    IMRunning:function(){

        var armature = cc.Armature.create("IMRun");
        armature.getAnimation().play("Running");
        armature.getAnimation().setSpeedScale(1.5);
        armature.setScale(0.6);
        armature.setAnchorPoint(cc.p(0.5,0));
        armature.setPosition(cc.p(50, 50));
        this.armaturePosition = armature.getPosition();
        this.addChild(armature);
        this.imManArmature = armature;

        this.actionNum = this.ACTION_RUN;
        if(GameScene.getScene() && GameScene.getScene().moveMap)
            GameScene.getScene().moveMap.move();
    },

    IMRunJump:function(){

        var armature = cc.Armature.create("IMRunJump");
        armature.getAnimation().play("RuningJump");
        armature.getAnimation().setSpeedScale(1.5);
        armature.setScale(0.6);
        armature.setAnchorPoint(cc.p(0.5,0));
        armature.setPosition(cc.p(50, 50));
        this.armaturePosition = armature.getPosition();
        this.addChild(armature);
        this.imManArmature = armature;

        this.actionNum = this.ACTION_RUN_JUMP;
    },

    IMStandJump:function(){

        var armature = cc.Armature.create("IMStandJump");
        armature.getAnimation().play("StandJump");
        armature.getAnimation().setSpeedScale(1.5);
        armature.setScale(0.6);
        armature.setAnchorPoint(cc.p(0.5,0));
        armature.setPosition(cc.p(50, 50));
        this.armaturePosition = armature.getPosition();
        this.addChild(armature);
        this.imManArmature = armature;

        this.actionNum = this.ACTION_STAND_JUMP;
    },

    IMRunningStop:function(){
        var armature = cc.Armature.create("IMRunStop");
        armature.getAnimation().play("RunningStop");
        armature.getAnimation().setSpeedScale(1.5);
        armature.setScale(0.6);
        armature.setAnchorPoint(cc.p(0.5,0));
        armature.setPosition(cc.p(50, 50));
        this.armaturePosition = armature.getPosition();
        this.addChild(armature);
        this.imManArmature = armature;

        this.actionNum = this.ACTION_RUN_STOP;
        console.log("IMRunningStop.");
        if(GameScene.getScene() && GameScene.getScene().moveMap)
            GameScene.getScene().moveMap.stop();
    },
    IMRunAttack:function(touch){
        //console.log("IMRunAttack.");
        var armature = cc.Armature.create("LaserRunAttack");
        armature.getAnimation().play("RunningAttack");
        armature.getAnimation().setSpeedScale(1.5);
        armature.setScale(0.6);
        armature.setAnchorPoint(cc.p(0.5,0));
        armature.setPosition(cc.p(50, 50));
        this.armaturePosition = armature.getPosition();
        this.addChild(armature);
        this.imManArmature = armature;
        //console.log("IMRunAttack end.");
        armature.getAnimation().setMovementEventCallFunc(this.setAttackEvent, this);
        //armature.getAnimation().setFrameEventCallFunc(this.setAttackEvent, this);
    },
    IMStandAttack:function(touch){
        //console.log("IMStandAttack.");
        var armature = cc.Armature.create("LaserStandAttack");
        armature.getAnimation().play("StandAttack");
        armature.getAnimation().setSpeedScale(1.5);
        armature.setScale(0.6);
        armature.setAnchorPoint(cc.p(0.5,0));
        armature.setPosition(cc.p(50, 50));
        this.armaturePosition = armature.getPosition();
        this.addChild(armature);
        this.imManArmature = armature;
        armature.getAnimation().setMovementEventCallFunc(this.setAttackEvent, this);
        //console.log("IMStandAttack end.");
    },
    IMDeath:function(){
        ;
    },
    setAttackEvent:function(armature, movementType, movementID){
        //console.log("setAttackEvent, movementType:", movementType, "movementID: ", movementID, "armature: ", armature);
        if (movementType == CC_MovementEventType_COMPLETE || movementType == CC_MovementEventType_LOOP_COMPLETE)
        {
            //play audio and launch laser.
            //AudioPlayer::sharedAudio()->playEffect(Effect_Attack_0);
            //GameScene::shareGameScene()->laser->addLaser(_attackPos, _attackDir);
            this.isAttack = false;
            this.imManArmature.stopAllActions();
            this.imManArmature.removeFromParent(false);
            if(this.actionNum == this.ACTION_RUN)
            {
                this.IMRunning();
            }
            else if(this.actionNum == this.ACTION_RUN_STOP)
            {
                this.IMRunningStop();
            }
        }
    },
    Dead:function(armature, movementType, movementID){
        console.log("Dead");
    },
    checkIfTouchNotInSetBtnArea:function(touchPosition, setBtnSize, setBtnPosition){
        return true;
    },
    getMonsterGroundAmount:function(){
        return this.monsterGroundAmount;
    },
    getMonsterSkyAmount:function(){
        return this.monsterSkyAmount;
    }

});