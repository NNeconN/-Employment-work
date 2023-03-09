//#define NOMINMAX
//
//#include	<windows.h>
//#include	<vector>
//
//#include	<assimp\Importer.hpp>
//#include	<assimp\scene.h>
//#include	<assimp\postprocess.h>
//#include	<assimp/cimport.h>
//#include	<map>
//#include	<DirectXMath.h>
//#include	<stdio.h>
//
//#include	"utftosjisconv.h"
//
//#pragma comment (lib,"assimp-vc141-mtd.lib")
//
//// 頂点データ
//struct Vertex {
//	DirectX::XMFLOAT3 m_Pos;			//	位置
//	DirectX::XMFLOAT3 m_Normal;			//	法線
//	DirectX::XMFLOAT2 m_Tex;			//	UV座標
//	int				m_BoneIndex[4];		//	本来はボーンインデックスで管理するべき
//	float			m_BoneWeight[4];	//	ウェイト値
//	int				m_BoneNum;			//	ボーン数
//	std::string		m_BoneName[4];		//	本来はボーンインデックスで管理するべき
//};
//
//// ボーンデータ
//struct BONE
//{
//	unsigned int idx = -1;				// ボーン配列のインデックス番号
//	//std::string Name;
//	aiMatrix4x4 Matrix;					// 初期配置行列
//	aiMatrix4x4 AnimationMatrix;		// ボーン行列
//	aiMatrix4x4 OffsetMatrix;			// ボーンオフセット行列
//};
//
//// ボーン辞書
//std::map<std::string, BONE> g_Bone;		//ボーンデータ（名前で参照）
//
//// ボーン辞書
//std::map < std::string, std::vector<Vertex>> g_MeshVertex;		//メッシュ頂点（名前で参照）
//
//// メッシュの解析
//void processMesh(aiMesh* mesh, const aiScene* scene, int meshidx)
//{
//	std::vector<Vertex> vertices;			// 頂点
//
//	// 頂点情報を取得
//	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
//	{
//		Vertex vertex;
//
//		vertex.m_Pos.x = mesh->mVertices[i].x;
//		vertex.m_Pos.y = mesh->mVertices[i].y;
//		vertex.m_Pos.z = mesh->mVertices[i].z;
//
//		// 法線ベクトルが存在するか？
//		if (mesh->HasNormals()) {
//			vertex.m_Normal.x = mesh->mNormals[i].x;
//			vertex.m_Normal.y = mesh->mNormals[i].y;
//			vertex.m_Normal.z = mesh->mNormals[i].z;
//		}
//		else {
//			vertex.m_Normal.x = 0.0f;
//			vertex.m_Normal.y = 0.0f;
//			vertex.m_Normal.z = 0.0f;
//		}
//
//		// テクスチャ座標（０番目）が存在するか？
//		if (mesh->HasTextureCoords(0)) {
//			vertex.m_Tex.x = mesh->mTextureCoords[0][i].x;
//			vertex.m_Tex.y = mesh->mTextureCoords[0][i].y;
//		}
//
//		vertex.m_BoneNum = 0;
//
//		for (unsigned int b = 0; b < 4; b++)
//		{
//			vertex.m_BoneIndex[b] = -1;
//			vertex.m_BoneName[b] = "";
//			vertex.m_BoneWeight[b] = 0.0f;
//		}
//
//		vertices.push_back(vertex);
//	}
//
//	//ボーンデータ初期化（メッシュの中に何個のボーンが存在するか）
//	for (unsigned int b = 0; b < mesh->mNumBones; b++)
//	{
//		// メッシュに関連づいてるボーン情報を取得
//		aiBone* bone = mesh->mBones[b];
//
//		// ボーンオフセット行列を取得
//		g_Bone[bone->mName.C_Str()].OffsetMatrix = bone->mOffsetMatrix;
//
//		// ボーンに関連づいている頂点を選び､ウェイト値をセットする
//		for (unsigned int widx = 0; widx < bone->mNumWeights; widx++)
//		{
//			aiVertexWeight weight = bone->mWeights[widx];
//
//			unsigned int vidx = weight.mVertexId;	// このウエイトに関連づいてる頂点idx
//
//			// メッシュの中の何番目か
//			vertices[vidx].m_BoneWeight[vertices[vidx].m_BoneNum] = weight.mWeight;
//			vertices[vidx].m_BoneName[vertices[vidx].m_BoneNum] = bone->mName.C_Str();
//			// 該当するボーン名のインデックス値をセット
//			vertices[vidx].m_BoneIndex[vertices[vidx].m_BoneNum] = g_Bone[bone->mName.C_Str()].idx;
//
//			vertices[vidx].m_BoneNum++;
//
//			assert(vertices[vidx].m_BoneNum <= 4);
//		}
//	}
//
//	g_MeshVertex[mesh->mName.C_Str()] = vertices;
//
//	return;
//}
//
//void processNode(aiNode* node, const aiScene* scene, int depth)
//{
//	// インデント
//	for (int i = 0; i < depth; i++) {
//		printf(" ");
//	}
//
//	// utf8をシフトＪＩＳに変換
//	std::string nodename = utf8_to_multi_winapi(std::string(node->mName.C_Str()));
//	printf("%s \n", nodename.c_str());
//
//	// ノード内のメッシュの数分ループする
//	for (unsigned int i = 0; i < node->mNumMeshes; i++)
//	{
//		int meshindex = node->mMeshes[i];			// ノードのi番目メッシュのインデックスを取得
//		aiMesh* mesh = scene->mMeshes[meshindex];	// シーンからメッシュ本体を取り出す
//
//		processMesh(mesh, scene, meshindex);
//	}
//
//	for (unsigned int i = 0; i < node->mNumChildren; i++)
//	{
//		processNode(node->mChildren[i], scene, depth + 1);
//	}
//}
//
//
//void CreateBone(aiNode* node)
//{
//	BONE bone;
//
//	// ノード名をキーにしてボーン情報を保存
//	g_Bone[node->mName.C_Str()] = bone;
//
//	for (unsigned int n = 0; n < node->mNumChildren; n++)
//	{
//		CreateBone(node->mChildren[n]);
//	}
//}
//
//int eee() {
//
//	Assimp::Importer importer;
//	std::string filename("HAL/halchan2.pmx");
//
//	const aiScene* pScene = importer.ReadFile(filename,
//		aiProcess_ConvertToLeftHanded |
//		aiProcessPreset_TargetRealtime_MaxQuality);
//
//	if (pScene == nullptr) {
//		printf("load halchan2.pmx error \n");
//		return false;
//	}
//
//	printf("load halchan2.pmx success \n");
//
//	// 空のボーンを生成する
//	CreateBone(pScene->mRootNode);
//
//	// ボーンの配列位置を格納する
//	unsigned int num = 0;
//	for (auto& data : g_Bone) {
//		data.second.idx = num;
//		num++;
//	}
//
//
//	// aiノードを再帰的に解析
//	processNode(pScene->mRootNode, pScene, 0);
//
//	// ボーン情報表示
//	printf("\n＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊\n");
//	printf("＊         ボーン情報         ＊\n");
//	printf("＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊\n");
//
//	for (auto& b : g_Bone) {
//		// utf8をシフトＪＩＳに変換
//		std::string nodename = utf8_to_multi_winapi(std::string(b.first.c_str()));
//		printf("\nボーン名: %s\n", nodename.c_str());
//		printf("  オフセット行列：%f %f %f\n",
//			b.second.OffsetMatrix.a4,
//			b.second.OffsetMatrix.b4,
//			b.second.OffsetMatrix.c4);
//	}
//
//
//	// 頂点情報表示
//	printf("\n＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊\n");
//	printf("＊         頂点情報         ＊\n");
//	printf("＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊\n");
//
//	for (auto& mv : g_MeshVertex) {
//		// utf8をシフトＪＩＳに変換
//		std::string meshname = utf8_to_multi_winapi(std::string(mv.first.c_str()));
//		printf("\nメッシュ名: %s\n", meshname.c_str());
//
//		for (auto& v : mv.second) {
//			// utf8をシフトＪＩＳに変換
//			std::string bid = utf8_to_multi_winapi(std::string(v.m_BoneName[0].c_str()));
//			printf("  ボーンID(0)：%s %s %f\n",
//				meshname.c_str(),
//				bid.c_str(), v.m_BoneWeight[0]);
//
//			bid = utf8_to_multi_winapi(std::string(v.m_BoneName[0].c_str()));
//			printf("  ボーンID(1)：%s %s %f\n",
//				meshname.c_str(),
//				bid.c_str(), v.m_BoneWeight[1]);
//
//			bid = utf8_to_multi_winapi(std::string(v.m_BoneName[0].c_str()));
//			printf("  ボーンID(2)：%s %s %f\n",
//				meshname.c_str(),
//				bid.c_str(), v.m_BoneWeight[2]);
//
//			bid = utf8_to_multi_winapi(std::string(v.m_BoneName[0].c_str()));
//			printf("  ボーンID(3)：%s %s %f\n\n",
//				meshname.c_str(),
//				bid.c_str(), v.m_BoneWeight[3]);
//
//		}
//	}
//
//	// 解放処理
//	aiReleaseImport(pScene);
//
//	int s = getchar();
//
//	return true;
//}