// Source: https://leetcode.com/problems/find-servers-that-handled-most-number-of-requests/   |   Difficulty: Hard
//
// Problem Description:
// You have k servers numbered from 0 to k-1 that are being used to handle multiple requests simultaneously. Each server has infinite computational capacity but cannot handle more than one request at a time. The requests are assigned to servers according to a specific algorithm:
//
//
// 	The ith (0-indexed) request arrives.
// 	If all servers are busy, the request is dropped (not handled at all).
// 	If the (i % k)th server is available, assign the request to that server.
// 	Otherwise, assign the request to the next available server (wrapping around the list of servers and starting from 0 if necessary). For example, if the ith server is busy, try to assign the request to the (i+1)th server, then the (i+2)th server, and so on.
//
//
// You are given a strictly increasing array arrival of positive integers, where arrival[i] represents the arrival time of the ith request, and another array load, where load[i] represents the load of the ith request (the time it takes to complete). Your goal is to find the busiest server(s). A server is considered busiest if it handled the most number of requests successfully among all the servers.
//
// Return a list containing the IDs (0-indexed) of the busiest server(s). You may return the IDs in any order.
//
// Example:
// Input: k = 3, arrival = [1,2,3,4,5], load = [5,2,3,3,3] 
// Output: [1] 
// Explanation: 
// All of the servers start out available.
// The first 3 requests are handled by the first 3 servers in order.
// Request 3 comes in. Server 0 is busy, so it's assigned to the next available server, which is 1.
// Request 4 comes in. It cannot be handled since all servers are busy, so it is dropped.
// Servers 0 and 2 handled one request each, while server 1 handled two requests. Hence server 1 is the busiest server.
//
// Constraints:
// 1 <= k <= 105
// 	1 <= arrival.length, load.length <= 105
// 	arrival.length == load.length
// 	1 <= arrival[i], load[i] <= 109
// 	arrival is strictly increasing.
//
// Helpful references (internal KB):
// - Priority Queues (array, heap, heap-select)
//   • When to use: Use when you need to efficiently retrieve the highest or lowest priority item from a dynamic collection. It's ideal for scenarios requiring frequent insertions and extractions of extreme values without full sorting.
//   • Idea: A Priority Queue is an abstract data type that provides efficient retrieval of the maximum or minimum element. It is typically implemented using a binary heap, which stores elements in an array representing a complete binary tree, maintaining the heap-ordered property for O(log N) insertion and deletion.
//   • Invariants: For a max-heap, every parent node's key is greater than or equal to its children's keys.; The heap structure is always a complete binary tree, represented contiguously in an array.
//   • Tips: Represent the complete binary tree using an array, often 1-indexed for simpler parent/child calculations.; Use 'swim' (bottom-up reheapify) after insertion to restore heap order.
//   • Pitfalls: Forgetting to handle 0-indexed vs 1-indexed array representations correctly (parent/child formulas differ).; Violating the heap-ordered property during updates or custom operations.
// - Scheduling jobs on two machines (array, number, simulation, enumeration)
//   • When to use: Use when determining the optimal sequence of jobs to minimize the total completion time (makespan) on two machines, with a fixed processing order (machine 1 then machine 2) for all jobs.
//   • Idea: This problem involves ordering N jobs, each with two processing times (one for each machine), to minimize the overall makespan. Johnson's rule provides an optimal greedy solution for this specific two-machine flow shop problem in O(N log N) or O(N) time.
//   • Invariants: All jobs processed so far maintain the optimal relative order determined by Johnson's rule.; The current makespan is the minimum possible for the jobs already scheduled.
//   • Tips: Sort jobs based on Johnson's rule criteria: jobs with min(a_i, b_i).; Prioritize jobs with shorter machine 1 times or longer machine 2 times for early scheduling.
//   • Pitfalls: Applying Johnson's rule to problems with more than two machines, where it is not optimal.; Incorrectly sorting jobs within the two partitioned sets.
// - Minimum stack / Minimum queue (queue, stack, simulation)
//   • When to use: Use when needing to efficiently query the minimum element of a stack or queue in O(1) average time. Also applicable for finding minimums in all fixed-length subarrays using a sliding window.
//   • Idea: This technique augments a stack or queue to support O(1) average time retrieval of its minimum element, typically by storing minimums alongside data or using auxiliary structures. It achieves amortized constant time for all operations.
//   • Invariants: For a minimum stack, the auxiliary minimum stack's top element is always the minimum of all elements currently in the main stack.; For a minimum queue implemented with two stacks, the output stack is only refilled from the input stack when the output stack becomes empty.
//   • Tips: For a minimum stack, use an auxiliary stack to store minimums encountered so far.; Only push to the auxiliary minimum stack if the new element is less than or equal to its current top.
//   • Pitfalls: Forgetting to pop from the auxiliary minimum stack when the main stack's top is removed.; Incorrectly handling the transfer logic between the two stacks for a minimum queue.
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
int* busiestServers(int k, int* arrival, int arrivalSize, int* load, int loadSize, int* returnSize) {
    // Min-heap implementation for managing server availability
    typedef struct {
        int serverId;
        long long freeAt;
    } Server;

    typedef struct {
        Server* data;
        int size;
        int capacity;
    } MinHeap;

    MinHeap* createHeap(int capacity) {
        MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
        heap->data = (Server*)malloc(sizeof(Server) * capacity);
        heap->size = 0;
        heap->capacity = capacity;
        return heap;
    }

    void swap(Server* a, Server* b) {
        Server temp = *a;
        *a = *b;
        *b = temp;
    }

    void heapifyUp(MinHeap* heap, int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap->data[parent].freeAt <= heap->data[index].freeAt) break;
            swap(&heap->data[parent], &heap->data[index]);
            index = parent;
        }
    }

    void heapifyDown(MinHeap* heap, int index) {
        while (2 * index + 1 < heap->size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = left;
            if (right < heap->size && heap->data[right].freeAt < heap->data[left].freeAt) {
                smallest = right;
            }
            if (heap->data[index].freeAt <= heap->data[smallest].freeAt) break;
            swap(&heap->data[index], &heap->data[smallest]);
            index = smallest;
        }
    }

    void push(MinHeap* heap, Server server) {
        if (heap->size == heap->capacity) return; // Heap full
        heap->data[heap->size] = server;
        heapifyUp(heap, heap->size);
        heap->size++;
    }

    Server pop(MinHeap* heap) {
        Server top = heap->data[0];
        heap->data[0] = heap->data[--heap->size];
        heapifyDown(heap, 0);
        return top;
    }

    // Initialize servers
    MinHeap* availableServers = createHeap(k);
    MinHeap* busyServers = createHeap(arrivalSize);
    for (int i = 0; i < k; i++) {
        Server server = {i, 0};
        push(availableServers, server);
    }
    int* requestCount = (int*)calloc(k, sizeof(int));
    for (int i = 0; i < arrivalSize; i++) {
        long long currentTime = arrival[i];
        // Free up busy servers
        while (busyServers->size > 0 && busyServers->data[0].freeAt <= currentTime) {
            Server freedServer = pop(busyServers);
            push(availableServers, freedServer);
        }
        if (availableServers->size == 0) {
            // All servers are busy, drop the request
            continue;
        }
        // Assign request to the appropriate server
        int serverIndex = i % k;
        MinHeap* tempHeap = createHeap(availableServers->capacity);
        Server assignedServer;
        int found = 0;
        while (availableServers->size > 0) {
            Server server = pop(availableServers);
            if (server.serverId >= serverIndex && !found) {
                assignedServer = server;
                found = 1;
                break;
            } else {
                push(tempHeap, server);
            }
        }
        if (!found) {
            // Wrap around to find the next available server
            while (tempHeap->size > 0) {
                Server server = pop(tempHeap);
                if (!found) {
                    assignedServer = server;
                    found = 1;
                    break;
                } else {
                    push(availableServers, server);
                }
            }
        }
        // Restore available servers
        while (tempHeap->size > 0) {
            push(availableServers, pop(tempHeap));
        }
        free(tempHeap->data);
        free(tempHeap);
        // Assign the request to the selected server
        assignedServer.freeAt = currentTime + load[i];
        push(busyServers, assignedServer);
        requestCount[assignedServer.serverId]++;
    }
    // Find the maximum request count
    int maxRequests = 0;
    for (int i = 0; i < k; i++) {
        if (requestCount[i] > maxRequests) {
            maxRequests = requestCount[i];
        }
    }
    // Collect busiest servers
    int* busiestServers = (int*)malloc(k * sizeof(int));
    int busiestCount = 0;
    for (int i = 0; i < k; i++) {
        if (requestCount[i] == maxRequests) {
            busiestServers[busiestCount++] = i;
        }
    }
    *returnSize = busiestCount;
    free(requestCount);
    free(availableServers->data);
    free(availableServers);
    free(busyServers->data);
    free(busyServers);
    return busiestServers;
}
