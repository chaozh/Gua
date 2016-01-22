//
//  MainLayer.cpp
//  Bagua
//
//  Created by chaozh on 15/12/6.
//
//

#include "MainLayer.h"

bool MainLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto lisener = EventListenerTouchOneByOne::create();
    lisener->onTouchBegan = CC_CALLBACK_2(MainLayer::onTouchBegan,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(lisener,this) ;
    
    createBgLayer();
    startGame();
    
    return true;
}

void MainLayer::createBgLayer()
{
    auto bgLayer = Layer::create();
    const GuaValue *p = guaStatus->getGuaValue(0);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    labelGuaName = Label::create(p->name.c_str(), "Arial", 96);
    bgLayer->addChild(labelGuaName);
    labelGuaName->setPosition(Vec2(100, visibleSize.height/2 + origin.y));
    
    labelGuaDetail = Label::create(p->detail.c_str(), "Arial", 12);
    //auto labelGuaDetail = Label::createWithTTF(p->detail, "fonts/arial.ttf", 18);
    bgLayer->addChild(labelGuaDetail);
    labelGuaDetail->setPosition(Vec2(visibleSize.width/2 - origin.x, visibleSize.height - origin.y));
    
    for(int i =0; i<YaoSize; ++i) {
        labelYaoDetail[i] = Label::create(p->yaoDetails[i].c_str(), "Arial", 12);
        //auto labelGuaDetail = Label::createWithTTF(p->detail, "fonts/arial.ttf", 18);
        bgLayer->addChild(labelYaoDetail[i]);
        labelYaoDetail[i]->setPosition(Vec2(visibleSize.width/2 - origin.x, visibleSize.height - origin.y));
    }
    
    this->addChild(bgLayer, 0);
}

void MainLayer::startGame()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Size size(visibleSize.width/4, visibleSize.width/48);
    //
    const GuaValue *p = guaStatus->getGuaValue(0);
    
    this->gua = Gua::createWithArgs(Color3B::WHITE, size, p->xiang);
    this->gua->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    this->addChild(this->gua, 1);
    
    this->scheduleUpdate();
}

void MainLayer::update(float dt)
{
    
}

bool MainLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    Point touchLocation = gua->convertTouchToNodeSpace(touch);
    CCLOG("touchLocation(%f, %f)", touchLocation.x, touchLocation.y);
    for (int i =0; i<YaoSize; ++i)
    {
        auto yao = this->gua->yaos[i];
        if ( yao->getBoundingBox().containsPoint(touchLocation) )
        {
            this->gua->toggleYingYang(i);
            
            const GuaValue *p = guaStatus->getGuaValue(this->gua->getXiang());
            labelGuaName->setString(p->name);
            labelGuaDetail->setString(p->detail);
            for(int j =0; j<YaoSize; ++j)
                labelYaoDetail[j]->setString(p->yaoDetails[j]);
            
            break;
        }
    }
    
    return true;
}