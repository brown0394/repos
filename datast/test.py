class what:
    def __init__(self, one = 1):
        self.one = one
    def printw(self):
        print("what")

class why(what):
    def __init__(self):
        super.__init__()
        self.two = 2
    def printwhy(self):
        print(self.one)
    def plus(self):
        self.one += 1
