// Source: https://leetcode.com/problems/ipo/   |   Difficulty: Hard
//
// Problem Description:
// Suppose LeetCode will start its IPO soon. In order to sell a good price of its shares to Venture Capital, LeetCode would like to work on some projects to increase its capital before the IPO. Since it has limited resources, it can only finish at most k distinct projects before the IPO. Help LeetCode design the best way to maximize its total capital after finishing at most k distinct projects.
//
// You are given n projects where the ith project has a pure profit profits[i] and a minimum capital of capital[i] is needed to start it.
//
// Initially, you have w capital. When you finish a project, you will obtain its pure profit and the profit will be added to your total capital.
//
// Pick a list of at most k distinct projects from given projects to maximize your final capital, and return the final maximized capital.
//
// The answer is guaranteed to fit in a 32-bit signed integer.
//
// Example:
// Input: k = 2, w = 0, profits = [1,2,3], capital = [0,1,1]
// Output: 4
// Explanation: Since your initial capital is 0, you can only start the project indexed 0.
// After finishing it you will obtain profit 1 and your capital becomes 1.
// With capital 1, you can either start the project indexed 1 or the project indexed 2.
// Since you can choose at most 2 projects, you need to finish the project indexed 2 to get the maximum capital.
// Therefore, output the final maximized capital, which is 0 + 1 + 3 = 4.
//
// Constraints:
// 1 <= k <= 105
// 	0 <= w <= 109
// 	n == profits.length
// 	n == capital.length
// 	1 <= n <= 105
// 	0 <= profits[i] <= 104
// 	0 <= capital[i] <= 109
//
// Helpful references (internal KB):
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - Mergesort (array, merge-sort, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, especially for large datasets or external sorting where data might not fit in memory.
//   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and requires O(N) auxiliary space.
//   • Invariants: The elements `index[lo...k-1]` are sorted and contain the smallest `k-lo` elements from the original `aux[lo...mid]` and `aux[mid+1...hi]` segments.; Pointer `i` always indicates the next element to consider from the left sorted sub-array (`aux[lo...mid]`).
//   • Tips: Implement the merge step carefully to ensure stability.; Consider an iterative bottom-up approach to avoid recursion overhead.
//   • Pitfalls: High auxiliary space complexity (O(N)) can be a concern for memory-constrained systems.; Recursive calls can lead to stack overflow for very large inputs without tail call optimization.
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int findMaximizedCapital(int k, int w, int* profits, int profitsSize, int* capital, int capitalSize) {
    // Min-heap for capital requirements
    typedef struct {
        int capital;
        int profit;
    } Project;

    typedef struct {
        Project* data;
        int size;
        int capacity;
    } MinHeap;

    MinHeap* createMinHeap(int capacity) {
        MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
        heap->data = (Project*)malloc(sizeof(Project) * capacity);
        heap->size = 0;
        heap->capacity = capacity;
        return heap;
    }

    void minHeapPush(MinHeap* heap, Project proj) {
        if (heap->size >= heap->capacity) return; // Overflow
        heap->data[heap->size++] = proj;
        int i = heap->size - 1;
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (heap->data[parent].capital <= heap->data[i].capital) break;
            Project temp = heap->data[parent];
            heap->data[parent] = heap->data[i];
            heap->data[i] = temp;
            i = parent;
        }
    }

    Project minHeapPop(MinHeap* heap) {
        Project root = heap->data[0];
        heap->data[0] = heap->data[--heap->size];
        int i = 0;
        while (1) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;
            if (left < heap->size && heap->data[left].capital < heap->data[smallest].capital)
                smallest = left;
            if (right < heap->size && heap->data[right].capital < heap->data[smallest].capital)
                smallest = right;
            if (smallest == i) break;
            Project temp = heap->data[i];
            heap->data[i] = heap->data[smallest];
            heap->data[smallest] = temp;
            i = smallest;
        }
        return root;
    }

    // Max-heap for profits
    typedef struct {
        int* data;
        int size;
        int capacity;
    } MaxHeap;
    MaxHeap* createMaxHeap(int capacity) {
        MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
        heap->data = (int*)malloc(sizeof(int) * capacity);
        heap->size = 0;
        heap->capacity = capacity;
        return heap;
    }
    void maxHeapPush(MaxHeap* heap, int val) {
        if (heap->size >= heap->capacity) return; // Overflow
        heap->data[heap->size++] = val;
        int i = heap->size - 1;
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (heap->data[parent] >= heap->data[i]) break;
            int temp = heap->data[parent];
            heap->data[parent] = heap->data[i];
            heap->data[i] = temp;
            i = parent;
        }
    }
    int maxHeapPop(MaxHeap* heap) {
        int root = heap->data[0];
        heap->data[0] = heap->data[--heap->size];
        int i = 0;
        while (1) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int largest = i;
            if (left < heap->size && heap->data[left] > heap->data[largest])
                largest = left;
            if (right < heap->size && heap->data[right] > heap->data[largest])
                largest = right;
            if (largest == i) break;
            int temp = heap->data[i];
            heap->data[i] = heap->data[largest];
            heap->data[largest] = temp;
            i = largest;
        }
        return root;
    }
    // Initialize min-heap with all projects
    MinHeap* capitalHeap = createMinHeap(profitsSize);
    for (int i = 0; i < profitsSize; i++) {
        Project proj = {capital[i], profits[i]};
        minHeapPush(capitalHeap, proj);
    }
    MaxHeap* profitHeap = createMaxHeap(profitsSize);
    // Select up to k projects
    for (int i = 0; i < k; i++) {
        // Move all affordable projects to profit max-heap
        while (capitalHeap->size > 0 && capitalHeap->data[0].capital <= w) {
            Project proj = minHeapPop(capitalHeap);
            maxHeapPush(profitHeap, proj.profit);
        }
        // If no projects can be done, break
        if (profitHeap->size == 0) {
            break;
        }
        // Do the most profitable project
        w += maxHeapPop(profitHeap);
    }
    // Cleanup
    free(capitalHeap->data);
    free(capitalHeap);
    free(profitHeap->data);
    free(profitHeap);
    return w;      
}
