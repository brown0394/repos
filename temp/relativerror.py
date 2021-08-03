from math import pow

while True:
    #E = float(input())
    #T = float(input())
    #print(abs(E-T) / T * 100)

    m1 = 216
    m2 = 216
    v1 = float(input())
    #print("v1' =", ((m1 - m2) / (m1+m2)) * v1)
    #print("v2' =", ((2*m1) / (m1+m2)) * v1)

    m1 /= 1000
    m2 /= 1000

    v1p = float(input())
    v2p = float(input())

    v1 /= 100
    v1p /= 100
    v2p /= 100


    #print(m1 * v1)
    #print((m1 * v1p) + (m2*v2p))
    print(0.5*m1 * pow(v1, 2))
    print((0.5*m1 * pow(v1p, 2)) + (0.5*m2 * pow(v2p, 2)))

    #귀찮으니까 ctrl+c로 종료