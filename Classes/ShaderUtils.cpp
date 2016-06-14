//
//  ShaderUtils.cpp
//  landking
//
//  Created by wxg on 16/1/7.
//
//

#include "ShaderUtils.h"
static const GLchar * vert       = "													\n\
attribute vec4 a_position;							\n\
attribute vec2 a_texCoord;							\n\
attribute vec4 a_color;								\n\
\n\
#ifdef GL_ES										\n\
varying lowp vec4 v_fragmentColor;					\n\
varying mediump vec2 v_texCoord;					\n\
#else												\n\
varying vec4 v_fragmentColor;						\n\
varying vec2 v_texCoord;							\n\
#endif												\n\
\n\
void main()											\n\
{													\n\
gl_Position = CC_MVPMatrix * a_position;		\n\
v_fragmentColor = a_color;						\n\
v_texCoord = a_texCoord;						\n\
}													\n\
";

static const GLchar * alphaMask_frag       ="												\n\
#ifdef GL_ES\n\
precision mediump float;\n\
#endif\n\
varying vec2 v_texCoord;\n\
\n\
varying vec4 v_fragmentColor;\n\
uniform sampler2D u_mask_texture;\n\
uniform sampler2D CC_Texture0;\n\
\n\
void main()\n\
{\n\
vec4 mask_FragColor = texture2D(CC_Texture0, v_texCoord);\n\
mask_FragColor.a = texture2D(u_mask_texture, v_texCoord).r;\n\
mask_FragColor.xyz = mask_FragColor.xyz * mask_FragColor.a;\n\
gl_FragColor = mask_FragColor * v_fragmentColor;\n\
//gl_FragColor = vec4(0.6, 0.0, 0.0, 1.0);\n\
}";

static const GLchar * color_frag       ="												\n\
#ifdef GL_ES\n\
precision mediump float;\n\
#endif\n\
varying vec2 v_texCoord;\n\
varying vec4 v_fragmentColor;\n\
uniform float u_dH;\n\
uniform float u_dS;\n\
const float u_dL=0.0;\n\
uniform sampler2D CC_Texture0;\n\
void main() {\n\
vec4 texColor=texture2D(CC_Texture0, v_texCoord);\n\
float r=texColor.r;\n\
float g=texColor.g;\n\
float b=texColor.b;\n\
float a=texColor.a;\n\
float h;\n\
float s;\n\
float l;\n\
{\n\
float max=max(max(r,g),b);\n\
float min=min(min(r,g),b);\n\
if(max==min){\n\
h=0.0;\n\
}else if(max==r&&g>=b){\n\
h=60.0*(g-b)/(max-min)+0.0;\n\
}else if(max==r&&g<b){\n\
h=60.0*(g-b)/(max-min)+360.0;\n\
}else if(max==g){\n\
h=60.0*(b-r)/(max-min)+120.0;\n\
}else if(max==b){\n\
h=60.0*(r-g)/(max-min)+240.0;\n\
}\n\
l=0.5*(max+min);\n\
if(l==0.0||max==min){\n\
s=0.0;\n\
}else if(0.0<=l&&l<=0.5){\n\
s=(max-min)/(2.0*l);\n\
}else if(l>0.5){\n\
s=(max-min)/(2.0-2.0*l);\n\
}\n\
}\n\
h=h+u_dH;\n\
s=min(1.0,max(0.0,s+u_dS));\n\
l=l;\n\
vec4 finalColor;\n\
{\n\
float q;\n\
if(l<0.5){\n\
q=l*(1.0+s);\n\
}else if(l>=0.5){\n\
q=l+s-l*s;\n\
}\n\
float p=2.0*l-q;\n\
float hk=h/360.0;\n\
float t[3];\n\
t[0]=hk+1.0/3.0;t[1]=hk;t[2]=hk-1.0/3.0;\n\
for(int i=0;i<3;i++){\n\
if(t[i]<0.0)t[i]+=1.0;\n\
if(t[i]>1.0)t[i]-=1.0;\n\
}\n\
float c[3];\n\
for(int i=0;i<3;i++){\n\
if(t[i]<1.0/6.0){\n\
c[i]=p+((q-p)*6.0*t[i]);\n\
}else if(1.0/6.0<=t[i]&&t[i]<0.5){\n\
c[i]=q;\n\
}else if(0.5<=t[i]&&t[i]<2.0/3.0){\n\
c[i]=p+((q-p)*6.0*(2.0/3.0-t[i]));\n\
}else{\n\
c[i]=p;\n\
}\n\
}\n\
finalColor=vec4(c[0],c[1],c[2],a);\n\
}\n\
finalColor+=vec4(u_dL,u_dL,u_dL,0.0);\n\
gl_FragColor=finalColor*v_fragmentColor;\n\
//gl_FragColor = vec4(0.6, 0.0, 0.0, 1.0);\n\
}";

static const GLchar * test_frag       = "													\n\
#ifdef GL_ES										\n\
precision lowp float;								\n\
#endif												\n\
\n\
varying vec4 v_fragmentColor;						\n\
varying vec2 v_texCoord;							\n\
uniform sampler2D CC_Texture0;						\n\
\n\
void main()											\n\
{													\n\
gl_FragColor = vec4( v_fragmentColor.rgb,										// RGB from uniform				\n\
v_fragmentColor.a * texture2D(CC_Texture0, v_texCoord).a	// A from texture & uniform		\n\
);							\n\
gl_FragColor = vec4(0.6, 0.0, 0.0, 1.0);\n\
}													\n\
";

