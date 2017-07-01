#pragma once
class Life
{
public:
	Life(unsigned int, unsigned int);
	~Life();

	bool getElem(unsigned int x, unsigned int y) const { return arr[x][y]; }
	void setElem(unsigned int x, unsigned int y, bool val) { arr[x][y] = val; }

	void step();

	const unsigned int size_width;
	const unsigned int size_height;
private:
	void initArr(bool**&);
	void delArr(bool**&);
	unsigned int countAround(unsigned int, unsigned int);

	bool** arr;
};