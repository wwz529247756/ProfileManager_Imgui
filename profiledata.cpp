#include "profiledata.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void ProfileData::LoadData()
{

    std::ifstream read_file;
    read_file.open( fs::u8path(infoFilePath), std::ios::in);
    std::string line;
    
	while(std::getline(read_file, line))
	{
        std::cout<<"line: "<< line << std::endl;
        std::string::size_type pos;
        pos = line.find(":");

        std::string tagStr = line.substr(0, pos);
        std::string dataStr = line.substr(pos + 1, line.length());
        if (tagStr.compare("name") == 0) {
            strcpy(mName, dataStr.c_str());
        } else if (tagStr.compare("area") == 0) {
            strcpy(mArea, dataStr.c_str());
        } else if (tagStr.compare("age") == 0) {
            strcpy(mAge, dataStr.c_str());
        }
	}
}

void ProfileData::SaveData()
{
    std::ofstream writeFile;
    std::cout << "write file to " << infoFilePath << std::endl; 
    writeFile.open(fs::u8path(infoFilePath), std::ios::out);
    // write all data to the file.
    writeFile << "name:" << mName << "\n";
    writeFile << "age:" << mAge << "\n";
    writeFile << "area:" << mArea << "\n";
    writeFile.close();
}

