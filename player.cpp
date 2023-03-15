#include	<random>
#include	"player.h"
#include	"drawaxis.h"
#include	"dx11mathutil.h"
#include	"ModelMgr.h"
#include	"CDirectInput.h"
#include	"StageHit.h"

// モンスターの親子関係及び初期位置・初期角度を定義したデータ
Monster::MonsterInitData	Monster::ObjectInitData[] = {
	// 親					モデル番号				初期位置		初期角度 
	// 注意：かならず子供より親が先にならぶこと
	{ MONSTERPARTS::NONE, MONSTERPARTS::HIP, {0.0f, 0.0f, 0.0f}, {0,0,0}, },
	{ MONSTERPARTS::HIP, MONSTERPARTS::BODY, {0.0f, 1.3f, -0.4f}, {0,0,0}, },
	{ MONSTERPARTS::BODY, MONSTERPARTS::HEAD, {0.0f, 1.85f, -0.55f}, {0,0,0}, },
	{ MONSTERPARTS::BODY, MONSTERPARTS::ARMR0, {-1.8f, 1.35f, -0.3f}, {0,0,0}, },
	{ MONSTERPARTS::BODY, MONSTERPARTS::ARML0, {1.8f, 1.35f, -0.3f}, {0,0,0}, },
	{ MONSTERPARTS::HIP, MONSTERPARTS::LEGR0, {-1.0f, -0.6f, 0.45f}, {0,0,0}, },
	{ MONSTERPARTS::HIP, MONSTERPARTS::LEGL0, { 1.0f, -0.6f, 0.45f}, {0,0,0}, },
	{ MONSTERPARTS::ARMR0, MONSTERPARTS::ARMR1, {-1.18f, -1.27f, 0.7f}, {0,0,0}, },
	{ MONSTERPARTS::ARML0, MONSTERPARTS::ARML1, { 1.18f, -1.27f, 0.7f}, {0,0,0}, },
	{ MONSTERPARTS::LEGR0, MONSTERPARTS::LEGR1, {-1.17f, -2.3f, -1.26f}, {0,0,0}, },
	{ MONSTERPARTS::LEGL0, MONSTERPARTS::LEGL1, { 1.17f, -2.3f, -1.26f}, {0,0,0}, },
	{ MONSTERPARTS::BODY, MONSTERPARTS::WINGR0, { 0.1f, 1.17f, 0.0f}, {0,0,0}, },
	{ MONSTERPARTS::BODY, MONSTERPARTS::WINGL0, {-0.1f, 1.17f, 0.0f}, {0,0,0}, },
	{ MONSTERPARTS::WINGR0, MONSTERPARTS::WINGR1, {-2.48f, 4.36f, 1.58f}, {0,0,0}, },
	{ MONSTERPARTS::WINGL0, MONSTERPARTS::WINGL1, { 2.48f, 4.36f, 1.58f}, {0,0,0}, },
	{ MONSTERPARTS::HIP, MONSTERPARTS::TAIL0 , { 0.0f, 0.0f, 0.0f }, {0,0,0}, },
	{ MONSTERPARTS::END, MONSTERPARTS::END, { 0.0f, 0.0f, 0.0f }, { 0,0,0 } } // 終了
};
// モデルファイル名リスト
Monster::MonsterModelData			Monster::XFileData[] = {
	{MONSTERPARTS::HIP, "assets/VCharacter/VChar.pmx"},
	{MONSTERPARTS::BODY, "assets/model/Char/E2/e2_body.x"},
	{MONSTERPARTS::HEAD, "assets/model/Char/E2/e2_head.x"},
	{MONSTERPARTS::ARMR0,"assets/model/Char/E2/e2_armr0.x"},
	{MONSTERPARTS::ARML0,"assets/model/Char/E2/e2_arml0.x"},
	{MONSTERPARTS::LEGR0,"assets/model/Char/E2/e2_legr0.x"},
	{MONSTERPARTS::LEGL0,"assets/model/Char/E2/e2_legl0.x"},
	{MONSTERPARTS::ARMR1,"assets/model/Char/E2/e2_armr1.x"},
	{MONSTERPARTS::ARML1,"assets/model/Char/E2/e2_arml1.x"},
	{MONSTERPARTS::LEGR1,"assets/model/Char/E2/e2_legr1.x"},
	{MONSTERPARTS::LEGL1,"assets/model/Char/E2/e2_legl1.x"},
	{MONSTERPARTS::WINGR0,"assets/model/Char/E2/e2_wingr0.x"},
	{MONSTERPARTS::WINGL0,"assets/model/Char/E2/e2_wingl0.x"},
	{MONSTERPARTS::WINGR1,"assets/model/Char/E2/e2_wingr1.x"},
	{MONSTERPARTS::WINGL1,"assets/model/Char/E2/e2_wingl1.x"},
	{MONSTERPARTS::TAIL0 ,"assets/model/Char/E2/e2_tail0.x"},
	{MONSTERPARTS::END,nullptr }
};

