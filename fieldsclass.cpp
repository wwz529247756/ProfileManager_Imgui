#include "fieldsclass.h"
#include <iostream>
#include <windows.h>
#include <io.h>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

FieldsClass::FieldsClass(std::string name) : fieldsName(name)
{
    std::string fieldPath = PROFILE_PATH + "/" + fieldsName;
    std::vector<std::string> dirPath;
    for (auto &p : fs::directory_iterator(fieldPath)) {
        if (fs::is_directory(p.path()) && fs::is_regular_file(fieldPath + "/" + p.path().filename().string() + "/candidate.info")) {
            dirPath.push_back(fieldPath + "/" + p.path().filename().string() + "/candidate.info");
        }
    }

    for (auto it : dirPath) {
        CreateProfileData(it);
        // std::cout << it.c_str() << std::endl;
    }
}

ProfileData* FieldsClass::CreateProfileData(std::string filePath)
{
    ProfileData *proData = new ProfileData(filePath); 
    proData->LoadData();
    profileList.push_back(proData);
    return nullptr;
}