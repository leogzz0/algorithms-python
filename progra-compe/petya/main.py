

# as input the first line contains two integers "n" and "k"(1 <= n, k <= 10^8) - the numeber of petya's friend an the number of sheets in each notebook respectively
# as output print one number - the minimum number of notebooks that Petya needs to buy
import math

def notebooks(n, k):
    red_sheets = 2 * n
    green_sheets = 5 * n
    blue_sheets = 8 * n

    red_notebooks = math.ceil(red_sheets / k)
    green_notebooks = math.ceil(green_sheets / k)
    blue_notebooks = math.ceil(blue_sheets / k)

    total = red_notebooks + green_notebooks + blue_notebooks

    return total

n, k = map(int, input().split())
result = notebooks(n, k)
print(result)

#sample 1 input:3 5 output:10
#sample 2 input:15 6 output:38
