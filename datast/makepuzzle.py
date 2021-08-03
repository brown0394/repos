import random

def main():
    probs = []
    while True:
        for i in range(5):
            probs.append(prob())
        res = findSol(probs)
        if len(res) < 9:
            probs.clear()
            continue
        if reschk(res, probs):
            break
        probs.clear()
    print(probs)
    printsol(res)
        

def reschk(res, probs):
    for i in range(5):
        if probs[i] not in res:
            print('hola')
            return False
    return True

def printsol(res):
    for i in range(9):
        print(res[i])
        print()

def prob():
    problist = []
    binary = [1, 0]
    for i in range(8):
        problist.append(random.choice(binary))
    return problist

def zeroChk(res):
    chk = [0, 0, 0, 0, 0, 0, 0, 0]
    if chk == res:
        return True
    return False

def findSol(p):
    res = 0
    seq = []
    for i in range(1000):
        a = p[random.randint(0, 4)]
        res = a
        seq.append(a)
        a = p[random.randint(0, 4)]
        seq.append(a)
        res = opxor(res, a)
        if sol(res):
            seq.clear()
            continue
        if zeroChk(res):
            seq.clear()
            break
        a = p[random.randint(0, 4)]
        seq.append(a)
        res = opnor(res, a)
        if sol(res):
            seq.clear()
            continue
        if zeroChk(res):
            seq.clear()
            break
        a = p[random.randint(0, 4)]
        seq.append(a)
        res = opxor(res, a)
        if sol(res):
            seq.clear()
            continue
        if zeroChk(res):
            seq.clear()
            break
        a = p[random.randint(0, 4)]
        seq.append(a)
        res = opnxor(res, a)
        if sol(res):
            seq.clear()
            continue
        if zeroChk(res):
            seq.clear()
            break 
        a = p[random.randint(0, 4)]
        seq.append(a)
        res = opxor(res, a)
        if sol(res):
            seq.clear()
            continue
        if zeroChk(res):
            seq.clear()
            break
        a = p[random.randint(0, 4)]
        seq.append(a)
        res = opnor(res, a)
        if sol(res):
            seq.clear()
            continue
        if zeroChk(res):
            seq.clear()
            break 
        a = p[random.randint(0, 4)]
        seq.append(a)
        res = opxor(res, a)
        if sol(res):
            seq.clear()
            continue
        if zeroChk(res):
            seq.clear()
            break      
        a = p[random.randint(0, 4)]
        seq.append(a)
        res = opnxor(res, a)
        if sol(res):
            break
        else:
            seq.clear()
    return seq


def opnor(one, two):
    res = []
    for i in range(8):
        res.append(int(not(one[i] | two[i])))
    return res

def opxor(one, two):
    res = []
    for i in range(8):
        res.append(one[i] ^ two[i])
    return res

def opnxor(one, two):
    res = []
    for i in range(8):
        res.append(int(not(one[i] ^ two[i])))
    return res

def sol(one):
    for i in range(8):
        res = one[i]
        if 0 == res:
            return False
    return True
main()