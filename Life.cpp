#include "Life.h"

Life::Life(unsigned int xSize, unsigned int ySize) :
	size_width(xSize),
	size_height(ySize)
{
	initArr(arr);
}

Life::~Life()
{
	delArr(arr);
}

void Life::step()
{
	bool** newArr = 0;
	initArr(newArr);

	for (int x = 0; x < size_width; x++)
	{
		for (int y = 0; y < size_height; y++)
		{
			int CA = countAround(x, y);
			if (CA < 2 || CA > 3)
				newArr[x][y] = false;
			else if (CA == 2)
				newArr[x][y] = arr[x][y];
			else if (CA == 3)
				newArr[x][y] = true;
		}
	}

	delArr(arr);
	arr = newArr;
}

void Life::initArr(bool**& pArr)
{
	pArr = new bool*[size_width];
	for (int i = 0; i < size_width; i++)
		pArr[i] = new bool[size_height];

	for (int x = 0; x < size_width; x++)
		for (int y = 0; y < size_height; y++)
			pArr[x][y] = false;
}

void Life::delArr(bool**& pArr)
{
	for (int i = 0; i < size_width; i++)
		delete[] pArr[i];
	delete[] pArr;

	pArr = 0;
}

unsigned int Life::countAround(unsigned int x, unsigned int y)
{
	if (x < 0 || x >= size_width || y < 0 || y >= size_height)
		return 0;
	int counterAround = 0;
	int variantsAround[8][2] = {
		{ -1, -1 },
		{ 0, -1 },
		{ 1, -1 },
		{ -1, 0 },
		{ 1, 0 },
		{ -1, 1 },
		{ 0, 1 },
		{ 1, 1 } };
	for (int i = 0; i < 8; i++)
	{
		if (x + variantsAround[i][0] < 0 || x + variantsAround[i][0] >= size_width ||
			y + variantsAround[i][1] < 0 || y + variantsAround[i][1] >= size_height)
			continue;
		if (arr[x + variantsAround[i][0]][y + variantsAround[i][1]])
			counterAround++;
	}
	return counterAround;
}