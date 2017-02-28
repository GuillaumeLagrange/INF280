#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

void calculateMinDistance(int * xPackage, int * yPackage,
        int * wPackage, int * minDistances, int i, int c);
int calculateRoundTrip(int minInd, int maxInd, int * xPackage, int * yPackage,
        int * minDistances);

int main() {
    int cases;
    cin >> cases;

    for(int serial = 0; serial < cases; serial++) {
        int c;
        cin >> c;
        int n;
        cin >> n;

        int xPackage[n];
        int yPackage[n];
        int wPackage[n];

        for (int i = 0; i < n; i ++) {
            cin >> xPackage[i];
            cin >> yPackage[i];
            cin >> wPackage[i];
        }

        /*
         *In this tab we'll hold the values of the minimal distances to deliver
         *i packages in minDistance[i]
         */
        int minDistances[n];

        for (int i = 0; i < n; i++)
            calculateMinDistance(xPackage, yPackage, wPackage, minDistances,
                    i, c);

        cout << minDistances[n-1] << endl;
        if (serial != cases-1)
            cout << endl;
    }

    return 0;
};

void calculateMinDistance(int * xPackage, int * yPackage,
        int * wPackage, int * minDistances, int i, int c)
{
    int totalWeight = wPackage[i];
    int j = i;
    int minDist = numeric_limits<int>::max();

    while ((j >= 0) && (totalWeight <= c)) {
        int dist = calculateRoundTrip(j, i, xPackage, yPackage, minDistances);
        minDist = min(dist, minDist);
        j --;
        if (j >= 0)
            totalWeight += wPackage[j];
    }

    minDistances[i] = minDist;
}

int calculateRoundTrip(int minInd, int maxInd, int * xPackage, int * yPackage,
        int * minDistances)
{
    int x = 0;
    int y = 0;
    int dist = 0;

    for (int i = minInd; i <= maxInd; i++) {
        dist += abs(xPackage[i] - x);
        dist += abs(yPackage[i] - y);

        x = xPackage[i];
        y = yPackage[i];
    }

    dist += x;
    dist += y;

    if (minInd == 0)
        return dist;
    else
        return minDistances[minInd - 1] + dist;
}
