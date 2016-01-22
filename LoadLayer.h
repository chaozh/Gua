//
//  LoadLayer.h
//  Bagua
//
//  Created by chaozh on 15/12/6.
//
//

#ifndef LoadScene_h
#define LoadScene_h

#include "cocos2d.h"
#include "SceneManager.h"

USING_NS_CC;

class LoadLayer : public Layer
{
public:
    virtual bool init();
    virtual void onEnter();
    void dispatchLoadCallbacks(float dt);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuStartCallback(Ref* pSender);
    
    CREATE_FUNC(LoadLayer);
    
    void setSceneManager(SceneManager *tsm) { _tsm = tsm; }
    SceneManager* getSceneManager() { return _tsm; }
private:
    SceneManager * _tsm;
};

#endif /* LoadLayer_h */
