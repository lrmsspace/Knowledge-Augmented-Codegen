// Source: https://leetcode.com/problems/single-threaded-cpu/   |   Difficulty: Medium
//
// Problem Description:
// You are given n​​​​​​ tasks labeled from 0 to n - 1 represented by a 2D integer array tasks, where tasks[i] = [enqueueTimei, processingTimei] means that the i​​​​​​th​​​​ task will be available to process at enqueueTimei and will take processingTimei to finish processing.
//
// You have a single-threaded CPU that can process at most one task at a time and will act in the following way:
//
//
// 	If the CPU is idle and there are no available tasks to process, the CPU remains idle.
// 	If the CPU is idle and there are available tasks, the CPU will choose the one with the shortest processing time. If multiple tasks have the same shortest processing time, it will choose the task with the smallest index.
// 	Once a task is started, the CPU will process the entire task without stopping.
// 	The CPU can finish a task then start a new one instantly.
//
//
// Return the order in which the CPU will process the tasks.
//
// Example:
// Input: tasks = [[1,2],[2,4],[3,2],[4,1]]
// Output: [0,2,3,1]
// Explanation: The events go as follows: 
// - At time = 1, task 0 is available to process. Available tasks = {0}.
// - Also at time = 1, the idle CPU starts processing task 0. Available tasks = {}.
// - At time = 2, task 1 is available to process. Available tasks = {1}.
// - At time = 3, task 2 is available to process. Available tasks = {1, 2}.
// - Also at time = 3, the CPU finishes task 0 and starts processing task 2 as it is the shortest. Available tasks = {1}.
// - At time = 4, task 3 is available to process. Available tasks = {1, 3}.
// - At time = 5, the CPU finishes task 2 and starts processing task 3 as it is the shortest. Available tasks = {1}.
// - At time = 6, the CPU finishes task 3 and starts processing task 1. Available tasks = {}.
// - At time = 10, the CPU finishes task 1 and becomes idle.
//
// Constraints:
// tasks.length == n
// 	1 <= n <= 105
// 	1 <= enqueueTimei, processingTimei <= 109
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getOrder(int** tasks, int tasksSize, int* tasksColSize, int* returnSize) {
    typedef struct {
        int index;
        int enqueueTime;
        int processingTime;
    } Task;

    int cmpTask(const void* a, const void* b) {
        Task* taskA = (Task*)a;
        Task* taskB = (Task*)b;
        if (taskA->enqueueTime != taskB->enqueueTime) {
            return taskA->enqueueTime - taskB->enqueueTime;
        }
        return taskA->index - taskB->index;
    }

    Task* taskList = (Task*)malloc(tasksSize * sizeof(Task));
    for (int i = 0; i < tasksSize; i++) {
        taskList[i].index = i;
        taskList[i].enqueueTime = tasks[i][0];
        taskList[i].processingTime = tasks[i][1];
    }

    qsort(taskList, tasksSize, sizeof(Task), cmpTask);

    typedef struct {
        int index;
        int processingTime;
    } HeapNode;

    typedef struct {
        HeapNode* data;
        int size;
        int capacity;
    } MinHeap;

    MinHeap* createMinHeap(int capacity) {
        MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
        heap->data = (HeapNode*)malloc(capacity * sizeof(HeapNode));
        heap->size = 0;
        heap->capacity = capacity;
        return heap;
    }

    void swap(HeapNode* a, HeapNode* b) {
        HeapNode temp = *a;
        *a = *b;
        *b = temp;
    }

    void minHeapifyUp(MinHeap* heap, int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap->data[index].processingTime < heap->data[parent].processingTime ||
                (heap->data[index].processingTime == heap->data[parent].processingTime &&
                 heap->data[index].index < heap->data[parent].index)) {
                swap(&heap->data[index], &heap->data[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void minHeapifyDown(MinHeap* heap, int index) {
        while (2 * index + 1 < heap->size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = left;

            if (right < heap->size &&
                (heap->data[right].processingTime < heap->data[left].processingTime ||
                 (heap->data[right].processingTime == heap->data[left].processingTime &&
                  heap->data[right].index < heap->data[left].index))) {
                smallest = right;
            }

            if (heap->data[index].processingTime > heap->data[smallest].processingTime ||
                (heap->data[index].processingTime == heap->data[smallest].processingTime &&
                 heap->data[index].index > heap->data[smallest].index)) {
                swap(&heap->data[index], &heap->data[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }   
    void minHeapPush(MinHeap* heap, HeapNode node) {
        if (heap->size == heap->capacity) return;
        heap->data[heap->size] = node;
        minHeapifyUp(heap, heap->size);
        heap->size++;
    }
    HeapNode minHeapPop(MinHeap* heap) {
        HeapNode ret = heap->data[0];
        heap->data[0] = heap->data[--heap->size];
        minHeapifyDown(heap, 0);
        return ret;
    }
    MinHeap* minHeap = createMinHeap(tasksSize);
    int* result = (int*)malloc(tasksSize * sizeof(int));
    int resultIndex = 0;
    long long currentTime = 0;
    int taskIndex = 0;
    while (resultIndex < tasksSize) {
        while (taskIndex < tasksSize && taskList[taskIndex].enqueueTime <= currentTime) {
            HeapNode node;
            node.index = taskList[taskIndex].index;
            node.processingTime = taskList[taskIndex].processingTime;
            minHeapPush(minHeap, node);
            taskIndex++;
        }

        if (minHeap->size > 0) {
            HeapNode nextTask = minHeapPop(minHeap);
            result[resultIndex++] = nextTask.index;
            currentTime += nextTask.processingTime;
        } else {
            currentTime = taskList[taskIndex].enqueueTime;
        }
    }
    *returnSize = tasksSize;
    free(taskList);
    free(minHeap->data);
    free(minHeap);
    return result;
}
