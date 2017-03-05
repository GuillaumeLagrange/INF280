#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

int main() {
    int n;
    int xPoints[6];
    int yPoints[6];
    int zPoints[6];
    int firstCorner[3];
    int secondCorner[3];

    while(true) {
        cin >> n;

        if (n == 0)
            return 0;

        int radius[n];

        for (int i = 0; i < 3; i++) {
            cin >> firstCorner[i];
        }

        for (int i = 0; i < 3; i++) {
            cin >> secondCorner[i];
        }

        for (int i = 0; i < n; i++) {
           cin >> xPoints[i];
           cin >> yPoints[i];
           cin >> zPoints[i];
        }

        /* Changement de repère pour mettre un coin de la boite à 0,0,0) */
        int minX = min(firstCorner[0], secondCorner[0]);
        int minY = min(firstCorner[1], secondCorner[1]);
        int minZ = min(firstCorner[2], secondCorner[2]);

        firstCorner[0] -= minX;
        firstCorner[1] -= minY;
        firstCorner[2] -= minZ;

        secondCorner[0] -= minX;
        secondCorner[1] -= minY;
        secondCorner[2] -= minZ;

        int boxX = max(firstCorner[0], secondCorner[0]);
        int boxY = max(firstCorner[1], secondCorner[1]);
        int boxZ = max(firstCorner[2], secondCorner[2]);

        for (int i = 0; i < n; i++) {
            xPoints[i] -= minX;
            yPoints[i] -= minY;
            zPoints[i] -= minZ;
        }

        int minVolume = numeric_limits<int>::max();

    }

    return -1;
};
