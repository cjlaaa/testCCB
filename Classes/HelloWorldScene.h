#ifndef __MainScene_SCENE_H__
#define __MainScene_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MainScene :public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
, public cocos2d::extension::CCTableViewDataSource
, public cocos2d::extension::CCTableViewDelegate

{
public:
//    virtual bool init();
    static cocos2d::CCScene* createMainScene();
    void menuCloseCallback(CCObject* pSender);
//    CREATE_FUNC(MainScene);
    void CCBPlayCallback();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName);
    void onMenuTestClicked(cocos2d::CCObject * pSender);
    void onActionMenuClicked(CCObject* pSender);
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    void tableViewSubBtnCallback(CCObject* pSender);
    
    bool Init();
    cocos2d::CCSprite * mBurstSprite;
    cocos2d::CCLabelTTF * mTestTitleLabelTTF;
    CCMenuItemSprite* m_actionBtn;
    
    CCBAnimationManager* m_AnimationManager;
    bool m_bMenuShow;
    int m_count;
    void draw();
};

/* Forward declaration. */
//class CCBReader;
//
//class MainSceneLayerLoader : public cocos2d::extension::CCLayerLoader {
//public:
//    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainSceneLayerLoader, loader);
//    
//protected:
//    virtual MainScene * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) { 
//        return MainScene::create();
//    }
//
//};

#endif // __MainScene_SCENE_H__
