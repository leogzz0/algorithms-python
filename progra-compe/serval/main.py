n, t = map(int, input().split())

min_arrival_time = float('inf')
selected_bus_route = None

for i in range(1, n+1):
    s, d = map(int, input().split())
    if t < s:
        arrival_time = s
    else:
        #(t - s + d - 1) calcula el  tiempo de diferencia y le restamos uno para agarrar el entero redondeado
        #se divide entre d para calcular el intervalo
        # se multiplica por d para sacar el siguiente autobus que se vera despues de la llegada
        arrival_time = s + ((t - s + d - 1) // d) * d
        #arrival_time = s + (t - s + d )
        #arrival_time = s + (t - s + d ) * d
        #arrival_time = s + (t - s + d - 1)
        #arrival_time = s + ((t - s + d - 1)// d ) * d
    if arrival_time < min_arrival_time:
        min_arrival_time = arrival_time
        selected_bus_route = i

print(selected_bus_route)