#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "order.h"

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

    vector<Order> orders;
    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        stringstream ss(line);
        string command;
        ss >> command;

        if (command == "BUY" || command == "SELL") {
            Order order;
            order.side = command;
            ss >> order.type;
            if (order.type == "LIMIT") {
                ss >> order.price;
            } else {
                order.price = 0;
            }
            ss >> order.quantity >> order.id;
            orders.push_back(order);
        } else {
            cout << "Unknown command: " << line << endl;
        }
    }
    file.close();

    for (int i = 0; i < orders.size(); i++) {
        Order o = orders[i];
        cout << o.id << " " << o.side << " " << o.type << " " << o.price << " " << o.quantity << endl;
    }

    return 0;
}
