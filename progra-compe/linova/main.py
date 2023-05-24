import heapq
from collections import defaultdict

def max_happiness(n, k, edges):
    graph = defaultdict(list)
    for u, v in edges:
        graph[u].append(v)
        graph[v].append(u)
        
    depth = [0] * (n + 1)
    visited = [False] * (n + 1)
    
    def dfs(node, d):
        visited[node] = True
        depth[node] = d
        for neighbor in graph[node]:
            if not visited[neighbor]:
                dfs(neighbor, d + 1)
    
    dfs(1, 0)
    
    pq = []
    for i in range(1, n + 1):
        heapq.heappush(pq, depth[i] - len(graph[i]) + 1)
        
        if len(pq) > k:
            heapq.heappop(pq)
            
    return sum(pq)

n, k = map(int, input().strip().split())
edges = []
for _ in range(n - 1):
    u, v = map(int, input().strip().split())
    edges.append((u, v))

print(max_happiness(n, k, edges))
