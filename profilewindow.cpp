#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include "profilewindow.h"
#include <iostream>
#include <io.h>
#include <filesystem>
#include <fstream>

#define    FONT_SCALE_100     4

namespace fs = std::filesystem;

const static char* g_status[] = {"已入职", "促报道", "Offer审批中", "面试中", "交流中", "待建联", "暂缓", "终止"};
const static ImU32 g_statusCol[] = {
    IM_COL32(0, 100, 0, 255), // 入职
    IM_COL32(46, 139, 87, 255), // 促报道
    IM_COL32(152, 251, 152, 255), // Offer 审批
    IM_COL32(162, 205, 90, 255), // 面试中
    IM_COL32(173, 216, 230, 255), // 交流中
    IM_COL32(255, 248, 220, 255), // 待建联
    IM_COL32(255, 255, 0, 255), // 暂缓
    IM_COL32(178, 34, 34, 255), // 促报道
};

ProfileWindow::ProfileWindow()
{
    ImGuiIO &io = ImGui::GetIO();
    static ImFontConfig cfg;
    cfg.OversampleH = 1;
    titleFont = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msyhbd.ttc",
        28.0f, &cfg, io.Fonts->GetGlyphRangesChineseFull());
    io.Fonts->TexDesiredWidth = 8096;
    io.Fonts->Build();
    
    if (access(PROFILE_PATH.c_str(), 0) == -1) {
        std::cout << "profiles dir does not exist!" << std::endl;
        return;
    }

    for (auto &p : fs::directory_iterator("profiles")) {
        if (fs::is_directory(p.path())) {
            fields.push_back(new FieldsClass( p.path().filename().string()));
        }
    }

}

void ProfileWindow::ShowAddNewProfile()
{
    ImGui::Begin("新建简历", nullptr, ImGuiWindowFlags_NoCollapse);
    ImGui::Text("请输入候选人姓名:");
    ImGui::SameLine(0, fontSize);
    ImGui::PushID("newprofile");
    ImGui::SetNextItemWidth(fontSize * 8);
    ImGui::InputText("", newName, 128);
    ImGui::PopID();
    static bool isShowErroMsg = false;
    if (ImGui::Button("确认", ImVec2(fontSize * 2, 0))) {
        std::string dirName = newName;
        ProfileData *newProfile = creatingField->CreateNewProfile(dirName);
        if (newProfile != nullptr) {
            shownProfile = newProfile;
            isShowDetailProfile = true;
            isShowCreateProfile = false;
        } else {
            isShowErroMsg = true;
        }
    }
    ImGui::SameLine(0, fontSize);
    if (ImGui::Button("取消", ImVec2(fontSize * 2, 0))) {
        isShowCreateProfile = false;
    }
    if (isShowErroMsg) {
        ImGui::TextDisabled("请检查候选人姓名是否重复！");
    }
    ImGui::End();
}

void ProfileWindow::ShortcutList(FieldsClass &field)
{
    static int columns_count = 3;
    ImGuiIO& io = ImGui::GetIO();

    if (!field.isSearchingField) {
        ImGui::BeginDisabled(isProEdit == ImGuiInputTextFlags_None);
        if (ImGui::Button("新建", ImVec2(fontSize * 3, 0))) {
            memset(newName, 0, sizeof(newName));
            isShowCreateProfile = true;
            creatingField = &field;
        }
        ImGui::EndDisabled();
        ImGui::SameLine(0,fontSize * 1);
    }

    ImGui::SetNextItemWidth(fontSize * 4);
    ImGui::SliderInt("显示列数", &columns_count, 2, 4, "%d", ImGuiSliderFlags_AlwaysClamp);
    
    ImGui::SameLine(0,fontSize * 2);
    ImGui::SetNextItemWidth(fontSize * 4);
    const char* items[] = {"80%", "85%", "90%", "95%", "100%", "105%", "110%", "115%", "120%"};
    static int itemIndx = FONT_SCALE_100;
    ImGui::Combo("文字缩放", &itemIndx, items, IM_ARRAYSIZE(items));
    io.FontGlobalScale = 1.0f + 0.05f * (float)(itemIndx - FONT_SCALE_100);

    ImGui::Columns(columns_count, NULL, true);
    for (auto it : field.profileList)
    {
        if(ImGui::GetColumnIndex() == 0) {
            ImGui::Separator();
        }
        ImGui::PushFont(titleFont);
        ImGui::Text("%s", it->mName);
        ImGui::PopFont();
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Text, g_statusCol[it->GetStatus()]);
        ImGui::Text(" [%s]", g_status[it->GetStatus()]);
        ImGui::PopStyleColor();
        ImGui::Text("出生 : %s", it->mBirthDate);
        ImGui::SameLine(0, fontSize * 3);
        ImGui::Text("预估职级 : %s", it->mPreGrade);
        ImGui::Text("地域 : %s", it->mArea);
        ImGui::SameLine(0, fontSize * 3);
        ImGui::Text("公司 : %s", it->mCompany);
        ImGui::PushID(it->mName);
        ImGui::BeginDisabled(isProEdit == ImGuiInputTextFlags_None);
        if(ImGui::Button("详情", ImVec2(-FLT_MIN, 0.0f))) {
            isShowDetailProfile = true;
            shownProfile = it;
        }
        ImGui::EndDisabled();
        ImGui::PopID();
        ImGui::NextColumn();
    }
    ImGui::Columns(1);
    ImGui::Separator();
}

