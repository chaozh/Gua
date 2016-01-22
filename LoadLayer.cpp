//
//  LoadScene.cpp
//  Bagua
//
//  Created by chaozh on 15/12/6.
//
//

#include "LoadLayer.h"
#include "GuaValue.h"

GuaStatus* guaStatus = NULL;
// on "init" you need to initialize your instance
bool LoadLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(LoadLayer::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // start menu
    auto labelStart = Label::createWithTTF("Start!", "fonts/Marker Felt.ttf", 24);
    
    auto startItem = MenuItemLabel::create(labelStart, CC_CALLBACK_1(LoadLayer::menuStartCallback, this));
    
    auto startMenu = Menu::create(startItem, NULL);
    startMenu->setPosition(Vec2(origin.x + visibleSize.width/2,
                       origin.y + visibleSize.height - labelStart->getContentSize().height));
    this->addChild(startMenu, 1);
    
    /////////////////////////////
    // progress bar
    auto bar = Sprite::create();
    bar->setTextureRect(Rect(0, 0, visibleSize.width/2, 50));
    //auto to1 = Sequence::createWithTwoActions(ProgressTo::create(2, 100), ProgressTo::create(0, 0));
    auto progress = ProgressTimer::create(bar);
    progress->setType(ProgressTimer::Type::BAR); // 设置进度为条形进度条
    // 设置进度的起点位置:在这里(0,0)表示进度的起始位置是(0,0)
    progress->setMidpoint(Vec2(0,0)); //
    // 设置进度改变速率:同设置MidPoint一样，也是用一个Vec2表示；
    progress->setBarChangeRate(Vec2(1, 0)); //
    this->addChild(progress);
    progress->setTag(100);
    progress->setPosition(Vec2(100, visibleSize.height/2));
    //progress->runAction(RepeatForever::create(to1));
    
    return true;
}

void LoadLayer::onEnter()
{
    //start loading resource
    guaStatus = new GuaStatus();
    guaStatus->loadGuas("res/gua.json");
    
    Director::getInstance()->getScheduler()->schedule(schedule_selector(LoadLayer::dispatchLoadCallbacks), this, 0, false);
}

void LoadLayer::dispatchLoadCallbacks(float dt)
{
    ProgressTimer* progress = (ProgressTimer*)getChildByTag(100);
    progress->setPercentage(progress->getPercentage() + 1);
    
    if(progress->getPercentage() >= 100 && guaStatus != NULL) {    
        //Director::getInstance()->getScheduler()->pauseTarget(this);
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(LoadLayer::dispatchLoadCallbacks), this);
        this->getSceneManager()->goMainScene();
    }
}

void LoadLayer::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void LoadLayer::menuStartCallback(Ref* pSender)
{
    this->getSceneManager()->goMainScene();
}
