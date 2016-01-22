//
//  MainLayer.h
//  Bagua
//
//  Created by chaozh on 15/12/6.
//
//

#ifndef MainLayer_h
#define MainLayer_h

#include "cocos2d.h"
#include "SceneManager.h"
#include "Gua.h"

USING_NS_CC;

class MainLayer : public Layer
{
public:
    virtual bool init();
    virtual void update(float dt);
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    CREATE_FUNC(MainLayer);
    void setSceneManager(SceneManager *tsm) { _tsm = tsm; }
    SceneManager* getSceneManager() { return _tsm; }
private:
    void startGame();
    void createBgLayer();
    SceneManager * _tsm;
    Gua* gua; //helper
    Label* labelGuaName;
    Label* labelGuaDetail;
    Label* labelYaoDetail[YaoSize];
};

#endif /* MainLayer_h */
