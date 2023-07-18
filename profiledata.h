#include <string>

class ProfileData
{

private:
    char mName[128];
    char mAge[128];
    char mArea[128];
    std::string infoFilePath;
    
public:
    ProfileData(std::string filePath) : infoFilePath(filePath){};
    void LoadData();
    void SaveData();

    char* GetName() {
        return mName;
    }

    char* GetAge() {
        return mAge;
    }

    char* GetArea() {
        return mArea;
    }
    
};