#include "profiledata.h"
#include <iostream>
#include <string.h>

void ProfileData::LoadData(std::string &data)
{
    std::string::size_type pos;
    pos = data.find(":");

    std::string tagStr = data.substr(0, pos);
    std::string dataStr = data.substr(pos + 1, data.length());
    if (tagStr.compare("name") == 0) {
        strcpy(mName, dataStr.c_str());
    } else if (tagStr.compare("area") == 0) {
        strcpy(mArea, dataStr.c_str());
    } else if (tagStr.compare("age") == 0) {
        strcpy(mAge, dataStr.c_str());
    }

}

