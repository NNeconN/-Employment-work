#include "implot/implot.h"
#include "imgui/imgui.h"
#include "myimplot.h"
#include "CCamera.h"
#include "TimelineData.h"
#include "player.h"

Timeline::Timeline()
{
}

void Timeline::Demo_TimelineGraph()
{
	ImGui::BulletText("Click and drag each point.");
	static ImPlotDragToolFlags flags = ImPlotDragToolFlags_None;
	ImPlotAxisFlags ax_flags = ImPlotAxisFlags_LockMin;

	//時間
	static float t = 0;
	t += ImGui::GetIO().DeltaTime;

	// アニメーション再生場所
	frametime = t;
 
	if (ImGui::CollapsingHeader(u8"ああああ"))
	{
		if (ImGui::Button("button"))
		{
			addButton = true;
		}

		if (addButton)
		{
			TrackData();
			//TrackData()が入る addButtonが押された後Trackが使えるようにする 2回押したら2Trackできる
		}

		if (ImGui::Button("file1"))
		{
			addButton2 = true;
		}
		else if(ImGui::Button("file2"))
		{

		}

		if (ImPlot::BeginPlot("##Bezier", ImVec2(-1, -1), ImPlotFlags_CanvasOnly)) {
			ImPlot::SetupAxes(0, 0, frametime, ax_flags);
			ImPlot::SetupAxesLimits(-5, 60, -0.2, 1);
			ImPlot::EndPlot();
		}
	}
}

//タイムライン上のトラック情報
void Timeline::TrackData()
{
	/*g_monster->g_MfileDa*/
	// Testing behavior of widgets stacking their own regular popups over the modal.
	static int item = 1;

	//ImGui::Combo("Combo", &item, "aaaa\0bbbb\0cccc\0dddd\0eeee\0\0");

	//if (ImGui::BeginMenuBar())
	//{
	//	if (ImGui::BeginMenu("File"))
	//	{
	//		if (ImGui::MenuItem("Some menu item")) {}
	//		ImGui::EndMenu();
	//	}
	//	ImGui::EndMenuBar();
	//}
}

//ファイル選択やカラーなど↓

//ImGui::TextWrapped("Modal windows are like popups but the user cannot close them by clicking outside.");
//
//if (ImGui::Button("Delete.."))
//ImGui::OpenPopup("Delete?");
//
//// Always center this window when appearing
//ImVec2 center = ImGui::GetMainViewport()->GetCenter();
//ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
//
//if (ImGui::BeginPopupModal("Delete?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
//{
//    ImGui::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!\n\n");
//    ImGui::Separator();
//
//    //static int unused_i = 0;
//    //ImGui::Combo("Combo", &unused_i, "Delete\0Delete harder\0");
//
//    static bool dont_ask_me_next_time = false;
//    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
//    ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
//    ImGui::PopStyleVar();
//
//    if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
//    ImGui::SetItemDefaultFocus();
//    ImGui::SameLine();
//    if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
//    ImGui::EndPopup();
//}
//
//if (ImGui::Button("Stacked modals.."))
//ImGui::OpenPopup("Stacked 1");
//if (ImGui::BeginPopupModal("Stacked 1", NULL, ImGuiWindowFlags_MenuBar))
//{
//    if (ImGui::BeginMenuBar())
//    {
//        if (ImGui::BeginMenu("File"))
//        {
//            if (ImGui::MenuItem("Some menu item")) {}
//            ImGui::EndMenu();
//        }
//        ImGui::EndMenuBar();
//    }
//    ImGui::Text("Hello from Stacked The First\nUsing style.Colors[ImGuiCol_ModalWindowDimBg] behind it.");
//
//    // Testing behavior of widgets stacking their own regular popups over the modal.
//    static int item = 1;
//    static float color[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
//    ImGui::Combo("Combo", &item, "aaaa\0bbbb\0cccc\0dddd\0eeee\0\0");
//    ImGui::ColorEdit4("color", color);
//
//    if (ImGui::Button("Add another modal.."))
//        ImGui::OpenPopup("Stacked 2");
//
//    // Also demonstrate passing a bool* to BeginPopupModal(), this will create a regular close button which
//    // will close the popup. Note that the visibility state of popups is owned by imgui, so the input value
//    // of the bool actually doesn't matter here.
//    bool unused_open = true;
//    if (ImGui::BeginPopupModal("Stacked 2", &unused_open))
//    {
//        ImGui::Text("Hello from Stacked The Second!");
//        if (ImGui::Button("Close"))
//            ImGui::CloseCurrentPopup();
//        ImGui::EndPopup();
//    }
//
//    if (ImGui::Button("Close"))
//        ImGui::CloseCurrentPopup();
//    ImGui::EndPopup();
//}