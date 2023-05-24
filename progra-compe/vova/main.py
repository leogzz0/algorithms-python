n, r = map(int, input().split()) # lee valores
a = list(map(int, input().split())) # lista

heaters = [0] * n # datos de posicion "1"
ans = 0 # counter

# checar los "1"
for i in range (n):
    if a[i] == 1:
        # marcar todos los que puedan ser marcados
        for j in range(max(0, i - r + 1), min(n, i + r)):
            heaters[j] = 1

#

if 0 not in heaters:
    print(0 if a.count(1) == n else 1)
else:
    for i in range(n):
        if a[i] == 0 and heaters[i] == 0:
            found = False
            for j in range(max(0, i - r + 1), min(n, i + r)):
                if heaters[j] == 1:
                    heaters[j] = 2
                    found = True
                    ans += 1
                    break
            if not found:
                print(-1)
                exit()

    print(ans)

"""
while 0 in heaters:
    found = False #flag
    # encontrar "0"
    for i in range(n):
        if a[i] == 0 and heaters[i] == 0:
            for j in range(max(0, i - r + 1), min(n, i + r)):
                if heaters[j] == 1: # si se encuntra un heater que cubre la posicion j
                    heaters[j] = 2 # lo marcamos como usado
                    found = True # flag encontrada
                    ans += 1 
                    break
        if found:
            break
    if not found:
        print(-1)
        exit()
    
print(ans)
"""