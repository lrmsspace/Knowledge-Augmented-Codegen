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

int findMaximizedCapital(int k, int w, int* profits, int profitsSize, int* capital, int capitalSize) {
    typedef struct {
        int profit;
        int capital;
    } Project;

    int cmpProject(const void *a, const void *b) {
        Project *pa = (Project*)a;
        Project *pb = (Project*)b;
        return pa->capital - pb->capital;
    }

    /* Min-heap for profits */
    typedef struct {
        int *data;
        int size;
        int capacity;
    } MinHeap;

    MinHeap* createMinHeap(int capacity) {
        MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
        heap->data = (int*)malloc(sizeof(int) * capacity);
        heap->size = 0;
        heap->capacity = capacity;
        return heap;
    }

    void freeMinHeap(MinHeap *heap) {
        free(heap->data);
        free(heap);
    }

    void minHeapPush(MinHeap *heap, int val) {
        if (heap->size >= heap->capacity) return; // Overflow
        heap->data[heap->size++] = val;
        int i = heap->size - 1;
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (heap->data[parent] <= heap->data[i]) break;
            int temp = heap->data[parent];
            heap->data[parent] = heap->data[i];
            heap->data[i] = temp;
            i = parent;
        }
    }

    int minHeapPop(MinHeap *heap) {
        if (heap->size == 0) return -1; // Underflow
        int root = heap->data[0];
        heap->data[0] = heap->data[--heap->size];
        int i = 0;
        while (1) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;
            if (left < heap->size && heap->data[left] < heap->data[smallest]) {
                smallest = left;
            }
            if (right < heap->size && heap->data[right] < heap->data[smallest]) {
                smallest = right;
            }
            if (smallest == i) break;
            int temp = heap->data[i];
            heap->data[i] = heap->data[smallest];
            heap->data[smallest] = temp;
            i = smallest;
        }
        return root;
    }
    /* Max-heap for profits */
    typedef struct {
        int *data;
        int size;
        int capacity;
    } MaxHeap;
    MaxHeap* createMaxHeap(int capacity) {
        MaxHeap *heap = (MaxHeap*)malloc(sizeof(MaxHeap));
        heap->data = (int*)malloc(sizeof(int) * capacity);
        heap->size = 0;
        heap->capacity = capacity;
        return heap;
    }
    void freeMaxHeap(MaxHeap *heap) {
        free(heap->data);
        free(heap);
    }
    void maxHeapPush(MaxHeap *heap, int val) {
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
    int maxHeapPop(MaxHeap *heap) {
        if (heap->size == 0) return -1; // Underflow
        int root = heap->data[0];
        heap->data[0] = heap->data[--heap->size];
        int i = 0;
        while (1) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int largest = i;
            if (left < heap->size && heap->data[left] > heap->data[largest]) {
                largest = left;
            }
            if (right < heap->size && heap->data[right] > heap->data[largest]) {
                largest = right;
            }
            if (largest == i) break;
            int temp = heap->data[i];
            heap->data[i] = heap->data[largest];
            heap->data[largest] = temp;
            i = largest;
        }
        return root;
    }
    // Create and sort projects by capital
    Project *projects = (Project*)malloc(sizeof(Project) * profitsSize);
    for (int i = 0; i < profitsSize; i++) {
        projects[i].profit = profits[i];
        projects[i].capital = capital[i];
    }
    qsort(projects, profitsSize, sizeof(Project), cmpProject);
    MaxHeap *profitHeap = createMaxHeap(profitsSize);
    int projectIndex = 0;
    for (int i = 0; i < k; i++) {
        // Add all feasible projects to the max-heap
        while (projectIndex < profitsSize && projects[projectIndex].capital <= w) {
            maxHeapPush(profitHeap, projects[projectIndex].profit);
            projectIndex++;
        }
        // If no feasible projects, break
        if (profitHeap->size == 0) {
            break;
        }
        // Select the most profitable project
        w += maxHeapPop(profitHeap);
    }
    free(projects);
    freeMaxHeap(profitHeap);
    return w;
}
