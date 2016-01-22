//
//  SceneManager.h
//  Bagua
//
//  Created by chaozh on 15/12/6.
//
//

#ifndef SceneManager_h
#define SceneManager_h

#include "cocos2d.h"

USING_NS_CC;

class SceneManager
{
public:
    Scene *loadScene;
    //Scene *openScene;
    // main scene for Bagua animation
    Scene *mainScene;
    
    void createLoadScene();
    //void goOpenScene();
    void goMainScene();
};

#endif /* SceneManager_h */
