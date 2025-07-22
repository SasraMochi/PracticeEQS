#include "Image.h"

int Image::GRASS_FIELD{ -1 };
int Image::WALL_FIELD{ -1 };
int Image::WATER_FIELD{ -1 };

void Image::Load() {
	GRASS_FIELD = LoadGraph("Assets/Sprite/Field/Grass_Field.bmp");
	assert(GRASS_FIELD != -1);	//‰æ‘œ“Ç‚İ‚İ¸”s

	WALL_FIELD = LoadGraph("Assets/Sprite/Field/Wall_Field.bmp");
	assert(WALL_FIELD != -1);	//‰æ‘œ“Ç‚İ‚İ¸”s

	WATER_FIELD = LoadGraph("Assets/Sprite/Field/Water_Field.bmp");
	assert(WATER_FIELD != -1);	//‰æ‘œ“Ç‚İ‚İ¸”s
}