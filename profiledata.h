#include <string>
#include <map>

class ProfileData
{

private:
    std::string infoFilePath;
    std::map<std::string, char*> dataMap;
    std::string EncodeMultiText(char *multiText);
    void DecodeMultiText(std::string &multiText);
    
public:
    ProfileData(std::string filePath);;
    void LoadData();
    void SaveData();

    char mName[128] = {0};
    char mBirthDate[32] = {0};
    char mArea[128] = {0};
    char mHometown[128] = {0};
    char mDiploma[32] = {0};
    char mCollege[128] = {0};
    char mGradDate[32] = {0};
    char mMajor[128] = {0};
    char mCompany[128] = {0};
    char mPosition[128] = {0};
    char mPreGrade[16] = {0};
    char mWechat[128] = {0};
    char mPhone[64] = {0};
    char mEmail[64] = {0};
    char mLinkedin[128] = {0};
    char mOtherLink[128] = {0};
    char mCurGrade[16] = {0};
    char mExperience[2048] = {0};
    char mLog[2048] = {0};

};