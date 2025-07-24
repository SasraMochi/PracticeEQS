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

	static int GROUND_FIELD;
	static int HOLE_FIELD;
};