#pragma once
#include	<directxmath.h>

class GameObject {
	uint64_t m_id = 0;			// 識別子
protected:
	DirectX::XMFLOAT3 m_pos;	// 位置
	DirectX::XMFLOAT4X4 m_mtx;	// 姿勢
	DirectX::XMFLOAT4X4 m_graph; //グラフ
public:
	GameObject() {}
	virtual ~GameObject() {}
	virtual bool Init() = 0;
	virtual void Finalize() = 0;

	// 姿勢を取得
	DirectX::XMFLOAT4X4 GetMtx() {
		return m_mtx;
	}

	DirectX::XMFLOAT4X4 SetGraph(DirectX::XMFLOAT4X4 graph_mtx) {
		m_graph = graph_mtx;
	}

	// 位置を取得
	DirectX::XMFLOAT3 GetPos() {
		return m_pos;
	}

	// ＩＤを取得
	uint64_t GetID() {
		return m_id;
	}

	// 初期位置セット
	void SetInitialPos(DirectX::XMFLOAT3 initpos) {
		m_pos = initpos;
	}
};