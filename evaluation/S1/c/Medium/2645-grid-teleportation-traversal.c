// Source: https://leetcode.com/problems/grid-teleportation-traversal/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D character grid matrix of size m x n, represented as an array of strings, where matrix[i][j] represents the cell at the intersection of the ith row and jth column. Each cell is one of the following:
//
//
// 	'.' representing an empty cell.
// 	'#' representing an obstacle.
// 	An uppercase letter ('A'-'Z') representing a teleportation portal.
//
//
// You start at the top-left cell (0, 0), and your goal is to reach the bottom-right cell (m - 1, n - 1). You can move from the current cell to any adjacent cell (up, down, left, right) as long as the destination cell is within the grid bounds and is not an obstacle.
//
// If you step on a cell containing a portal letter and you haven't used that portal letter before, you may instantly teleport to any other cell in the grid with the same letter. This teleportation does not count as a move, but each portal letter can be used at most once during your journey.
//
// Return the minimum number of moves required to reach the bottom-right cell. If it is not possible to reach the destination, return -1.
//
// Example:
// Input: matrix = ["A..",".A.","..."]
//
// Output: 2
//
// Explanation:
//
//
//
//
// 	Before the first move, teleport from (0, 0) to (1, 1).
// 	In the first move, move from (1, 1) to (1, 2).
// 	In the second move, move from (1, 2) to (2, 2).
//
// Constraints:
// 1 <= m == matrix.length <= 103
// 	1 <= n == matrix[i].length <= 103
// 	matrix[i][j] is either '#', '.', or an uppercase English letter.
// 	matrix[0][0] is not an obstacle.
//
// Helpful references (internal KB):
// - 0-1 BFS (graph, deque, 01-bfs, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently computes single-source shortest paths, outperforming Dijkstra's for this specific weight constraint.
//   • Idea: 0-1 BFS is a graph traversal algorithm that finds the single-source shortest paths in a graph where all edge weights are restricted to 0 or 1. It uses a deque to process nodes, achieving an optimal time complexity of O(V + E).
//   • Invariants: When a node 'u' is extracted from the front of the deque, 'dist[u]' is its shortest path from the source.; The deque always contains nodes whose distances are either 'D' or 'D+1', where 'D' is the distance of the last node extracted.
//   • Tips: Always push 0-weight edges to the front of the deque.; Push 1-weight edges to the back of the deque.
//   • Pitfalls: Pushing 0-weight edges to the back or 1-weight edges to the front of the deque.; Not correctly initializing distances or the source node.
// - Submask Enumeration
//  (number, bitset, enumeration)
//   • When to use: When you need to iterate through all possible submasks of a given bitmask efficiently, typically for problems involving subsets or combinations represented by bits.
//   • Idea: This algorithm efficiently iterates through all submasks of a given bitmask in descending order using a clever bitwise trick. It processes each submask in O(1) time, leading to an overall complexity of O(2^k) where k is the number of set bits in the original mask.
//   • Invariants: Each `s` generated is a valid submask of the original mask `m`.; The value of `s` strictly decreases in each iteration until it reaches 0 (or the loop terminates).
//   • Tips: Always consider processing the submask 0 separately if it's a valid case for your problem.; The iteration naturally generates submasks in strictly descending numerical order.
//   • Pitfalls: Forgetting that the standard loop structure `for (int s = m; s > 0; s = (s - 1) & m)` omits submask 0.; Incorrectly assuming the iteration order is ascending; it is always descending.
// - Breadth-first search (graph, array, stack, bfs, enumeration)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level. It is suitable for exploring all reachable nodes from a source in increasing order of distance.
//   • Idea: Breadth-First Search (BFS) is a graph traversal algorithm that explores all the neighbor nodes at the current depth level before moving on to nodes at the next depth level. It finds the shortest path in an unweighted graph in O(V + E) time.
//   • Invariants: All nodes currently in the queue are at the same or adjacent depth level.; All 'marked' nodes have been visited, and their 'distTo' values are the shortest path from the source.
//   • Tips: Use a queue to manage nodes to visit, ensuring level-by-level exploration.; Maintain a 'visited' array or set to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly using a stack instead of a queue will result in Depth-First Search behavior.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minMoves(char** matrix, int matrixSize) {
    int n = strlen(matrix[0]);
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    
    /* Map portals */
    typedef struct PortalNode {
        int x;
        int y;
        struct PortalNode* next;
    } PortalNode;
    
    PortalNode* portals[26] = {NULL};
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < n; j++) {
            char c = matrix[i][j];
            if (c >= 'A' && c <= 'Z') {
                PortalNode* newNode = (PortalNode*)malloc(sizeof(PortalNode));
                newNode->x = i;
                newNode->y = j;
                newNode->next = portals[c - 'A'];
                portals[c - 'A'] = newNode;
            }
        }
    }
    
    /* BFS setup */
    int** dist = (int**)malloc(matrixSize * sizeof(int*));
    for (int i = 0; i < matrixSize; i++) {
        dist[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            dist[i][j] = -1;
        }
    }
    
    typedef struct QueueNode {
        int x;
        int y;
        struct QueueNode* next;
    } QueueNode;
    
    QueueNode* front = NULL;
    QueueNode* back = NULL;
    
    /* Enqueue function */
    void enqueue(int x, int y) {
        QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
        newNode->x = x;
        newNode->y = y;
        newNode->next = NULL;
        if (back) {
            back->next = newNode;
        } else {
            front = newNode;
        }
        back = newNode;
    }
    
    /* Dequeue function */
    void dequeue(int* x, int* y) {
        if (!front) return;
        QueueNode* temp = front;
        *x = temp->x;
        *y = temp->y;
        front = front->next;
        if (!front) back = NULL;
        free(temp);
    }
    
    /* Start BFS */
    enqueue(0, 0);
    dist[0][0] = 0;
    bool usedPortals[26] = {false};
    while (front) {
        int x, y;
        dequeue(&x, &y);
        
        /* Check if reached destination */
        if (x == matrixSize - 1 && y == n - 1) {
            int result = dist[x][y];
            for (int i = 0; i < matrixSize; i++) {
                free(dist[i]);
            }
            free(dist);
            for (int i = 0; i < 26; i++) {
                PortalNode* node = portals[i];
                while (node) {
                    PortalNode* temp = node;
                    node = node->next;
                    free(temp);
                }
            }
            return result;
        }
        
        /* Explore neighbors */
        for (int d = 0; d < 4; d++) {
            int nx = x + directions[d][0];
            int ny = y + directions[d][1];
            if (nx >= 0 && nx < matrixSize && ny >= 0 && ny < n && matrix[nx][ny] != '#' && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                enqueue(nx, ny);
            }
        }
        
        /* Teleportation */
        char c = matrix[x][y];
        if (c >= 'A' && c <= 'Z' && !usedPortals[c - 'A']) {
            usedPortals[c - 'A'] = true;
            PortalNode* node = portals[c - 'A'];
            while (node) {
                int nx = node->x;
                int ny = node->y;
                if (dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[x][y];
                    enqueue(nx, ny);
                }
                node = node->next;
            }
        }
    }
    for (int i = 0; i < matrixSize; i++) {
        free(dist[i]);
    }
    free(dist);
    for (int i = 0; i < 26; i++) {
        PortalNode* node = portals[i];
        while (node) {
            PortalNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
    return -1;
}
