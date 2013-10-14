var s_HelloWorld = "res/HelloWorld.png";
var s_CloseNormal = "res/CloseNormal.png";
var s_CloseSelected = "res/CloseSelected.png";

var s_s_IMCrouchPng = "res/IMCrouch0.png";
var s_IMCrouchExportJson = "res/IMCrouch.ExportJson";
var s_IMCrouchPlist = "res/IMCrouch0.plist";

var s_s_IMRunPng = "res/IMRun0.png";
var s_IMRunExportJson = "res/IMRun.ExportJson";
var s_IMRunPlist = "res/IMRun0.plist";

var s_s_IMRunJumpPng = "res/IMRunJump0.png";
var s_IMRunJumpExportJson = "res/IMRunJump.ExportJson";
var s_IMRunJumpPlist = "res/IMRunJump0.plist";



cc.ArmatureDataManager.getInstance().addArmatureFileInfo("res/IMStandJump.ExportJson");
cc.ArmatureDataManager.getInstance().addArmatureFileInfo("res/IMCrouchJump.ExportJson");
cc.ArmatureDataManager.getInstance().addArmatureFileInfo("res/IMRunStop.ExportJson");
cc.ArmatureDataManager.getInstance().addArmatureFileInfo("res/LaserRunAttack.ExportJson");
cc.ArmatureDataManager.getInstance().addArmatureFileInfo("res/LaserStandAttack.ExportJson");

var g_resources = [
    //image
    {src:s_HelloWorld},
    {src:s_CloseNormal},
    {src:s_CloseSelected},
    {src:s_s_IMRunPng},
    {src:s_s_IMCrouchPng},
    {src:s_s_IMRunJumpPng},

    //Json
    {src:s_IMRunExportJson},
    {src:s_IMCrouchExportJson},
    {src:s_IMCrouchExportJson},

    //plist
    {src:s_IMRunPlist},
    {src:s_IMCrouchPlist}

    //fnt

    //tmx

    //bgm

    //effect
];