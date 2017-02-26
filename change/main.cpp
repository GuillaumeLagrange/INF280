#include <iostream>
#include <algorithm>

using namespace std;

bool test(int i, int j, int k, int l, int m, int amount, int * values);

int main() {
    int samples;
    int amount;
    int k;
    cin >> samples;

    while (samples != 0) {
        samples --;

        int values[5] = {1,0,0,0,0};

        cin >> amount;
        cin >> k;

        for (int i = 0; i < 5; i++)
            if(i < k)
                cin >> values[i];

        int maxNumber = amount / values[0] + 1;

        for (int i = 0; i <= maxNumber; i++)
            for (int j = i; j >= 0; j--)
                for (int k = j; k >= 0; k--)
                        for (int l = k; l >= 0; l--)
                            for (int m = l; m >= 0; m--)
                                if (test(i,j,k,l,m,amount,values)) {
                                    cout << "YES" << endl;
                                    goto end;
                                }
    cout << "NO" << endl;

    end :
        if (samples!= 0)
            cout << endl;
    }

    return 0;
};


bool test(int i, int j, int k, int l, int m, int amount, int* values) {
    int testValue = i * values[0] +
                    j * values[1] +
                    k * values[2] +
                    l * values[3] +
                    m * values[4];

    return testValue == amount;
}
