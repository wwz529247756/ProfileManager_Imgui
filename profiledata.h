#include <string>
#include <map>
#include <vector>

class ProfileData
{

private:
    std::string proDirPath;
    const char *infoFileName = "/candidate.info";
    std::map<std::string, char*> dataMap;
    int flowStatus = 0;

    std::string EncodeMultiText(char *multiText);
    void DecodeMultiText(std::string &multiText);
    
    
public:
    ProfileData(std::string dirPath);
    void LoadData();
    void SaveData();
    void LoadFileList();
    void OpenFile(int fileIdx);
    void OpenProfileDir();

    int GetStatus() {
        return flowStatus;
    }

    void SetStatus(int status) {
        flowStatus = status;
        mStatus[0] = status + '0';
        mStatus[1] = '\0';
    }

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
    char mStatus[4] = {0};

    std::vector<std::string> fileList;

};