import random
import math

def main():
    nodes = create_nodes(5)
    graph = create_graph(nodes)
    graph = reduce_edges(graph)
    for line in graph:
        print(line)
    print()
    print(nodes)
    print(f"bfs:    {bfs(graph, 0)}")
    print(f"dfs:    {dfs(graph, 0)}")
    print(f"mst:    {mst(graph, 0)}")
    print(f"greedy: {greedy_search(graph, 0)}")
    ends = find_disconnected_nodes(graph)
    if ends:
        start, end = ends
        print(f"bi_bfs: {bi_bfs(graph, start, end)}")
    else:
        print("bi_bfs:  There's no disconnected edges")

def find_disconnected_nodes(graph):
    n = len(graph)
    for i in range(n):
        for j in range(n):
            if graph[i][j] == 0 and i != j:
                return i, j
    return False

def bi_bfs(graph, start, end):
    n = len(graph)
    start_state = ([start], 0)
    end_state = ([end], 0)
    start_queue = [start_state]
    end_queue = [end_state]
    best_state = ([], float('inf'))

    while start_queue and end_queue:

        start_state = start_queue.pop(0)
        end_state = end_queue.pop(0)

        start_route, start_cost = start_state
        end_route, end_cost = end_state

        for start_index, value in enumerate(start_route):
            if value not in end_route:
                continue
            end_index = end_route.index(value)
            best_route, best_cost = best_state
            route = start_route[:start_index + 1] + list(reversed(end_route[:end_index]))
            cost = calc_route_cost(graph, route)
            if cost < best_cost:
                best_state = (route, cost)
                break

        for i in range(n):
            if i not in start_route \
                and graph[start_route[-1]][i] > 0:
                start_queue.append((start_route + [i],
                                    start_cost + graph[start_route[-1]][i]))
            if i not in end_route \
                and graph[end_route[-1]][i] > 0:
                end_queue.append((end_route + [i],
                                  end_cost + graph[end_route[-1]][i]))
                
    return best_state

def calc_route_cost(graph, route):
    cost = 0
    for index in range(1, len(route)):
        if graph[route[index - 1]][route[index]] == 0:
            return False
        cost += graph[route[index - 1]][route[index]]
    return cost

def mst(graph, start):
    n = len(graph)
    edges = []

    # Sorted list of edges
    for i in range(n):
        for j in range(n):
            weight = graph[i][j]
            if weight == 0  or (j, i, weight) in edges:
                continue
            edge = (i, j, weight)
            edges.append(edge)

    edges = sorted(edges, key=lambda e: e[2])

    # Tree generation
    tree = [[0 for _ in range(n)] 
           for _ in range(n)]
    connected = []
    while len(edges) > 0:
        i, j, weight = edges.pop(0)
        if i not in connected \
            or j not in connected \
                and weight > 0:
            tree[i][j] = tree[j][i] = weight
            connected.append(i)
            connected.append(j)

    stack = [start]
    route = []
    while stack:
        node1 = stack.pop()
        route.append(node1)
        for node2 in range(n):
            if tree[node1][node2] > 0 and node2 not in route:
                stack.append(node2)

    if len(route) < n or graph[route[-1]][start] == 0:
        return "There's no path"
    
    route.append(start)
    cost = calc_route_cost(graph, route)

    if cost == False:
        return "There's no path"
    
    return route, cost

def greedy_search(graph, start):
    n = len(graph)
    state = ([start], 0)

    while len(state[0]) < n:
        route, cost = state
        children = []
        for node in range(n):
            if node in route or \
                graph[route[-1]][node] == 0:
                continue
            children.append((route + [node],
                            cost + graph[route[-1]][node]))
        
        if len(children) == 0:
            return "There's no path"
        
        state = min(children, key=lambda c: c[1])

    route, cost = state
    if graph[route[-1]][start] == 0:
        return "There's no path"
    
    state = (route + [start],
             cost + graph[route[-1]][start])

    return state

def bfs(graph, start):
    n = len(graph)
    state = ([start], 0)
    queue = [state]
    best_state = ([], float('inf'))

    while len(queue) > 0:
        state = queue.pop(0)
        route, cost = state

        for node in range(n):
            if node in route or graph[route[-1]][node] == 0:
                continue
            child_state = (route + [node], 
                              cost + graph[route[-1]][node])
            queue.append(child_state)
        
        while len(queue) > 0 and len(queue[-1][0]) == n:
            route, cost = queue.pop()
            if graph[route[-1]][start] == 0:
                break
            cost += graph[route[-1]][start]
            route += [start]
            best_route, best_cost = best_state
            if cost < best_cost:
                best_state = (route, cost)

    return best_state

def dfs(graph, start):
    n = len(graph)
    state = ([start], 0)
    stack = [state]
    best_state = ([], float('inf'))

    while len(stack) > 0:
        state = stack.pop()
        route, cost = state

        for node in range(n):
            if node in route or graph[route[-1]][node] == 0:
                continue
            child_state = (route + [node], 
                              cost + graph[route[-1]][node])
            stack.append(child_state)
        
        while len(stack) > 0 and len(stack[-1][0]) == n:
            route, cost = stack.pop()
            if graph[route[-1]][start] == 0:
                break
            cost += graph[route[-1]][start]
            route += [start]
            best_route, best_cost = best_state
            if cost < best_cost:
                best_state = (route, cost)

    return best_state

def reduce_edges(graph):
    n = len(graph)
    num_edges = 0.5 * (n - 1) * n
    num_edges = math.floor(0.2 * num_edges)

    for _ in range(num_edges):
        i = random.randint(0, n - 1)
        j = random.randint(0, n - 1)
        graph[i][j] = 0
        graph[j][i] = 0

    return graph

def create_graph(nodes):
    graph = [[0 for _ in range(len(nodes))] 
             for _ in range(len(nodes))]
    for i, node1 in enumerate(nodes):
        for j, node2 in enumerate(nodes):
            x1 = node1[0]
            y1 = node1[1]
            x2 = node2[0]
            y2 = node2[1]
            distance = math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2)
            graph[i][j] = distance
    return graph

def create_nodes(num):
    nodes = []
    for _ in range(num):
        node = (random.randint(-100, 100),
                random.randint(-100, 100))
        nodes.append(node)
    return nodes

if __name__ == "__main__":
    main()