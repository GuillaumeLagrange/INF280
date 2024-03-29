/* Guillaume Lagrange
 * Trash removal
 * https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3139
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <cmath>

#define EPS 0.0000001

using namespace std;

/* Data structure for either a vector or a vertex */
struct Vec2d {
    double x, y;
    Vec2d() {
        x=0.0; y=0.0;
    }

    Vec2d(double in_x, double in_y): x(in_x), y(in_y) {}

    /* Creates the vector from point u to point v */
    Vec2d(Vec2d u, Vec2d v): x(v.x - u.x), y(v.y - u.y) {};

    inline bool operator == (Vec2d pt2) const {
        return (fabs(x - pt2.x) < EPS && (fabs(y - pt2.y) < EPS));
    }

    inline Vec2d operator -() const {
        return Vec2d(-this->x, -this->y);
    }

    inline Vec2d operator*(double d) const {
        return Vec2d(this->x * d, this->y * d);
    }

    inline Vec2d operator/(double d) const {
        return Vec2d(this->x / d, this->y / d);
    }

    inline Vec2d operator+(Vec2d v) const {
        return Vec2d(this->x + v.x, this->y + v.y);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec2d &v)  {
        // write obj to stream
        os << "x : " << v.x << "  y : " << v.y;
        return os;
    }

    inline double dot(Vec2d v) const {
        return this->x*v.x + this->y*v.y;
    }

    inline double vect(Vec2d v) const {
        return this->x*v.y - this->y*v.x;
    }

    inline double norm() const {
        return hypot(this->x, this->y);
    }

    inline double unsigned_angle(Vec2d v) const {
        return acos(this->dot(v)/(this->norm()*v.norm()));
    }

    inline double ox_angle() const {
        return atan2(this->y, this->x);
    }
};

/* Struct use to sort the polygon vertices with their angle */
struct comparator {
    Vec2d origin;
    comparator(Vec2d org) : origin(org) {};
    /* Returns true if the angle (origin_u, origin_v) is positive */
    bool operator() (Vec2d u, Vec2d v) {
        Vec2d origin_u = Vec2d(origin, u);
        Vec2d origin_v = Vec2d(origin, v);
        return (origin_v.ox_angle() - origin_u.ox_angle()) > 0;
    }
};

/* Returns true if there is a left turn between p and the last two points
 * in hull
 */
bool right_turn(vector<Vec2d> &hull, Vec2d &p) {
    Vec2d u = Vec2d(hull[hull.size() - 2], hull[hull.size() -1]);
    Vec2d v = Vec2d(hull[hull.size() - 1], p);

    return u.vect(v) < 0;
}

/* Graham scan, returns the convex hull of the polygon */
vector<Vec2d> graham(vector<Vec2d> &polygon) {

    /* Sorting the vertices*/
    comparator cmp(polygon[0]);
    sort(polygon.begin() + 1, polygon.end(), cmp);

    vector<Vec2d> hull;
    hull.push_back(polygon[0]);
    hull.push_back(polygon[1]);

    for (unsigned int i=2; i<polygon.size(); i++) {
        while(right_turn(hull, polygon[i]))
            hull.pop_back();
        hull.push_back(polygon[i]);
    }

    return hull;
}


int main() {
    int serial = 0;

    while(true) {
        serial++;
        int n;
        if (scanf("%d", &n) != 1)
            return -1;
        if(n == 0)
            break;

        /* Registering polygon */
        vector<Vec2d> polygon;
        for(int i=0; i<n; i++) {
            int x,y;
            if (scanf("%d %d", &x, &y) != 2)
                return -1;
            polygon.push_back(Vec2d((double) x, (double) y));
        }

        vector<Vec2d> hull = graham(polygon);

        /* Leaning hull agaisnt a wall, calculating distance of the other wall */
        double min_max = numeric_limits<double>::max();
        for(unsigned int i=0; i< hull.size(); i++) {
            Vec2d base = Vec2d(hull[i], hull[(i+1)%hull.size()]);
            double current_max = 0;
            for(auto point : hull) {
                Vec2d u = Vec2d(hull[i], point);
                double dist = fabs(u.vect(base)) / base.norm();
                if (dist > current_max)
                    current_max = dist;
            }
            if (current_max <= min_max)
                min_max = current_max;
        }

        /* Rounding the result */
        float rounded_result = round(min_max * 100)/100;
        printf("Case %d: %.2f\n", serial, rounded_result);
    }

    return 0;
};
