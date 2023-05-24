t = int(input())
for _ in range(t):
    s = input().strip()
    n = len(s)
    working_buttons = set()
    i = 0
    while i < n:
        if i + 1 < n and s[i] == s[i+1]:
            i += 2
        else:
            working_buttons.add(s[i])
            i += 1
    print(''.join(sorted(list(working_buttons))))
