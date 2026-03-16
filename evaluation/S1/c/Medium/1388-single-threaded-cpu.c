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
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, especially for large datasets or external sorting where data might not fit in memory.
//   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and requires O(N) auxiliary space.
//   • Invariants: The elements `index[lo...k-1]` are sorted and contain the smallest `k-lo` elements from the original `aux[lo...mid]` and `aux[mid+1...hi]` segments.; Pointer `i` always indicates the next element to consider from the left sorted sub-array (`aux[lo...mid]`).
//   • Tips: Implement the merge step carefully to ensure stability.; Consider an iterative bottom-up approach to avoid recursion overhead.
//   • Pitfalls: High auxiliary space complexity (O(N)) can be a concern for memory-constrained systems.; Recursive calls can lead to stack overflow for very large inputs without tail call optimization.
// - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
//   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
//   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
//   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
//   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
//   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
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
int* getOrder(int** tasks, int tasksSize, int* tasksColSize, int* returnSize) {
    #define MAX_HEAP_SIZE 100005
    #define HEAP_PARENT(i) (((i) - 1) / 2)
    #define HEAP_LEFT(i) (2 * (i) + 1)
    #define HEAP_RIGHT(i) (2 * (i) + 2)

    typedef struct {
        int enqueueTime;
        int processingTime;
        int index;
    } Task;

    typedef struct {
        Task data[MAX_HEAP_SIZE];
        int size;
    } MinHeap;

    void heapifyUp(MinHeap* heap, int index) {
        while (index > 0) {
            int parent = HEAP_PARENT(index);
            if (heap->data[index].processingTime < heap->data[parent].processingTime ||
                (heap->data[index].processingTime == heap->data[parent].processingTime &&
                 heap->data[index].index < heap->data[parent].index)) {
                Task temp = heap->data[index];
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
                (heap->data[left].processingTime < heap->data[smallest].processingTime ||
                 (heap->data[left].processingTime == heap->data[smallest].processingTime &&
                  heap->data[left].index < heap->data[smallest].index))) {
                smallest = left;
            }
            if (right < heap->size &&
                (heap->data[right].processingTime < heap->data[smallest].processingTime ||
                 (heap->data[right].processingTime == heap->data[smallest].processingTime &&
                  heap->data[right].index < heap->data[smallest].index))) {
                smallest = right;
            }
            if (smallest != index) {
                Task temp = heap->data[index];
                heap->data[index] = heap->data[smallest];
                heap->data[smallest] = temp;
                index = smallest;
            } else {
                break;
            }
        }
    }

    void heapPush(MinHeap* heap, Task task) {
        heap->data[heap->size] = task;
        heap->size++;
        heapifyUp(heap, heap->size - 1);
    }
    Task heapPop(MinHeap* heap) {
        Task top = heap->data[0];
        heap->data[0] = heap->data[heap->size - 1];
        heap->size--;
        heapifyDown(heap, 0);
        return top;
    }
    // Augment tasks with their original indices
    Task* augmentedTasks = (Task*)malloc(tasksSize * sizeof(Task));
    for (int i = 0; i < tasksSize; i++) {
        augmentedTasks[i].enqueueTime = tasks[i][0];
        augmentedTasks[i].processingTime = tasks[i][1];
        augmentedTasks[i].index = i;
    }
    // Sort tasks by enqueue time using mergesort
    void merge(Task* arr, int left, int mid, int right, Task* temp) {
        int i = left, j = mid + 1, k = left;
        while (i <= mid && j <= right) {
            if (arr[i].enqueueTime <= arr[j].enqueueTime) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }
        while (i <= mid) {
            temp[k++] = arr[i++];
        }
        while (j <= right) {
            temp[k++] = arr[j++];
        }
        for (i = left; i <= right; i++) {
            arr[i] = temp[i];
        }
    }
    void mergeSort(Task* arr, int left, int right, Task* temp) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid, temp);
            mergeSort(arr, mid + 1, right, temp);
            merge(arr, left, mid, right, temp);
        }
    }
    Task* temp = (Task*)malloc(tasksSize * sizeof(Task));
    mergeSort(augmentedTasks, 0, tasksSize - 1, temp);
    free(temp);
    MinHeap heap = { .size = 0 };
    int* result = (int*)malloc(tasksSize * sizeof(int));
    int resultIdx = 0;
    long long currentTime = 0;
    int taskIdx = 0;
    while (resultIdx < tasksSize) {
        // Add all tasks that have become available by currentTime
        while (taskIdx < tasksSize && augmentedTasks[taskIdx].enqueueTime <= currentTime) {
            heapPush(&heap, augmentedTasks[taskIdx]);
            taskIdx++;
        }
        if (heap.size > 0) {
            // Process the next task
            Task nextTask = heapPop(&heap);
            result[resultIdx++] = nextTask.index;
            currentTime += nextTask.processingTime;
        } else {
            // No available tasks, jump to the next task's enqueue time
            currentTime = augmentedTasks[taskIdx].enqueueTime;
        }
    }
    free(augmentedTasks);
    *returnSize = tasksSize;
    return result;
}
