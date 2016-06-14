//
//  ShaderUtils.h
//  landking
//
//  Created by wxg on 16/1/7.
//
//

#ifndef __landking__ShaderUtils__
#define __landking__ShaderUtils__

#include <stdio.h>
#include <string>
#include "cocos2d.h"
//#include "UIButton.h"
//#include "UIScale9Sprite.h"
using namespace std;
USING_NS_CC;

#endif /* defined(__landking__ShaderUtils__) */
class ShaderUtils{



public:
    static void alphaMask(CCSprite* n1, const std::string& mask);
//    static void alphaMaskUi(cocos2d::ui::Widget* n1, const std::string& mask);
    static void colorHSL(CCSprite* n1,const float u_DH, const float u_DS);
private:
    static void renderMask(CCSprite* sprite, CCTexture2D* mask);

};