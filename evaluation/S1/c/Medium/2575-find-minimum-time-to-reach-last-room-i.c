// Source: https://leetcode.com/problems/find-minimum-time-to-reach-last-room-i/   |   Difficulty: Medium
//
// Problem Description:
// There is a dungeon with n x m rooms arranged as a grid.
//
// You are given a 2D array moveTime of size n x m, where moveTime[i][j] represents the minimum time in seconds after which the room opens and can be moved to. You start from the room (0, 0) at time t = 0 and can move to an adjacent room. Moving between adjacent rooms takes exactly one second.
//
// Return the minimum time to reach the room (n - 1, m - 1).
//
// Two rooms are adjacent if they share a common wall, either horizontally or vertically.
//
// Example:
// Input: moveTime = [[0,4],[4,4]]
//
// Output: 6
//
// Explanation:
//
// The minimum time required is 6 seconds.
//
//
// 	At time t == 4, move from room (0, 0) to room (1, 0) in one second.
// 	At time t == 5, move from room (1, 0) to room (1, 1) in one second.
//
// Constraints:
// 2 <= n == moveTime.length <= 50
// 	2 <= m == moveTime[i].length <= 50
// 	0 <= moveTime[i][j] <= 109
//
// Helpful references (internal KB):
// - Dijkstra Algorithm (graph, array, dijkstra, greedy)
//   • When to use: Use this algorithm to find the shortest paths from a single source to all other vertices in a graph. It is applicable when all edge weights are non-negative.
//   • Idea: Dijkstra's algorithm finds the shortest paths from a single source vertex to all other vertices in a weighted graph with non-negative edge weights. It iteratively selects the unvisited vertex with the smallest known distance, relaxing its outgoing edges, achieving O(V^2 + E) or O(E log V) complexity.
//   • Invariants: For any marked vertex v, d[v] holds the true shortest path distance from s to v.; For any unmarked vertex v, d[v] holds the shortest path distance from s to v using only marked intermediate vertices.
//   • Tips: Use a priority queue for sparse graphs to optimize performance to O(E log V).; Initialize distances to infinity for all vertices except the source, which is zero.
//   • Pitfalls: Dijkstra's algorithm does not work correctly with negative edge weights; use Bellman-Ford or SPFA instead.; Failing to use an efficient data structure (like a priority queue) for vertex selection can lead to O(V^2) performance on sparse graphs.
// - Solving assignment problem using min-cost-flow (graph, dijkstra, bellman-ford)
//   • When to use: Use when finding a one-to-one assignment between two sets of entities, such as workers to tasks, to minimize the total cost. It's suitable for problems modelable as min-cost max-flow in a bipartite graph.
//   • Idea: This technique models the assignment problem as a minimum cost maximum flow problem on a specially constructed bipartite graph. It finds a perfect matching with the lowest total cost, typically with a polynomial time complexity depending on the shortest path algorithm used.
//   • Invariants: Flow conservation holds for all intermediate nodes in the network.; The flow on any edge never exceeds its defined capacity.
//   • Tips: Construct a bipartite graph with a source and sink nodes.; Set capacities to 1 for all assignment-related edges to ensure one-to-one mapping.
//   • Pitfalls: Incorrectly modeling capacities or costs on graph edges can lead to wrong solutions.; Forgetting to ensure a perfect matching (flow value equals N) is found for a complete assignment.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, counting)
//   • When to use: Use when needing to count the number of paths of a specific length between all pairs of vertices in a graph, or to find reachability in a fixed number of steps.
//   • Idea: This algorithm leverages matrix exponentiation to find the number of paths of a fixed length `k` between all pairs of vertices in a graph. Each matrix multiplication step extends path lengths by one, resulting in an O(N^3 log K) time complexity for an N-vertex graph.
//   • Invariants: After `m` matrix multiplications, `C_m[i][j]` stores the number of paths of length `m` from `i` to `j`.; The initial adjacency matrix `G` remains constant throughout the exponentiation process.
//   • Tips: Represent the graph as an adjacency matrix where `G[i][j]` is the number of direct edges.; Matrix multiplication `C_k * G` yields `C_{k+1}` for path counts.
//   • Pitfalls: Standard matrix multiplication is O(N^3), leading to O(N^3 log K) overall time complexity.; Memory usage is O(N^2) for storing matrices, which can be prohibitive for very large graphs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minTimeToReach(int** moveTime, int moveTimeSize, int* moveTimeColSize) {
    int n = moveTimeSize;
    int m = moveTimeColSize[0];
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    
    // Min-heap priority queue
    typedef struct {
        int time;
        int x;
        int y;
    } Node;
    
    typedef struct {
        Node* data;
        int size;
        int capacity;
    } MinHeap;
    
    MinHeap* createMinHeap(int capacity) {
        MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
        heap->data = (Node*)malloc(sizeof(Node) * capacity);
        heap->size = 0;
        heap->capacity = capacity;
        return heap;
    }
    
    void swap(Node* a, Node* b) {
        Node temp = *a;
        *a = *b;
        *b = temp;
    }
    
    void minHeapify(MinHeap* heap, int idx) {
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        
        if (left < heap->size && heap->data[left].time < heap->data[smallest].time)
            smallest = left;
        
        if (right < heap->size && heap->data[right].time < heap->data[smallest].time)
            smallest = right;
        
        if (smallest != idx) {
            swap(&heap->data[smallest], &heap->data[idx]);
            minHeapify(heap, smallest);
        }
    }
    
    void insertMinHeap(MinHeap* heap, Node node) {
        if (heap->size == heap->capacity) return; // Heap full
        
        heap->data[heap->size] = node;
        int i = heap->size++;
        
        while (i && heap->data[(i - 1) / 2].time > heap->data[i].time) {
            swap(&heap->data[i], &heap->data[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
    
    Node extractMin(MinHeap* heap) {
        Node root = heap->data[0];
        heap->data[0] = heap->data[--heap->size];
        minHeapify(heap, 0);
        return root;
    }
    MinHeap* heap = createMinHeap(n * m);
    int** dist = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        dist[i] = (int*)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            dist[i][j] = __INT_MAX__;
        }
    }
    dist[0][0] = 0;
    insertMinHeap(heap, (Node){0, 0, 0});
    while (heap->size) {
        Node current = extractMin(heap);
        int curTime = current.time;
        int x = current.x;
        int y = current.y;
        
        if (x == n - 1 && y == m - 1) {
            // Free allocated memory
            for (int i = 0; i < n; i++) {
                free(dist[i]);
            }
            free(dist);
            free(heap->data);
            free(heap);
            return curTime;
        }
        
        for (int d = 0; d < 4; d++) {
            int newX = x + directions[d][0];
            int newY = y + directions[d][1];
            
            if (newX >= 0 && newX < n && newY >= 0 && newY < m) {
                int waitTime = 0;
                if (curTime + 1 < moveTime[newX][newY]) {
                    waitTime = moveTime[newX][newY] - (curTime + 1);
                }
                int newTime = curTime + 1 + waitTime;
                
                if (newTime < dist[newX][newY]) {
                    dist[newX][newY] = newTime;
                    insertMinHeap(heap, (Node){newTime, newX, newY});
                }
            }
        }
    }
    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(dist[i]);
    }
    free(dist);
    free(heap->data);
    free(heap);
    return -1; // Should not reach here
}

