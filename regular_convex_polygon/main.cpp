#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <ctgmath>

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
    while (true) {
        Vec2d points[3];

        /* Get points from input */
        for(int i=0; i<3; i++) {
            string str1, str2;
            cin >> str1 >> str2;
            if (str1 == "END")
                return 0;
            double x = (double) atof(str1.c_str());
            double y = (double) atof(str2.c_str());
            points[i] = Vec2d(x,y);
        }

        /* Get angles at the center of the circumscribed circle */
        Vec2d g = circumcenter(points[0], points[1], points[2]);
        double angles[3];
        for(int i=0; i<3; i++) {
            Vec2d a = Vec2d(g, points[(i+1)%3]);
            Vec2d b = Vec2d(g, points[(i+2)%3]);
            angles[i] = a.unsigned_angle(b);
        }

        /* Find the smallest angle and putting it first */
        for(int i=1; i<3; i++) {
            if (angles[0] < angles[i]) {
                double tmp = angles[0];
                angles[0] = angles[i];
                angles[i] = tmp;
            }
        }

        /* Find the biggest angle that divides all three angles */
        int result = - 1;
        for (int i=1; i<= 1000; i++) {
            double current_angle = angles[0] / i;
            double rem1 = fmod(angles[1], current_angle);
            if(fabs(rem1) < EPS || fabs(current_angle - rem1) < EPS) {
                double rem2 = fmod(angles[2], current_angle);
                if(fabs(rem2) < EPS || fabs(current_angle - rem2) < EPS) {
                    result = i;
                    break;
                }
            }
        }

        double angle = angles[0]/result;
        double d = 2*M_PI/angle;
        d += 0.5;
        int n = (int) d;
        cout << n << endl;
    }

    return -1;
};
