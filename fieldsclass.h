#include <profiledata.h>
#include <string>
#include <vector>

class FieldsClass
{
private:
    std::string fieldsName;
    const std::string PROFILE_PATH = "./profiles";

    void CreateProfileData(std::string filePath);

public: 
    std::vector<ProfileData*> profileList;
    FieldsClass(std::string name);
    ProfileData *AddNewProfile(std::string &dirName);
    
    std::string GetName() {
        return fieldsName;
    };


};