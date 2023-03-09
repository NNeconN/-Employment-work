#include	<random>
#include	"tank.h"
#include	"drawaxis.h"
#include	"dx11mathutil.h"
#include	"ModelMgr.h"
#include	"CDirectInput.h"
#include	"StageHit.h"

// 戦車の親子関係及び初期位置・初期角度を定義したデータ
Tank::TankInitData	Tank::ObjectInitData[] = {
	//   親							モデル番号						初期位置				初期角度	// 注意：かならず子供より親が先にならぶこと
	{ Tank::NONE,				Tank::TANK_CATERPILLAR,			{ 0, 0, 0 },				{ 0, 0, 0 } },	// 戦車 キャタピラー
	{ Tank::TANK_CATERPILLAR,	Tank::TANK_BASE,				{ 0, 0, 0 },				{ 0, 0, 0 } },	// 戦車 ベース
	{ Tank::TANK_BASE,			Tank::TANK_TOP,					{ 0, 3.82394f, -1.15362f }, { 0, 0, 0 } },	// 戦車 砲台
	{ Tank::TANK_TOP,			Tank::TANK_BARREL,				{ 0, 0.684f, -3.53283f },	{ 0, 0, 0 } },	// 戦車 砲身
	{ Tank::END,				Tank::END,						{ 0, 0, 0 },				{ 0, 0, 0 } },	// 終端コード
};

// モデルファイル名リスト
Tank::TankModelData			Tank::XFileData[] = {
	{ Tank::TANK_CATERPILLAR,	"assets/tank/tank10_cat.x" },				// 戦車のキャタピラー
	{ Tank::TANK_BASE,			"assets/tank/tank10_base.x" },				// 戦車の土台
	{ Tank::TANK_TOP,			"assets/tank/tank10_top.x" },				// 戦車の砲台
	{ Tank::TANK_BARREL,		"assets/tank/tank10_pipe.x" },				// 戦車の砲身
	{ Tank::END, nullptr }													// 終端コード
};

// モデルを読み込んだかどうか
bool Tank::m_modelloadflag = false;

bool Tank::Init() {

	bool sts = true;

	// 行列初期化
	DX11MtxIdentity(m_mtx);					// モデルを読み込む

	// 読み込みが完了していなければ読み込む
	if (Tank::m_modelloadflag == false) {
		// モデル読み込み（戦車用）
		for (int i = 0; i < static_cast<int>(Tank::PARTSMAX) - 2; i++) {
			sts = ModelMgr::GetInstance().LoadModel(
				Tank::XFileData[i].XfileName,	// ファイル名 
				"shader/vs.hlsl",				// 頂点シェーダー
				"shader/ps.hlsl",				// ピクセルシェーダー
				"assets/tank/");				// テクスチャの格納フォルダ
			if (!sts) {
				char str[128];
				sprintf_s<128>(str, "%s", Tank::XFileData[i].XfileName);
				MessageBox(nullptr, str, "load error", MB_OK);
			}
		}
		Tank::m_modelloadflag = true;
	}

	// モデルポインターをセット
	for (int i = 0; i < static_cast<int>(Tank::PARTSMAX) - 2; i++) {
		SetModel(ModelMgr::GetInstance().GetModelPtr(XFileData[i].XfileName), i);
	}

	// プレイヤ行列初期化(初期位置)（自分のことだけを考えた行列を作成）
	for (int i = 0; i < static_cast<int>(TANKPARTS::PARTSMAX) - 2; i++) {
		DX11MakeWorldMatrix(m_mtxlocalpose[i], ObjectInitData[i].FirstAngle, ObjectInitData[i].FirstPosition);
	}

	// 親子関係を考慮した行列を計算する
	CaliculateParentChildMtx();					// 親の行列を掛け算してグローバルポーズを作る

	return sts;
}

void Tank::Draw() {

	// モデル描画
//	drawaxis(m_mtx, 200, m_pos);

	for (int i = 0; i < static_cast<int>(TANKPARTS::PARTSMAX) - 2; i++) {
		m_models[i]->Draw(m_mtxParentChild[i]);
	}
}

