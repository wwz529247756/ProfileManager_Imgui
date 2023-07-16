#include <profiledata.h>
#include <string>
#include <vector>

class FieldsClass
{
private:
    std::string fieldsName;
    // std::vector<ProfileData*> profileList;
    const std::string PROFILE_PATH = "./profiles";

    ProfileData* CreateProfileData(std::string filePath);

public: 
    std::vector<ProfileData*> profileList;
    FieldsClass(std::string name);
    
    std::string GetName() {
        return fieldsName;
    };


};