#pragma once

#include	<random>
#include	"gameobject.h"
#include	"CModel.h"
#include	"dx11mathutil.h"

class Stage :public GameObject {
private:
	CModel*	m_pmodel;						// ‚R‚cƒ‚ƒfƒ‹

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
};