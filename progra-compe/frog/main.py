def minimal_jumps(n, d, s):
    jumps = [float('inf')] * n
    jumps[0] = 0
    
    for i in range(1, n):
        if s[i] == '1':
            for j in range(1, min(i, d) + 1):
                if s[i-j] == '1':
                    jumps[i] = min(jumps[i], jumps[i-j] + 1)
    
    return jumps[-1] if jumps[-1] != float('inf') else -1

n, d = map(int, input().split())
s = input()

result = minimal_jumps(n, d, s)
print(result)
