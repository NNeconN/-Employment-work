#include	<random>
#include	"player.h"
#include	"drawaxis.h"
#include	"dx11mathutil.h"
#include	"ModelMgr.h"
#include	"CDirectInput.h"

// モンスターの親子関係及び初期位置・初期角度を定義したデータ
Character::CharacterInitData	Character::ObjectInitData[] = {
										// 初期位置			初期角度 
	// 注意：かならず子供より親が先にならぶこと
	{ CHARACTERS::NONE, CHARACTERS::CHAR, {0.0f, 0.0f, 0.0f}, {0,0,0}, },
	{CHARACTERS::CHAR,CHARACTERS::STAGE,{0.0f, -10.0f, 0.0f}, {0,0,0}, },
	{ CHARACTERS::END, CHARACTERS::END, { 0.0f, 0.0f, 0.0f }, { 0,0,0 } } // 終了
};

// モデルファイル名リスト
Character::CharacterModelData			Character::XFileData[] = {
	{CHARACTERS::CHAR, "assets/VCharacter/VCharacter.pmx"},
	{CHARACTERS::STAGE,"assets/stage/kyousitu/koukoukyousitu.pmx"},
	{CHARACTERS::END,nullptr }
};

// モデルを読み込んだかどうか
bool Character::m_modelloadflag = false;

bool Character::Init()
{
	bool sts = true;

	// 行列初期化
	DX11MtxIdentity(m_mtx);	// モデルを読み込む

	// 読み込みが完了していなければ読み込む
	if (Character::m_modelloadflag == false) {
		// モデル読み込み
		for (int i = 0; i < static_cast<int>(Character::PARTSMAX) - 2; i++) {
			sts = ModelMgr::GetInstance().LoadModel(
				Character::XFileData[i].XfileName,	// ファイル名 
				"shader/vs.hlsl",					// 頂点シェーダー
				"shader/ps.hlsl",					// ピクセルシェーダー
				"assets/texture/");					// テクスチャの格納フォルダ
			if (!sts) {
				char str[128];
				sprintf_s<128>(str, "%s", Character::XFileData[i].XfileName);
				MessageBox(nullptr, str, "load error", MB_OK);
			}
		}
		Character::m_modelloadflag = true;
	}

	// モデルポインターをセット
	for (int i = 0; i < static_cast<int>(Character::PARTSMAX) - 2; i++) {
		SetModel(ModelMgr::GetInstance().GetModelPtr(XFileData[i].XfileName), i);
	}

	// プレイヤ行列初期化(初期位置)（自分のことだけを考えた行列を作成）
	for (int i = 0; i < static_cast<int>(CHARACTERS::PARTSMAX) - 2; i++) {
		DX11MakeWorldMatrix(m_mtxlocalpose[i], ObjectInitData[i].FirstAngle, ObjectInitData[i].FirstPosition);
	}

	// 親子関係を考慮した行列を計算する
	CaliculateParentChildMtx();	

	return sts;
}

void Character::Draw()
{
	// モデル描画

	for (int i = 0; i < static_cast<int>(CHARACTERS::PARTSMAX) - 2; i++) {
		m_models[i]->Draw(m_mtxParentChild[i]);
	}
}

//キャラクター更新処理
void Character::Update()
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

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_A)) {
		m_angle.y -= 2.0f;
		keyinput = true;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_D)) {
		m_angle.y += 2.0f;
		keyinput = true;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_S)) {
		m_speed = 0.8f;
		keyinput = true;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_W)) {
		m_speed = -0.8f;
		keyinput = true;
	}

	// キー入力があった場合
	if (keyinput) {
		XMFLOAT4 qt;	// クオータニオン

		// 行列からクオータニオンを生成
		DX11GetQtfromMatrix(m_mtx, qt);

		XMFLOAT4 qtx, qty, qtz;		// クオータニオン

		// 指定軸回転のクオータニオンを生成
		DX11QtRotationAxis(qtx, axisX, m_angle.x);
		DX11QtRotationAxis(qty, axisY, m_angle.y);
		DX11QtRotationAxis(qtz, axisZ, m_angle.z);

		// クオータニオンを合成
		XMFLOAT4 tempqt1;
		DX11QtMul(tempqt1, qt, qtx);

		XMFLOAT4 tempqt2;
		DX11QtMul(tempqt2, qty, qtz);

		XMFLOAT4 tempqt3;
		DX11QtMul(tempqt3, tempqt1, tempqt2);

		// クオータニオンをノーマライズ
		DX11QtNormalize(tempqt3, tempqt3);

		// クオータニオンから行列を作成
		DX11MtxFromQt(m_mtx, tempqt3);
	}

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

	CaliculateParentChildMtx();

	keyinput = false;
}

void Character::Finalize()
{
}


void Character::CaliculateParentChildMtx()
{
	m_mtxlocalpose[CHARACTERS::CHAR] = m_mtx;

	m_mtxParentChild[CHARACTERS::CHAR] = m_mtxlocalpose[CHARACTERS::CHAR];

	DX11MtxMultiply(m_mtxParentChild[CHARACTERS::STAGE], m_mtxlocalpose[CHARACTERS::STAGE], m_mtxlocalpose[CHARACTERS::CHAR]);
}

