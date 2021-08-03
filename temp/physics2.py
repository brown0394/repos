import math

number = 5
x = [0, 0.03125, 0.09245, 0.15125, 0.19845]
y = [0, 0.5, 1, 1.5, 2]


xip = 0
yip = 0
xiyi = 0
xi = 0
yi = 0

for i in range(0, number):
    xip += math.pow(x[i], 2)
    yip += math.pow(y[i], 2)
    xiyi += x[i] * y[i]
    xi += x[i]
    yi += y[i]


a = ((xip * yi) - (xi * xiyi)) / (((number*xip) - (math.pow(xi, 2))))
b = ((number * xiyi) - (xi * yi)) / (((number*xip) - (math.pow(xi, 2))))

temp = 0
for i in range(0, number):
    temp += math.pow(y[i] - a - (b*x[i]), 2)

Sy = math.sqrt((1/(number-2)) * temp)
Sa = math.sqrt(xip / ((number*xip) - math.pow(xi, 2))) * Sy
Sb = math.sqrt(number / ((number*xip) - math.pow(xi, 2))) * Sy

resx = (1.0-a) / b


print("xi^2 = ", xip)
print("xi = ", xi)
print("yi^2 = ", yip)
print("yi = ", yi)
print("xiyi = ", xiyi)
print("y 절편 A =", a)
print("기울기 B =", b)
print("Sy =", Sy)
print("(A의 불확도)Sa =", Sa)
print("(B의 불확도)Sb =", Sb)

print("res = ", resx)