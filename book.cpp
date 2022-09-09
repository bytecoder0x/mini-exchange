#include "book.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>

bool compareBids(Order a, Order b) {
    if (a.price != b.price) return a.price > b.price;
    return a.number < b.number;
}

bool compareAsks(Order a, Order b) {
    if (a.price != b.price) return a.price < b.price;
    return a.number < b.number;
}

void printTrade(Trade t) {
    cout << "TRADE " << t.buyId << " " << t.sellId << " " << t.quantity << " x " << t.price << endl;
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
        Trade t;
        t.price = best.price;
        t.quantity = quantity;
        if (order.side == "BUY") {
            t.buyId = order.id;
            t.sellId = best.id;
        } else {
            t.buyId = best.id;
            t.sellId = order.id;
        }
        book.trades.push_back(t);
        printTrade(t);

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

bool cancelOrder(OrderBook &book, string id) {
    for (int i = 0; i < book.bids.size(); i++) {
        if (book.bids[i].id == id) {
            book.bids.erase(book.bids.begin() + i);
            return true;
        }
    }
    for (int i = 0; i < book.asks.size(); i++) {
        if (book.asks[i].id == id) {
            book.asks.erase(book.asks.begin() + i);
            return true;
        }
    }
    return false;
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

void saveTrades(OrderBook &book, string fileName) {
    ofstream file(fileName);
    file << fixed << setprecision(2);
    file << "buy_id,sell_id,price,quantity" << endl;
    for (int i = 0; i < book.trades.size(); i++) {
        Trade t = book.trades[i];
        file << t.buyId << "," << t.sellId << "," << t.price << "," << t.quantity << endl;
    }
    file.close();
}
