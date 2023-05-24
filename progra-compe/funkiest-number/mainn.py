def is_triangular_sum(n):
    triangular_numbers = []
    i = 1
    while (i*(i+1))//2 <= n:
        triangular_numbers.append((i*(i+1))//2)
        i += 1

    l, r = 0, len(triangular_numbers) - 1
    while l <= r:
        if triangular_numbers[l] + triangular_numbers[r] == n:
            return "YES"
        elif triangular_numbers[l] + triangular_numbers[r] < n:
            l += 1
        else:
            r -= 1

    return "NO"

n = int(input())
print(is_triangular_sum(n))
