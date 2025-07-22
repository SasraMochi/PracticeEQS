#pragma once

#include "DxLib.h"
#include <assert.h>

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>

class Image {
public:
	Image() {};	//初期化コンストラクタ
	~Image() {};	//破棄するデストラクタ
	static void Load();

	static int GRASS_FIELD;
	static int WALL_FIELD;
	static int WATER_FIELD;
};