//
//  GuaValue.hpp
//  Bagua
//
//  Created by chaozh on 15/12/23.
//
//

#ifndef GuaValue_hpp
#define GuaValue_hpp

#include "cocos2d.h"

USING_NS_CC;

#define YaoSize 6

class GuaValue: public Ref
{
public:
    std::string name;
    std::string detail;
    std::string yaoDetails[YaoSize];
    
    int xiang;
    void setXiang(const std::string _xiang)
    {
        int t = 0;
        for(int i =0; i<YaoSize; i++){
            if(_xiang[i] == '1')
                t += (1<<i);
        }
        this->xiang = t;
    }
};

class GuaStatus: public Ref {
public:
    const GuaValue* getGuaValue(int i);
    bool loadGuas(const std::string& filename);
    
    //static GuaValue* getInstance() { return _gua; }
private:
    //game resource
    Map<int, GuaValue*> _guaMap;
//    GuaValue* _gua;
};

extern GuaStatus* guaStatus;

#endif /* GuaValue_hpp */
