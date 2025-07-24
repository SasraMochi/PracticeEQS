#include "Image.h"

int Image::GROUND_FIELD{ -1 };
int Image::HOLE_FIELD{ -1 };

void Image::Load() {
	GROUND_FIELD = LoadGraph("Assets/Sprite/Field/Ground_Field.png");
	assert(GROUND_FIELD != -1);	//‰æ‘œ“Ç‚İ‚İ¸”s

	HOLE_FIELD = LoadGraph("Assets/Sprite/Field/Hole_Field.png");
	assert(HOLE_FIELD != -1);	//‰æ‘œ“Ç‚İ‚İ¸”s
}