#include <cinttypes>

#include "dx11util.h"
#include "CModel.h"
#include "CCamera.h"
#include "DX11Settransform.h"
#include "dx11mathutil.h"
#include "Application.h"
#include "CDirectInput.h"
#include "updatespherecamera.h"
#include "BoundingSphere.h"
#include "myimgui.h"
#include "ModelMgr.h"
#include "implot/implot.h"
#include "myimplot.h"
#include "player.h"
#include "AnimationData.h"

//AnimationData g_anime;
AnimationData g_anime;
Character g_character;

//モーショングラフリスト
enum GraphList 
{
	animetion,
	timeline
};

template <typename T>
inline T RandomRange(T min, T max) {
	T scale = rand() / (T)RAND_MAX;
	return min + scale * (max - min);
}

struct ScrollingBuffer {
	int MaxSize;
	int Offset;
	ImVector<ImVec2> Data;
	ScrollingBuffer(int max_size = 2000) {
		MaxSize = max_size;
		Offset = 0;
		Data.reserve(MaxSize);
	}
	void AddPoint(float x, float y) {
		if (Data.size() < MaxSize)
			Data.push_back(ImVec2(x, y));
		else {
			Data[Offset] = ImVec2(x, y);
			Offset = (Offset + 1) % MaxSize;
		}
	}
	void Erase() {
		if (Data.size() > 0) {
			Data.shrink(0);
			Offset = 0;
		}
	}
};

struct RollingBuffer {
	float Span;
	ImVector<ImVec2> Data;
	RollingBuffer() {
		Span = 10.0f;
		Data.reserve(2000);
	}
	void AddPoint(float x, float y) {
		float xmod = fmodf(x, Span);
		if (!Data.empty() && xmod < Data.back().x)
			Data.shrink(0);
		Data.push_back(ImVec2(xmod, y));
	}
};

ImVec4 RandomColor() {
	ImVec4 col;
	col.x = RandomRange(0.0f, 1.0f);
	col.y = RandomRange(0.0f, 1.0f);
	col.z = RandomRange(0.0f, 1.0f);
	col.w = 1.0f;
	return col;
}

// IMGUIウインドウ
void imguidebug() {
	static int listNo;

	if (ImGui::Button(u8"アニメーション"))
	{
		listNo = animetion;
	}

	if (listNo == animetion)
	{
		g_anime.Demo_DragPoints();
	}

	//現在の座標をImGuiで表す
	ImGui::Begin(u8"座標");
	static float slider1 = 0.0f;
	static float slider2 = 0.0f;
	slider1 = g_anime.g_character.GetPos().x;
	slider2 = g_anime.g_character.GetPos().y;
	static char text1[8] = "";

	ImGui::SliderFloat(u8"現在座標", &slider1, -100, 100);

	DirectX::XMFLOAT3 outputpos = { 0,0,0 };

	outputpos.x = slider1;
	outputpos.y = slider2;

	g_character.SetPos(outputpos);

	ImGui::End();
}

//ゲーム初期化
void GameInit() {
	// DX11初期化
	DX11Init(
		Application::Instance()->GetHWnd(),
		Application::CLIENT_WIDTH,
		Application::CLIENT_HEIGHT,
		false);

	// カメラが必要
	DirectX::XMFLOAT3 eye(0, 20, -160);	// カメラの位置
	DirectX::XMFLOAT3 lookat(0, 0, 0);	// 注視点
	DirectX::XMFLOAT3 up(0, 1, 0);		// カメラの上向きベクトル

	CCamera::GetInstance()->Init(
		10.0f,							// ニアクリップ
		10000.0f,						// ファークリップ
		XM_PI / 5.0f,					// 視野角
		static_cast<float>(Application::CLIENT_WIDTH),		// スクリーン幅
		static_cast<float>(Application::CLIENT_HEIGHT),		// スクリーンの高さ
		eye, lookat, up);				// カメラのデータ

	// 平行光源をセット
	DX11LightInit(
		DirectX::XMFLOAT4(1, 1, -1, 0));

	// アルファブレンド有効化
	TurnOnAlphablend();

	// DirectT INPUT 初期化
	CDirectInput::GetInstance().Init(
		Application::Instance()->GetHInst(),
		Application::Instance()->GetHWnd(),
		Application::CLIENT_WIDTH,
		Application::CLIENT_HEIGHT);

	// キャラクター初期化
	g_character.Init();

	// IMGUI初期化
	imguiInit();
	implotInit();
}

void GameInput(uint64_t dt) {
	CDirectInput::GetInstance().GetKeyBuffer();
}

//更新処理
void GameUpdate(uint64_t dt) {
	DirectX::XMFLOAT3 eye = CCamera::GetInstance()->GetEye();
	// キャラクター更新
	g_character.Update();

	//カメラ操作
	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_A)) {
		DirectX::XMFLOAT4(eye.x, eye.y -= 2.0f, eye.z, 0);
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_D)) {
		DirectX::XMFLOAT4(eye.x, eye.y += 2.0f, eye.z, 0);
	}
}

//描画
void GameRender(uint64_t dt) {

	float col[4] = { 1,0,0,1 };

	// 描画前処理
	DX11BeforeRender(col);

	XMFLOAT4X4 mtx;

	// プロジェクション変換行列取得
	mtx = CCamera::GetInstance()->GetProjectionMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION, mtx);

	// ビュー変換行列を取得
	mtx = CCamera::GetInstance()->GetCameraMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW, mtx);

	//ライティング
	DirectX::XMFLOAT3 eye = CCamera::GetInstance()->GetEye();
	DX11LightUpdate(DirectX::XMFLOAT4(eye.x, eye.y, eye.z, 0));

	// キャラクター描画
	g_character.Draw();

	// imgui 描画
	imguiDraw(imguidebug);

	// 描画後処理
	DX11AfterRender();
}

void GameDispose() {

	ModelMgr::GetInstance().Finalize();
	imguiExit();
	DX11Uninit();
}