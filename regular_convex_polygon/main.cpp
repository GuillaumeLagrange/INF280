#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <ctgmath>

#define EPS 0.000000001

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
};

Vec2d circumcenter(Vec2d a, Vec2d b, Vec2d c)
{
    Vec2d ac = Vec2d(a, c);
    Vec2d ab = Vec2d(a, b);
    Vec2d bc = Vec2d(b, c);

    double alpha = ac.unsigned_angle(ab);
    double beta  = bc.unsigned_angle(-ab);
    double gamma = ac.unsigned_angle(bc);

    double tana = tan(alpha);
    double tanb = tan(beta);
    double tanc = tan(gamma);

    Vec2d barycenter = (a * (tanb + tanc) +
                         b * (tanc + tana) +
                         c * (tana + tanb)) /
                         (2.f * (tana + tanb + tanc));

    return barycenter;
}

int main() {
    string i;
    cin >> i;
    cout << i << endl;
    double a = (double) atof(i.c_str());
    cout << a << endl;

    Vec2d u = Vec2d(1, 1);
    Vec2d v = Vec2d(2, 0);
    cout << u.dot(v)<< endl;
    cout << hypot(u.x, u.y) << endl;
    return 0;
};
