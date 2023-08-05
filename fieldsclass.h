#include <profiledata.h>
#include <string>
#include <vector>

class FieldsClass
{
private:
    std::string fieldsName;

public: 
    bool isSearchingField = false;
    std::vector<ProfileData*> profileList;
    FieldsClass(std::string name);
    FieldsClass() {
        isSearchingField = true;
    }
    ProfileData *CreateNewProfile(std::string &dirName);
    
    std::string GetName() {
        return fieldsName;
    };
    void Refresh();
    void ExportToExcel(std::ofstream &oFile);
    void sort();

};