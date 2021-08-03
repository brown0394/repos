import numpy as np

def main():
    a = np.arange(6)
    print(a)
    b = a.reshape(3, 2)
    print(b)
    print(b[1,1])
    print(b[:,1])

if __name__ == "__main__":
    main()