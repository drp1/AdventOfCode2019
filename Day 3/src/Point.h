
#ifndef _Point_h_
#define _Point_h_

class Point
{
public:
	Point(int x, int y);
	bool operator==(Point const& other) const;
	int GetX() const;
	int GetY() const;
private:
	int x, y;
};


#endif