void ProfileWindow::ShowContactInfoTab() 
{
    ImGui::Text("手机:");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("phonenum");
    ImGui::SetNextItemWidth(fontSize * 8);
    ImGui::InputText("", shownProfile->mPhone, 64, isProEdit);
    ImGui::PopID();

    ImGui::Text("微信:");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("wechat");
    ImGui::SetNextItemWidth(fontSize * 8);
    ImGui::InputText("", shownProfile->mWechat, 128, isProEdit);
    ImGui::PopID();

    ImGui::Text("邮箱:");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("email");
    ImGui::SetNextItemWidth(fontSize * 16);
    ImGui::InputText("", shownProfile->mEmail, 64, isProEdit);
    ImGui::PopID();

    ImGui::Text("LinkedIn:");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("linkedin");
    ImGui::SetNextItemWidth(fontSize * 24);
    ImGui::InputText("", shownProfile->mLinkedin, 128, isProEdit);
    ImGui::PopID();

    ImGui::Text("其他链接");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("otherlink");
    ImGui::SetNextItemWidth(fontSize * 24);
    ImGui::InputText("", shownProfile->mOtherLink, 128, isProEdit);
    ImGui::PopID();
}


void ProfileWindow::ShowBasicInfoTab()
{
    /* Name */
    ImGui::Text("姓名:");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("name");
    ImGui::SetNextItemWidth(fontSize * 8);
    ImGui::InputText("", shownProfile->mName, 128, isProEdit);
    ImGui::PopID();

    ImGui::Text("预估职级:");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("pregrade");
    ImGui::SetNextItemWidth(fontSize * 4);
    ImGui::InputText("", shownProfile->mPreGrade, 16, isProEdit);
    ImGui::PopID();

    ImGui::Text("公司:");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("company");
    ImGui::SetNextItemWidth(fontSize * 8);
    ImGui::InputText("", shownProfile->mCompany, 128, isProEdit);
    ImGui::PopID();

    ImGui::SameLine(0, fontSize * 1);
    ImGui::Text("职级:");
    ImGui::SameLine(0, fontSize);
    ImGui::PushID("grade");
    ImGui::SetNextItemWidth(fontSize * 4);
    ImGui::InputText("", shownProfile->mCurGrade, 16, isProEdit);
    ImGui::PopID();

    /* Born Year */
    ImGui::Text("出生年份:");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("age");
    ImGui::SetNextItemWidth(fontSize * 4);
    ImGui::InputText("", shownProfile->mBirthDate, 128, isProEdit);
    ImGui::PopID();

    /* Working Area */
    ImGui::Text("工作地:");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("area");
    ImGui::SetNextItemWidth(fontSize * 4);
    ImGui::InputText("", shownProfile->mArea, 128, isProEdit);
    ImGui::PopID();

    /* HomeTown */
    ImGui::SameLine(0, fontSize * 5);
    ImGui::Text("家乡:");
    ImGui::SameLine(0, fontSize);
    ImGui::PushID("hometown");
    ImGui::SetNextItemWidth(fontSize * 8);
    ImGui::InputText("", shownProfile->mHometown, 128, isProEdit);
    ImGui::PopID();

    /* Diploma */
    ImGui::Text("学历:");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("diploma");
    ImGui::SetNextItemWidth(fontSize * 4);
    ImGui::InputText("", shownProfile->mDiploma, 32, isProEdit);
    ImGui::PopID();

    /* Major */
    ImGui::SameLine(0, fontSize * 5);
    ImGui::Text("专业:");
    ImGui::SameLine(0, fontSize);
    ImGui::PushID("major");
    ImGui::SetNextItemWidth(fontSize * 8);
    ImGui::InputText("", shownProfile->mMajor, 128, isProEdit);
    ImGui::PopID();

    ImGui::Text("毕业院校:");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("college");
    ImGui::SetNextItemWidth(fontSize * 8);
    ImGui::InputText("", shownProfile->mCollege, 128, isProEdit);
    ImGui::PopID();

    ImGui::SameLine(0, fontSize);
    ImGui::Text("毕业时间:");
    ImGui::SameLine(0, fontSize);
    ImGui::PushID("graddate");
    ImGui::SetNextItemWidth(fontSize * 4);
    ImGui::InputText("", shownProfile->mGradDate, 32, isProEdit);
    ImGui::PopID();

    ImGui::Text("经历:");
    ImGui::InputTextMultiline("experience", shownProfile->mExperience, 2048, ImVec2(-FLT_MIN, fontSize * 8), isProEdit);
}

