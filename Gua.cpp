//
//  Gua.cpp
//  Bagua
//
//  Created by chaozh on 15/12/6.
//
//

#include "Gua.h"

Sprite* Yao::initBlockWithArgs(Color3B color, Size size)
{
    auto block = new Sprite();
    block->init();
    block->setContentSize(size);
    block->setAnchorPoint(Point::ZERO);
    block->setTextureRect(Rect(0, 0, size.width, size.height));
    block->setColor(color);
    block->autorelease();
    
    return block;
}

Yao* Yao::createWithArgs(Color3B color, Size size, bool isYang)
{
    auto y = new Yao();
    y->initWithArgs(color, size, isYang);
    y->autorelease();
    
    return y;
}

bool Yao::initWithArgs(Color3B color, Size size, bool isYang)
{
    Sprite::init();
    Sprite::setContentSize(size);
    
    setIsYingYang(isYang);
    //yang
    auto block = initBlockWithArgs(color, size);
    this->addChild(block, 0, 0);
    block->setPosition(0, 0);
    //ying
    Size tmp(size.width/3, size.height);
    auto block1 = initBlockWithArgs(color, tmp);
    auto block2 = initBlockWithArgs(color, tmp);
    
    this->addChild(block1, 0, 1);
    this->addChild(block2, 0, 2);
    
    block1->setPosition(0, 0);
    block2->setPosition(size.width * 2/3, 0);
    
    if(isYang){
        block1->setVisible(false);
        block2->setVisible(false);
    }else{
        block->setVisible(false);
    }
    
    /*
    auto myLabel = Label::create();
    myLabel->setString(label);
    myLabel->setSystemFontSize(fontSize);
    myLabel->setTextColor(textColor);
    addChild(myLabel);
    myLabel->setPosition(size.width/2, size.height/2);
     */
    
    return true;
}

void Yao::toggleYingYang()
{
    //
    _isYang = !_isYang;
    //change sprite
    auto block = this->getChildByTag(0);
    auto block1 = this->getChildByTag(1);
    auto block2 = this->getChildByTag(2);
    
    if(_isYang){
        block->setVisible(true);
        block1->setVisible(false);
        block2->setVisible(false);
    } else {
        block->setVisible(false);
        block1->setVisible(true);
        block2->setVisible(true);
    }
}

void Gua::toggleYingYang(int i)
{
    auto y = yaos[i];
    y->toggleYingYang();
    
    if(y->checkYingYang())
        xiang += (1<<i);
    else
        xiang -= (1<<i);
    
    CCLOG("%d", xiang);
}

Gua* Gua::createWithArgs(Color3B color, Size size, int xiang)
{
    auto g = new Gua();
    g->initWithArgs(color, size, xiang);
    g->autorelease();
    
    return g;
}

bool Gua::initWithArgs(Color3B color, Size size, int xiang)
{
    Sprite::init();
    
    for(int i = 0; i < YaoSize; ++i){
        //CCLOG("%d", (bool)(xiang & 1<<i));
        auto y = Yao::createWithArgs(color, size, (bool)(xiang & 1<<i));
        y->setPosition(Vec2(0, -size.height * i * 2));
        this->addChild(y, 0, i);
        this->yaos[i] = y;
    }
    
    return true;
}

