#pragma once
#include	<DirectXMath.h>
#include	<vector>
#include	<memory>
#include	"gameobject.h"

// 前方宣言
class CModel;

// 弾ステータス
enum class BULLETSTATUS{
	LIVE,
	DEAD
};

class Bullet :public GameObject {
private:
	BULLETSTATUS	m_sts;				// ステータス
	CModel*		m_pmodel;				// ３Ｄモデル
	DirectX::XMFLOAT3	m_direction;	// 発射方向
	float		m_speed = 2.0f;
	uint32_t	m_life = 60;
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

	void SetDirection(DirectX::XMFLOAT4X4 mtx) {
		m_mtx = mtx;
		m_direction = DirectX::XMFLOAT3(mtx._31, mtx._32, mtx._33);
	}

	bool isLive() {
		if (m_sts == BULLETSTATUS::LIVE) {
			return true;
		}
		else {
			return false;
		}
	}
};

class BulletMgr {
private:
	std::vector<std::unique_ptr<Bullet>>	m_bullets;
public:
	// 弾発射
	void Fire(DirectX::XMFLOAT4X4 mtx);

	void Update(DirectX::XMFLOAT4X4 mtx);

	void Draw();

	void Finalize();
};

