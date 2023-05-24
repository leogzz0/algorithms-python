def next_prime(n):
    def is_prime(num):
        if num < 2:
            return False
        for i in range(2, int(num**0.5) + 1):
            if num % i == 0:
                return False
        return True

    prime = n
    while not is_prime(prime):
        prime += 1
    return prime

def mat():
    n, m = map(int, input().split())
    matrix = [list(map(int, input().split())) for _ in range(n)]
    
    moves = [[next_prime(matrix[i][j]) - matrix[i][j] for j in range(m)] for i in range(n)]
    
    min_moves_row = min(sum(row) for row in moves)
    min_moves_col = min(sum(col) for col in zip(*moves))
    
    return min(min_moves_row, min_moves_col)

print(mat())
