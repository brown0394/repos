

class Basket:
    customerName=""
    booklist=[]
    bookcount = 0
    def __init__(self, name, bookcount=0):
        self.customerName = name
        self.bookcount = bookcount

    def add(self, bookname, price):
        self.booklist.append([bookname, price])
        self.bookcount += 1
    def showBasket(self):
        print("************************************")
        totalprice = 0
        for (title, price) in self.booklist:
            print("Title:", title + ", Price: KRW", price)
            totalprice += price
        print("------------------------------------")
        print("Total price = KRW", totalprice)
        print("************************************")
        print()
    def delete(self, name):
        for num in range(0, self.bookcount):
            if name == self.booklist[num][0]:
                self.booklist.remove([name, self.booklist[num][1]])
                self.bookcount -= 1
                break


leeBasket = Basket('Lee')
leeBasket.add('Momo', 6500)
leeBasket.showBasket()
leeBasket.add('Little Prince', 5000)
leeBasket.showBasket()
leeBasket.add('Harry Potter', 8500)
leeBasket.showBasket()
leeBasket.delete('Little Prince')
leeBasket.showBasket()