void Tank::UpdateLocalpose() {

	// 各パーツの回転角度(前フレームからの変位量)
	XMFLOAT3			partsangle[static_cast<int>(TANKPARTS::PARTSMAX)];
	XMFLOAT3			partstrans[static_cast<int>(TANKPARTS::PARTSMAX)];

	// どのパーツを動かすか
	int idx = 0;

	// 角度と移動量を初期化
	for (int i = 0; i < static_cast<int>(TANKPARTS::PARTSMAX); i++) {
		partsangle[i].x = 0.0f;
		partsangle[i].y = 0.0f;
		partsangle[i].z = 0.0f;
		partstrans[i].x = 0.0f;
		partstrans[i].y = 0.0f;
		partstrans[i].z = 0.0f;
	}


	// キャタピラを動かす
//	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_A)) {
//		idx = TANK_CATERPILLAR;
//		partsangle[idx].y += 1.0f;
//	}

	// キャタピラを動かす
//	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_D)) {
//		idx = TANK_CATERPILLAR;
//		partsangle[idx].y -= 1.0f;
//	}


	// パーツのローカルポーズを決める為のキー操作
	// 砲身を動かす
	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_UP)) {
		idx = TANK_BARREL;
		partsangle[idx].x += 1.0f;
	}

	// 砲身を動かす
	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_DOWN)) {
		idx = TANK_BARREL;
		partsangle[idx].x -= 1.0f;
	}

	// 砲台を動かす
	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_LEFT)) {
		idx = TANK_TOP;
		partsangle[idx].y += 1.0f;
	}

	// 砲台を動かす
	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_RIGHT)) {
		idx = TANK_TOP;
		partsangle[idx].y -= 1.0f;
	}

	// パーツの角度ローカルポーズを表す行列を計算
	XMFLOAT4X4 partsmtx;
	DX11MakeWorldMatrix(partsmtx, partsangle[idx], partstrans[idx]);
	DX11MtxMultiply(m_mtxlocalpose[idx], partsmtx, m_mtxlocalpose[idx]);
}

// 更新
void Tank::Update() {

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
		m_angle.y -= 1.0f;
		keyinput = true;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_D)) {
		m_angle.y += 1.0f;
		keyinput = true;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_W)) {
		m_speed = 1.0f;
		keyinput = true;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_S)) {
		m_speed = -1.0f;
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
	m_pos.x += axisZ.x*m_speed;
	m_pos.y += axisZ.y*m_speed;
	m_pos.z += axisZ.z*m_speed;

	m_mtx._41 = m_pos.x;
	m_mtx._42 = m_pos.y;					
	m_mtx._43 = m_pos.z;

	// ローカルポーズを更新する
	UpdateLocalpose();

	// 親子関係を考慮した行列を計算する
	CaliculateParentChildMtx();

	keyinput = false;
}

void Tank::Finalize() {

}

void Tank::CaliculateParentChildMtx() {

	// 一番の親のキャタピラに行列をセット
//	m_mtxlocalpose[TANK_CATERPILLAR] = m_mtx;

/*
	// 親子関係を考慮した行列を作る
	for (int i = 0; i < static_cast<int>(TANKPARTS::PARTSMAX) - 2; i++) {
		m_mtxParentChild[i] = m_mtxlocalpose[i];
		for (int j = static_cast<int>(ObjectInitData[i].ParentObjectNo);
			j != static_cast<int>(TANKPARTS::NONE);
			j = static_cast<int>(ObjectInitData[j].ParentObjectNo)) {

			DX11MtxMultiply(m_mtxParentChild[i], m_mtxParentChild[i], m_mtxlocalpose[j]);
		}
	}
*/

	// ローカルポーズを親方向に掛けていく


	m_mtxlocalpose[Tank::TANK_CATERPILLAR] = m_mtx;

	// キャタピラ
	m_mtxParentChild[Tank::TANK_CATERPILLAR] = m_mtxlocalpose[Tank::TANK_CATERPILLAR];

	// 本体
	DX11MtxMultiply(m_mtxParentChild[Tank::TANK_BASE], m_mtxlocalpose[Tank::TANK_BASE], m_mtxlocalpose[Tank::TANK_CATERPILLAR]);

	// 砲台
	DX11MtxMultiply(m_mtxParentChild[Tank::TANK_TOP], m_mtxlocalpose[Tank::TANK_TOP], m_mtxlocalpose[Tank::TANK_BASE]);
	DX11MtxMultiply(m_mtxParentChild[Tank::TANK_TOP], m_mtxParentChild[Tank::TANK_TOP], m_mtxlocalpose[Tank::TANK_CATERPILLAR]);

	// 砲身
	DX11MtxMultiply(m_mtxParentChild[Tank::TANK_BARREL], m_mtxlocalpose[Tank::TANK_BARREL], m_mtxlocalpose[Tank::TANK_TOP]);
	DX11MtxMultiply(m_mtxParentChild[Tank::TANK_BARREL], m_mtxParentChild[Tank::TANK_BARREL], m_mtxlocalpose[Tank::TANK_BASE]);
	DX11MtxMultiply(m_mtxParentChild[Tank::TANK_BARREL], m_mtxParentChild[Tank::TANK_BARREL], m_mtxlocalpose[Tank::TANK_CATERPILLAR]);

}