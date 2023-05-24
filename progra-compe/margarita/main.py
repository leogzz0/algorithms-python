def solve_query(l, r):
    def sum_first_n(n):
        return n // 2 if n % 2 == 0 else -(n // 2 + 1)

    return sum_first_n(r) - sum_first_n(l - 1)

q = int(input().strip())
for _ in range(q):
    l, r = map(int, input().strip().split())
    print(solve_query(l, r))

"""
input
5
1 3
2 5
5 5
4 4
2 3

output
-2
-2
-5
4
-1
"""