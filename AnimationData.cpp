#include "implot/implot.h"
#include "imgui/imgui.h"
#include "myimplot.h"
#include "CCamera.h"
#include "AnimationData.h"
//#include "player.h"	//相互インクルードを防ぐ為にcppにかく。ほんとはhに書くのがいい

CDirectInput directinput;

XMFLOAT3 outputpos = { 0,0,0 };

AnimationData::AnimationData() //コンストラクタ
{
}

//線形保管されているグラフ
void AnimationData::Demo_DragPoints()
{
	static bool barStart = false;
	ImGui::BulletText("Click and drag each point.");
	static ImPlotDragToolFlags flags = ImPlotDragToolFlags_None;
	ImPlotAxisFlags ax_flags = ImPlotAxisFlags_LockMin | ImPlotAxisFlags_NoTickMarks;

	//時間
	static float t = 0;

	// アニメーション再生場所
	double frametime = t;

	if (ImGui::Button(u8"再生"))
	{
		barStart = true;
	}
	ImGui::SameLine();
	if (ImGui::Button(u8"停止"))
	{
		barStart = false;
	}

	if (barStart == true)
	{
		t += ImGui::GetIO().DeltaTime;
	}
	
	if (ImGui::CollapsingHeader(u8"グラフ"))
	{
		ImGui::Text("Graph");

		if (ImPlot::BeginPlot("##Bezier", ImVec2(-1, -1), ImPlotFlags_CanvasOnly)) {
			ImPlot::SetupAxes(0, 0, frametime, ax_flags);
			ImPlot::SetupAxesLimits(-5, 60, -0.2, 1);
			static ImPlotPoint P[] = { ImPlotPoint(.0f,.0f), ImPlotPoint(5,0.4),  ImPlotPoint(.0f,.0f),  ImPlotPoint(0.2,0.2) };

			// ドラック検知初期化とフレームの時間表示
			bool isDragFrameTime = ImPlot::DragLineX(0, &frametime, { 1,1,0,1 });

			sx = lerp(P[0].x, P[1].x, t);
			sy = lerp(P[0].y, P[1].y, t);

			if (isDragFrameTime == true)
			{
				t = frametime;
			}

			if (P[1].x > t)
			{
				outputpos.x = sx;
				outputpos.y = sy;
			}		

			g_character.SetPos(outputpos); //プレイヤー座標結果

			//ImVec4点のRGBA
			ImPlot::DragPoint(0, &P[0].x, &P[0].y, ImVec4(1, 0.5f, 0.5f, 1), 4, flags);
			ImPlot::DragPoint(1, &P[1].x, &P[1].y, ImVec4(1, 0.5f, 0.5f, 1), 4, flags);

			//ImVec4線のRGBA
			ImPlot::SetNextLineStyle(ImVec4(1, 0.5f, 0.5f, 1));
			ImPlot::PlotLine("##h1", &P[0].x, &P[0].y, 2, 0, 0, sizeof(ImPlotPoint));

			ImPlot::EndPlot();
		}
	}
}