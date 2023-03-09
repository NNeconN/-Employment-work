#pragma once
#include "gameobject.h"
#include "CModel.h"

class Nikoniko :public GameObject {
public:
	// オブジェクト名
	enum Nikonikos {
		NikoModel, // キャラクター
		Maxobj
	};

	// 構造体型タグ(親子関係と初期配置データ)
	struct NikonikoInitData {
		Nikoniko::Nikonikos ParentObjectNo; // 親オブジェクトＮｏ
		Nikoniko::Nikonikos ModelNo; // モデル番号
		DirectX::XMFLOAT3 FirstPosition; // 最初の位置
		DirectX::XMFLOAT3 FirstAngle; // 最初の角度

	};

	// モンスターのモデル名リスト
	struct NikonikoModelData {
		Nikoniko::Nikonikos ModelNo; // モデル番号
		const char* XfileName; // Ｘファイル名

	};

	// 初期配置データ
	static NikonikoInitData ObjectInitData[];

	// モデルファイル名リスト
	static NikonikoModelData XFileData[];

	// モデルセット
	void SetModel(CModel* p, int idx) {
		m_models = p;

	}

	void SetPos(DirectX::XMFLOAT3 input)
	{

		m_pos = input;
	}

	bool Init();
	void Draw();
	void Update();
	void Finalize();

private:
	void UpdateLocalpose(); // ローカルポーズを更新する
	void CaliculateParentChildMtx(); // 親子関係を考慮した行列を作成
	static bool m_modelloadflag; // モデルを読み込んだかどうか
	CModel* m_models;
	DirectX::XMFLOAT4X4 m_mtxlocalpose;
	// 親子関係を考慮した行列

	float m_speed = 0.0f; // スピード
	DirectX::XMFLOAT3 m_angle; // 回転角

public:
	float hp = 100;
};