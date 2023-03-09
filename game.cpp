#include <cinttypes>

#include "dx11util.h"
#include "CModel.h"
#include "CCamera.h"
#include "DX11Settransform.h"
#include "dx11mathutil.h"
#include "Application.h"
#include "CDirectInput.h"
#include "skydome.h"
#include "updatespherecamera.h"
#include "BoundingSphere.h"
#include "myimgui.h"
#include "ModelMgr.h"
#include "stage.h"
#include "StageHit.h"
#include "tank.h"
#include "implot/implot.h"
#include "myimplot.h"
#include "player.h"	//���݃C���N���[�h��h���ׂ�cpp�ɂ����B�ق�Ƃ�h�ɏ����̂�����
#include "AnimationData.h"
#include "TimelineData.h"

enum GraphList //���[�V�����O���t���X�g
{
	animetion,
	timeline
};

//AnimationData g_anime;
Timeline g_timeline;
AnimationData g_anime;
Monster g_monster;

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

void GameInit() {
	// DX11������
	DX11Init(
		Application::Instance()->GetHWnd(),
		Application::CLIENT_WIDTH,
		Application::CLIENT_HEIGHT,
		false);

	// �J�������K�v
	DirectX::XMFLOAT3 eye(0, 10, -270);	// �J�����̈ʒu
	DirectX::XMFLOAT3 lookat(0, 0, 0);	// �����_
	DirectX::XMFLOAT3 up(0, 1, 0);		// �J�����̏�����x�N�g��

	CCamera::GetInstance()->Init(
		10.0f,							// �j�A�N���b�v
		10000.0f,						// �t�@�[�N���b�v
		XM_PI / 5.0f,					// ����p
		static_cast<float>(Application::CLIENT_WIDTH),		// �X�N���[����
		static_cast<float>(Application::CLIENT_HEIGHT),		// �X�N���[���̍���
		eye, lookat, up);				// �J�����̃f�[�^

	// ���s�������Z�b�g
	DX11LightInit(
		DirectX::XMFLOAT4(1, 1, -1, 0));

	// �A���t�@�u�����h�L����
	TurnOnAlphablend();

	// DirectT INPUT ������
	CDirectInput::GetInstance().Init(
		Application::Instance()->GetHInst(),
		Application::Instance()->GetHWnd(),
		Application::CLIENT_WIDTH,
		Application::CLIENT_HEIGHT);

	g_monster.Init();

	// IMGUI������
	imguiInit();
	implotInit();
}

void GameInput(uint64_t dt) {
	CDirectInput::GetInstance().GetKeyBuffer();
}

void GameUpdate(uint64_t dt) {
	// �v���C���X�V
	g_monster.Update();
}

//�t�@�C���I��
void FileSelection()
{
	if (ImGui::Button("Model File"))
		ImGui::OpenPopup("Model File");
	if (ImGui::BeginPopupModal("Model File", NULL, ImGuiWindowFlags_MenuBar))
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Some menu item")) {}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::Text("Hello from Stacked The First\nUsing style.Colors[ImGuiCol_ModalWindowDimBg] behind it.");

		// Testing behavior of widgets stacking their own regular popups over the modal.
		static int item = 1;
		static float color[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
		ImGui::Combo("Combo", &item, "aaaa\0bbbb\0cccc\0dddd\0eeee\0\0");
		ImGui::ColorEdit4("color", color);

		if (ImGui::Button("Add another modal.."))
			ImGui::OpenPopup("Stacked 2");

		// Also demonstrate passing a bool* to BeginPopupModal(), this will create a regular close button which
		// will close the popup. Note that the visibility state of popups is owned by imgui, so the input value
		// of the bool actually doesn't matter here.
		bool unused_open = true;
		if (ImGui::BeginPopupModal("Stacked 2", &unused_open))
		{
			ImGui::Text("Hello from Stacked The Second!");
			if (ImGui::Button("Close"))
				ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
		}

		if (ImGui::Button("Close"))
			ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}
}

// IMGUI�E�C���h�E
void imguidebug() {
	//Demo_DragPoints();
	static int listNo;

	if (ImGui::Button(u8"�A�j���[�V����"))
	{
		listNo = animetion;
	}

	if (ImGui::Button(u8"�^�C�����C��"))
	{
		listNo = timeline;
	}

	if (listNo == animetion)
	{
		g_anime.Demo_DragPoints();
	}

	if (listNo == timeline)
	{
		g_timeline.Demo_TimelineGraph();
	}

	//���W��DragGui
	ImGui::Begin(u8"���W");
	static float slider1 = 0.0f;
	static float slider2 = 0.0f;
	slider1 = g_anime.g_monster.GetPos().x;
	slider2 = g_anime.g_monster.GetPos().y;
	static char text1[8] = "";

	ImGui::Text("fps: %.2f", &g_monster.hp);
	ImGui::SliderFloat("slider 1", &slider1, -100, 100);

	FileSelection();

	DirectX::XMFLOAT3 outputpos = { 0,0,0 };

	outputpos.x = slider1;
	outputpos.y = slider2;

	g_monster.SetPos(outputpos);
	ImGui::InputText("textbox 1", text1, sizeof(text1));
	if (ImGui::Button("button 1")) {
		slider1 = 0.0f;
		strcpy(text1, "button 1");
	}

	ImGui::End();
}

void GameRender(uint64_t dt) {

	float col[4] = { 1,0,0,1 };

	// �`��O����
	DX11BeforeRender(col);

	XMFLOAT4X4 mtx;

	// �v���W�F�N�V�����ϊ��s��擾
	mtx = CCamera::GetInstance()->GetProjectionMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION, mtx);

	// �r���[�ϊ��s����擾
	mtx = CCamera::GetInstance()->GetCameraMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW, mtx);

	//���C�e�B���O
	DirectX::XMFLOAT3 eye = CCamera::GetInstance()->GetEye();
	DX11LightUpdate(DirectX::XMFLOAT4(eye.x, eye.y, eye.z, 0));

	g_monster.Draw();

	// imgui �`��
	imguiDraw(imguidebug);

	// �`��㏈��
	DX11AfterRender();
}

void GameDispose() {

	ModelMgr::GetInstance().Finalize();

	imguiExit();
	DX11Uninit();
}