#include "HelloWorldScene.h"
#include "ShaderUtils.h"
#include "cocos2dFilters.h"

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

bool MainScene::Init()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(MainScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));
    this->addChild(pLabel, 1,1);

    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
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
    }
    
//    CCSprite* pSp = CCSprite::create("Icon-144.png");
//    addChild(pSp,0,100);
//    pSp->setPosition(ccp(visibleSize.width/2,visibleSize.height/3));
    
    CCFilteredSpriteWithOne* pSpOne = CCFilteredSpriteWithOne::create("Icon-144.png");
    addChild(pSpOne);
    pSpOne->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
    CCGrayFilter* pF = CCGrayFilter::create(ccc4f(0.2, 0.3, 0.5, 0.1));
    pSpOne->setFilter(pF);

    CCFilteredSpriteWithMulti* pSpMulti = CCFilteredSpriteWithMulti::create("Icon-144.png");
    addChild(pSpMulti);
    pSpMulti->setPosition(ccp(visibleSize.width/2,visibleSize.height/4));
    CCHueFilter* pF1 = CCHueFilter::create(240);
    CCSaturationFilter* pF2 = CCSaturationFilter::create(1.5);
    CCBrightnessFilter* pF3 = CCBrightnessFilter::create(-0.4);
    CCArray* pArray = CCArray::create();
    pArray->addObject(pF1);
    pArray->addObject(pF2);
    pArray->addObject(pF3);
    pSpMulti->setFilters(pArray);
    
//    //test setBlendFunc
//    ccBlendFunc cbl = { GL_SRC_ALPHA , GL_ONE };
//    CCRotateBy * ccRotateBy = CCRotateBy::create(20.0f, 360);
//    CCRepeatForever * ccRepeatForever = CCRepeatForever::create(ccRotateBy);
//    this->mBurstSprite->runAction(ccRepeatForever);
//    pSp->setBlendFunc(cbl);
    
    //test Shader Utils
//    ShaderUtils::alphaMask(pSp, "Icon-114.png");
//    ShaderUtils::colorHSL(pSp, 120, 60);
    
    m_count = 0;
    
    return true;
}

void MainScene::draw()
{
    CCLayer::draw();
    
//    CCSprite* pSp = dynamic_cast<CCSprite*>(getChildByTag(100));
//    ShaderUtils::colorHSL(pSp, 0, 0);
//    CCLog("xxx");
}

void MainScene::CCBPlayCallback()
{
    CCLog("CCBPlayCallback");
}

void MainScene::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
    CCLog("onNodeLoaded...");
}

void MainScene::onActionMenuClicked(CCObject* pSender)
{
    if(m_bMenuShow)
    {
        m_AnimationManager->runAnimationsForSequenceNamed("menu_action_in");
        m_bMenuShow = false;
        m_actionBtn->setNormalImage(CCSprite::create("main/mainUiFeeling/mainUi_btn_gongneng.png"));
        
    }
    else
    {
        m_AnimationManager->runAnimationsForSequenceNamed("menu_action_out");
        m_bMenuShow = true;
        m_actionBtn->setNormalImage(CCSprite::create("main/mainUiFeeling/mainUi_btn_gongneng_2.png"));
    }
}

void MainScene::onMenuTestClicked(cocos2d::CCObject * pSender)
{
//    CCLog("onMenuTestClicked");
//    CCLabelTTF* pLabel = dynamic_cast<CCLabelTTF*>(getChildByTag(1));
//    CCLog("pLabel String %s",pLabel->getString());
//    pLabel->setString("onMenuTestClicked");
//    mTestTitleLabelTTF->setString("战力123K");
    CCLog("%d",m_count++);
}
                        
SEL_MenuHandler MainScene::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuTestClicked", MainScene::onMenuTestClicked);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onActionMenuClicked", MainScene::onActionMenuClicked);
    
    return NULL;
}
SEL_CallFuncN MainScene::onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this,"onCCBTestCallbacks",MainScene::onMenuTestClicked);
    
    return NULL;
};

SEL_CCControlHandler MainScene::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
    CCLog("onResolveCCBCCControlSelector...");
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onMenuTestClicked", MainScene::onMenuTestClicked);
    
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
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    CCNode * node1 = ccbReader->readNodeGraphFromFile("testCallbacks.ccbi", this);
    addChild(node1);
    
//    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
#endif
}