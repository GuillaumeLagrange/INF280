#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<int, int[2]> line;
int firstMember, lastMember;

void handleEmergency(int emergency);

int main() {
    int p;
    int c;
    int serial = 0;
    char command;
    int emergency;

    while (serial < 10) {
        cin >> p;
        cin >> c;

        if (p == 0)
            return 0;

        serial ++;
        cout << "Case " << serial << ":" << endl;

        firstMember = 1;
        lastMember = min(p, c);

        line[firstMember][0] = lastMember;
        line[firstMember][1] = firstMember + 1;
        line[lastMember][0] = lastMember - 1;
        line[lastMember][1] = firstMember;

        for(int i = 2; i < min(p, c); i++) {
                line[i][0] = i - 1;
                line[i][1] = i + 1;
        }

        for (int i = 0; i < c; i++) {
            cin >> command;
            if (command == 'N') {
                cout << firstMember << endl;
                lastMember = firstMember;
                firstMember = line[firstMember][1];
            } else {
                cin >> emergency;
                handleEmergency(emergency);
            }
        }
    }
};

void handleEmergency(int emergency) {
    if (emergency == firstMember)
        return;
    else if (emergency == lastMember) {
        firstMember = lastMember;
        lastMember = line[lastMember][0];
    } else {
        int previousEmergency = line[emergency][0];
        int nextEmergency = line[emergency][1];

        line[previousEmergency][1] = line[emergency][1];
        line[nextEmergency][0] = line[emergency][0];
        line[lastMember][1] = emergency;
        line[firstMember][0] = emergency;
        line[emergency][0] = lastMember;
        line[emergency][1] = firstMember;

        firstMember = emergency;
    }
}
