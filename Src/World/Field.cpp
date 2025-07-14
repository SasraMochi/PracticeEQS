#include "Field.h"

#include "DxLib.h"

Field::Field(int line_max_length, int cell_size)
	:mLineMaxLength{ line_max_length }
	, mCellSize{ cell_size }
{

}

Field::~Field()
{
}

void Field::draw()
{
#if 0
	// �c���`��
	for (int i = 0; i < mLineMaxLength; i += mCellSize) {
		DrawLine(i, 0, i, mLineMaxLength, GetColor(255, 255, 255));
	}

	// �����`��
	for (int j = 0; j < mLineMaxLength; j += mCellSize) {

		DrawLine(0, j, mLineMaxLength, j, GetColor(255, 255, 255));
	}
#endif
}
