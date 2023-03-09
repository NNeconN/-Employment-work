#include	<random>
#include	"stage.h"
#include	"drawaxis.h"
#include	"ModelMgr.h"


bool Stage::Init() {

	bool sts = true;

	// s—ñ‰Šú‰»
	DX11MtxIdentity(m_mtx);

	




	return sts;
}

void Stage::Draw() {

	// ƒ‚ƒfƒ‹•`‰æ
	m_pmodel->Draw(m_mtx);

}

void Stage::Update() {

}

void Stage::Finalize() {

}
