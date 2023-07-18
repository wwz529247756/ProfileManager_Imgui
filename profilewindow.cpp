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
    static int columns_count = 4;
    ImGui::DragInt("##columns_count", &columns_count, 0.1f, 2, 4, "%d columns");
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

void ProfileWindow::ShowDetailProfile()
{
    ImGui::Begin( "简历详情", &isShowDetailProfile);

    ImGui::BeginDisabled(isProEdit == ImGuiInputTextFlags_None);
    if(ImGui::Button("编辑")) {
        isProEdit = ImGuiInputTextFlags_None;
    };
    ImGui::EndDisabled();
    ImGui::SameLine(0, 30);
    ImGui::BeginDisabled(isProEdit == ImGuiInputTextFlags_ReadOnly);
    if(ImGui::Button("保存")) {
        isProEdit = ImGuiInputTextFlags_ReadOnly;
        shownProfile->SaveData();
    };
    ImGui::EndDisabled();

    ImGui::Separator();
    ImGui::NewLine();

    /* Name */
    ImGui::Text("姓名:");
    ImGui::SameLine(100, 0);
    ImGui::PushID("name");
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
    ImGui::InputText("", shownProfile->GetName(), 128, isProEdit);
    ImGui::PopID();

    /* Age */
    ImGui::Text("出生年份:");
    ImGui::SameLine(100, 0);
    ImGui::PushID("age");
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 4);
    ImGui::InputText("", shownProfile->GetAge(), 128, isProEdit);
    ImGui::PopID();

    /* Age */
    ImGui::Text("工作地:");
    ImGui::SameLine(100, 0);
    ImGui::PushID("area");
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 4);
    ImGui::InputText("", shownProfile->GetArea(), 128, isProEdit);
    ImGui::PopID();

    ImGui::SameLine(0, 80);
    ImGui::Text("家乡:");
    ImGui::SameLine(0, 10);
    ImGui::PushID("hometown");
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 4);
    ImGui::InputText("", "-", 128, isProEdit);
    ImGui::PopID();

    
    ImGui::Text("学历:");
    ImGui::SameLine(100, 0);
    ImGui::PushID("diploma");
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 4);
    ImGui::InputText("", "-", 128, isProEdit);
    ImGui::PopID();

    ImGui::SameLine(0, 80);
    ImGui::Text("专业:");
    ImGui::SameLine(0, 10);
    ImGui::PushID("major");
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
    ImGui::InputText("", "-", 128, isProEdit);
    ImGui::PopID();

    ImGui::Text("毕业院校:");
    ImGui::SameLine(100, 0);
    ImGui::PushID("college");
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
    ImGui::InputText("", "-", 128, isProEdit);
    ImGui::PopID();

    ImGui::SameLine(0, 7);
    ImGui::Text("from");
    ImGui::SameLine(0, 10);
    ImGui::PushID("from");
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 4);
    ImGui::InputText("", "-", 32, isProEdit);
    ImGui::PopID();
    ImGui::SameLine(0, 10);
    ImGui::Text("to");
    ImGui::SameLine(0, 10);
    ImGui::PushID("to");
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 4);
    ImGui::InputText("", "-", 32, isProEdit);
    ImGui::PopID();


    ImGui::End();
}

void ProfileWindow::Draw()
{
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