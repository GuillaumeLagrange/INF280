#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>
#include <cmath>

using namespace std;

int computeVolumes(int * order, float * xPoints, float * yPoints,
        float * zPoints, float * box, int n, float * radius);

int main() {
    int n;
    float xPoints[6];
    float yPoints[6];
    float zPoints[6];
    float firstCorner[3];
    float secondCorner[3];
    int serial = 0;

    while(true) {
        cin >> n;

        if (n == 0)
            return 0;

        serial ++;
        float radius[n];

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
        float minX = min(firstCorner[0], secondCorner[0]);
        float minY = min(firstCorner[1], secondCorner[1]);
        float minZ = min(firstCorner[2], secondCorner[2]);

        firstCorner[0] -= minX;
        firstCorner[1] -= minY;
        firstCorner[2] -= minZ;

        secondCorner[0] -= minX;
        secondCorner[1] -= minY;
        secondCorner[2] -= minZ;

        float box[3];
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

int computeVolumes(int * order, float * xPoints, float * yPoints,
        float * zPoints, float * box, int n, float * radius)
{
    vector<float>radiuses;
    /* Remise de radius à 0 */
    for (int i = 0; i < n; i ++)
        radius[i] = 0.f;

    for (int i = 0; i < n; i++) {
        int j = order[i];
        float minDistRadius = numeric_limits<float>::max();
        for (int k = 0; k < n; k++) {
            if (k != j) {
                float dist = sqrt(pow(xPoints[j] - xPoints[k], 2) +
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
    float volumeBallons = 0.f;
    for(int i = 0; i < n; i++) {
        volumeBallons += 4.f/3.f * M_PI * pow(radius[i], 3);
    }

    float volume = box[0] * box[0] * box[0] - volumeBallons;

    return round(volume);
}
