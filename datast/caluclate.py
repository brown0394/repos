import numpy as np
import math

def main():
    #z1 = -0.25j
    #z2 = 0.5j
    #z3 = 2.165 + 1.25j
    number = 10


    #z4 = 0.5j
    #z5 = -0.5j
    #z6 = -5j
    #A = np.array([[z1, z2], [z4, z5]])
    #B = np.array([z3, z6])

    #C = np.linalg.solve(A, B)
    #print(C)

    A = np.array([[0, 1, 1, 1], [3, 0, 3, -4], [1, 1, 1, 2], [2, 3, 1, 3]])
    B = np.array([0, 7, 6, 6])
    C = np.linalg.solve(A, B)
    print(C)

    #polar(0.45515, -0.439)
    #phasor(20, 10)
    #resParr(3.2941, -0.5882j)
    #volcurdiv(10, 6.5 -11.75j, 5-10j)#첫 번째가 윗놈. 세번째가 v나 i

def polar(x, y):
    print(math.sqrt(math.pow(x, 2) + math.pow(y, 2)))
    print(math.degrees(math.atan(y / x)))

def phasor(x, y):
    print(((np.cos(np.deg2rad(y)))) * x)
    print(((np.sin(np.deg2rad(y)))) * x)

def resParr(x, y):
    print((x * y) / (x + y))

def volcurdiv(r1, r2, v):
    print((r1 / (r1+r2)) * v)
main()