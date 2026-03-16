// Source: https://leetcode.com/problems/jump-game-iv/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of integers arr, you are initially positioned at the first index of the array.
//
// In one step you can jump from index i to index:
//
//
// 	i + 1 where: i + 1 < arr.length.
// 	i - 1 where: i - 1 >= 0.
// 	j where: arr[i] == arr[j] and i != j.
//
//
// Return the minimum number of steps to reach the last index of the array.
//
// Notice that you can not jump outside of the array at any time.
//
// Example:
// Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
// Output: 3
// Explanation: You need three jumps from index 0 --> 4 --> 3 --> 9. Note that index 9 is the last index of the array.
//
// Constraints:
// 1 <= arr.length <= 5 * 104
// 	-108 <= arr[i] <= 108
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minJumps(int* arr, int arrSize) {
    #define MAX_QUEUE_SIZE 50000
    #define HASH_SIZE 100001

    typedef struct Node {
        int index;
        int steps;
        struct Node* next;
    } Node;

    Node* createNode(int index, int steps) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->index = index;
        newNode->steps = steps;
        newNode->next = NULL;
        return newNode;
    }

    typedef struct Queue {
        Node* front;
        Node* rear;
    } Queue;

    void enqueue(Queue* q, int index, int steps) {
        Node* newNode = createNode(index, steps);
        if (q->rear) {
            q->rear->next = newNode;
        } else {
            q->front = newNode;
        }
        q->rear = newNode;
    }

    Node* dequeue(Queue* q) {
        if (!q->front) return NULL;
        Node* temp = q->front;
        q->front = q->front->next;
        if (!q->front) q->rear = NULL;
        return temp;
    }

    int hash(int key) {
        return (key + 1000000000) % HASH_SIZE;
    }

    typedef struct HashMap {
        int* keys[HASH_SIZE];
        int sizes[HASH_SIZE];
    } HashMap;

    void initHashMap(HashMap* map) {
        for (int i = 0; i < HASH_SIZE; i++) {
            map->keys[i] = NULL;
            map->sizes[i] = 0;
        }
    }

    void insertHashMap(HashMap* map, int key, int index) {
        int h = hash(key);
        map->keys[h] = (int*)realloc(map->keys[h], sizeof(int) * (map->sizes[h] + 1));
        map->keys[h][map->sizes[h]] = index;
        map->sizes[h]++;
    }

    int* getHashMap(HashMap* map, int key, int* size) {
        int h = hash(key);
        *size = map->sizes[h];
        return map->keys[h];
    }

    HashMap map;
    initHashMap(&map);
    for (int i = 0; i < arrSize; i++) {
        insertHashMap(&map, arr[i], i);
    }
    bool* visited = (bool*)calloc(arrSize, sizeof(bool));
    Queue queue = {NULL, NULL};
    enqueue(&queue, 0, 0);
    visited[0] = true;
    while (queue.front) {
        Node* current = dequeue(&queue);
        int index = current->index;
        int steps = current->steps;
        free(current);
        if (index == arrSize - 1) {
            for (int i = 0; i < HASH_SIZE; i++) {
                free(map.keys[i]);
            }
            free(visited);
            return steps;
        }
        // Jump to index + 1
        if (index + 1 < arrSize && !visited[index + 1]) {
            visited[index + 1] = true;
            enqueue(&queue, index + 1, steps + 1);
        }
        // Jump to index - 1
        if (index - 1 >= 0 && !visited[index - 1]) {
            visited[index - 1] = true;
            enqueue(&queue, index - 1, steps + 1);
        }
        // Jump to all indices with the same value
        int size;
        int* sameValueIndices = getHashMap(&map, arr[index], &size);
        for (int i = 0; i < size; i++) {
            int nextIndex = sameValueIndices[i];
            if (nextIndex != index && !visited[nextIndex]) {
                visited[nextIndex] = true;
                enqueue(&queue, nextIndex, steps + 1);
            }
        }
        // Clear the list to prevent future redundant checks
        map.sizes[hash(arr[index])] = 0;
    }
    for (int i = 0; i < HASH_SIZE; i++) {
        free(map.keys[i]);
    }
    free(visited);
    return -1; // Should never reach here
}