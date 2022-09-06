#ifndef MINI_EXCHANGE_BOOK_H
#define MINI_EXCHANGE_BOOK_H

#include <vector>

#include "order.h"

struct OrderBook {
    vector<Order> bids;
    vector<Order> asks;
};

void addOrder(OrderBook &book, Order order);
bool cancelOrder(OrderBook &book, string id);
void printBook(OrderBook &book);

#endif
