// Source: https://leetcode.com/problems/rectangle-area-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D array of axis-aligned rectangles. Each rectangle[i] = [xi1, yi1, xi2, yi2] denotes the ith rectangle where (xi1, yi1) are the coordinates of the bottom-left corner, and (xi2, yi2) are the coordinates of the top-right corner.
//
// Calculate the total area covered by all rectangles in the plane. Any area covered by two or more rectangles should only be counted once.
//
// Return the total area. Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: rectangles = [[0,0,2,2],[1,0,2,3],[1,0,3,1]]
// Output: 6
// Explanation: A total area of 6 is covered by all three rectangles, as illustrated in the picture.
// From (1,1) to (2,2), the green and red rectangles overlap.
// From (1,0) to (2,3), all three rectangles overlap.
//
// Constraints:
// 1 <= rectangles.length <= 200
// 	rectanges[i].length == 4
// 	0 <= xi1, yi1, xi2, yi2 <= 109
// 	xi1 <= xi2
// 	yi1 <= yi2
// 	All rectangles have non zero area.
//
// Helpful references (internal KB):
// - Search for a pair of intersecting segments (tree, geometry, sweep-line, counting)
//   • When to use: Use this algorithm to efficiently determine if any pair of line segments in a given set intersect. It is particularly effective for detecting geometric overlaps in a 2D plane.
//   • Idea: This algorithm processes segments by sweeping a vertical line across the plane, maintaining an ordered set of active segments to efficiently check for intersections with neighbors. It achieves an optimal time complexity of O(N log N).
//   • Invariants: The sweep line always moves from left to right, processing events in increasing x-coordinate order.; The set of active segments contains all segments currently intersected by the sweep line, ordered by their y-coordinate at the sweep line's current x-position.
//   • Tips: Process events at the same x-coordinate by adding segments before removing them to catch vertex intersections.; Use a balanced binary search tree (e.g., `std::set`) to maintain active segments, ordered by their y-coordinate.
//   • Pitfalls: Incorrect event ordering (e.g., removing before adding) can lead to missing intersections at shared endpoints.; Floating point precision issues can cause incorrect intersection detection or ordering of segments.
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
// - Segment Tree (tree, array, segment-tree)
//   • When to use: Use when you need to perform range queries (like sum, min, max) and point or range updates on an array efficiently, typically in logarithmic time.
//   • Idea: A Segment Tree is a tree-based data structure that stores information about array intervals, enabling efficient O(log n) range queries and point/range updates.
//   • Invariants: Each node in the segment tree represents a contiguous subsegment of the original array.; The value stored in a non-leaf node is an aggregation of the values from its direct children.
//   • Tips: Build the tree recursively, dividing the array into halves.; Use lazy propagation for efficient range updates to avoid O(N) updates.
//   • Pitfalls: Off-by-one errors when defining segment boundaries or array indices.; Forgetting to push down lazy tags before querying or updating children nodes.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

