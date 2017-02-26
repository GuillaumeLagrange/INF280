#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    while(true) {
        int nx, ny;
        float w;

        cin >> nx;
        cin >> ny;
        cin >> w;

        if (nx <= 0 && ny <= 0)
            return 0;

        vector<float> start_length(0);

        for (int i = 0; i < nx; i++){
            float val;
            cin >> val;
            start_length.push_back(val);
        }

        vector<float> start_width(0);

        for (int i = 0; i < ny; i++){
            float val;
            cin >> val;
            start_width.push_back(val);
        }

        sort(start_length.begin(), start_length.end());

        bool mowed_length = true;
        float bottom = 0.f;

        for (auto s : start_length){
            if (s - w/2 > bottom){
                mowed_length = false;
                break;
            }
            bottom = s + w/2;
        }

        mowed_length &= bottom >= 75.f;

        sort(start_width.begin(), start_width.end());

        bool mowed_width = true;
        float left = 0.f;

        for (auto s : start_width){
            if (s - w/2 > left){
                mowed_width = false;
                break;
            }
            left = s + w/2;
        }

        mowed_width &= left >= 100.f;

        if (mowed_length && mowed_width)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
};
