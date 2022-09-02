#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    string fileName = "orders.txt";
    if (argc > 1) {
        fileName = argv[1];
    }

    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Can't open file " << fileName << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        cout << line << endl;
    }
    file.close();

    return 0;
}
