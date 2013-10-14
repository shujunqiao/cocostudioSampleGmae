/*
var GameScenePlayLayer = ACTION ({
    CROUCH = 0;

});*/
var GameScenePlayLayer = cc.Layer.extend({
    isMouseDown:false,
    armature:null,
    ACTION_CROUCH:0,
    ACTION_RUN:1,
    ACTION_STAND_JUMP:2,
    ACTION_RUN_JUMP:3,
    ACTION_CROUCH_JUMP:4,
    ACTION_RUN_STOP:5,
    init:function () {
        var selfPointer = this;

        this._super();

        var size = cc.Director.getInstance().getWinSize();

        cc.ArmatureDataManager.getInstance().addArmatureFileInfo(Json_IMCrouch);
        cc.ArmatureDataManager.getInstance().addArmatureFileInfo(Json_IMCrouchJump);
        cc.ArmatureDataManager.getInstance().addArmatureFileInfo(Json_IMRun);
        cc.ArmatureDataManager.getInstance().addArmatureFileInfo(Json_IMRunJump);
        cc.ArmatureDataManager.getInstance().addArmatureFileInfo(Json_IMRunStop);
        cc.ArmatureDataManager.getInstance().addArmatureFileInfo(Json_IMStandJump);
        cc.ArmatureDataManager.getInstance().addArmatureFileInfo(Json_LaserRunAttack);
        cc.ArmatureDataManager.getInstance().addArmatureFileInfo(Json_LaserStandAttack);

        this.touchTime = 0;
        this.IMCrouch();
        this.actionNum = this.ACTION_CROUCH;

/*
        var armature = cc.Armature.create("IMRun");
        armature.getAnimation().play("Running");
        armature.setScale(1.0);
        armature.setAnchorPoint(cc.p(0.5, 0.5));
        armature.setPosition(cc.p(100, size.height / 2));
        this.addChild(armature);
*/

        return true;
    },
    onTouchesBegan:function (touches, event) {
        this.isMouseDown = true;
    },
    onTouchesMoved:function (touches, event) {
        if (this.isMouseDown) {
            if (touches) {
                //this.circle.setPosition(cc.p(touches[0].getLocation().x, touches[0].getLocation().y));
            }
        }
    },
    onTouchesEnded:function (touches, event) {
        this.isMouseDown = false;
    },
    onTouchesCancelled:function (touches, event) {
        console.log("onTouchesCancelled");
    },

    IMCrouch:function(){
    armature = cc.Armature.create("IMCrouch");
    armature.getAnimation().play("crouch");
    armature.getAnimation().setSpeedScale(1.5);
    armature.setScale(0.6);
    armature.setAnchorPoint(cc.p(0.5,0));
    armature.setPosition(cc.p(50, 50));
    amaturePosition = armature.getPosition();
    this.addChild(armature);
      
    actionNum = this.ACTION_CROUCH;
    },

  IMRunning:function(){
    armature = cc.Armature.create("IMRun");
    armature.getAnimation().play("Running");
    armature.getAnimation().setSpeedScale(1.5);
    armature.setScale(0.6);
    armature.setAnchorPoint(cc.p(0.5,0));
    armature.setPosition(cc.p(50, 50));
    amaturePosition = armature.getPosition();
    this.addChild(armature);
      
    actionNum = this.ACTION_RUN;
},

  IMStandJump:function(){
    armature = cc.Armature.create("IMStandJump");
    armature.getAnimation().play("StandJump");
    armature.getAnimation().setSpeedScale(1.5);
    armature.setScale(0.6);
    armature.setAnchorPoint(cc.p(0.5,0));
    armature.setPosition(cc.p(50, 50));
    amaturePosition = armature.getPosition();
    this.addChild(armature);
      
    actionNum = this.ACTION_STAND_JUMP;
},

  IMRunJump:function(){
    armature = cc.Armature.create("IMRunJump");
    armature.getAnimation().play("RuningJump");
    armature.getAnimation().setSpeedScale(1.5);
    armature.setScale(0.6);
    armature.setAnchorPoint(cc.p(0.5,0));
    armature.setPosition(cc.p(50, 50));
    amaturePosition = armature.getPosition();
    this.addChild(armature);
      
    actionNum = this.ACTION_RUN_JUMP;
},

  IMCrouchJump:function(){

    
    armature = cc.Armature.create("IMCrouchJump");
    armature.getAnimation().play("CrouchJump");
    armature.getAnimation().setSpeedScale(1.5);
    armature.setScale(0.6);
    armature.setAnchorPoint(cc.p(0.5,0));
    armature.setPosition(cc.p(50, 50));
    amaturePosition = armature.getPosition();
    this.addChild(armature);
      
    actionNum = this.ACTION_CROUCH_JUMP;
},

  IMRunningStop:function(){
    armature = cc.Armature.create("IMRunStop");
    armature.getAnimation().play("RunningStop");
    armature.getAnimation().setSpeedScale(1.5);
    armature.setScale(0.6);
    armature.setAnchorPoint(cc.p(0.5,0));
    armature.setPosition(cc.p(50, 50));
    amaturePosition = armature.getPosition();
    this.addChild(armature);
      
    actionNum = this.ACTION_RUN_STOP;
}

});


