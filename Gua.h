//
//  Gua.hpp
//  Bagua
//
//  Created by chaozh on 15/12/6.
//
//

#ifndef Gua_h
#define Gua_h

#include "cocos2d.h"
#include "GuaValue.h"

USING_NS_CC;

class Yao: public Sprite
{
public:
    void setIsYingYang(bool isYang) { _isYang = isYang; }
    bool checkYingYang() { return _isYang; }
    void toggleYingYang();
    
    static Yao* createWithArgs(Color3B color, Size size, bool isYang);
    virtual bool initWithArgs(Color3B color, Size size, bool isYang);
private:
    bool _isYang;
    Sprite* initBlockWithArgs(Color3B color, Size size);
};

class Gua: public Sprite
{
public:
    void toggleYingYang(int i);
    int getXiang() { return xiang; }
    
    static Gua* createWithArgs(Color3B color, Size size, int xiang);
    virtual bool initWithArgs(Color3B color, Size size, int xiang);
    
    Yao* yaos[YaoSize];
private:
    int xiang; //six
};

#endif /* Gua_h */