// Comparator for qsort
int compareInt(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

// Segment Tree node structure
typedef struct {
    long long length;
    int count;
} SegmentTreeNode;

// Build segment tree
void buildTree(SegmentTreeNode* tree, int node, int start, int end) {
    if (start == end) {
        tree[node].count = 0;
        tree[node].length = 0;
        return;
    }
    int mid = start + (end - start) / 2;
    buildTree(tree, 2 * node, start, mid);
    buildTree(tree, 2 * node + 1, mid + 1, end);
    tree[node].count = 0;
    tree[node].length = 0;
}

// Update segment tree
void updateTree(SegmentTreeNode* tree, int node, int start, int end, int l, int r, int val, int* coords, int coordSize) {
    if (r < start || l > end) return;
    
    if (l <= start && end <= r) {
        tree[node].count += val;
        if (tree[node].count > 0) {
            tree[node].length = coords[end + 1] - coords[start];
        } else {
            tree[node].length = 0;
        }
        return;
    }
    
    int mid = start + (end - start) / 2;
    updateTree(tree, 2 * node, start, mid, l, r, val, coords, coordSize);
    updateTree(tree, 2 * node + 1, mid + 1, end, l, r, val, coords, coordSize);
    
    if (tree[2 * node].count > 0 || tree[2 * node].length > 0) {
        tree[node].length = tree[2 * node].length;
    } else {
        tree[node].length = 0;
    }
    tree[node].length += tree[2 * node + 1].length;
}

int rectangleArea(int** rectangles, int rectanglesSize, int* rectanglesColSize) {
    const long long MOD = 1e9 + 7;
    
    // Collect all x and y coordinates
    int* xCoords = (int*)malloc(rectanglesSize * 2 * sizeof(int));
    int* yCoords = (int*)malloc(rectanglesSize * 2 * sizeof(int));
    int xSize = 0, ySize = 0;
    
    for (int i = 0; i < rectanglesSize; i++) {
        xCoords[xSize++] = rectangles[i][0];
        xCoords[xSize++] = rectangles[i][2];
        yCoords[ySize++] = rectangles[i][1];
        yCoords[ySize++] = rectangles[i][3];
    }
    
    // Sort and remove duplicates
    qsort(xCoords, xSize, sizeof(int), compareInt);
    qsort(yCoords, ySize, sizeof(int), compareInt);
    
    int xCompressed = 1;
    for (int i = 1; i < xSize; i++) {
        if (xCoords[i] != xCoords[xCompressed - 1]) {
            xCoords[xCompressed++] = xCoords[i];
        }
    }
    xSize = xCompressed;
    
    int yCompressed = 1;
    for (int i = 1; i < ySize; i++) {
        if (yCoords[i] != yCoords[yCompressed - 1]) {
            yCoords[yCompressed++] = yCoords[i];
        }
    }
    ySize = yCompressed;
    
    // Create events for sweep line
    typedef struct {
        int x;
        int y1;
        int y2;
        int type; // 1 for start, -1 for end
    } Event;
    
    Event* events = (Event*)malloc(rectanglesSize * 2 * sizeof(Event));
    int eventSize = 0;
    
    for (int i = 0; i < rectanglesSize; i++) {
        events[eventSize].x = rectangles[i][0];
        events[eventSize].y1 = rectangles[i][1];
        events[eventSize].y2 = rectangles[i][3];
        events[eventSize].type = 1;
        eventSize++;
        
        events[eventSize].x = rectangles[i][2];
        events[eventSize].y1 = rectangles[i][1];
        events[eventSize].y2 = rectangles[i][3];
        events[eventSize].type = -1;
        eventSize++;
    }
    
    // Sort events by x coordinate, then by type (start before end for same x)
    qsort(events, eventSize, sizeof(Event), compareInt);
    
    // Create segment tree for y-coordinates
    int treeSize = 4 * ySize;
    SegmentTreeNode* tree = (SegmentTreeNode*)malloc(treeSize * sizeof(SegmentTreeNode));
    buildTree(tree, 1, 0, ySize - 2);
    
    long long totalArea = 0;
    int prevX = 0;
    
    for (int i = 0; i < eventSize; ) {
        int currX = events[i].x;
        
        // Process all events at same x coordinate
        while (i < eventSize && events[i].x == currX) {
            // Find y indices
            int y1Idx = 0, y2Idx = 0;
            for (int j = 0; j < ySize; j++) {
                if (yCoords[j] == events[i].y1) y1Idx = j;
                if (yCoords[j] == events[i].y2) y2Idx = j;
            }
            
            updateTree(tree, 1, 0, ySize - 2, y1Idx, y2Idx - 1, events[i].type, yCoords, ySize);
            i++;
        }
        
        // Add area for the current vertical strip
        if (prevX > 0 && tree[1].length > 0) {
            long long stripArea = (long long)(currX - prevX) * tree[1].length;
            totalArea = (totalArea + stripArea) % MOD;
        }
        
        prevX = currX;
    }
    
    free(xCoords);
    free(yCoords);
    free(events);
    free(tree);
    
    return (int)(totalArea % MOD);
}
