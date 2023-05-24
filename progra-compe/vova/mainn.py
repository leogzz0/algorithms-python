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

# contador para ver que todos esten en 1 osea calentados
if 0 not in heaters:
    ans = a.count(1)
else: #
    for i in range(n):
        if a[i] == 0 and heaters[i] == 0: # si hay un 0 (espacion no calentado)
            found = False # flag
            for j in range(max(0, i - r + 1), min(n, i + r)):
                if heaters[j] == 1: # si hay un calentador que cubra j
                    heaters[j] = 2 # marcar el heater usado
                    found = True 
                    ans += 1
                    break
            if not found:
                print(-1)
                exit()

print(ans)

