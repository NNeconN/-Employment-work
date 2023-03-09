#pragma once
#include	"gameobject.h"
#include	"CModel.h"

class Tank :public GameObject {
public:
	// オブジェクト名
	enum TANKPARTS {
		TANK_CATERPILLAR,			// キャタピラ
		TANK_BASE,					// 本体
		TANK_TOP,					// 砲塔
		TANK_BARREL,				// 砲身
		NONE,						// なし
		END,						// 終了
		PARTSMAX					// パーツの最大数
	};

	// 構造体型タグ
	struct	TankInitData {
		Tank::TANKPARTS		ParentObjectNo;		// 親オブジェクトＮｏ
		Tank::TANKPARTS		ModelNo;			// モデル番号
		DirectX::XMFLOAT3	FirstPosition;		// 最初の位置
		DirectX::XMFLOAT3	FirstAngle;			// 最初の角度
	};

	// タンクのモデル名リスト
	struct	TankModelData {
		Tank::TANKPARTS		ModelNo;					// モデル番号
		const char*			XfileName;					// Ｘファイル名
	};

	// 初期配置データ
	static TankInitData	ObjectInitData[];

	// モデルファイル名リスト
	static TankModelData			XFileData[];

	// モデルセット
	void SetModel(CModel* p,int idx) {
		m_models[idx] = p;
	}

	bool Init();
	void Draw();
	void Update();
	void Finalize();

private:
	void UpdateLocalpose();				// ローカルポーズを更新する
	void CaliculateParentChildMtx();	// 親子関係を考慮した行列を作成
	static bool m_modelloadflag;		// モデルを読み込んだかどうか
	CModel*		m_models[TANKPARTS::PARTSMAX];
	DirectX::XMFLOAT4X4			m_mtxlocalpose[PARTSMAX];	// 自分のことだけを考えた行列
	DirectX::XMFLOAT4X4			m_mtxParentChild[PARTSMAX];	// 親子関係を考慮した行列

	float						m_speed = 0.0f;				// スピード
	DirectX::XMFLOAT3			m_angle;					// 回転角
};