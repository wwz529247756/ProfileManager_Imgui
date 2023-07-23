#include "profiledata.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <filesystem>
#include <windows.h>

namespace fs = std::filesystem;

ProfileData::ProfileData(std::string dirPath) : proDirPath(dirPath)
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
    dataMap["curgrade"] = mCurGrade;
    dataMap["otherlink"] = mOtherLink;
    dataMap["experience"] = mExperience;
    dataMap["log"] = mLog;
    dataMap["status"] = mStatus;
}

void ProfileData::LoadData()
{

    std::ifstream read_file;
    std::string infoFilePath = proDirPath + infoFileName;
    read_file.open( fs::u8path(infoFilePath), std::ios::in);
    std::string line;
    bool isMultiText = false;
    
	while(std::getline(read_file, line))
	{
        std::string::size_type pos;
        pos = line.find(":");

        std::string tagStr = line.substr(0, pos);
        std::string dataStr = line.substr(pos + 1, line.length());
        if (tagStr.compare("experience") == 0 || tagStr.compare("log") == 0) {
            DecodeMultiText(dataStr);
        }

        if (dataMap.find(tagStr) != dataMap.end()) {
            strcpy(dataMap[tagStr],  dataStr.c_str());
        }
	}
    read_file.close();

    LoadFileList();

    if (strlen(dataMap["status"]) > 0 ) {
        int tmpStatus = atoi(dataMap["status"]);
        if (tmpStatus >= 0 && tmpStatus < 6) {
            flowStatus = tmpStatus;
            return;
        }
    }
    flowStatus = 0;

}

void ProfileData::LoadFileList()
{
    std::vector<std::string> dirPath;
    fileList.clear();
    for (auto &p : fs::directory_iterator(proDirPath)) {
        fileList.push_back(p.path().filename().string());
    }
}

void ProfileData::OpenFile(int fileIdx) {
    std::string dirPath = proDirPath;

    for (int i = 0; i < dirPath.length(); i++ ) {
        if (dirPath[i] == '/') {
            dirPath[i] = '\\';
            dirPath.insert(i + 1, 1, '\\');
        }
    }
    dirPath = dirPath + "\\\\" + fileList[fileIdx];
    ShellExecuteW(0, L"open", fs::u8path(dirPath).wstring().c_str(), L"", L"", SW_SHOWNORMAL);
}

void ProfileData::OpenProfileDir() {

    std::string dirPath = proDirPath;

    for (int i = 0; i < dirPath.length(); i++ ) {
        if (dirPath[i] == '/') {
            dirPath[i] = '\\';
            dirPath.insert(i + 1, 1, '\\');
        }
    }
    ShellExecuteW(0, L"open", fs::u8path(dirPath).wstring().c_str(), L"", L"", SW_SHOWNORMAL);
}

void ProfileData::DecodeMultiText(std::string &multiText)
{
    for (int i = 0; i < multiText.length(); i++) {
        if (multiText[i] == '\\' && multiText[i+1] == 'n') {
            multiText[i] = '\n';
            multiText.erase(i+1, 1);
        }
    }
}

std::string ProfileData::EncodeMultiText(char *multiText)
{
    std::string multiTextStr = std::string(multiText);
    for (int i = 0; i < multiTextStr.length(); i++) {
        if (multiTextStr[i] == '\n') {
            multiTextStr[i] = '\\';
            multiTextStr.insert(i + 1, 1, 'n');
        }
    }
    return multiTextStr;
}

void ProfileData::SaveData()
{
    std::ofstream writeFile;
    std::string infoFilePath = proDirPath + infoFileName;
    writeFile.open(fs::u8path(infoFilePath), std::ios::out);
    // write all data to the file.
    for (auto &it : dataMap) {
        if (it.first.compare("experience") == 0 || it.first.compare("log") == 0) {
            writeFile << it.first << ":" << EncodeMultiText(it.second) << "\n";
            continue;
        }
        writeFile << it.first << ":" << it.second << "\n";
    }
    writeFile.close();
}

