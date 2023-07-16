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
    std::ifstream read_file;
    ProfileData *proData = new ProfileData(); 
    read_file.open( fs::u8path(filePath), std::ios::in);

	std::string line;
    
	while(std::getline(read_file, line))
	{
        std::cout<<"line: "<< line << std::endl;
        proData->LoadData(line);
	}
    profileList.push_back(proData);
    return nullptr;
}