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
				handle = Image::GROUND_FIELD;
				break;
			case 1:
				handle = Image::HOLE_FIELD;
				break;
			}

			assert(handle != -1);

			Vector2 draw_pos(x * mCellSize, y * mCellSize);

			DrawGraph(draw_pos.x, draw_pos.y, handle, false);
		}
	}
}

bool Field::is_check_movable(Vector2 pos) const
{
	auto point = pos / mCellSize;

	// もし指定した座標が壁ならばfalseを返す
	if (mTerrain[point.y][point.x] == 1)
	{
		return false;
	}

	return true;
}

void Field::load(std::string file_path)
{
	// csvファイルを開く
	std::ifstream ifs_csv_file(file_path);
	if (!ifs_csv_file.is_open())
	{
		assert(!"csvファイルが読み込めません。");
	}

	// 1行分を格納する変数
	std::string line;

	mMaxWidth = 0;
	mMaxHeight = 0;

	// 1行ずつ読み込む
	while (std::getline(ifs_csv_file, line))
	{
		std::istringstream linestream(line);
		std::string cell;
		std::vector<int> row;
		int width = 0;

		// 読み込んだ行を1文字ずつint型に変換してvectorに格納する
		while (std::getline(linestream, cell, ','))
		{
			int num = std::stoi(cell);
			row.push_back(num);
			width++;
		}

		if (width > mMaxWidth)
		{
			mMaxWidth = width;
		}

		if (!row.empty())
		{
			mTerrain.push_back(row);
		}

		mMaxHeight++;
	}
}
