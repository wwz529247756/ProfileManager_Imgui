#include <string>
#include <map>

class ProfileData
{

private:
    char mName[128];
    char mBirthDate[32];
    char mArea[128];
    char mHometown[128];
    char mDiploma[32];
    char mCollege[128];
    char mGradDate[32];
    char mMajor[128];
    char mCompany[128];
    char mPosition[128];
    char mPreGrade[16];
    char mWechat[128];
    char mPhone[64];
    char mEmail[64];
    char mLinkedin[128];

    std::string infoFilePath;
    std::map<std::string, char*> dataMap;
    
public:
    ProfileData(std::string filePath);;
    void LoadData();
    void SaveData();

    char* GetName() {
        return mName;
    }

    char* GetAge() {
        return mBirthDate;
    }

    char* GetArea() {
        return mArea;
    }
    
};