void ProfileWindow::ShowComLog()
{
    ImGui::Text("沟通记录:");
    ImGui::InputTextMultiline("communication", shownProfile->mLog, 2048,
        ImVec2(-FLT_MIN, fontSize * 16), isProEdit);
}

void ProfileWindow::ShowFileBrowser()
{
    ImGui::NewLine();
    if(ImGui::Button("打开文件夹", ImVec2(fontSize * 5, 0))) {
        shownProfile->OpenProfileDir();
    }
    ImGui::SameLine(0, fontSize);
    if(ImGui::Button("刷新", ImVec2(fontSize * 4, 0))) {
        shownProfile->LoadFileList();
    }
    
    ImGui::BeginTable("FileBrowser", 1,
        ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_BordersOuterV);
    ImGui::TableSetupColumn("文件列表");
    ImGui::TableHeadersRow();
    for (int i = 0; i < shownProfile->fileList.size(); i++) {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        
        ImGui::Dummy(ImVec2(fontSize, 0));
        ImGui::SameLine(0, 0);
        ImGui::PushID(i);
        if(ImGui::Button("打开", ImVec2(fontSize * 3, 0))) {
            shownProfile->OpenFile(i);
        }
        ImGui::PopID();
        ImGui::SameLine(0, fontSize);
        ImGui::TextUnformatted(shownProfile->fileList[i].c_str());
        
    }
    ImGui::EndTable();
}

void ProfileWindow::ShowDetailProfile()
{
    ImGui::Begin( "简历详情", &isShowDetailProfile);
    if(isProEdit == ImGuiInputTextFlags_ReadOnly) {
        if(ImGui::Button("编辑", ImVec2(fontSize * 4, 0))) {
            isProEdit = ImGuiInputTextFlags_None;
        };
    } else if (isProEdit == ImGuiInputTextFlags_None) {
        if(ImGui::IsKeyDown(ImGuiKey_LeftCtrl) && ImGui::IsKeyDown(ImGuiKey_S))
        {
            isProEdit = ImGuiInputTextFlags_ReadOnly;
            shownProfile->SaveData();
        }
        if(ImGui::Button("保存", ImVec2(fontSize * 4, 0))) {
            isProEdit = ImGuiInputTextFlags_ReadOnly;
            shownProfile->SaveData();
            for (auto &it : fields) {
                it->sort();
            }
        };

        ImGui::SameLine(0, fontSize);
        if(ImGui::Button("取消", ImVec2(fontSize * 4, 0))) {
            isProEdit = ImGuiInputTextFlags_ReadOnly;
            shownProfile->LoadData();
        };
    }

    ImGui::Separator();
    ImGui::Dummy(ImVec2(fontSize * 2 , 0));
    ImGui::PushFont(titleFont);
    ImGui::TextDisabled(shownProfile->mName);
    ImGui::PopFont();

    ImGui::SameLine(0, fontSize * 5);
    ImGui::SetNextItemWidth(fontSize * 6);
    ImGui::BeginDisabled(isProEdit == ImGuiInputTextFlags_ReadOnly);
    
    int statusIdx = shownProfile->GetStatus();
    if(ImGui::Combo(" ", &statusIdx, g_status, IM_ARRAYSIZE(g_status))) {
        shownProfile->SetStatus(statusIdx);
    }
    ImGui::EndDisabled();
    ImGui::Dummy(ImVec2(fontSize * 2 , 0));
    
    
    ImGui::BeginTabBar("ProfileDetail");
    if (ImGui::BeginTabItem("基础信息")) {
        ShowBasicInfoTab();
        ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("联系方式")) {
        ShowContactInfoTab();
        ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("沟通记录")) {
        ShowComLog();
        ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("文件浏览")) {
        ShowFileBrowser();
        ImGui::EndTabItem();
    }
    ImGui::EndTabBar();

    ImGui::End();
}

