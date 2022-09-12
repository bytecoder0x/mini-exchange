# mini-exchange

Simple simulator of exchange order book, written on C++ for practice.
Program reads orders from file and matches them like real exchange do (buy with sell).

### How it works

- all orders are in the text file, one order on line
- BUY orders are sorted from highest price, SELL orders from lowest. If price is same, first order goes first
- LIMIT order is matched only when price is ok, if not it waits in the book
- MARKET order takes best price right now, if book is empty the rest is just dropped
- when quantity is different, order is filled partially and the rest stays in the book
- every trade is printed and in the end all trades are saved to trades.csv

### Commands

```
BUY LIMIT 100.5 10 b1     buy 10 by price 100.5, id is b1
SELL LIMIT 101 5 s1
SELL MARKET 7 s2          market order, without price
CANCEL b1                 remove order from the book
PRINT                     print the book
```

lines that start with # are skipped

### Example

orders.txt:

```
BUY LIMIT 100 10 b1
BUY LIMIT 100.5 5 b2
SELL LIMIT 101 8 s1
SELL LIMIT 100.5 3 s3
SELL MARKET 7 s4
```

output:

```
TRADE b2 s3 3 x 100.50
TRADE b2 s4 2 x 100.50
TRADE b1 s4 5 x 100.00
--- ASKS ---
101.00	8	s1
--- BIDS ---
100.00	5	b1

Total trades: 3
Trades saved to trades.csv
```

### Build

Open the project in CLion (CMakeLists.txt is there) or from terminal:

```
g++ main.cpp book.cpp -o mini_exchange
./mini_exchange orders.txt
```

If file name is not given, program reads orders.txt

### Todo

- read orders from console, not only from file
- stop orders
- check that id is not repeated
