#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "book.h"

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

    cout << fixed << setprecision(2);

    OrderBook book;
    string line;
    int number = 0;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        stringstream ss(line);
        string command;
        ss >> command;

        if (command == "PRINT") {
            printBook(book);
        } else if (command == "CANCEL") {
            string id;
            ss >> id;
            if (cancelOrder(book, id)) {
                cout << "CANCELED " << id << endl;
            } else {
                cout << "NOT FOUND " << id << endl;
            }
        } else if (command == "BUY" || command == "SELL") {
            Order order;
            order.side = command;
            ss >> order.type;
            if (order.type == "LIMIT") {
                ss >> order.price;
            } else {
                order.price = 0;
            }
            ss >> order.quantity >> order.id;
            number++;
            order.number = number;
            addOrder(book, order);
        } else {
            cout << "Unknown command: " << line << endl;
        }
    }
    file.close();

    printBook(book);
    cout << "Total trades: " << book.trades.size() << endl;

    return 0;
}
