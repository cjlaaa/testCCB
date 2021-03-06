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
    
//    /* Create an autorelease CCNodeLoaderLibrary. */
//    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
////    ccNodeLoaderLibrary->registerCCNodeLoader("MainScene", MainSceneLayerLoader::loader());
//    /* Create an autorelease CCBReader. */
//    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
//    /* Read a ccbi file. */
//    CCNode * node = ccbReader->readNodeGraphFromFile("MainScene.ccbi", this);
//    m_AnimationManager = ccbReader->getAnimationManager();
//    m_AnimationManager->runAnimationsForSequenceNamed("default");
//    m_bMenuShow = true;
//    ccbReader->release();
//    if(node != NULL) {
//        this->addChild(node);
//    }
    
//    CCFilteredSpriteWithOne* pSpOne = CCFilteredSpriteWithOne::create("Icon-144.png");
//    addChild(pSpOne);
//    pSpOne->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
//    CCGrayFilter* pF = CCGrayFilter::create(ccc4f(0.2, 0.3, 0.5, 0.1));
//    pSpOne->setFilter(pF);
//
//    CCFilteredSpriteWithMulti* pSpMulti = CCFilteredSpriteWithMulti::create("Icon-144.png");
//    addChild(pSpMulti);
//    pSpMulti->setPosition(ccp(visibleSize.width/2,visibleSize.height/4));
//    CCHueFilter* pF1 = CCHueFilter::create(240);
//    CCSaturationFilter* pF2 = CCSaturationFilter::create(1.5);
//    CCBrightnessFilter* pF3 = CCBrightnessFilter::create(-0.4);
//    CCArray* pArray = CCArray::create();
//    pArray->addObject(pF1);
//    pArray->addObject(pF2);
//    pArray->addObject(pF3);
//    pSpMulti->setFilters(pArray);
    
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
    
//    CCSprite *sprite = CCSprite::create("Icon-144.png");
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//    CCTableView* tableView = CCTableView::create(this,ccp(sprite->getContentSize().width*4,sprite->getContentSize().height*4));
//    tableView->setDirection(kCCScrollViewDirectionVertical);
//    tableView->setPosition(ccp(winSize.width/3,winSize.height/3));
//    tableView->setDelegate(this);
//    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
//    this->addChild(tableView,0,111);
//    tableView->reloadData();
//    sprite->release();
    
    //背景图片
    CCSprite * background = CCSprite::create("HelloWorld.png");
    background->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
    this->addChild(background,0);
    //创建一个裁剪节点用来实现遮罩的效果
    CCClippingNode * clippingNode = CCClippingNode::create();
    this->addChild(clippingNode,1);
    //向裁剪节点中加入内容，这里加入的是一个透明的层
    CCLayerColor * layer = CCLayerColor::create(ccc4(0,0,0,200));
    clippingNode->addChild(layer);
    //继续向裁剪节点中加入内容，这里加入的是一个精灵
    CCSprite * sprite = CCSprite::create("Icon-144.png");
    sprite->setPosition(ccp(visibleSize.width/4,visibleSize.height/2));
    clippingNode->addChild(sprite);
    //创建模板，裁剪节点将按照这个模板来裁剪区域
    CCSprite * stencil = CCSprite::create("Icon-114.png");
    stencil->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
    clippingNode->setStencil(stencil);
    //向裁剪节点中加入精灵，精灵的位置和裁剪的位置相同，所以最后让裁剪掉了
    CCSprite * sprite2 = CCSprite::create("Icon-144.png");
    sprite2->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
    clippingNode->addChild(sprite2);
    //这个是用来设置显示裁剪区域还是非裁剪区域的
    clippingNode->setInverted(true);
    //我们之前放了一张裁剪的模板，按照这个模板裁剪的时候同时按照这个alpha的值裁剪，这个值的范围是0-1
    //设为0就把透明的区域裁剪掉了
//    clippingNode->setAlphaThreshold(0);
    
    return true;
}

void MainScene::scrollViewDidScroll(CCScrollView* view)
{
//    CCLog("scrollViewDidScroll");
};

void MainScene::scrollViewDidZoom(CCScrollView* view)
{
//    CCLog("scrollViewDidZoom");
}

void MainScene::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("tableCellTouched,%d",cell->getIdx());
}

CCSize MainScene::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    CCSprite *sprite = CCSprite::create("Icon-144.png");
    CCSize size = sprite->getContentSize();
    sprite->release();
    return size;
}

void MainScene::tableViewSubBtnCallback(CCObject* pSender)
{
    CCTableViewCell *cell = (CCTableViewCell*)(((CCMenuItemImage*)pSender)->getParent()->getParent());
    CCLog("tableViewSubBtnCallback,%d",cell->getIdx());
//    ((CCMenuItemImage*)pSender)->setScaleX(2);
}


CCTableViewCell* MainScene::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCString *string = CCString::createWithFormat("%d", idx);
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        CCSprite *sprite = CCSprite::create("Icon-144.png");
        sprite->setAnchorPoint(CCPointZero);
        sprite->setPosition(ccp(0, 0));
        sprite->setScaleX(2);
        cell->addChild(sprite);
        
        CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 20.0);
        label->setPosition(CCPointZero);
        label->setAnchorPoint(CCPointZero);
        label->setTag(123);
        cell->addChild(label);
        
        CCMenuItemImage *pBtn = CCMenuItemImage::create(
                                                        "CloseNormal.png",
                                                        "CloseSelected.png",
                                                        this,
                                                        menu_selector(MainScene::tableViewSubBtnCallback));
        CCMenu* pMenu = CCMenu::create(pBtn, NULL);
        pBtn->setPosition(ccp(pBtn->getContentSize().width/2,pBtn->getContentSize().height/2));
        pMenu->setPosition(CCPointZero);
        cell->addChild(pMenu, 1);
        cell->setTag(idx);
    }
    else
    {
        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
        label->setString(string->getCString());
    }

    
    return cell;
}

unsigned int MainScene::numberOfCellsInTableView(CCTableView *table)
{
    return 100;
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