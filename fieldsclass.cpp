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
    this->sort();
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
    this->sort();

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

void FieldsClass::ExportToExcel(std::ofstream &oFile)
{
    const char* status[] = {
        "已入职", "促报道", "Offer审批中",
        "面试中", "交流中", "待建联", 
        "暂缓", "终止"
    };
	
    for (auto &it : profileList) {
        oFile << "\"" << fieldsName << "\"" << ",";
        oFile << "\"" << it->mName << "\"" << ",";
        oFile << "\"" << status[atoi(it->mStatus)] << "\"" << ",";
        oFile << "\"" << it->mPreGrade << "\"" << ",";
        oFile << "\"" << it->mBirthDate << "\"" << ",";
        oFile << "\"" << it->mArea << "\"" << ",";
        oFile << "\"" << it->mCompany << "\"" << ",";
        oFile << "\"" << it->mExperience << "\"" << ",";
        oFile << "\"" << it->mCollege << "\"" << ",";
        oFile << "\"" << it->mDiploma << "\"" << ",";
        oFile << "\"" << it->mMajor << "\"" << ",";
        oFile << "\"" << it->mGradDate << "\"" << ",";
        oFile << "\"" << it->mEmail << "\"" << ",";
        oFile << "\"" << it->mPhone << "\"" << ",";
        oFile << "\"" << it->mLinkedin << "\"" << ",";
        oFile << "\"" << it->mOtherLink << "\"" << ",";
        oFile << "\"" << it->mLog << "\"" << std::endl;
    }
}

bool CmpFunc(ProfileData *p1, ProfileData *p2)
{
    return p1->GetStatus() < p2->GetStatus();
}

void FieldsClass::sort()
{
    std::sort(profileList.begin(), profileList.end(), CmpFunc);
}