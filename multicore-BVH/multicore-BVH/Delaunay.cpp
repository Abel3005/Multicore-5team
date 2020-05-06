#include "Delaunay.h"
bool is_circum(tri cur, int i, vector<vect>& point) { // 외접원안에 점이 들어오는지 확인
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
    freopen("input.txt", "rt", stdin); // input.txt 를 불러와서
    freopen("output.txt", "w", stdout); // output.txt 로 triangluation 된 값을 내보낸다.
    int n;
    scanf("%d", &n);
    vector<vect> point(n + 3); // super triangle 을 만들기 위하여 3만큼 더 크게 잡는다.
    for (int i = 0; i < n; i++) {
        double x, y;
        scanf("%lf %lf", &x, &y);
        point[i] = vect(x, y);
    }

    // Super Triangle Phase
    point[n] = vect(-2e9, -2e9);
    point[n + 1] = vect(2e9, -2e9);
    point[n + 2] = vect(0, 2e9);
    vector<tri> triangle;
    triangle.push_back(tri(n, n + 1, n + 2));

    // Delaunay Triangluation
    // Time Complexity O(N^2 log N) << Polygon 구현 과정을 set으로 구현했다.
    for (int i = 0; i < n; i++) {
        set<edg> polygon;
        vector<int> complete(triangle.size(), 0);
        for (int j = 0; j < triangle.size(); j++) {
            if (complete[j]) continue;
            tri cur = triangle[j];
            if (is_circum(cur, i, point)) {
                if (polygon.count(edg(cur.a, cur.b))) polygon.erase(edg(cur.a, cur.b)); // 만약 겹치는 edge라면 제거
                else polygon.insert(edg(cur.a, cur.b)); // 안 겹치면 삽입
                if (polygon.count(edg(cur.b, cur.c))) polygon.erase(edg(cur.b, cur.c));
                else polygon.insert(edg(cur.b, cur.c));
                if (polygon.count(edg(cur.c, cur.a))) polygon.erase(edg(cur.c, cur.a));
                else polygon.insert(edg(cur.c, cur.a));

                swap(complete[j], complete[triangle.size() - 1]); // bad triangle 은 제거한다.
                swap(triangle[j], triangle[triangle.size() - 1]);
                triangle.pop_back();
                j--;
                continue;
            }
            complete[j] = true;
        }
        for (auto& cur : polygon) {
            if ((point[cur.b] - point[cur.a]).cross(point[i] - point[cur.a]) == 0) continue; // 일직선이므로 삼각형이 될 수 없다. 따라서 무시
            triangle.push_back(tri(cur.a, cur.b, i));
        }
    }

    // SuperTriangle delete
    for (int i = 0; i < triangle.size(); i++) {
        tri cur = triangle[i];
        if (cur.a >= n || cur.b >= n || cur.c >= n) { // n ~ n+2 의 정점을 사용하는 삼각형은 모두 처분한다.
            swap(triangle[i], triangle[triangle.size() - 1]);
            triangle.pop_back();
            i--;
            continue;
        }
    }

    printf("%d\n", triangle.size()); // triangle size 출력
    for (int i = 0; i < triangle.size(); i++) {
        tri cur = triangle[i];
        printf("%d %d %d %d %d %d\n", point[cur.a].x, point[cur.a].y, point[cur.b].x, point[cur.b].y, point[cur.c].x, point[cur.c].y); // 한줄에 삼각형 하나씩 출력한다. (소수점 6째자리 까지 허용)
    }

    return 0;
}