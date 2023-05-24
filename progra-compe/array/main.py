n = int(input())
arr = list(map(int, input().split()))

max_length = 1
current_length = 1

for i in range(1, n):
    if arr[i] > arr[i-1]:
        current_length += 1
    else:
        if current_length > max_length:
            max_length = current_length
        current_length = 1

if current_length > max_length:
    max_length = current_length

print(max_length)
