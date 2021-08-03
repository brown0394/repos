import math

FA = int(input("MA : "))
FB = int(input("MB : "))
theta = int(input("FBtheta : "))

FA = FA * 9.8
FB = FB * 9.8

print("FA =", FA)
print("FB =", FB)

FBcos = math.cos(math.radians(theta))
FBsin = math.sin(math.radians(theta))

print("FB cos =", FBcos)
print("FBsin =", FBsin)

F = math.sqrt(math.pow(FA,2)+math.pow(FB,2)+ (2*FA*FB*FBcos))
print("F =",F)

deg = (FB * FBsin) / (FA + (FB * FBcos))
deg = math.degrees(math.atan(deg))
print("deg =", deg)
print("MC = ", F / 9.8)