/* Guillaume Lagrange
 * Trash removal
 * https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3139
 */
#include <iostream>
#include <algorithm>

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

/* Graham scan */



int main() {

    while(true) {
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

        /* Sorting the vertices for Graham scan */
        comparator cmp(polygon[0]);
        sort(polygon.begin() + 1, polygon.end(), cmp);
    }

    return 0;
};
