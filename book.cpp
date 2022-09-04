#include "book.h"

#include <algorithm>
#include <iostream>

bool compareBids(Order a, Order b) {
    if (a.price != b.price) return a.price > b.price;
    return a.number < b.number;
}

bool compareAsks(Order a, Order b) {
    if (a.price != b.price) return a.price < b.price;
    return a.number < b.number;
}

void addOrder(OrderBook &book, Order order) {
    if (order.type == "MARKET") {
        cout << "Market orders are not supported yet" << endl;
        return;
    }

    if (order.side == "BUY") {
        book.bids.push_back(order);
        sort(book.bids.begin(), book.bids.end(), compareBids);
    } else {
        book.asks.push_back(order);
        sort(book.asks.begin(), book.asks.end(), compareAsks);
    }
}

void printBook(OrderBook &book) {
    cout << "--- ASKS ---" << endl;
    for (int i = 0; i < book.asks.size(); i++) {
        cout << book.asks[i].price << "\t" << book.asks[i].quantity << "\t" << book.asks[i].id << endl;
    }
    cout << "--- BIDS ---" << endl;
    for (int i = 0; i < book.bids.size(); i++) {
        cout << book.bids[i].price << "\t" << book.bids[i].quantity << "\t" << book.bids[i].id << endl;
    }
    cout << endl;
}
