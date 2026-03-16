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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* busiestServers(int k, int* arrival, int arrivalSize, int* load, int loadSize, int* returnSize) {
    // Min-heap structure for busy servers
    typedef struct {
        int endTime;
        int serverId;
    } HeapNode;

    typedef struct {
        HeapNode* data;
        int size;
        int capacity;
    } MinHeap;

    MinHeap* createHeap(int capacity) {
        MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
        heap->data = (HeapNode*)malloc(sizeof(HeapNode) * capacity);
        heap->size = 0;
        heap->capacity = capacity;
        return heap;
    }

    void swap(HeapNode* a, HeapNode* b) {
        HeapNode temp = *a;
        *a = *b;
        *b = temp;
    }

    void heapifyUp(MinHeap* heap, int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap->data[parent].endTime <= heap->data[index].endTime) break;
            swap(&heap->data[parent], &heap->data[index]);
            index = parent;
        }
    }

    void heapifyDown(MinHeap* heap, int index) {
        while (index < heap->size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < heap->size && heap->data[left].endTime < heap->data[smallest].endTime) {
                smallest = left;
            }
            if (right < heap->size && heap->data[right].endTime < heap->data[smallest].endTime) {
                smallest = right;
            }
            if (smallest == index) break;
            swap(&heap->data[smallest], &heap->data[index]);
            index = smallest;
        }
    }

    void push(MinHeap* heap, int endTime, int serverId) {
        if (heap->size == heap->capacity) return; // Heap is full
        heap->data[heap->size].endTime = endTime;
        heap->data[heap->size].serverId = serverId;
        heapifyUp(heap, heap->size);
        heap->size++;
    }

    HeapNode pop(MinHeap* heap) {
        HeapNode root = heap->data[0];
        heap->data[0] = heap->data[--heap->size];
        heapifyDown(heap, 0);
        return root;
    }
    int isEmpty(MinHeap* heap) {
        return heap->size == 0;
    }
    // Initialize data structures
    MinHeap* busyHeap = createHeap(arrivalSize);
    int* requestCount = (int*)calloc(k, sizeof(int));
    int maxRequests = 0;
    int* availableServers = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        availableServers[i] = i;
    }
    int availableSize = k;
    // Process each request
    for (int i = 0; i < arrivalSize; i++) {
        int currentTime = arrival[i];
        // Free up servers that have completed their tasks
        while (!isEmpty(busyHeap) && busyHeap->data[0].endTime <= currentTime) {
            HeapNode node = pop(busyHeap);
            availableServers[availableSize++] = node.serverId;
        }
        if (availableSize == 0) {
            // All servers are busy, drop the request
            continue;
        }
        // Find the server to handle the request
        int serverIndex = i % k;
        int chosenServer = -1;
        for (int j = 0; j < availableSize; j++) {
            if (availableServers[j] >= serverIndex) {
                chosenServer = availableServers[j];
                // Remove chosen server from available list
                availableServers[j] = availableServers[--availableSize];
                break;
            }
        }
        if (chosenServer == -1) {
            // Wrap around to find the next available server
            chosenServer = availableServers[0];
            availableServers[0] = availableServers[--availableSize];
        }
        // Assign the request to the chosen server
        push(busyHeap, currentTime + load[i], chosenServer);
        requestCount[chosenServer]++;
        if (requestCount[chosenServer] > maxRequests) {
            maxRequests = requestCount[chosenServer];
        }
    }
    // Collect the busiest servers
    int* result = (int*)malloc(k * sizeof(int));
    *returnSize = 0;
    for (int i = 0; i < k; i++) {
        if (requestCount[i] == maxRequests) {
            result[(*returnSize)++] = i;
        }
    }
    // Cleanup
    free(busyHeap->data);
    free(busyHeap);
    free(requestCount);
    free(availableServers);
    return result;
}