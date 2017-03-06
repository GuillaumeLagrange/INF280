#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>
#include <cmath>

using namespace std;

int computeVolumes(int * order, double * xPoints, double * yPoints,
        double * zPoints, double * box, int n, double * radius);

int main() {
    int n;
    double xPoints[6];
    double yPoints[6];
    double zPoints[6];
    double firstCorner[3];
    double secondCorner[3];
    int serial = 0;

    while(true) {
        cin >> n;

        if (n == 0)
            return 0;

        serial ++;
        double radius[n];

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
        double minX = min(firstCorner[0], secondCorner[0]);
        double minY = min(firstCorner[1], secondCorner[1]);
        double minZ = min(firstCorner[2], secondCorner[2]);

        firstCorner[0] -= minX;
        firstCorner[1] -= minY;
        firstCorner[2] -= minZ;

        secondCorner[0] -= minX;
        secondCorner[1] -= minY;
        secondCorner[2] -= minZ;

        double box[3];
        box[0] = max(firstCorner[0], secondCorner[0]);
        box[1] = max(firstCorner[1], secondCorner[1]);
        box[2] = max(firstCorner[2], secondCorner[2]);

        for (int i = 0; i < n; i++) {
            xPoints[i] -= minX;
            yPoints[i] -= minY;
            zPoints[i] -= minZ;
        }

        int minVolume = numeric_limits<int>::max();

        int order[] = {0,1,2,3,4};

        do {
            int volume = computeVolumes(order, xPoints, yPoints, zPoints, box,
                    n, radius);
            minVolume = min(minVolume, volume);
        } while (next_permutation(order, order + n));

        cout << "Box " << serial << ": " << minVolume << endl;
    }

    return -1;
};

int computeVolumes(int * order, double * xPoints, double * yPoints,
        double * zPoints, double * box, int n, double * radius)
{
    vector<double>radiuses;
    /* Remise de radius à 0 */
    for (int i = 0; i < n; i ++)
        radius[i] = 0.f;

    for (int i = 0; i < n; i++) {
        int j = order[i];
        double minDistRadius = numeric_limits<double>::max();
        for (int k = 0; k < n; k++) {
            if (k != j) {
                double dist = sqrt(pow(xPoints[j] - xPoints[k], 2) +
                                  pow(yPoints[j] - yPoints[k], 2) +
                                  pow(zPoints[j] - yPoints[k], 2));
                minDistRadius = min(minDistRadius, dist - radius[k]);
            }
        }
        radiuses.clear();
        radiuses.push_back(minDistRadius);
        radiuses.push_back(xPoints[j]);
        radiuses.push_back(yPoints[j]);
        radiuses.push_back(zPoints[j]);
        radiuses.push_back(box[0] - xPoints[j]);
        radiuses.push_back(box[1] - yPoints[j]);
        radiuses.push_back(box[2] - zPoints[j]);

        radius[j] = *min_element(radiuses.begin(), radiuses.end());
    }
    double volumeBallons = 0.f;
    for(int i = 0; i < n; i++) {
        volumeBallons += 4.f/3.f * M_PI * pow(radius[i], 3);
    }

    double volume = box[0] * box[0] * box[0] - volumeBallons;

    return round(volume);
}
