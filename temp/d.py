import random
import string
 
num = 100 #문자열 개수
max_len = 1001 # 문자열 최대 길이
f = open('./input.txt', mode='wt', encoding='utf-8')
for j in range(0,num):
    _strlen = random.randrange(3,max_len)
    string_pool = ['a','c','g','t']
    result = ""
    for i in range(_strlen):
        result += random.choice(string_pool)
    f.write(result + "\n")

f.close()
