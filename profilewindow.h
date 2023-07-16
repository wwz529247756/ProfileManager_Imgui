#include <vector>
#include <string>
#include "fieldsclass.h"
#include <windows.h>

class ProfileWindow
{

private:
    std::vector<FieldsClass*> fields;
    const std::string PROFILE_PATH = "./profiles";
    bool isShowDetailProfile = FALSE;
    ProfileData  *shownProfile = nullptr;

    void ShortcutList(FieldsClass &field);
    void ShowDetailProfile();

public:
    ProfileWindow();
    void Draw();

};