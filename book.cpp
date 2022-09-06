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
    vector<Order> &opposite = order.side == "BUY" ? book.asks : book.bids;

    while (order.quantity > 0 && !opposite.empty()) {
        Order &best = opposite[0];
        if (order.type == "LIMIT") {
            if (order.side == "BUY" && best.price > order.price) break;
            if (order.side == "SELL" && best.price < order.price) break;
        }

        int quantity = min(order.quantity, best.quantity);
        cout << "TRADE " << order.id << " " << best.id << " " << quantity << " x " << best.price << endl;

        order.quantity -= quantity;
        best.quantity -= quantity;
        if (best.quantity == 0) opposite.erase(opposite.begin());
    }

    if (order.quantity > 0) {
        if (order.type == "MARKET") {
            cout << "UNFILLED " << order.id << " " << order.quantity << endl;
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
}

void printBook(OrderBook &book) {
    cout << "--- ASKS ---" << endl;
    for (int i = book.asks.size() - 1; i >= 0; i--) {
        cout << book.asks[i].price << "\t" << book.asks[i].quantity << "\t" << book.asks[i].id << endl;
    }
    cout << "--- BIDS ---" << endl;
    for (int i = 0; i < book.bids.size(); i++) {
        cout << book.bids[i].price << "\t" << book.bids[i].quantity << "\t" << book.bids[i].id << endl;
    }
    cout << endl;
}
