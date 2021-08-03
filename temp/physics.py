import math

print(84.64 * 52.98 * 0.64)
num = int(input("number of data: "))
result = 0
numbers = []
for i in range(0, num):
    numbers.append(float(input()))

mean = sum(numbers) / len(numbers)
print("mean :", mean)

for i in range(0, num):
    result += math.pow(numbers[i] - mean, 2)

result = math.sqrt(result / (num - 1))
print("Sx =", result)
result = result / math.sqrt(num)
print(result)