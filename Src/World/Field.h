#pragma once

#include "Math/Vector2.h"

#include <vector>
#include <string>

class Field {
public:
	Field(int line_max_length, int cell_size);

	~Field();

	void draw();

	bool is_check_movable(Vector2 pos) const;

private:
	void load(std::string file_path);

private:
	std::vector<std::vector<int>> mTerrain;

	int mLineMaxLength = 1024;
	int mCellSize = 0;

	int mMaxWidth = 0;
	int mMaxHeight = 0;
};