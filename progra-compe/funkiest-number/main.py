def triangular(num):
    print(num)
    # print(math.sqrt(8 * num + 1) % 1)
    return (8*num + 1)**0.5 % 1 == 0

# the first input line contains an integer n(1 <= n <= 10^9)
n = int(input())

# print "YES", if n can be represented as a sum of two traingular numbers, otherwise print "NO"
for i in range(1, n+1):
    if triangular(i) and triangular(n-i):
        print("YES")
        break
else:
    print("NO")
