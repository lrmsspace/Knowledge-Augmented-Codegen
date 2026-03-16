// Source: https://leetcode.com/problems/process-tasks-using-servers/   |   Difficulty: Medium
//
// Problem Description:
// You are given two 0-indexed integer arrays servers and tasks of lengths n​​​​​​ and m​​​​​​ respectively. servers[i] is the weight of the i​​​​​​th​​​​ server, and tasks[j] is the time needed to process the j​​​​​​th​​​​ task in seconds.
//
// Tasks are assigned to the servers using a task queue. Initially, all servers are free, and the queue is empty.
//
// At second j, the jth task is inserted into the queue (starting with the 0th task being inserted at second 0). As long as there are free servers and the queue is not empty, the task in the front of the queue will be assigned to a free server with the smallest weight, and in case of a tie, it is assigned to a free server with the smallest index.
//
// If there are no free servers and the queue is not empty, we wait until a server becomes free and immediately assign the next task. If multiple servers become free at the same time, then multiple tasks from the queue will be assigned in order of insertion following the weight and index priorities above.
//
// A server that is assigned task j at second t will be free again at second t + tasks[j].
//
// Build an array ans​​​​ of length m, where ans[j] is the index of the server the j​​​​​​th task will be assigned to.
//
// Return the array ans​​​​.
//
// Example:
// Input: servers = [3,3,2], tasks = [1,2,3,2,1,2]
// Output: [2,2,0,2,1,2]
// Explanation: Events in chronological order go as follows:
// - At second 0, task 0 is added and processed using server 2 until second 1.
// - At second 1, server 2 becomes free. Task 1 is added and processed using server 2 until second 3.
// - At second 2, task 2 is added and processed using server 0 until second 5.
// - At second 3, server 2 becomes free. Task 3 is added and processed using server 2 until second 5.
// - At second 4, task 4 is added and processed using server 1 until second 5.
// - At second 5, all servers become free. Task 5 is added and processed using server 2 until second 7.
//
// Constraints:
// servers.length == n
// 	tasks.length == m
// 	1 <= n, m <= 2 * 105
// 	1 <= servers[i], tasks[j] <= 2 * 105
//
// Helpful references (internal KB):
// - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
//   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
//   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
//   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
//   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
//   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Minimum spanning tree - Prim's algorithm (graph, mst-prim, greedy)
//   • When to use: Use Prim's algorithm to find a minimum spanning tree in a connected, undirected, weighted graph. It is often preferred for dense graphs due to its O(V^2) or O(E log V) complexity.
//   • Idea: Prim's algorithm is a greedy algorithm that builds a minimum spanning tree by iteratively adding the cheapest edge connecting a vertex in the growing tree to one outside it. It typically runs in O(E log V) time with a binary heap or O(V^2) with an adjacency matrix.
//   • Invariants: The set of vertices already included in the MST forms a connected component.; For any vertex not yet in the MST, its associated key/distance stores the minimum weight of an edge connecting it to a vertex already in the MST.
//   • Tips: Use a priority queue to efficiently retrieve the minimum weight edge connecting to the MST.; Initialize distances for all vertices to infinity, except the starting vertex (0).
//   • Pitfalls: Not suitable for disconnected graphs; it will only find an MST for the component of the starting vertex.; Forgetting to handle edge cases like graphs with no edges or a single vertex.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* assignTasks(int* servers, int serversSize, int* tasks, int tasksSize, int* returnSize) {
    #define MAX_HEAP_SIZE 200005
    #define HEAP_PARENT(i) (((i) - 1) / 2)
    #define HEAP_LEFT(i) (2 * (i) + 1)
    #define HEAP_RIGHT(i) (2 * (i) + 2)

    typedef struct {
        int weight;
        int index;
    } Server;

    typedef struct {
        int freeTime;
        Server server;
    } BusyServer;

    typedef struct {
        Server data[MAX_HEAP_SIZE];
        int size;
    } MinHeap;

    typedef struct {
        BusyServer data[MAX_HEAP_SIZE];
        int size;
    } BusyMinHeap;

    void heapifyUp(MinHeap* heap, int index) {
        while (index > 0) {
            int parent = HEAP_PARENT(index);
            if (heap->data[index].weight < heap->data[parent].weight ||
                (heap->data[index].weight == heap->data[parent].weight &&
                 heap->data[index].index < heap->data[parent].index)) {
                Server temp = heap->data[index];
                heap->data[index] = heap->data[parent];
                heap->data[parent] = temp;
                index = parent;
            } else {
                break;
            }
        }
    }
    void heapifyDown(MinHeap* heap, int index) {
        while (1) {
            int left = HEAP_LEFT(index);
            int right = HEAP_RIGHT(index);
            int smallest = index;

            if (left < heap->size &&
                (heap->data[left].weight < heap->data[smallest].weight ||
                 (heap->data[left].weight == heap->data[smallest].weight &&
                  heap->data[left].index < heap->data[smallest].index))) {
                smallest = left;
            }
            if (right < heap->size &&
                (heap->data[right].weight < heap->data[smallest].weight ||
                 (heap->data[right].weight == heap->data[smallest].weight &&
                  heap->data[right].index < heap->data[smallest].index))) {
                smallest = right;
            }
            if (smallest != index) {
                Server temp = heap->data[index];
                heap->data[index] = heap->data[smallest];
                heap->data[smallest] = temp;
                index = smallest;
            } else {
                break;
            }
        }
    }
    void heapPush(MinHeap* heap, Server server) {
        heap->data[heap->size] = server;
        heap->size++;
        heapifyUp(heap->size - 1);
    }
    Server heapPop(MinHeap* heap) {
        Server top = heap->data[0];
        heap->data[0] = heap->data[heap->size - 1];
        heap->size--;
        heapifyDown(heap, 0);
        return top;
    }
    void busyHeapifyUp(BusyMinHeap* heap, int index) {
        while (index > 0) {
            int parent = HEAP_PARENT(index);
            if (heap->data[index].freeTime < heap->data[parent].freeTime) {
                BusyServer temp = heap->data[index];
                heap->data[index] = heap->data[parent];
                heap->data[parent] = temp;
                index = parent;
            } else {
                break;
            }
        }
    }
    void busyHeapifyDown(BusyMinHeap* heap, int index) {
        while (1) {
            int left = HEAP_LEFT(index);
            int right = HEAP_RIGHT(index);
            int smallest = index;

            if (left < heap->size &&
                heap->data[left].freeTime < heap->data[smallest].freeTime) {
                smallest = left;
            }
            if (right < heap->size &&
                heap->data[right].freeTime < heap->data[smallest].freeTime) {
                smallest = right;
            }
            if (smallest != index) {
                BusyServer temp = heap->data[index];
                heap->data[index] = heap->data[smallest];
                heap->data[smallest] = temp;
                index = smallest;
            } else {
                break;
            }
        }
    }
    void busyHeapPush(BusyMinHeap* heap, BusyServer busyServer) {
        heap->data[heap->size] = busyServer;
        heap->size++;
        busyHeapifyUp(heap, heap->size - 1);
    }
    BusyServer busyHeapPop(BusyMinHeap* heap) {
        BusyServer top = heap->data[0];
        heap->data[0] = heap->data[heap->size - 1];
        heap->size--;
        busyHeapifyDown(heap, 0);
        return top;
    }
    MinHeap freeServers = { .size = 0 };
    BusyMinHeap busyServers = { .size = 0 };
    for (int i = 0; i < serversSize; i++) {
        Server server = { servers[i], i };
        heapPush(&freeServers, server);
    }
    int* result = (int*)malloc(tasksSize * sizeof(int));
    long long currentTime = 0;
    for (int i = 0; i < tasksSize; i++) {
        currentTime = i > currentTime ? i : currentTime;

        // Free up servers that have completed their tasks by currentTime
        while (busyServers.size > 0 && busyServers.data[0].freeTime <= currentTime) {
            BusyServer freedServer = busyHeapPop(&busyServers);
            heapPush(&freeServers, freedServer.server);
        }

        // If no free servers, wait for the next server to become free
        if (freeServers.size == 0) {
            BusyServer nextFree = busyHeapPop(&busyServers);
            currentTime = nextFree.freeTime;
            heapPush(&freeServers, nextFree.server);

            // Free up any other servers that have also become free by currentTime
            while (busyServers.size > 0 && busyServers.data[0].freeTime <= currentTime) {
                BusyServer freedServer = busyHeapPop(&busyServers);
                heapPush(&freeServers, freedServer.server);
            }
        }

        // Assign the task to the best available server
        Server assignedServer = heapPop(&freeServers);
        result[i] = assignedServer.index;
        BusyServer busyServer = { currentTime + tasks[i], assignedServer };
        busyHeapPush(&busyServers, busyServer);
    }
    *returnSize = tasksSize;
    return result;
}
