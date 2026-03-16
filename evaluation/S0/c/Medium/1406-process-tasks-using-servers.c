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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* assignTasks(int* servers, int serversSize, int* tasks, int tasksSize, int* returnSize) {
    // Min-heap implementation for servers based on (weight, index)
    typedef struct {
        int weight;
        int index;
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
            if (heap->data[index].weight < heap->data[parent].weight ||
                (heap->data[index].weight == heap->data[parent].weight && heap->data[index].index < heap->data[parent].index)) {
                swap(&heap->data[index], &heap->data[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }
    void heapifyDown(MinHeap* heap, int index) {
        while (index * 2 + 1 < heap->size) {
            int left = index * 2 + 1;
            int right = index * 2 + 2;
            int smallest = left;

            if (right < heap->size &&
                (heap->data[right].weight < heap->data[left].weight ||
                 (heap->data[right].weight == heap->data[left].weight && heap->data[right].index < heap->data[left].index))) {
                smallest = right;
            }

            if (heap->data[index].weight > heap->data[smallest].weight ||
                (heap->data[index].weight == heap->data[smallest].weight && heap->data[index].index > heap->data[smallest].index)) {
                swap(&heap->data[index], &heap->data[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }
    void push(MinHeap* heap, Server server) {
        if (heap->size == heap->capacity) return;
        heap->data[heap->size] = server;
        heapifyUp(heap, heap->size);
        heap->size++;
    }
    Server pop(MinHeap* heap) {
        Server ret = heap->data[0];
        heap->data[0] = heap->data[--heap->size];
        heapifyDown(heap, 0);
        return ret;
    }
    // Min-heap implementation for busy servers based on (free_time, weight, index)
    typedef struct {
        long free_time;
        int weight;
        int index;
    } BusyServer;
    typedef struct {
        BusyServer* data;
        int size;
        int capacity;
    } BusyMinHeap;
    BusyMinHeap* createBusyHeap(int capacity) {
        BusyMinHeap* heap = (BusyMinHeap*)malloc(sizeof(BusyMinHeap));
        heap->data = (BusyServer*)malloc(sizeof(BusyServer) * capacity);
        heap->size = 0;
        heap->capacity = capacity;
        return heap;
    }
    void swapBusy(BusyServer* a, BusyServer* b) {
        BusyServer temp = *a;
        *a = *b;
        *b = temp;
    }
    void busyHeapifyUp(BusyMinHeap* heap, int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap->data[index].free_time < heap->data[parent].free_time ||
                (heap->data[index].free_time == heap->data[parent].free_time &&
                 (heap->data[index].weight < heap->data[parent].weight ||
                  (heap->data[index].weight == heap->data[parent].weight &&
                   heap->data[index].index < heap->data[parent].index)))) {
                swapBusy(&heap->data[index], &heap->data[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }
    void busyHeapifyDown(BusyMinHeap* heap, int index) {
        while (index * 2 + 1 < heap->size) {
            int left = index * 2 + 1;
            int right = index * 2 + 2;
            int smallest = left;

            if (right < heap->size &&
                (heap->data[right].free_time < heap->data[left].free_time ||
                 (heap->data[right].free_time == heap->data[left].free_time &&
                  (heap->data[right].weight < heap->data[left].weight ||
                   (heap->data[right].weight == heap->data[left].weight &&
                    heap->data[right].index < heap->data[left].index))))) {
                smallest = right;
            }

            if (heap->data[index].free_time > heap->data[smallest].free_time ||
                (heap->data[index].free_time == heap->data[smallest].free_time &&
                 (heap->data[index].weight > heap->data[smallest].weight ||
                  (heap->data[index].weight == heap->data[smallest].weight &&
                   heap->data[index].index > heap->data[smallest].index)))) {
                swapBusy(&heap->data[index], &heap->data[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }
    void pushBusy(BusyMinHeap* heap, BusyServer server) {
        if (heap->size == heap->capacity) return;
        heap->data[heap->size] = server;
        busyHeapifyUp(heap, heap->size);
        heap->size++;
    }
    BusyServer popBusy(BusyMinHeap* heap) {
        BusyServer ret = heap->data[0];
        heap->data[0] = heap->data[--heap->size];
        busyHeapifyDown(heap, 0);
        return ret;
    }
    // Initialize free servers heap
    MinHeap* freeServers = createHeap(serversSize);
    for (int i = 0; i < serversSize; i++) {
        Server server = {servers[i], i};
        push(freeServers, server);
    }
    // Initialize busy servers heap
    BusyMinHeap* busyServers = createBusyHeap(serversSize);
    int* result = (int*)malloc(sizeof(int) * tasksSize);
    long currentTime = 0;
    for (int i = 0; i < tasksSize; i++) {
        currentTime = (currentTime > i) ? currentTime : i;

        // Free up servers that have completed their tasks by currentTime
        while (busyServers->size > 0 && busyServers->data[0].free_time <= currentTime) {
            BusyServer busyServer = popBusy(busyServers);
            Server server = {busyServer.weight, busyServer.index};
            push(freeServers, server);
        }

        // If no free servers, advance time to the next server free time
        if (freeServers->size == 0) {
            BusyServer nextFree = popBusy(busyServers);
            currentTime = nextFree.free_time;
            Server server = {nextFree.weight, nextFree.index};
            push(freeServers, server);

            // Free up any other servers that are now free
            while (busyServers->size > 0 && busyServers->data[0].free_time <= currentTime) {
                BusyServer busyServer = popBusy(busyServers);
                Server srv = {busyServer.weight, busyServer.index};
                push(freeServers, srv);
            }
        }

        // Assign the task to the best available server
        Server assignedServer = pop(freeServers);
        result[i] = assignedServer.index;
        BusyServer busyServer = {currentTime + tasks[i], assignedServer.weight, assignedServer.index};
        pushBusy(busyServers, busyServer);
    }
    *returnSize = tasksSize;
    // Free heaps
    free(freeServers->data);
    free(freeServers);
    free(busyServers->data);
    free(busyServers);
    return result;
}
