#pragma once
#include "Object.h"
using namespace std;
class Delaunay
{
public:
	bool is_circum(tri cur, int i, vector<vect>& point);
	int execute();
};
struct vect {
	int x;
	int y;
	vect() { x = y = 0; }
	vect(double x, double y) {
		this->x = x;
		this->y = y;
	}

	const double dist() const {
		return(x * x + y * y);
	}
	const double inner(const vect& a) const {
		return x * a.y - y * a.x;
	}
	const double cross(const vect& a) const {
		return x * a.y - y * a.x;
	}
	const vect operator+ (const vect& a)const {
		return vect(x + a.x, y + a.y);
	}
	const vect operator- (const vect& a) const {
		return vect(x - a.x, y - a.y);
	}
	const vect operator* (const double& a) const {
		return vect(a * x, a * y);
	}
	const vect proj(const vect& a) const {
		return *this * (inner(*this) / inner(a));
	}
	const double get_cos(const vect& a) const {
		return inner(a) / (dist() * a.dist());
	}
};

struct edg {
	int a;
	int b;
	edg() { a = b = 0; }
	edg(int a, int b) {
		if (a < b) {
			this->a = a;
			this->b = b;
		}
		else {
			this->a = b;
		}
	}
	const bool operator == (const edg& x) const {
		return a == x.a && b == x.b;
	}
	const bool operator < (const edg& x) const {
		if (a == x.a) return b < x.b;
		return a < x.a;
	}
};

struct tri {
	int a;
	int b;
	int c;
	tri() {
		a = b = c = 0;
	}
	tri(int a, int b, int c) {
		this->a = a;
		this->b = b;
		this->c = c;

	}
};

