#pragma once
#include "gameobject.h"
#include "CModel.h"

class Character :public GameObject {
public:
	// �I�u�W�F�N�g��
	enum CHARACTERS {
		CHAR, // �L����
		STAGE,//�X�e�[�W
		NONE, // �Ȃ�
		END, // �I��
		PARTSMAX
	};

	// �\���̌^�^�O(�e�q�֌W�Ə����z�u�f�[�^)
	struct CharacterInitData {
		Character::CHARACTERS ParentObjectNo; // �e�I�u�W�F�N�g�m��
		Character::CHARACTERS ModelNo; // ���f���ԍ�
		DirectX::XMFLOAT3 FirstPosition; // �ŏ��̈ʒu
		DirectX::XMFLOAT3 FirstAngle; // �ŏ��̊p�x
	};

	// �L�����N�^�[�̃��f�������X�g
	struct CharacterModelData {
		Character::CHARACTERS ModelNo; // ���f���ԍ�
		const char* XfileName; // �w�t�@�C����
	};

	// �����z�u�f�[�^
	static CharacterInitData ObjectInitData[];

	// ���f���t�@�C�������X�g
	static CharacterModelData XFileData[];

	// ���f���Z�b�g
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
	void UpdateLocalpose(); // ���[�J���|�[�Y���X�V����
	void CaliculateParentChildMtx(); // �e�q�֌W���l�������s����쐬
	static bool m_modelloadflag; // ���f����ǂݍ��񂾂��ǂ���
	CModel* m_models[CHARACTERS::PARTSMAX];
	DirectX::XMFLOAT4X4 m_mtxlocalpose[CHARACTERS::PARTSMAX];
	// �����̂��Ƃ������l�����s��
	DirectX::XMFLOAT4X4 m_mtxParentChild[CHARACTERS::PARTSMAX];
	// �e�q�֌W���l�������s��

	float m_speed = 0.0f; // �X�s�[�h
	DirectX::XMFLOAT3 m_angle; // ��]�p

public:
	float hp = 100;
	CHARACTERS *g_MfileData;
};