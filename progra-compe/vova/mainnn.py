def min_heaters(n, r, house):
    num_heaters = 0
    cur_pos = 0 

    while cur_pos < n: 
        max_pos = -1 
        for i in range(cur_pos - r + 1, cur_pos + r): 
            if i >= 0 and i < n and house[i] == 1:
                max_pos = i 
        if max_pos == -1: 
            return -1
        cur_pos = max_pos + r 
        num_heaters += 1 

    return num_heaters

n, r = map(int, input().split())
house = list(map(int, input().split()))

print(min_heaters(n, r, house))
