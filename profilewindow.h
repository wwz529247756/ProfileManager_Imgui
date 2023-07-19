#include <vector>
#include <string>
#include "fieldsclass.h"
#include <windows.h>
#include "imgui.h"

class ProfileWindow
{

private:
    std::vector<FieldsClass*> fields;
    const std::string PROFILE_PATH = "./profiles";
    bool isShowDetailProfile = FALSE;
    ProfileData  *shownProfile = nullptr;
    ImGuiInputTextFlags isProEdit = ImGuiInputTextFlags_ReadOnly;

    void ShortcutList(FieldsClass &field);
    void ShowDetailProfile();
    void ShowBasicInfoTab();
    void ShowContactInfoTab();


public:
    ProfileWindow();
    void Draw();

};