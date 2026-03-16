// Source: https://leetcode.com/problems/maximum-average-pass-ratio/   |   Difficulty: Medium
//
// Problem Description:
// There is a school that has classes of students and each class will be having a final exam. You are given a 2D integer array classes, where classes[i] = [passi, totali]. You know beforehand that in the ith class, there are totali total students, but only passi number of students will pass the exam.
//
// You are also given an integer extraStudents. There are another extraStudents brilliant students that are guaranteed to pass the exam of any class they are assigned to. You want to assign each of the extraStudents students to a class in a way that maximizes the average pass ratio across all the classes.
//
// The pass ratio of a class is equal to the number of students of the class that will pass the exam divided by the total number of students of the class. The average pass ratio is the sum of pass ratios of all the classes divided by the number of the classes.
//
// Return the maximum possible average pass ratio after assigning the extraStudents students. Answers within 10-5 of the actual answer will be accepted.
//
// Example:
// Input: classes = [[1,2],[3,5],[2,2]], extraStudents = 2
// Output: 0.78333
// Explanation: You can assign the two extra students to the first class. The average pass ratio will be equal to (3/4 + 3/5 + 2/2) / 3 = 0.78333.
//
// Constraints:
// 1 <= classes.length <= 105
// 	classes[i].length == 2
// 	1 <= passi <= totali <= 105
// 	1 <= extraStudents <= 105
//

double maxAverageRatio(int** classes, int classesSize, int* classesColSize, int extraStudents) {
    typedef struct {
        double diff;
        int pass;
        int total;
    } HeapNode;

    typedef struct {
        HeapNode* data;
        int size;
        int capacity;
    } MaxHeap;

    MaxHeap* createHeap(int capacity) {
        MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
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

    void heapifyUp(MaxHeap* heap, int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap->data[index].diff > heap->data[parent].diff) {
                swap(&heap->data[index], &heap->data[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(MaxHeap* heap, int index) {
        int left, right, largest;
        while (1) {
            left = 2 * index + 1;
            right = 2 * index + 2;
            largest = index;

            if (left < heap->size && heap->data[left].diff > heap->data[largest].diff) {
                largest = left;
            }
            if (right < heap->size && heap->data[right].diff > heap->data[largest].diff) {
                largest = right;
            }
            if (largest != index) {
                swap(&heap->data[index], &heap->data[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

    void insert(MaxHeap* heap, HeapNode node) {
        if (heap->size == heap->capacity) return; // Heap is full
        heap->data[heap->size] = node;
        heapifyUp(heap, heap->size);
        heap->size++;
    }

    HeapNode extractMax(MaxHeap* heap) {
        if (heap->size == 0) {
            HeapNode empty = {0, 0, 0};
            return empty; // Heap is empty
        }
        HeapNode maxNode = heap->data[0];
        heap->data[0] = heap->data[--heap->size];
        heapifyDown(heap, 0);
        return maxNode;
    }
    MaxHeap* heap = createHeap(classesSize);
    for (int i = 0; i < classesSize; i++) {
        int pass = classes[i][0];
        int total = classes[i][1];
        double currRatio = (double)pass / total;
        double newRatio = (double)(pass + 1) / (total + 1);
        double diff = newRatio - currRatio;
        insert(heap, (HeapNode){diff, pass, total});
    }
    for (int i = 0; i < extraStudents; i++) {
        HeapNode node = extractMax(heap);
        node.pass += 1;
        node.total += 1;
        double currRatio = (double)(node.pass - 1) / (node.total - 1);
        double newRatio = (double)(node.pass) / (node.total);
        node.diff = newRatio - currRatio;
        insert(heap, node);
    }
    double totalRatio = 0.0;
    for (int i = 0; i < heap->size; i++) {
        totalRatio += (double)heap->data[i].pass / heap->data[i].total;
    }
    return totalRatio / classesSize;
}
