#pragma once
#include	"gameobject.h"
#include	"CModel.h"

class Skydome : public GameObject {
private:
	CModel*	m_pmodel;	// ３Ｄモデル
public:
	bool Init();		// 初期処理

	void Draw();		// 描画

	void Update();		// 更新

	void SetModel(CModel* p) {
		m_pmodel = p;
	}

	void Finalize();	// 終了処理	
};