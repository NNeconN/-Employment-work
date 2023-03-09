#include	"skydome.h"
#include	"dx11mathutil.h"

bool Skydome::Init() {

	bool sts = true;

	// s—ñ‰Šú‰»
	DX11MtxIdentity(m_mtx);


	return sts;
}

void Skydome::Draw() {

	// ƒ‚ƒfƒ‹•`‰æ
	m_pmodel->Draw(m_mtx);

}

void Skydome::Update() {

}

void Skydome::Finalize() {
}
