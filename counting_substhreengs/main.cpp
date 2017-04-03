/* Guillaume Lagrange
 * Counting Subthreengs
 * https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&page=show_problem&problem=2960
 */

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

typedef unsigned long ulong;

/* This function looks for any substhreeng between left and right in str,
 * and adds the adequate number to counter
 */
void subthreengs(ulong& counter, ulong left, ulong right, string& str) {
    int remainders[3] = {0, 0, 0};

    for(ulong i=left; i <= right; i++) {
        int current = (str[i] - 48) % 3;

        if(current == 0)
            remainders[0] ++;
        else if(current == 1) {
            int tmp = remainders[2];
            remainders[2] = remainders[1];
            remainders[1] = ++remainders[0];
            remainders[0] = tmp;
        }
        else if(current == 2) {
            int tmp = remainders[0];
            remainders[0] = remainders[1];
            remainders[1] = remainders[2];
            remainders[2] = ++tmp;
        }

        counter += remainders[0];
    }
}

int main() {

    while(true) {
        string str;
        getline(cin, str);

        if (str.empty())
            break;

        ulong left = 0, right = 0, counter = 0;

        /* Looking for substrings composed entirely of digits */
        for(ulong i=0; i<str.size(); i++) {
            right = i;
            if (!(str[i] >= 48 && str[i] <= 57)) {
                if (right > left)
                    subthreengs(counter, left, right - 1, str);
                left = i+1;
            }
        }

        if (right >= left)
            subthreengs(counter, left, right, str);

        printf("%lu\n", counter);
    }

    return 0;
};