void ProfileWindow::ShowSearchingTab()
{
    if (ImGui::BeginTabItem("搜索结果", nullptr, needToShowResult | ImGuiTabItemFlags_Trailing)) {
        ShortcutList(searchingField);
        ImGui::EndTabItem();
    } 
}

void DoSearch(FieldsClass &searchField, std::vector<FieldsClass*> &fields, char *targStr) {
    searchField.profileList.clear();
    for (auto &it : fields) {
        for (auto &sit : it->profileList) {
            if (strstr(sit->mName, targStr) != nullptr) {
                searchField.profileList.push_back(sit);
            }
        }
    }
}

static const char *g_csvTag[] = {
    "领域",
    "姓名",
    "状态",
    "预估职级",
    "出生年份",
    "地域",
    "公司",
    "经历简介",
    "毕业院校",
    "学历",
    "专业",
    "毕业时间",
    "邮箱",
    "手机",
    "Linkedin链接",
    "其他链接",
    "沟通记录",
};

void ExportCSV(std::vector<FieldsClass*> &fields)
{
    std::ofstream oFile;
    oFile.open("./export.csv", std::ios::out | std::ios::trunc);

    for (int i = 0; i < sizeof(g_csvTag) / sizeof(char*); i++) {
        oFile << g_csvTag[i] << ",";
    }
    oFile << std::endl;

    for (auto &it : fields) {
        it->ExportToExcel(oFile);
    }
    oFile.close();
}

void OpenProfileDir(std::string dirPath)
{
    for (int i = 0; i < dirPath.length(); i++ ) {
        if (dirPath[i] == '/') {
            dirPath[i] = '\\';
            dirPath.insert(i + 1, 1, '\\');
        }
    }
    ShellExecuteW(0, L"open", fs::u8path(dirPath).wstring().c_str(), L"", L"", SW_SHOWNORMAL);
}

void ProfileWindow::Draw()
{
    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowRounding = 8.0f;
    style.ItemSpacing = ImVec2(6, 10);
    style.FrameRounding = 4.0f;
    style.WindowPadding = ImVec2(10, 15);
    fontSize = ImGui::GetFontSize();


    ImGui::Begin( "简历列表", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("文件"))
        {
            if(ImGui::MenuItem("导出Excel")) {
                ExportCSV(fields);
            }
            if (ImGui::MenuItem("打开文件夹")) {
                OpenProfileDir(PROFILE_PATH);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    bool isClicked = false;
    ImGui::PushID("搜索条");
    if(ImGui::InputText("", searchInput, 128, ImGuiInputTextFlags_EnterReturnsTrue)) {
        DoSearch(searchingField, fields, searchInput);
        isClicked = true;
    }
    ImGui::PopID();
    ImGui::SameLine(0, fontSize);
    
    if (ImGui::Button("搜索", ImVec2(fontSize * 4, 0))) {
        DoSearch(searchingField, fields, searchInput);
        isClicked = true;
    };
    ImGui::SameLine(0, fontSize);

    if (ImGui::Button("刷新", ImVec2(fontSize * 4, 0))) {
        RefreshFields();
    }

    ImGui::Separator();
    ImGui::NewLine();

    ImGui::BeginTabBar("FieldsTab");
    for (auto it : fields) {
        if (ImGui::BeginTabItem(it->GetName().c_str())) {
            ShortcutList(*it);
            needToShowResult = ImGuiTabItemFlags_None;
            ImGui::EndTabItem();
        } 
    }
    if (isClicked) {
        needToShowResult = ImGuiTabItemFlags_SetSelected;
    }
    ShowSearchingTab();
    ImGui::EndTabBar();
    ImGui::End();

    if (isShowCreateProfile) {
        ShowAddNewProfile();
    }

    if(isShowDetailProfile) {
        ShowDetailProfile();
    } else if (isProEdit == ImGuiInputTextFlags_None) {
        isProEdit = ImGuiInputTextFlags_ReadOnly;
        shownProfile->SaveData();
    }

}

void ProfileWindow::RefreshFields()
{
    for (auto &it : fields) {
        it->Refresh();
    }
    searchingField.Refresh();
    isShowDetailProfile = false;
}

