// Source: https://leetcode.com/problems/the-skyline-problem/   |   Difficulty: Hard
//
// Problem Description:
// A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Given the locations and heights of all the buildings, return the skyline formed by these buildings collectively.
//
// The geometric information of each building is given in the array buildings where buildings[i] = [lefti, righti, heighti]:
//
//
// 	lefti is the x coordinate of the left edge of the ith building.
// 	righti is the x coordinate of the right edge of the ith building.
// 	heighti is the height of the ith building.
//
//
// You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.
//
// The skyline should be represented as a list of "key points" sorted by their x-coordinate in the form [[x1,y1],[x2,y2],...]. Each key point is the left endpoint of some horizontal segment in the skyline except the last point in the list, which always has a y-coordinate 0 and is used to mark the skyline's termination where the rightmost building ends. Any ground between the leftmost and rightmost buildings should be part of the skyline's contour.
//
// Note: There must be no consecutive horizontal lines of equal height in the output skyline. For instance, [...,[2 3],[4 5],[7 5],[11 5],[12 7],...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such: [...,[2 3],[4 5],[12 7],...]
//
// Example:
// Input: buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
// Output: [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
// Explanation:
// Figure A shows the buildings of the input.
// Figure B shows the skyline formed by those buildings. The red points in figure B represent the key points in the output list.
//
// Constraints:
// 1 <= buildings.length <= 104
// 	0 <= lefti < righti <= 231 - 1
// 	1 <= heighti <= 231 - 1
// 	buildings is sorted by lefti in non-decreasing order.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** getSkyline(int** buildings, int buildingsSize, int* buildingsColSize, int* returnSize, int** returnColumnSizes) {
    // Implementation of the skyline problem using a sweep line algorithm with a max-heap
    
    // Define events
    typedef struct {
        int x;
        int height;
        int isStart; // 1 for start of building, 0 for end
    } Event;
    
    Event* events = (Event*)malloc(sizeof(Event) * buildingsSize * 2);
    int eventCount = 0;
    
    for (int i = 0; i < buildingsSize; i++) {
        events[eventCount++] = (Event){buildings[i][0], buildings[i][2], 1}; // Start of building
        events[eventCount++] = (Event){buildings[i][1], buildings[i][2], 0}; // End of building
    }
    
    // Sort events
    int compare(const void* a, const void* b) {
        Event* e1 = (Event*)a;
        Event* e2 = (Event*)b;
        if (e1->x != e2->x) return e1->x - e2->x;
        if (e1->isStart != e2->isStart) return e2->isStart - e1->isStart; // Start before end
        return (e1->isStart ? e2->height - e1->height : e1->height - e2->height); // Higher height first for start, lower height first for end
    }
    
    qsort(events, eventCount, sizeof(Event), compare);
    
    // Max-heap to keep track of heights
    typedef struct {
        int* data;
        int size;
        int capacity;
    } MaxHeap;
    
    MaxHeap* createHeap(int capacity) {
        MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
        heap->data = (int*)malloc(sizeof(int) * capacity);
        heap->size = 0;
        heap->capacity = capacity;
        return heap;
    }
    
    void insert(MaxHeap* heap, int value) {
        if (heap->size == heap->capacity) return; // Heap full
        heap->data[heap->size++] = value;
        int idx = heap->size - 1;
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (heap->data[parent] >= heap->data[idx]) break;
            int temp = heap->data[parent];
            heap->data[parent] = heap->data[idx];
            heap->data[idx] = temp;
            idx = parent;
        }
    }
    
    int extractMax(MaxHeap* heap) {
        if (heap->size == 0) return 0;
        int maxVal = heap->data[0];
        heap->data[0] = heap->data[--heap->size];
        int idx = 0;
        while (1) {
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;
            int largest = idx;
            if (left < heap->size && heap->data[left] > heap->data[largest]) largest = left;
            if (right < heap->size && heap->data[right] > heap->data[largest]) largest = right;
            if (largest == idx) break;
            int temp = heap->data[idx];
            heap->data[idx] = heap->data[largest];
            heap->data[largest] = temp;
            idx = largest;
        }
        return maxVal;
    }
}