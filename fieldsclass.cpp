#include "fieldsclass.h"
#include <iostream>
#include <windows.h>
#include <io.h>
#include <filesystem>
#include <fstream>
#include <algorithm>

namespace fs = std::filesystem;

const static char configFileName[] = "/candidate.info";
const static std::string profilePathName = "./profiles";

FieldsClass::FieldsClass(std::string name) : fieldsName(name)
{
    std::string fieldPath = profilePathName + "/" + fieldsName;
    std::string dirPathName;
    for (auto &p : fs::directory_iterator(fieldPath)) {
        dirPathName = fieldPath + "/" + p.path().filename().string();
        if (fs::is_directory(p.path()) && fs::is_regular_file(dirPathName + configFileName)) {
            ProfileData *proData = new ProfileData(fieldPath + "/" + p.path().filename().string()); 
            proData->LoadData();
            profileList.push_back(proData);
        }
    }
}

ProfileData *FieldsClass::CreateNewProfile(std::string &dirName)
{
    std::string newDirPath = profilePathName + "/" + fieldsName + "/" + dirName;
    if(!fs::create_directories(fs::path(newDirPath))) {
        std::cout << "[AddNewProfile] new dir failed" << std::endl;
        return nullptr;
    }

    ProfileData *proData = new ProfileData(newDirPath);
    strcpy(proData->mName, dirName.c_str());
    proData->SaveData();
    profileList.push_back(proData);
    proData->LoadData();

    return proData;
}

void FieldsClass::Refresh()
{
    for (int i = 0; i < profileList.size(); i++) {
        if(!profileList[i]->IsExist()) {
            profileList.erase(profileList.begin() + i);
            i--;
        }
    }
}