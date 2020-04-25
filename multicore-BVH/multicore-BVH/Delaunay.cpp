#include "Delaunay.h"
bool Delaunay::is_circum(tri cur, int i, vector<vect>& point) {
	double ccw = (point[cur.b] - point[cur.a]).cross(point[cur.c] - point[cur.a]);

	double adx = point[cur.a].x - point[i].x, ady = point[cur.a].y - point[i].y,
		bdx = point[cur.b].x - point[i].x, bdy = point[cur.b].y - point[i].y,
		cdx = point[cur.c].x - point[i].x, cdy = point[cur.c].y - point[i].y,
		bdxcdy = bdx * cdy, cdxbdy = cdx * bdy,
		cdxady = cdx * ady, adxcdy = adx * cdy,
		adxbdy = adx * bdy, bdxady = bdx * ady,
		alift = adx * adx + ady * ady,
		blift = bdx * bdx + bdy * bdy,
		clift = cdx * cdx + cdy * cdy;
	double det = alift * (bdxcdy - cdxbdy)
		+ blift * (cdxady - adxcdy)
		+ clift * (adxbdy - bdxady);

	if (ccw > 0) return det >= 0;
	else return det <= 0;
}
int Delaunay::execute() {
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "w", stdout);

	int n;
	scanf("%d", n);
	vector<vect> point(n + 3);
	for (int i = 0; i < n; i++)
	{
		double x, y;
		scanf("%lf %lf", &x, &y);
		point[i] = vect(x, y);
	}

	point[n] = vect(-2e9, -2e9);
	point[n + 1] = vect(2e9, -2e9);
	point[n + 2] = vect(0, 2e9);
	vector<tri> triangle;
	triangle.push_back(tri(n, n + 1, n + 2));

	for (int i = 0; i < n; i++) {
		set<edg> polygon;
		vector<int> complete(triangle.size(), 0);
		for (int j = 0; j < triangle.size(); j++) {
			if (complete[j]) continue;
			tri cur = triangle[j];
			if (is_circum(cur, i, point)) {
				if (polygon.count(edg(cur.a, cur.b))) polygon.erase(edg(cur.a, cur.b));
				else polygon.insert(edg(cur.a, cur.b));
				if (polygon.count(edg(cur.b, cur.c))) polygon.erase(edg(cur.b, cur.c));
				else polygon.insert(edg(cur.a, cur.b));
				if (polygon.count(edg(cur.c, cur.a))) polygon.erase(edg(cur.c, cur.a));
				else polygon.insert(edg(cur.c, cur.a));

				swap(complete[j], complete[triangle.size() - 1]);
				swap(triangle[j], triangle[triangle.size() - 1]);
				triangle.pop_back();
				j--;
				continue;
			}
			complete[j] = true;
		}
		for (auto& cur : polygon) {
			if ((point[cur.b] - point[cur.a]).cross(point[i] - point[cur.a]) == 0) continue;
			triangle.push_back(tri(cur.a, cur.b, i));
		}
	}

	for (int i = 0; i < triangle.size(); i++) {
		tri cur = triangle[i];
		if (cur.a >= n || cur.b >= n || cur.c >= n) {
			swap(triangle[i], triangle[triangle.size() - 1]);
			triangle.pop_back();
			i--;
			continue;
		}
	}

	printf("%d\n", triangle.size());
	for (int i = 0; i < triangle.size(); i++) {
		tri cur = triangle[i];
		printf("%d %d %d %d %d %d\n", point[cur.a].x, point[cur.a].y, point[cur.b].x, point[cur.c].x, point[cur.c].y);
	}
	return 0;
}