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
    bool isShowCreateProfile = FALSE;
    FieldsClass *creatingField;
    FieldsClass searchingField;
    ProfileData  *shownProfile = nullptr;
    ImGuiInputTextFlags isProEdit = ImGuiInputTextFlags_ReadOnly;
    ImFont *titleFont = nullptr;
    char newName[128] = {0};
    char searchInput[128] = {0};
    int needToShowResult = ImGuiTabItemFlags_None;
    float fontSize = 0;

    void ShortcutList(FieldsClass &field);
    void ShowDetailProfile();
    void ShowBasicInfoTab();
    void ShowContactInfoTab();
    void ShowComLog();
    void ShowFileBrowser();
    void ShowAddNewProfile();
    void ShowSearchingTab();
    void RefreshFields();

public:
    ProfileWindow();
    void Draw();

};