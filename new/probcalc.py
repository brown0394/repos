import math

def main():
    result = 0
    for i in range(1, 4):
        result += expo(i, 3, 0.04)
    print(result)

def expo(x, n, p):
    a = math.comb(n, x)
    b = p ** x
    c = (1-p) ** (n-x)
    print(a * b * c)
    return a * b * c


main()