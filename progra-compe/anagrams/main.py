def solve(s, q, queries):
    # inicializar el prefijo como lista
    prefix_sum = [[0]*26 for _ in range(len(s)+1)]

    # por cada posicion en el string
    for i in range(1, len(s)+1):
        # 
        for j in range(26):
            prefix_sum[i][j] = prefix_sum[i-1][j]
        prefix_sum[i][ord(s[i-1])-97] += 1

    for query in queries:
        # tomar los base 1 del substring
        l, r = query
        # convertirlos a base 0
        l -= 1
        r -= 1
        if l == r:
            print("Yes")
            continue
        elif s[l] != s[r]:
            print("Yes")
            continue
        else:
            count = 0
            for i in range(26):
                if prefix_sum[r+1][i] - (prefix_sum[l][i] if l > 0 else 0) > 0:
                    count += 1
            if count > 2:
                print("Yes")
            else:
                print("No")

s = input().strip()
q = int(input().strip())
queries = []
for _ in range(q):
    queries.append(list(map(int, input().strip().split())))
solve(s, q, queries)

