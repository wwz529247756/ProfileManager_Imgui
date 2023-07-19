#include "profiledata.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

ProfileData::ProfileData(std::string filePath) : infoFilePath(filePath)
{
    dataMap["name"] = mName;
    dataMap["birthdate"] = mBirthDate;
    dataMap["area"] = mArea;
    dataMap["hometown"] = mHometown;
    dataMap["diploma"] = mDiploma;
    dataMap["college"] = mCollege;
    dataMap["graddate"] = mGradDate;
    dataMap["major"] = mMajor;
    dataMap["company"] = mCompany;
    dataMap["position"] = mPosition;
    dataMap["pregrade"] = mPreGrade;
    dataMap["wechat"] = mWechat;
    dataMap["phone"] = mPhone;
    dataMap["email"] = mEmail;
    dataMap["linkedin"] = mLinkedin;
}

void ProfileData::LoadData()
{

    std::ifstream read_file;
    read_file.open( fs::u8path(infoFilePath), std::ios::in);
    std::string line;
    
	while(std::getline(read_file, line))
	{
        std::string::size_type pos;
        pos = line.find(":");

        std::string tagStr = line.substr(0, pos);
        std::string dataStr = line.substr(pos + 1, line.length());

        if (dataMap.find(tagStr) != dataMap.end()) {
            strcpy(dataMap[tagStr],  dataStr.c_str());
        }
	}
}

void ProfileData::SaveData()
{
    std::ofstream writeFile;
    std::cout << "write file to " << infoFilePath << std::endl; 
    writeFile.open(fs::u8path(infoFilePath), std::ios::out);
    // write all data to the file.
    for (auto &it : dataMap) {
        writeFile << it.first << ":" << it.second << "\n";
    }
    writeFile.close();
}

