#include	<random>
#include	"nikoniko.h"
#include	"drawaxis.h"
#include	"dx11mathutil.h"
#include	"ModelMgr.h"
#include	"CDirectInput.h"
#include	"StageHit.h"

// モンスターの親子関係及び初期位置・初期角度を定義したデータ
Nikoniko::NikonikoInitData	Nikoniko::ObjectInitData[] = {
	// 親					モデル番号				初期位置		初期角度 
	// 注意：かならず子供より親が先にならぶこと
	{ Nikonikos::NikoModel, Nikonikos::NikoModel, {0.0f, 0.0f, 0.0f}, {0,0,0}, },
};
// モデルファイル名リスト
Nikoniko::NikonikoModelData			Nikoniko::XFileData[] = {
	{Nikonikos::NikoModel, "assets/paimon/Texture/paimon.pmx"},
};

// モデルを読み込んだかどうか
bool Nikoniko::m_modelloadflag = false;

bool Nikoniko::Init()
{
	bool sts = true;

	// 行列初期化
	DX11MtxIdentity(m_mtx);					// モデルを読み込む

	// 読み込みが完了していなければ読み込む
	if (Nikoniko::m_modelloadflag == false) {
		// モデル読み込み（モンスター用）
			sts = ModelMgr::GetInstance().LoadModel(
				Nikoniko::XFileData[0].XfileName,	// ファイル名 
				"shader/vs.hlsl",				// 頂点シェーダー
				"shader/ps.hlsl",				// ピクセルシェーダー
				"assets/paimon/Texture");		// テクスチャの格納フォルダ
			if (!sts) {
				char str[128];
				sprintf_s<128>(str, "%s", Nikoniko::XFileData[0].XfileName);
				MessageBox(nullptr, str, "load error", MB_OK);
			}

		Nikoniko::m_modelloadflag = true;
	}

	// モデルポインターをセット
	SetModel(ModelMgr::GetInstance().GetModelPtr(XFileData[0].XfileName), 1);

	return sts;
}

void Nikoniko::Draw()
{
	// モデル描画
	drawaxis(m_mtx, 200, m_pos);
	m_models->Draw(m_mtx);
}

void Nikoniko::Update()
{

	XMFLOAT4 axisX;
	XMFLOAT4 axisY;
	XMFLOAT4 axisZ;

	static bool keyinput = true;

	//　本体の移動処理
	//  X軸を取り出す
	axisX.x = m_mtx._11;
	axisX.y = m_mtx._12;
	axisX.z = m_mtx._13;
	axisX.w = 0.0f;

	// Y軸を取り出す
	axisY.x = m_mtx._21;
	axisY.y = m_mtx._22;
	axisY.z = m_mtx._23;
	axisY.w = 0.0f;

	// Z軸を取り出す
	axisZ.x = m_mtx._31;
	axisZ.y = m_mtx._32;
	axisZ.z = m_mtx._33;
	axisZ.w = 0.0f;

	// 移動量及び角度を０にする
	m_speed = 0.0f;
	m_angle.x = m_angle.y = m_angle.z = 0.0f;

	// Z軸を取り出す
	axisZ.x = m_mtx._31;
	axisZ.y = m_mtx._32;
	axisZ.z = m_mtx._33;
	axisZ.w = 0.0f;

	// 位置を更新
	m_pos.x += axisZ.x * m_speed;
	m_pos.y += axisZ.y * m_speed;
	m_pos.z += axisZ.z * m_speed;

	m_mtx._41 = m_pos.x;
	m_mtx._42 = m_pos.y;
	m_mtx._43 = m_pos.z;

	keyinput = false;
}

void Nikoniko::Finalize()
{
}