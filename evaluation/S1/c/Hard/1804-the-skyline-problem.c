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
// Helpful references (internal KB):
// - Point location in O(logn) (geometry, sweep-line, enumeration)
//   • When to use: Use when needing to efficiently determine which region or geometric primitive a given query point belongs to within a static set of geometric objects, such as polygons or diagrams.
//   • Idea: This algorithm efficiently locates query points within a geometric structure by processing events along a sweep line. It typically achieves O(log N) query time after an initial preprocessing phase.
//   • Invariants: All events with x-coordinate less than the current sweep line position have been processed.; The active set of edges contains all segments currently intersected by the sweep line, ordered by their y-intercept.
//   • Tips: Sort all event points by x-coordinate, then by event type for consistent processing.; Maintain an ordered data structure (e.g., balanced BST) for active edges intersected by the sweep line.
//   • Pitfalls: Incorrectly handling edge cases like vertical edges or points exactly on edges.; Maintaining the active edge set inefficiently, leading to higher than O(log N) complexity.
// - Priority Queues (array, heap, heap-select)
//   • When to use: Use when you need to efficiently retrieve the highest or lowest priority item from a dynamic collection. It's ideal for scenarios requiring frequent insertions and extractions of extreme values without full sorting.
//   • Idea: A Priority Queue is an abstract data type that provides efficient retrieval of the maximum or minimum element. It is typically implemented using a binary heap, which stores elements in an array representing a complete binary tree, maintaining the heap-ordered property for O(log N) insertion and deletion.
//   • Invariants: For a max-heap, every parent node's key is greater than or equal to its children's keys.; The heap structure is always a complete binary tree, represented contiguously in an array.
//   • Tips: Represent the complete binary tree using an array, often 1-indexed for simpler parent/child calculations.; Use 'swim' (bottom-up reheapify) after insertion to restore heap order.
//   • Pitfalls: Forgetting to handle 0-indexed vs 1-indexed array representations correctly (parent/child formulas differ).; Violating the heap-ordered property during updates or custom operations.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

// Helper structure to represent events (building start or end)
typedef struct {
    int x;       // x-coordinate
    int height;  // height (negative for start, positive for end)
    int isStart; // 1 for start, 0 for end
} Event;

// Comparison function for qsort
int compareEvents(const void* a, const void* b) {
    Event* e1 = (Event*)a;
    Event* e2 = (Event*)b;
    
    // Sort by x-coordinate first
    if (e1->x != e2->x) {
        return e1->x - e2->x;
    }
    
    // If same x, prioritize:
    // 1. Start events before end events
    // 2. Higher buildings before lower (for starts)
    // 3. Lower buildings before higher (for ends)
    if (e1->isStart && e2->isStart) {
        return e2->height - e1->height; // Higher first for starts
    } else if (!e1->isStart && !e2->isStart) {
        return e1->height - e2->height; // Lower first for ends
    } else {
        return e2->isStart - e1->isStart; // Starts before ends
    }
}

// Simple max heap implementation for heights
typedef struct {
    int* data;
    int* counts;  // Count of each height in heap
    int size;
    int capacity;
} MaxHeap;

MaxHeap* createHeap(int capacity) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->data = (int*)malloc(capacity * sizeof(int));
    heap->counts = (int*)calloc(100001, sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void insertHeap(MaxHeap* heap, int val) {
    heap->counts[val]++;
}

void removeHeap(MaxHeap* heap, int val) {
    if (heap->counts[val] > 0) {
        heap->counts[val]--;
    }
}

int getMax(MaxHeap* heap) {
    for (int i = 100000; i >= 0; i--) {
        if (heap->counts[i] > 0) {
            return i;
        }
    }
    return 0;
}

void freeHeap(MaxHeap* heap) {
    free(heap->data);
    free(heap->counts);
    free(heap);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** getSkyline(int** buildings, int buildingsSize, int* buildingsColSize, int* returnSize, int** returnColumnSizes) {
    // Allocate result array (maximum possible size is 2 * buildingsSize)
    int** result = (int**)malloc(buildingsSize * 2 * sizeof(int*));
    *returnColumnSizes = (int*)malloc(buildingsSize * 2 * sizeof(int));
    *returnSize = 0;
    
    if (buildingsSize == 0) {
        return result;
    }
    
    // Create events for all buildings
    Event* events = (Event*)malloc(buildingsSize * 2 * sizeof(Event));
    int eventCount = 0;
    
    for (int i = 0; i < buildingsSize; i++) {
        // Start event
        events[eventCount].x = buildings[i][0];
        events[eventCount].height = buildings[i][2];
        events[eventCount].isStart = 1;
        eventCount++;
        
        // End event
        events[eventCount].x = buildings[i][1];
        events[eventCount].height = buildings[i][2];
        events[eventCount].isStart = 0;
        eventCount++;
    }
    
    // Sort events
    qsort(events, eventCount, sizeof(Event), compareEvents);
    
    // Create max heap to track active heights
    MaxHeap* heap = createHeap(buildingsSize * 2);
    insertHeap(heap, 0); // Ground level
    
    int prevMaxHeight = 0;
    
    // Process events
    for (int i = 0; i < eventCount; i++) {
        int x = events[i].x;
        int height = events[i].height;
        
        // Process all events at the same x-coordinate
        int j = i;
        while (j < eventCount && events[j].x == x) {
            if (events[j].isStart) {
                insertHeap(heap, events[j].height);
            } else {
                removeHeap(heap, events[j].height);
            }
            j++;
        }
        
        // Get current max height
        int maxHeight = getMax(heap);
        
        // If height changed, add key point
        if (maxHeight != prevMaxHeight) {
            result[*returnSize] = (int*)malloc(2 * sizeof(int));
            result[*returnSize][0] = x;
            result[*returnSize][1] = maxHeight;
            (*returnColumnSizes)[*returnSize] = 2;
            (*returnSize)++;
            prevMaxHeight = maxHeight;
        }
        
        i = j - 1; // Move to last event at this x
    }
    
    // Cleanup
    free(events);
    freeHeap(heap);
    
    return result;
}
