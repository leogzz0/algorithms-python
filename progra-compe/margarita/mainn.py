def solve_query(l, r):
    def sum_first_n(n):
        return n // 2 if n % 2 == 0 else -(n // 2 + 1)

    return sum_first_n(r) - sum_first_n(l - 1)

input_lines = []
q = int(input().strip())
for _ in range(q):
    input_lines.append(input().strip())

for input_line in input_lines:
    l, r = map(int, input_line.split())
    print(solve_query(l, r))
