#pragma once
#include <string>
#include <vector>
#include <iostream>

// オブジェクト名
enum class MODELID {
	PLAYER,
	SKYDOME,
	ENEMY,
	MISSILE,
	HOMING,
};

class CModelFile
{
public:

	struct ModelDataList
	{
		MODELID		id;
		std::string	modelname;
		std::string vsfilename;
		std::string psfilename;
		std::string texfolder;
	};

	std::vector<ModelDataList>	g_modellist = {
	{MODELID::PLAYER,"assets/model/Char/E2/e2_body.x"},
	};
	
public:
	CModelFile();
	

private:

};
