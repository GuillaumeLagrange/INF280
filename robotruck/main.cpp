#include <iostream>
#include <algorithm>

using namespace std;

void calculateMinDistance(int * xPackage, int * yPackage,
        int * wPackage, int * minDistances, int i);

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
            calculateMinDistance(xPackage, yPackage, wPackage, minDistances, i);

        cout << minDistances[n-1] << endl;
        if (serial != c-1)
            cout << endl;
    }

    return 0;
};

void calculateMinDistance(int * xPackage, int * yPackage,
        int * wPackage, int * minDistances, int i)
{
    int totalWeight = wPackage[i];
}
