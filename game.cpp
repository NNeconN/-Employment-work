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

//���[�V�����O���t���X�g
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

// IMGUI�E�C���h�E
void imguidebug() {
	static int listNo;

	if (ImGui::Button(u8"�A�j���[�V����"))
	{
		listNo = animetion;
	}

	if (listNo == animetion)
	{
		g_anime.Demo_DragPoints();
	}

	//���݂̍��W��ImGui�ŕ\��
	ImGui::Begin(u8"���W");
	static float slider1 = 0.0f;
	static float slider2 = 0.0f;
	slider1 = g_anime.g_character.GetPos().x;
	slider2 = g_anime.g_character.GetPos().y;
	static char text1[8] = "";

	ImGui::SliderFloat(u8"���ݍ��W", &slider1, -100, 100);

	DirectX::XMFLOAT3 outputpos = { 0,0,0 };

	outputpos.x = slider1;
	outputpos.y = slider2;

	g_character.SetPos(outputpos);

	ImGui::End();
}

//�Q�[��������
void GameInit() {
	// DX11������
	DX11Init(
		Application::Instance()->GetHWnd(),
		Application::CLIENT_WIDTH,
		Application::CLIENT_HEIGHT,
		false);

	// �J�������K�v
	DirectX::XMFLOAT3 eye(0, 20, -160);	// �J�����̈ʒu
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

	// �L�����N�^�[������
	g_character.Init();

	// IMGUI������
	imguiInit();
	implotInit();
}

void GameInput(uint64_t dt) {
	CDirectInput::GetInstance().GetKeyBuffer();
}

//�X�V����
void GameUpdate(uint64_t dt) {
	DirectX::XMFLOAT3 eye = CCamera::GetInstance()->GetEye();
	// �L�����N�^�[�X�V
	g_character.Update();

	//�J��������
	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_A)) {
		DirectX::XMFLOAT4(eye.x, eye.y -= 2.0f, eye.z, 0);
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_D)) {
		DirectX::XMFLOAT4(eye.x, eye.y += 2.0f, eye.z, 0);
	}
}

//�`��
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

	// �L�����N�^�[�`��
	g_character.Draw();

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