static const GLchar * test_vert       = "													\n\
attribute vec4 a_position;							\n\
attribute vec2 a_texCoord;							\n\
attribute vec4 a_color;								\n\
\n\
#ifdef GL_ES										\n\
varying lowp vec4 v_fragmentColor;					\n\
varying mediump vec2 v_texCoord;					\n\
#else												\n\
varying vec4 v_fragmentColor;						\n\
varying vec2 v_texCoord;							\n\
#endif												\n\
\n\
void main()											\n\
{													\n\
gl_Position = CC_MVPMatrix * a_position;		\n\
v_fragmentColor = a_color;						\n\
v_texCoord = a_texCoord;						\n\
}													\n\
";

//static const GLchar* color_frag        ="\n\
//#ifdef GL_ES\n\
//precision mediump float;\n\
//#endif\n\
//"


USING_NS_CC;

void ShaderUtils::alphaMask(CCSprite* node, const std::string& mask)
{
//    auto TexCache = cocos2d::Director::getInstance()->getTextureCache();
//    auto wave1 = TexCache->addImage(mask);
//    auto program = GLProgram::createWithByteArrays(vert, alphaMask_frag);
//    auto glProgramState = GLProgramState::getOrCreateWithGLProgram(program);
//    node->setGLProgramState(glProgramState);
//    glProgramState->setUniformTexture("u_mask_texture", wave1->getName());
    
    CCTexture2D* wave1 = CCTextureCache::sharedTextureCache()->addImage(mask.c_str());
    CCGLProgram* program = new CCGLProgram();
    program->autorelease();
    program->initWithVertexShaderByteArray(vert, alphaMask_frag);
    program->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    program->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
    program->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
//    program->initWithVertexShaderByteArray(ccPositionTexture_uColor_vert, ccPositionTexture_uColor_frag);
    program->addAttribute("u_mask_texture", wave1->getName());
    program->link();
    program->updateUniforms();
    node->setShaderProgram(program);
}

/*
void ShaderUtils::alphaMaskUi(cocos2d::ui::Widget* node, const std::string& mask){
    
    auto TexCache = cocos2d::Director::getInstance()->getTextureCache();
    auto wave1 = TexCache->addImage(mask);
//    auto program = GLProgram::createWithByteArrays(vert, alphaMask_frag);
//    auto glProgramState = GLProgramState::getOrCreateWithGLProgram(program);
    auto* pS9Sprite = dynamic_cast<cocos2d::ui::Scale9Sprite*>(node->getVirtualRenderer());
    if (pS9Sprite)
    {
//        pS9Sprite->getSprite()->setGLProgram(program);
        renderMask(pS9Sprite->getSprite(),wave1);
    }
    else
    {
        //There is nothing to do with widget ,when sp9Sprite has no sprite children
//        node->setGLProgram(program);
    }
//    glProgramState->setUniformTexture("u_mask_texture", wave1->getName());
    
    if(strcmp(typeid(node).name(),typeid(cocos2d::ui::Button*).name()))
    {
        auto button = dynamic_cast<cocos2d::ui::Button*>(node);
        auto* pS9Sprite1 = dynamic_cast<cocos2d::ui::Scale9Sprite*>(button->_buttonClickedRenderer);
        if (pS9Sprite1)
        {
            renderMask(pS9Sprite1->getSprite(),wave1);
        }
        else{
            //There is nothing to do with widget ,when sp9Sprite has no sprite children
        }
        auto* pS9Sprite2 = dynamic_cast<cocos2d::ui::Scale9Sprite*>(button->_buttonDisableRenderer);
        if (pS9Sprite2)
        {
            renderMask(pS9Sprite2->getSprite(),wave1);
        }
        else{
            //There is nothing to do with widget ,when sp9Sprite has no sprite children
        }
    }
    
    
}
 */

void ShaderUtils::renderMask(CCSprite* sprite, CCTexture2D* mask)
{
//    auto program1 = GLProgram::createWithByteArrays(vert, alphaMask_frag);
//    auto glProgramState1 = GLProgramState::getOrCreateWithGLProgram(program1);
//    sprite->setGLProgram(program1);
//    glProgramState1->setUniformTexture("u_mask_texture", mask->getName());
    
    CCGLProgram* program = new CCGLProgram();
    program->autorelease();
    program->initWithVertexShaderByteArray(vert, alphaMask_frag);
    program->addAttribute("u_mask_texture", mask->getName());
    program->link();
    program->updateUniforms();
    sprite->setShaderProgram(program);
}

void ShaderUtils::colorHSL(CCSprite* node, const float u_DH, const float u_DS)
{
//    auto program = GLProgram::createWithByteArrays(vert, color_frag);
//    auto glProgramState = GLProgramState::getOrCreateWithGLProgram(program);
//    glProgramState->setUniformFloat("u_dH", u_DH);
//    glProgramState->setUniformFloat("u_dS", u_DS);
//    node->setGLProgramState(glProgramState);
    
    CCGLProgram* program = new CCGLProgram();
    program->retain();
    program->initWithVertexShaderByteArray(vert, color_frag);
//    program->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
//    program->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
//    program->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    program->setUniformLocationWith1f(program->getUniformLocationForName("u_dH"), u_DH);
    program->setUniformLocationWith1f(program->getUniformLocationForName("u_dS"), u_DS);
    program->link();
    program->updateUniforms();
    node->setShaderProgram(program);
}
