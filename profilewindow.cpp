#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include "profilewindow.h"
#include <iostream>
#include <io.h>
#include <filesystem>

namespace fs = std::filesystem;

ProfileWindow::ProfileWindow()
{
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

void ProfileWindow::ShortcutList(FieldsClass &field)
{
    static int columns_count = 3;
    ImGuiIO& io = ImGui::GetIO();
    float fontSize = ImGui::GetFontSize();


    ImGui::SetNextItemWidth(fontSize * 8);
    // ImGui::DragInt("##columns_count", &columns_count, 0.1f, 2, 4, "%d columns");
    ImGui::SliderInt("显示列数", &columns_count, 2, 4, "%d", ImGuiSliderFlags_AlwaysClamp);
    ImGui::SameLine(0,fontSize*6);
    ImGui::SetNextItemWidth(fontSize * 16);
    // ImGui::SliderFloat("文字缩放", &io.FontGlobalScale, 0.5f, 1.5f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
    ImGui::DragFloat("文字缩放", &io.FontGlobalScale, 0.005f, 0.8f, 1.5f, "%.2f", ImGuiSliderFlags_AlwaysClamp);

    if (columns_count < 2)
        columns_count = 2;
    ImGui::Columns(columns_count, NULL, TRUE);
    for (auto it : field.profileList)
    {
        if(ImGui::GetColumnIndex() == 0)
            ImGui::Separator();
        ImGui::Text("姓名: %s", it->GetName());
        ImGui::Text("年龄: %s", it->GetAge());
        ImGui::Text("地域: %s", it->GetArea());
        ImGui::PushID(it->GetName());
        ImGui::BeginDisabled(isProEdit == ImGuiInputTextFlags_None);
        if(ImGui::Button("详情", ImVec2(-FLT_MIN, 0.0f))) {
            isShowDetailProfile = TRUE;
            shownProfile = it;
            std::cout << it->GetName() << " is clicked" << std::endl;
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
    float fontSize = ImGui::GetFontSize();

    ImGui::Text("手机:");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("phonenum");
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
    ImGui::InputText("", "-", 128, isProEdit);
    ImGui::PopID();

    ImGui::Text("微信:");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("wechat");
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
    ImGui::InputText("", "-", 128, isProEdit);
    ImGui::PopID();

    ImGui::Text("邮箱:");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("email");
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 16);
    ImGui::InputText("", "-", 128, isProEdit);
    ImGui::PopID();

    ImGui::Text("LinkedIn:");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("linkedin");
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 16);
    ImGui::InputText("", "-", 128, isProEdit);
    ImGui::PopID();

    ImGui::Text("其他链接");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("otherlink");
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 16);
    ImGui::InputText("", "-", 128, isProEdit);
    ImGui::PopID();
}


void ProfileWindow::ShowBasicInfoTab()
{
    float fontSize = ImGui::GetFontSize();

    /* Name */
    ImGui::Text("姓名:");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("name");
    ImGui::SetNextItemWidth(fontSize * 8);
    ImGui::InputText("", shownProfile->GetName(), 128, isProEdit);
    ImGui::PopID();

    ImGui::Text("预估职级:");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("pregrade");
    ImGui::SetNextItemWidth(fontSize * 4);
    ImGui::InputText("", "-", 128, isProEdit);
    ImGui::PopID();

    ImGui::Text("公司:");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("company");
    ImGui::SetNextItemWidth(fontSize * 8);
    ImGui::InputText("", "-", 128, isProEdit);
    ImGui::PopID();

    ImGui::SameLine(0, fontSize * 1);
    ImGui::Text("职级:");
    ImGui::SameLine(0, fontSize);
    ImGui::PushID("grade");
    ImGui::SetNextItemWidth(fontSize * 4);
    ImGui::InputText("", "-", 128, isProEdit);
    ImGui::PopID();

    /* Age */
    ImGui::Text("出生年份:");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("age");
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 4);
    ImGui::InputText("", shownProfile->GetAge(), 128, isProEdit);
    ImGui::PopID();

    /* Age */
    ImGui::Text("工作地:");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("area");
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 4);
    ImGui::InputText("", shownProfile->GetArea(), 128, isProEdit);
    ImGui::PopID();

    ImGui::SameLine(0, fontSize * 5);
    ImGui::Text("家乡:");
    ImGui::SameLine(0, fontSize);
    ImGui::PushID("hometown");
    ImGui::SetNextItemWidth(fontSize * 8);
    ImGui::InputText("", "-", 128, isProEdit);
    ImGui::PopID();

    
    ImGui::Text("学历:");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("diploma");
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 4);
    ImGui::InputText("", "-", 128, isProEdit);
    ImGui::PopID();

    ImGui::SameLine(0, fontSize * 5);
    ImGui::Text("专业:");
    ImGui::SameLine(0, fontSize);
    ImGui::PushID("major");
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
    ImGui::InputText("", "-", 128, isProEdit);
    ImGui::PopID();

    ImGui::Text("毕业院校:");
    ImGui::SameLine(fontSize * 5, 0);
    ImGui::PushID("college");
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
    ImGui::InputText("", "-", 128, isProEdit);
    ImGui::PopID();

    ImGui::SameLine(0, fontSize);
    ImGui::Text("毕业时间:");
    ImGui::SameLine(0, fontSize);
    ImGui::PushID("graddate");
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 4);
    ImGui::InputText("", "-", 128, isProEdit);
    ImGui::PopID();

    ImGui::Text("经历:");
    ImGui::InputTextMultiline("career", "-", 4, ImVec2(-FLT_MIN, fontSize * 8), isProEdit);
}

void ProfileWindow::ShowDetailProfile()
{
    ImGui::Begin( "简历详情", &isShowDetailProfile);

    float fontSize = ImGui::GetFontSize();
    ImGui::BeginDisabled(isProEdit == ImGuiInputTextFlags_None);
    if(ImGui::Button("编辑", ImVec2(fontSize * 4, 0))) {
        isProEdit = ImGuiInputTextFlags_None;
    };
    ImGui::EndDisabled();
    ImGui::SameLine(0, fontSize);
    ImGui::BeginDisabled(isProEdit == ImGuiInputTextFlags_ReadOnly);
    if(ImGui::Button("保存", ImVec2(fontSize * 4, 0))) {
        isProEdit = ImGuiInputTextFlags_ReadOnly;
        shownProfile->SaveData();
    };
    ImGui::EndDisabled();

    ImGui::Separator();
    ImGui::NewLine();
    
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
        // TODO Here
        ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("文件浏览")) {
        // TODO Here
        ImGui::EndTabItem();
    }
    ImGui::EndTabBar();

    ImGui::End();
}

void ProfileWindow::Draw()
{
    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowRounding = 8.0f;
    style.ItemSpacing = ImVec2(6, 10);
    style.FrameRounding = 4.0f;
    style.WindowPadding = ImVec2(10, 15);

    ImGui::Begin( "简历列表", nullptr, ImGuiWindowFlags_NoCollapse);
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
    ImGui::BeginTabBar("FieldsTab");
    for (auto it : fields) {
        if (ImGui::BeginTabItem(it->GetName().c_str())) {
            ShortcutList(*it);
            ImGui::EndTabItem();
        }
    }
    ImGui::EndTabBar();
    ImGui::End();

    if(isShowDetailProfile) {
        ShowDetailProfile();
    } else if (isProEdit == ImGuiInputTextFlags_None) {
        isProEdit = ImGuiInputTextFlags_ReadOnly;
        shownProfile->SaveData();
    }

}