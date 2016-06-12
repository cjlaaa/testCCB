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
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
//    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* createMainScene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
//    CREATE_FUNC(MainScene);
    
    CCNode* LoadCCB(CCScene*);
    
    void CCBPlayCallback();
//    static CCBAnimationManager* m_AnimationManager;
    
//    virtual void registerWithTouchDispatcher();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName);
    void onMenuTestClicked(cocos2d::CCObject * pSender);
    void onActionMenuClicked(CCObject* pSender);
    
    bool Init();
    cocos2d::CCSprite * mBurstSprite;
    cocos2d::CCLabelTTF * mTestTitleLabelTTF;
    CCMenuItemSprite* m_actionBtn;
    
    CCBAnimationManager* m_AnimationManager;
    bool m_bMenuShow;
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
