#include <string>

class ProfileData
{

private:
    char mName[128];
    char mAge[128];
    char mArea[128];
    
public:
    ProfileData(){};
    void LoadData(std::string &data);

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