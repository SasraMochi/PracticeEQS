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
	Image() {};	//�������R���X�g���N�^
	~Image() {};	//�j������f�X�g���N�^
	static void Load();

	static int GROUND_FIELD;
	static int HOLE_FIELD;
};