// モデルを読み込んだかどうか
bool Monster::m_modelloadflag = false;

bool Monster::Init()
{
	bool sts = true;

	// 行列初期化
	DX11MtxIdentity(m_mtx);					// モデルを読み込む

	// 読み込みが完了していなければ読み込む
	if (Monster::m_modelloadflag == false) {
		// モデル読み込み（モンスター用）
		for (int i = 0; i < static_cast<int>(Monster::PARTSMAX) - 2; i++) {
			sts = ModelMgr::GetInstance().LoadModel(
				Monster::XFileData[i].XfileName,	// ファイル名 
				"shader/vs.hlsl",				// 頂点シェーダー
				"shader/ps.hlsl",				// ピクセルシェーダー
				"assets/VCharacter/Texture/");				// テクスチャの格納フォルダ
			if (!sts) {
				char str[128];
				sprintf_s<128>(str, "%s", Monster::XFileData[i].XfileName);
				MessageBox(nullptr, str, "load error", MB_OK);
			}
		}
		Monster::m_modelloadflag = true;
	}

	// モデルポインターをセット
	for (int i = 0; i < static_cast<int>(Monster::PARTSMAX) - 2; i++) {
		SetModel(ModelMgr::GetInstance().GetModelPtr(XFileData[i].XfileName), i);
	}

	// プレイヤ行列初期化(初期位置)（自分のことだけを考えた行列を作成）
	for (int i = 0; i < static_cast<int>(MONSTERPARTS::PARTSMAX) - 2; i++) {
		DX11MakeWorldMatrix(m_mtxlocalpose[i], ObjectInitData[i].FirstAngle, ObjectInitData[i].FirstPosition);
	}

	// 親子関係を考慮した行列を計算する
	CaliculateParentChildMtx();					// 親の行列を掛け算してグローバルポーズを作る

	return sts;
}

void Monster::Draw()
{
	// モデル描画
	// drawaxis(m_mtx, 200, m_pos);

	for (int i = 0; i < static_cast<int>(MONSTERPARTS::PARTSMAX) - 2; i++) {
		m_models[i]->Draw(m_mtxParentChild[i]);
	}
}

//キャラクター更新処理
void Monster::Update()
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

	// ローカルポーズを更新する
	UpdateLocalpose();

	// 親子関係を考慮した行列を計算する
	CaliculateParentChildMtx();

	keyinput = false;
}

void Monster::Finalize()
{
}

//キャラクター移動処理
void Monster::UpdateLocalpose()
{

	// 各パーツの回転角度(前フレームからの変位量)
	XMFLOAT3 partsangle[static_cast<int>(MONSTERPARTS::PARTSMAX)];
	XMFLOAT3 partstrans[static_cast<int>(MONSTERPARTS::PARTSMAX)];

	// どのパーツを動かすか
	int idx = 0;

	// 角度と移動量を初期化
	for (int i = 0; i < static_cast<int>(MONSTERPARTS::PARTSMAX); i++) {
		partsangle[i].x = 0.0f;
		partsangle[i].y = 0.0f;
		partsangle[i].z = 0.0f;
		partstrans[i].x = 0.0f;
		partstrans[i].y = 0.0f;
		partstrans[i].z = 0.0f;
	}

	// パーツのローカルポーズを決める為のキー操作
	// 腰を動かす
	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_UP)) {
		idx = HIP;
		partsangle[idx].x += 1.0f;
	}

	// 腰を動かす
	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_DOWN)) {
		idx = HIP;
		partsangle[idx].x -= 1.0f;
	}

	// 腰を動かす
	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_RIGHT)) {
		idx = HIP;
		partsangle[idx].y += 1.0f;
	}

	// 腰を動かす
	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_LEFT)) {
		idx = HIP;
		partsangle[idx].y -= 1.0f;
	}


	// パーツの角度ローカルポーズを表す行列を計算
	XMFLOAT4X4 partsmtx;
	DX11MakeWorldMatrix(partsmtx, partsangle[idx], partstrans[idx]);
	DX11MtxMultiply(m_mtxlocalpose[idx], partsmtx, m_mtxlocalpose[idx]);
}


