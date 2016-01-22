//
//  SceneManager.cpp
//  Bagua
//
//  Created by chaozh on 15/12/6.
//
//

#include "SceneManager.h"
#include "LoadLayer.h"
#include "MainLayer.h"

void SceneManager::createLoadScene()
{
    loadScene = Scene::create();
    auto layer = LoadLayer::create();
    layer->setSceneManager(this);
    loadScene->addChild(layer);
}

//void SceneManager::goOpenScene()
//{
//    openScene = Scene::create();
//    
//    auto layer = OpenLayer::create();
//    layer->setSceneManager(this);
//    openScene->addChild(layer);
//    
//    Director::getInstance()->replaceScene(openScene);
//}

void SceneManager::goMainScene()
{
    mainScene = Scene::create();
    auto mainLayer = MainLayer::create();
    mainLayer->setSceneManager(this);
    mainScene->addChild(mainLayer, 1);
    
    Director::getInstance()->replaceScene(mainScene);
}
