#ifndef MINI_EXCHANGE_ORDER_H
#define MINI_EXCHANGE_ORDER_H

#include <string>

using namespace std;

struct Order {
    string id;
    string side;   // BUY or SELL
    string type;   // LIMIT or MARKET
    double price;
    int quantity;
};

#endif
