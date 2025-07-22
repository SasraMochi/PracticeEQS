#include "Field.h"

#include "DxLib.h"
#include "Image.h"

#include <fstream>
#include <sstream>
#include <assert.h>

Field::Field(int line_max_length, int cell_size)
	: mLineMaxLength{ line_max_length }
	, mCellSize{ cell_size }
{
	std::string file_path = "C:/C++/Practice_EQS/Assets/Map/map.csv";
	load(file_path);
}

Field::~Field()
{
}

void Field::draw()
{
	for (int x = 0; x < mMaxWidth; ++x)
	{
		for (int y = 0; y < mMaxHeight; ++y)
		{
			int handle = -1;

			switch (mTerrain[y][x])
			{
			case 0:
				handle = Image::GRASS_FIELD;
				break;
			case 1:
				handle = Image::WALL_FIELD;
				break;
			case 2:
				handle = Image::WATER_FIELD;
				break;
			}

			assert(handle != -1);

			DrawGraph(x * mCellSize, y * mCellSize, handle, false);
		}
	}
}

void Field::load(std::string file_path)
{
	// csv�t�@�C�����J��
	std::ifstream ifs_csv_file(file_path);
	if (!ifs_csv_file.is_open())
	{
		assert(!"csv�t�@�C�����ǂݍ��߂܂���B");
	}

	// 1�s�����i�[����ϐ�
	std::string line;

	mMaxWidth = 0;
	mMaxHeight = 0;

	// 1�s���ǂݍ���
	while (std::getline(ifs_csv_file, line))
	{
		std::istringstream linestream(line);
		std::string cell;
		std::vector<int> row;
		int width = 0;

		// �ǂݍ��񂾍s��1��������int�^�ɕϊ�����vector�Ɋi�[����
		while (std::getline(linestream, cell, ','))
		{
			int num = std::stoi(cell);
			row.push_back(num);
			width++;
		}

		if (width > mMaxWidth) mMaxWidth = width;
		if (!row.empty()) mTerrain.push_back(row);
		mMaxHeight++;
	}
}
