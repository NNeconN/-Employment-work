#pragma once
#include "gameobject.h"
#include "CModel.h"

class Character :public GameObject {
public:
	// オブジェクト名
	enum CHARACTERS {
		CHAR, // キャラ
		STAGE,//ステージ
		NONE, // なし
		END, // 終了
		PARTSMAX
	};

	// 構造体型タグ(親子関係と初期配置データ)
	struct CharacterInitData {
		Character::CHARACTERS ParentObjectNo; // 親オブジェクトＮｏ
		Character::CHARACTERS ModelNo; // モデル番号
		DirectX::XMFLOAT3 FirstPosition; // 最初の位置
		DirectX::XMFLOAT3 FirstAngle; // 最初の角度
	};

	// キャラクターのモデル名リスト
	struct CharacterModelData {
		Character::CHARACTERS ModelNo; // モデル番号
		const char* XfileName; // Ｘファイル名
	};

	// 初期配置データ
	static CharacterInitData ObjectInitData[];

	// モデルファイル名リスト
	static CharacterModelData XFileData[];

	// モデルセット
	void SetModel(CModel* p, int idx) {
		m_models[idx] = p;
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
	CModel* m_models[CHARACTERS::PARTSMAX];
	DirectX::XMFLOAT4X4 m_mtxlocalpose[CHARACTERS::PARTSMAX];
	// 自分のことだけを考えた行列
	DirectX::XMFLOAT4X4 m_mtxParentChild[CHARACTERS::PARTSMAX];
	// 親子関係を考慮した行列

	float m_speed = 0.0f; // スピード
	DirectX::XMFLOAT3 m_angle; // 回転角

public:
	float hp = 100;
	CHARACTERS *g_MfileData;
};