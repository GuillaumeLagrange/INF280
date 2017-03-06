#include <iostream>
#include <algorithm>

using namespace std;

int * scribersRepartition;
int scribers;
int books;

bool computeRepartition(int k, long * books);

int main() {
    int serial;
    cin >> serial;

    for (int i = 0; i < serial; i++) {
        cin >> books;
        cin >> scribers;

        long booksPages[books];

        for (int j = 0; j < books; j ++) {
            cin >> booksPages[j];
        }

        bool LUL = computeRepartition(1700, booksPages);
        cout << LUL << endl << endl;
        for (int j = 0; j < scribers; j++)
            cout << scribersRepartition[j] << endl;
        cout << endl << endl;
    }

    return 0;
};

bool computeRepartition(int k, long * booksPages) {
    scribersRepartition = new int[scribers];
    int currScriber = scribers - 1; // We start from the end
    int currBook = books - 1;

    while(true) {
        int total = 0;
        bool scriberDone = false;
        while(!scriberDone) {
            if (total + booksPages[currBook] <= k) {
                total += booksPages[currBook--];
                if (currBook == -1)
                    return true;
                else if (currBook == currScriber)
                    goto finish;
            } else {
                scriberDone = true;
                scribersRepartition[currScriber] = currBook + 1;
            }
        }
        currScriber --;
        if (currScriber == -1)
            return false;
    }

    /* At least one book must be assigned to each scriber */
finish:
    while(currBook >= 0) {
        scribersRepartition[currBook] = currBook;
        currBook --;
    }
    return true;
}
