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

        bool LUL = computeRepartition(500, booksPages);
        cout << LUL << endl;
    }

    return 0;
};

bool computeRepartition(int k, long * booksPages) {
    scribersRepartition = new int[scribers];
    int currScriber = scribers - 1; // We start from the end
    int currBook = 0;

    while(true) {
        int total = 0;
        bool scriberDone = false;
        while(!scriberDone) {
            if (total + booksPages[currBook] >= k) {
                total += booksPages[currBook++];
                if (currBook == books)
                    return true;
            } else {
                scriberDone = true;
                scribersRepartition[currScriber] = currBook;
            }
        }
        currScriber --;
        if (currScriber == 0)
            return false;
    }
}
