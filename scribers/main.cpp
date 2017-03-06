#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> scribersRepartition;
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

        int minDich = 0;
        int maxDich = 0;
        for (int j = 0; j < books; j++)
            maxDich += booksPages[j];
        while((maxDich- minDich ) > 1)
            if (computeRepartition((minDich + maxDich)/2, booksPages))
                maxDich = (minDich + maxDich)/2;
            else
                minDich = (minDich + maxDich)/2;

        //for (int j = 0; j < scribers; j++)
            //cout << scribersRepartition[j] << endl;
        //cout << endl << endl;
        for (int j = 0; j < scribers - 1; j++) {
            for (int k = scribersRepartition[j]; k < scribersRepartition[j+1]; k++)
                cout << booksPages[k] << " ";
            cout << "/ ";
        }
        for (int k = scribersRepartition[scribers - 1]; k < books; k++) {
            cout << booksPages[k];
            if (k != books - 1)
                cout << " ";
        }
        cout << endl;
    }

    return 0;
};

bool computeRepartition(int k, long * booksPages) {
    scribersRepartition.clear();
    scribersRepartition = vector<int>(scribers);
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