void Monster::CaliculateParentChildMtx()
{
	// ローカルポーズを親方向に掛けていく


	m_mtxlocalpose[MONSTERPARTS::HIP] = m_mtx;

	// キャタピラ
	m_mtxParentChild[MONSTERPARTS::HIP] = m_mtxlocalpose[MONSTERPARTS::HIP];

	// 本体
	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::BODY], m_mtxlocalpose[MONSTERPARTS::BODY], m_mtxlocalpose[MONSTERPARTS::HIP]);

	// 砲台
	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::HEAD], m_mtxlocalpose[MONSTERPARTS::HEAD], m_mtxlocalpose[MONSTERPARTS::BODY]);
	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::HEAD], m_mtxParentChild[MONSTERPARTS::HEAD], m_mtxlocalpose[MONSTERPARTS::HIP]);

	// 砲身
	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::ARMR0], m_mtxlocalpose[MONSTERPARTS::ARMR0], m_mtxlocalpose[MONSTERPARTS::BODY]);
	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::ARMR0], m_mtxParentChild[MONSTERPARTS::ARMR0], m_mtxlocalpose[MONSTERPARTS::HIP]);

	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::ARML0], m_mtxlocalpose[MONSTERPARTS::ARML0], m_mtxlocalpose[MONSTERPARTS::BODY]);
	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::ARML0], m_mtxParentChild[MONSTERPARTS::ARML0], m_mtxlocalpose[MONSTERPARTS::HIP]);

	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::LEGR0], m_mtxlocalpose[MONSTERPARTS::LEGR0], m_mtxlocalpose[MONSTERPARTS::HIP]);

	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::LEGL0], m_mtxlocalpose[MONSTERPARTS::LEGL0], m_mtxlocalpose[MONSTERPARTS::HIP]);

	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::ARMR1], m_mtxlocalpose[MONSTERPARTS::ARMR1], m_mtxlocalpose[MONSTERPARTS::ARMR0]);
	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::ARMR1], m_mtxParentChild[MONSTERPARTS::ARMR1], m_mtxlocalpose[MONSTERPARTS::BODY]);
	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::ARMR1], m_mtxParentChild[MONSTERPARTS::ARMR1], m_mtxlocalpose[MONSTERPARTS::HIP]);

	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::ARML1], m_mtxlocalpose[MONSTERPARTS::ARML1], m_mtxlocalpose[MONSTERPARTS::ARML0]);
	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::ARML1], m_mtxParentChild[MONSTERPARTS::ARML1], m_mtxlocalpose[MONSTERPARTS::BODY]);
	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::ARML1], m_mtxParentChild[MONSTERPARTS::ARML1], m_mtxlocalpose[MONSTERPARTS::HIP]);

	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::LEGR1], m_mtxlocalpose[MONSTERPARTS::LEGR1], m_mtxlocalpose[MONSTERPARTS::LEGR0]);
	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::LEGR1], m_mtxParentChild[MONSTERPARTS::LEGR1], m_mtxlocalpose[MONSTERPARTS::HIP]);

	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::LEGL1], m_mtxlocalpose[MONSTERPARTS::LEGL1], m_mtxlocalpose[MONSTERPARTS::LEGL0]);
	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::LEGL1], m_mtxParentChild[MONSTERPARTS::LEGL1], m_mtxlocalpose[MONSTERPARTS::HIP]);

	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::WINGR0], m_mtxlocalpose[MONSTERPARTS::WINGR0], m_mtxlocalpose[MONSTERPARTS::BODY]);
	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::WINGR0], m_mtxParentChild[MONSTERPARTS::WINGR0], m_mtxlocalpose[MONSTERPARTS::HIP]);

	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::WINGL0], m_mtxlocalpose[MONSTERPARTS::WINGL0], m_mtxlocalpose[MONSTERPARTS::BODY]);
	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::WINGL0], m_mtxParentChild[MONSTERPARTS::WINGL0], m_mtxlocalpose[MONSTERPARTS::HIP]);

	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::WINGR1], m_mtxlocalpose[MONSTERPARTS::WINGR1], m_mtxlocalpose[MONSTERPARTS::WINGR0]);
	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::WINGR1], m_mtxParentChild[MONSTERPARTS::WINGR1], m_mtxlocalpose[MONSTERPARTS::BODY]);
	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::WINGR1], m_mtxParentChild[MONSTERPARTS::WINGR1], m_mtxlocalpose[MONSTERPARTS::HIP]);

	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::WINGL1], m_mtxlocalpose[MONSTERPARTS::WINGL1], m_mtxlocalpose[MONSTERPARTS::WINGL0]);
	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::WINGL1], m_mtxParentChild[MONSTERPARTS::WINGL1], m_mtxlocalpose[MONSTERPARTS::BODY]);
	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::WINGL1], m_mtxParentChild[MONSTERPARTS::WINGL1], m_mtxlocalpose[MONSTERPARTS::HIP]);

	DX11MtxMultiply(m_mtxParentChild[MONSTERPARTS::TAIL0], m_mtxlocalpose[MONSTERPARTS::TAIL0], m_mtxlocalpose[MONSTERPARTS::HIP]);
}

