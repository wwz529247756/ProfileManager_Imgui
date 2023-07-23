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
    ImFont *titleFont = nullptr;
    ImFont *shortCutTitleFont = nullptr;

    void ShortcutList(FieldsClass &field);
    void ShowDetailProfile();
    void ShowBasicInfoTab();
    void ShowContactInfoTab();
    void ShowComLog();
    void ShowFileBrowser();

public:
    ProfileWindow();
    void Draw();

};