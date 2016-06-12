#include "HelloWorldScene.h"

CCScene* MainScene::createMainScene()
{
    CCScene* scene = new CCScene;
    
    MainScene* pPlayer = new MainScene;
    if (pPlayer && pPlayer->Init()==true)
    {
        pPlayer->autorelease();
        scene->addChild(pPlayer);
        return scene;
    }
    delete pPlayer;
    delete scene;
    return NULL;
}

// on "init" you need to initialize your instance
bool MainScene::Init()
{
    //////////////////////////////
    // 1. super init first
//    if ( !CCLayer::init() )
//    {
//        return false;
//    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(MainScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
//    pLabel->setString("xxx");
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1,1);

    // add "MainScene" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    setTouchEnabled(true);
    
    /* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
//    ccNodeLoaderLibrary->registerCCNodeLoader("MainScene", MainSceneLayerLoader::loader());
    
    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    CCNode * node = ccbReader->readNodeGraphFromFile("MainScene.ccbi", this);
    m_AnimationManager = ccbReader->getAnimationManager();
    m_AnimationManager->runAnimationsForSequenceNamed("default");
    m_bMenuShow = true;
    
    ccbReader->release();
    
    if(node != NULL) {
        this->addChild(node);
        //        return node;
    }
    
    CCRotateBy * ccRotateBy = CCRotateBy::create(20.0f, 360);
    CCRepeatForever * ccRepeatForever = CCRepeatForever::create(ccRotateBy);
    this->mBurstSprite->runAction(ccRepeatForever);
    
    return true;
}

CCNode* MainScene::LoadCCB(CCScene* scene)
{
    /* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
//    ccNodeLoaderLibrary->registerCCNodeLoader("MainScene", MainSceneLayerLoader::loader());
    
    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
//    CCBAnimationManager* AnimationManager = ccbReader->getAnimationManager();
//    AnimationManager->runAnimations("Default Timeline");
//    AnimationManager->setAnimationCompletedCallback(scene, callfunc_selector(MainScene::CCBPlayCallback));
//    AnimationManager->runAnimationsForSequenceNamed("Default Timeline");
    
    /* Read a ccbi file. */
    //    CCNode * node = ccbReader->readNodeGraphFromFile("MainScene.ccbi", this);
    CCNode * node = ccbReader->readNodeGraphFromFile("MainScene.ccbi", scene);
    
    ccbReader->release();
    
    if(node != NULL) {
//        this->addChild(node);
        return node;
    }
    
    return NULL;
}

void MainScene::CCBPlayCallback()
{
    CCLog("CCBPlayCallback");
}

//void MainScene::registerWithTouchDispatcher()
//{
//    
//}

void MainScene::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
    CCLog("onNodeLoaded...");
//    CCRotateBy * ccRotateBy = CCRotateBy::create(20.0f, 360);
//    CCRepeatForever * ccRepeatForever = CCRepeatForever::create(ccRotateBy);
//    this->runAction(ccRepeatForever);
}

void MainScene::onActionMenuClicked(CCObject* pSender)
{
    if(m_bMenuShow)
    {
        m_AnimationManager->runAnimationsForSequenceNamed("menu_action_in");
        m_bMenuShow = false;
        m_actionBtn->setNormalImage(CCSprite::create("mainUi_btn_gongneng.png"));
        
    }
    else
    {
        m_AnimationManager->runAnimationsForSequenceNamed("menu_action_out");
        m_bMenuShow = true;
        m_actionBtn->setNormalImage(CCSprite::create("mainUi_btn_gongneng_2.png"));
    }
}

void MainScene::onMenuTestClicked(cocos2d::CCObject * pSender)
{
    CCLog("onMenuTestClicked");
    CCLabelTTF* pLabel = dynamic_cast<CCLabelTTF*>(getChildByTag(1));
    CCLog("pLabel String %s",pLabel->getString());
    pLabel->setString("onMenuTestClicked");
    mTestTitleLabelTTF->setString("战力123K");
}
                        
SEL_MenuHandler MainScene::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuTestClicked", MainScene::onMenuTestClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onActionMenuClicked", MainScene::onActionMenuClicked);
    
    return NULL;
}
SEL_CallFuncN MainScene::onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this,"onCCBTestCallbacks",MainScene::onMenuTestClicked)
    return NULL;
};

SEL_CCControlHandler MainScene::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
    CCLog("onResolveCCBCCControlSelector...");
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuTestClicked", MainScene::onMenuTestClicked);
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSpriteTestClicked", HelloCocosBuilderLayer::onSpriteTestClicked);
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonTestClicked", HelloCocosBuilderLayer::onButtonTestClicked);
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onAnimationsTestClicked", HelloCocosBuilderLayer::onAnimationsTestClicked);
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onParticleSystemTestClicked", HelloCocosBuilderLayer::onParticleSystemTestClicked);
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onScrollViewTestClicked", HelloCocosBuilderLayer::onScrollViewTestClicked);
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onTimelineCallbackSoundClicked", HelloCocosBuilderLayer::onTimelineCallbackSoundClicked);
    
    return NULL;
}

bool MainScene::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    CCLog("onAssignCCBMemberVariable...");
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBurstSprite", CCSprite *, this->mBurstSprite);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTestTitleLabelTTF", CCLabelTTF *, this->mTestTitleLabelTTF);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_actionBtn", CCMenuItemSprite *, this->m_actionBtn);
    
    return false;
}

bool MainScene::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    CCLog("onAssignCCBCustomProperty...");
    bool bRet = false;
//    if (pTarget == this)
//    {
//        if (0 == strcmp(pMemberVariableName, "mCustomPropertyInt"))
//        {
//            this->mCustomPropertyInt = pCCBValue->getIntValue();
//            CCLog("mCustomPropertyInt = %d", mCustomPropertyInt);
//            bRet = true;
//        }
//        else if ( 0 == strcmp(pMemberVariableName, "mCustomPropertyFloat"))
//        {
//            this->mCustomPropertyFloat = pCCBValue->getFloatValue();
//            CCLog("mCustomPropertyFloat = %f", mCustomPropertyFloat);
//            bRet = true;
//        }
//        else if ( 0  == strcmp(pMemberVariableName, "mCustomPropertyBoolean"))
//        {
//            this->mCustomPropertyBoolean = pCCBValue->getBoolValue();
//            CCLog("mCustomPropertyBoolean = %d", mCustomPropertyBoolean);
//            bRet = true;
//        }
//        else if ( 0  == strcmp(pMemberVariableName, "mCustomPropertyString"))
//        {
//            this->mCustomPropertyString = pCCBValue->getStringValue();
//            CCLog("mCustomPropertyString = %s", mCustomPropertyString.c_str());
//            bRet = true;
//        }
//        
//    }
    
    return bRet;
}


void MainScene::menuCloseCallback(CCObject* pSender)
{
//    LoadCCB();
    
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
