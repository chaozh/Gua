//
//  GuaValue.cpp
//  Bagua
//
//  Created by chaozh on 16/1/12.
//
//

#include "GuaValue.h"

#include "json/document.h"
#include "json/stringbuffer.h"

const GuaValue* GuaStatus::getGuaValue(int i){
    return this->_guaMap.at(i);
}

bool GuaStatus::loadGuas(const std::string& filename)
{
    std::string jsStr = FileUtils::getInstance()->getStringFromFile(filename);
    rapidjson::Document doc;
    doc.Parse<0>(jsStr.c_str());
    
    if (doc.HasParseError())
    {
        CCLOG("LoadLayer::LoadGuas parse json error!");
        return false;
    }
    
    if (doc.HasMember("gua"))
    {
        const rapidjson::Value& guaListValue=doc["gua"];
        if (guaListValue.IsArray() && guaListValue.Size()>0)
        {
            
            int guaListSize = guaListValue.Size();
            for (int i=0; i<guaListSize; i++)
            {
                const rapidjson::Value &guaValue = guaListValue[i];
                if (guaValue.IsObject())
                {
                    GuaValue *pGua = new GuaValue();
                    pGua->setXiang(guaValue["gua-xiang"].GetString());
                    pGua->name = guaValue["gua-name"].GetString();
                    pGua->detail = guaValue["gua-detail"].GetString();
                    
                    const rapidjson::Value& yaoArray = guaValue["yao-detail"];
                    if(yaoArray.IsArray()){
                        for (rapidjson::SizeType i = 0; i < yaoArray.Size(); i++)
                            pGua->yaoDetails[i] = yaoArray[i].GetString();
                    }
                    
                    this->_guaMap.insert(pGua->xiang, pGua);
                }
            }
        }
    }
    
    return true;
}

