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

### Build

Open the project in CLion (CMakeLists.txt is there) or from terminal:

```
g++ main.cpp book.cpp -o mini_exchange
./mini_exchange orders.txt
```

If file name is not given, program reads orders.txt
