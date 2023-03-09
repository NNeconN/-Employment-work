#pragma once
#include "gameobject.h"
#include "CModel.h"

class Monster :public GameObject {
public:
	// オブジェクト名
	enum MONSTERPARTS {
		HIP, // 腰
		BODY, // 胴体
		HEAD, // 頭
		ARMR0, // 右上腕
		ARML0, // 左上腕
		LEGR0, // 左太もも
		LEGL0, // 左太もも
		ARMR1, // 右上腕
		ARML1, // 左上腕
		LEGR1, // 右もも
		LEGL1, // 左もも
		WINGR0, // 右翼０
		WINGL0, // 左翼０
		WINGR1, // 右翼１
		WINGL1, // 左翼１
		TAIL0, // 尻尾
		NONE, // なし
		END, // 終了
		PARTSMAX

	};

	// 構造体型タグ(親子関係と初期配置データ)
	struct MonsterInitData {
		Monster::MONSTERPARTS ParentObjectNo; // 親オブジェクトＮｏ
		Monster::MONSTERPARTS ModelNo; // モデル番号
		DirectX::XMFLOAT3 FirstPosition; // 最初の位置
		DirectX::XMFLOAT3 FirstAngle; // 最初の角度

	};

	// モンスターのモデル名リスト
	struct MonsterModelData {
		Monster::MONSTERPARTS ModelNo; // モデル番号
		const char* XfileName; // Ｘファイル名

	};

	// 初期配置データ
	static MonsterInitData ObjectInitData[];

	// モデルファイル名リスト
	static MonsterModelData XFileData[];

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
	CModel* m_models[MONSTERPARTS::PARTSMAX];
	DirectX::XMFLOAT4X4 m_mtxlocalpose[MONSTERPARTS::PARTSMAX];
	// 自分のことだけを考えた行列
	DirectX::XMFLOAT4X4 m_mtxParentChild[MONSTERPARTS::PARTSMAX];
	// 親子関係を考慮した行列

	float m_speed = 0.0f; // スピード
	DirectX::XMFLOAT3 m_angle; // 回転角

public:
	float hp = 100;
	MONSTERPARTS *g_MfileData;
};