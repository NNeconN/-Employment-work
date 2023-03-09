#pragma once

#include	<random>
#include	"gameobject.h"
#include	"CModel.h"
#include	"dx11mathutil.h"
#include	"CDirectInput.h"

class Enemy :public GameObject {
private:
	CModel*	m_pmodel;						// ３Ｄモデル

	// 状態
	enum class STATUS{
		S1_MOVE_FLY = 0,
		S1_MOVE_BOMB,
	};

	enum class ACTION{
		ACT_LEFT = 0,
		ACT_RIGHT,
		ACT_UP,
		ACT_DOWN,
		ACT_ROLLP,
		ACT_ROLLM,
		ACT_STRAIGHT,

		MAX_ACTION
	};

	float				m_speed=1.0;		// スピード

	XMFLOAT3			m_angle;			// 回転角

	std::mt19937		m_mt;				// 乱数発生用
	std::mt19937		m_mt2;

	ACTION				m_action;			// アクション種別
	unsigned int		m_actionKeepTime;	// アクションカウンタ

public:
	bool Init();

	void Draw();

	void Update();

	void Finalize();

	void SetModel(CModel* p) {
		m_pmodel = p;
	}

	CModel* GetModel() {
		return m_pmodel;
	}

	void AutoPilot();

};