var GameScene = cc.Scene.extend({
    moveMap:null,
    playerLayer:null,
    menuLayer:null,
    gameSceneMonster:null,
    onEnter:function () {
        this._super();

        //map
        this.moveMap = new MovedMap();
        this.moveMap.init();
        this.moveMap.setMovedSpeed(3);
        this.addChild(this.moveMap, 0);

        //menu
        this.menuLayer = new GameSceneMenuLayer();
        this.menuLayer.init(100, "0");
        this.menuLayer.setAnchorPoint(cc.p(0, 0));
        this.menuLayer.setPosition(cc.p(0, 0));
        this.menuLayer.setScale(0.5);
        this.addChild(this.menuLayer, 0);

        //player
        this.playLayer = new GameScenePlayLayer();
        this.playLayer.init();
        this.addChild(this.playLayer, 0);

        //monster
        this.gameSceneMonster = new GameSceneMonster();
        this.gameSceneMonster.init();
        this.addChild(this.gameSceneMonster, 0);

        //this.scheduleUpdate();
    },
    gameOver:function(){
        console.log("gameOver.");
        var overLayer = new GameSceneOverLayer();

        if (!overLayer.init())
        {
            overLayer = null;
            return;
        }

        this.playLayer.stopAllActions();
        this.playLayer.unscheduleUpdate();
        this.moveMap.stop();
        this.gameSceneMonster.stopAllActions();
        this.gameSceneMonster.unscheduleUpdate();

        this.menuLayer.unscheduleUpdate();

        this.addChild(overLayer, 0);
    },
    update:function(dt){
        console.log("update.");
//        CCArmature * imManArmature = playLayer->imManArmature;
//        int actionNum = playLayer->actionNum;
//        if(actionNum ==playLayer->ACTION_RUN)
//        {
//            playLayer->playerBoundingBox = CCRectMake(imManArmature->getPosition().x-imManArmature->getContentSize().width/2+46,imManArmature->getPosition().y,imManArmature->getContentSize().width-90,imManArmature->getContentSize().height-50);
//        }
//        else if(actionNum == playLayer->ACTION_STAND_JUMP)
//        {
//            playLayer->playerBoundingBox = CCRectMake(imManArmature->getPosition().x-imManArmature->getContentSize().width/2+30,imManArmature->getPosition().y,imManArmature->getContentSize().width-50,imManArmature->getContentSize().height-50);
//        }
//        else if(actionNum == playLayer->ACTION_RUN_JUMP)
//        {
//            playLayer->playerBoundingBox = CCRectMake(imManArmature->getPosition().x-imManArmature->getContentSize().width/2+33,imManArmature->getPosition().y,imManArmature->getContentSize().width-70,imManArmature->getContentSize().height-50);
//        }
//        else if(actionNum == playLayer->ACTION_RUN_STOP)
//        {
//            playLayer->playerBoundingBox = CCRectMake(imManArmature->getPosition().x-imManArmature->getContentSize().width/2+40,imManArmature->getPosition().y,imManArmature->getContentSize().width-110,imManArmature->getContentSize().height-45);
//        }
//        else if(actionNum == playLayer->ACTION_RUN_ATTACK)
//        {
//            playLayer->playerBoundingBox = CCRectMake(imManArmature->getPosition().x-imManArmature->getContentSize().width/2,imManArmature->getPosition().y,imManArmature->getContentSize().width,imManArmature->getContentSize().height);
//
//        }
//        else if(actionNum == playLayer->ACTION_STAND_ATTACK)
//        {
//            playLayer->playerBoundingBox = CCRectMake(imManArmature->getPosition().x-imManArmature->getContentSize().width/2,imManArmature->getPosition().y,imManArmature->getContentSize().width,imManArmature->getContentSize().height);
//
//        }
//        else if(actionNum == playLayer->ACTION_DEATH)
//        {
//            playLayer->playerBoundingBox = CCRectMake(imManArmature->getPosition().x-imManArmature->getContentSize().width/2,imManArmature->getPosition().y,imManArmature->getContentSize().width,imManArmature->getContentSize().height);
//        }
//
//        if(gameSceneMonster->MonsterIndex == MonsterGround_enum)
//        {
//            gameSceneMonster->MonsterAmatureBoundingBox = CCRectMake(gameSceneMonster->MonsterAmature->getPosition().x-gameSceneMonster->MonsterAmature->getContentSize().width/2+45,gameSceneMonster->MonsterAmature->getPosition().y+21,gameSceneMonster->MonsterAmature->getContentSize().width-90,gameSceneMonster->MonsterAmature->getContentSize().height-90);
//        }
//        else if(gameSceneMonster->MonsterIndex == MonsterSky_enum)
//        {
//            gameSceneMonster->MonsterAmatureBoundingBox = CCRectMake(gameSceneMonster->MonsterAmature->getPosition().x-gameSceneMonster->MonsterAmature->getContentSize().width/2+45,gameSceneMonster->MonsterAmature->getPosition().y+21,gameSceneMonster->MonsterAmature->getContentSize().width-90,gameSceneMonster->MonsterAmature->getContentSize().height-90);
//        }
//
//        if (playLayer->playerBoundingBox.intersectsRect(gameSceneMonster->MonsterAmatureBoundingBox))
//        {
//            //this->unscheduleUpdate();
//            //gameSceneMonster->MonsterDestroyAction();
//            playLayer->imManArmatureBrood-=1;
//            if(playLayer->imManArmatureBrood<1)
//            {
//                GameScene::shareGameScene()->menuLayer->setBroodBarPercent(0);
//                this->unscheduleUpdate();
//                playLayer->IMDeath();
//                return;
//            }
//
//            GameScene::shareGameScene()->menuLayer->setBroodBarPercent(playLayer->imManArmatureBrood);
//        }
    }
});

GameScene.Scene = null;
GameScene.getScene = function(){
    return this.Scene;
}
