#include	<random>
#include	"player.h"
#include	"drawaxis.h"
#include	"dx11mathutil.h"
#include	"ModelMgr.h"
#include	"CDirectInput.h"

// �����X�^�[�̐e�q�֌W�y�я����ʒu�E�����p�x���`�����f�[�^
Character::CharacterInitData	Character::ObjectInitData[] = {
										// �����ʒu			�����p�x 
	// ���ӁF���Ȃ炸�q�����e����ɂȂ�Ԃ���
	{ CHARACTERS::NONE, CHARACTERS::CHAR, {0.0f, 0.0f, 0.0f}, {0,0,0}, },
	{CHARACTERS::CHAR,CHARACTERS::STAGE,{0.0f, -10.0f, 0.0f}, {0,0,0}, },
	{ CHARACTERS::END, CHARACTERS::END, { 0.0f, 0.0f, 0.0f }, { 0,0,0 } } // �I��
};

// ���f���t�@�C�������X�g
Character::CharacterModelData			Character::XFileData[] = {
	{CHARACTERS::CHAR, "assets/VCharacter/VCharacter.pmx"},
	{CHARACTERS::STAGE,"assets/stage/kyousitu/koukoukyousitu.pmx"},
	{CHARACTERS::END,nullptr }
};

// ���f����ǂݍ��񂾂��ǂ���
bool Character::m_modelloadflag = false;

bool Character::Init()
{
	bool sts = true;

	// �s�񏉊���
	DX11MtxIdentity(m_mtx);	// ���f����ǂݍ���

	// �ǂݍ��݂��������Ă��Ȃ���Γǂݍ���
	if (Character::m_modelloadflag == false) {
		// ���f���ǂݍ���
		for (int i = 0; i < static_cast<int>(Character::PARTSMAX) - 2; i++) {
			sts = ModelMgr::GetInstance().LoadModel(
				Character::XFileData[i].XfileName,	// �t�@�C���� 
				"shader/vs.hlsl",					// ���_�V�F�[�_�[
				"shader/ps.hlsl",					// �s�N�Z���V�F�[�_�[
				"assets/texture/");					// �e�N�X�`���̊i�[�t�H���_
			if (!sts) {
				char str[128];
				sprintf_s<128>(str, "%s", Character::XFileData[i].XfileName);
				MessageBox(nullptr, str, "load error", MB_OK);
			}
		}
		Character::m_modelloadflag = true;
	}

	// ���f���|�C���^�[���Z�b�g
	for (int i = 0; i < static_cast<int>(Character::PARTSMAX) - 2; i++) {
		SetModel(ModelMgr::GetInstance().GetModelPtr(XFileData[i].XfileName), i);
	}

	// �v���C���s�񏉊���(�����ʒu)�i�����̂��Ƃ������l�����s����쐬�j
	for (int i = 0; i < static_cast<int>(CHARACTERS::PARTSMAX) - 2; i++) {
		DX11MakeWorldMatrix(m_mtxlocalpose[i], ObjectInitData[i].FirstAngle, ObjectInitData[i].FirstPosition);
	}

	// �e�q�֌W���l�������s����v�Z����
	CaliculateParentChildMtx();	

	return sts;
}

void Character::Draw()
{
	// ���f���`��

	for (int i = 0; i < static_cast<int>(CHARACTERS::PARTSMAX) - 2; i++) {
		m_models[i]->Draw(m_mtxParentChild[i]);
	}
}

//�L�����N�^�[�X�V����
void Character::Update()
{

	XMFLOAT4 axisX;
	XMFLOAT4 axisY;
	XMFLOAT4 axisZ;

	static bool keyinput = true;

	//�@�{�̂̈ړ�����
	//  X�������o��
	axisX.x = m_mtx._11;
	axisX.y = m_mtx._12;
	axisX.z = m_mtx._13;
	axisX.w = 0.0f;

	// Y�������o��
	axisY.x = m_mtx._21;
	axisY.y = m_mtx._22;
	axisY.z = m_mtx._23;
	axisY.w = 0.0f;

	// Z�������o��
	axisZ.x = m_mtx._31;
	axisZ.y = m_mtx._32;
	axisZ.z = m_mtx._33;
	axisZ.w = 0.0f;

	// �ړ��ʋy�ъp�x���O�ɂ���
	m_speed = 0.0f;
	m_angle.x = m_angle.y = m_angle.z = 0.0f;

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_A)) {
		m_angle.y -= 2.0f;
		keyinput = true;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_D)) {
		m_angle.y += 2.0f;
		keyinput = true;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_S)) {
		m_speed = 0.8f;
		keyinput = true;
	}

	if (CDirectInput::GetInstance().CheckKeyBuffer(DIK_W)) {
		m_speed = -0.8f;
		keyinput = true;
	}

	// �L�[���͂��������ꍇ
	if (keyinput) {
		XMFLOAT4 qt;	// �N�I�[�^�j�I��

		// �s�񂩂�N�I�[�^�j�I���𐶐�
		DX11GetQtfromMatrix(m_mtx, qt);

		XMFLOAT4 qtx, qty, qtz;		// �N�I�[�^�j�I��

		// �w�莲��]�̃N�I�[�^�j�I���𐶐�
		DX11QtRotationAxis(qtx, axisX, m_angle.x);
		DX11QtRotationAxis(qty, axisY, m_angle.y);
		DX11QtRotationAxis(qtz, axisZ, m_angle.z);

		// �N�I�[�^�j�I��������
		XMFLOAT4 tempqt1;
		DX11QtMul(tempqt1, qt, qtx);

		XMFLOAT4 tempqt2;
		DX11QtMul(tempqt2, qty, qtz);

		XMFLOAT4 tempqt3;
		DX11QtMul(tempqt3, tempqt1, tempqt2);

		// �N�I�[�^�j�I�����m�[�}���C�Y
		DX11QtNormalize(tempqt3, tempqt3);

		// �N�I�[�^�j�I������s����쐬
		DX11MtxFromQt(m_mtx, tempqt3);
	}

	// Z�������o��
	axisZ.x = m_mtx._31;
	axisZ.y = m_mtx._32;
	axisZ.z = m_mtx._33;
	axisZ.w = 0.0f;

	// �ʒu���X�V
	m_pos.x += axisZ.x * m_speed;
	m_pos.y += axisZ.y * m_speed;
	m_pos.z += axisZ.z * m_speed;

	m_mtx._41 = m_pos.x;
	m_mtx._42 = m_pos.y;
	m_mtx._43 = m_pos.z;

	CaliculateParentChildMtx();

	keyinput = false;
}

void Character::Finalize()
{
}


void Character::CaliculateParentChildMtx()
{
	m_mtxlocalpose[CHARACTERS::CHAR] = m_mtx;

	m_mtxParentChild[CHARACTERS::CHAR] = m_mtxlocalpose[CHARACTERS::CHAR];

	DX11MtxMultiply(m_mtxParentChild[CHARACTERS::STAGE], m_mtxlocalpose[CHARACTERS::STAGE], m_mtxlocalpose[CHARACTERS::CHAR]);
}

