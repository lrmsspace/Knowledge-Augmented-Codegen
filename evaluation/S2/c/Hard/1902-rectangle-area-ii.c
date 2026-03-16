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
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
// - Check if two segments intersect (geometry, number, simulation)
//   • When to use: Use this when determining if two line segments in a 2D plane share any common points, especially when floating-point precision issues need to be avoided.
//   • Idea: This algorithm determines if two line segments intersect by handling collinear and non-collinear cases separately, primarily using integer arithmetic to avoid precision errors. It typically runs in O(1) time.
//   • Invariants: If segments are collinear, their 1D projections on both axes must overlap for intersection.; If segments are not collinear, each segment's endpoints must lie on opposite sides of the line containing the other segment.
//   • Tips: Handle collinear segments as a distinct special case.; Utilize cross products for efficient orientation checks.
//   • Pitfalls: Failing to correctly identify and handle collinear segments.; Introducing floating-point errors by using division for slopes.
// - The Inclusion-Exclusion Principle (matrix, array, dp-2d, counting)
//   • When to use: Use when needing to count elements satisfying "at least one" of several properties, especially when direct counting is complicated by overlapping sets. It's also applicable for counting elements satisfying "none" of the properties by subtracting from the total.
//   • Idea: The Inclusion-Exclusion Principle is a combinatorial method to determine the size of the union of multiple finite sets. It works by summing the sizes of individual sets, subtracting the sizes of all pairwise intersections, adding back the sizes of all three-way intersections, and so on, with alternating signs.
//   • Invariants: The count for any element satisfying `k` properties is adjusted to be exactly 1 in the final sum.; Each term in the sum corresponds to the size of an intersection of a distinct subset of properties.
//   • Tips: Clearly define the universe and the properties (sets) you are interested in.; Systematically list all combinations of properties for intersection terms.
//   • Pitfalls: Incorrectly identifying or defining the properties or sets.; Missing certain intersection terms or double-counting them.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int rectangleArea(int** rectangles, int rectanglesSize, int* rectanglesColSize) {
    // Step 1: Collect all unique x-coordinates (start and end of rectangles)
    int* x_coords = (int*)malloc(rectanglesSize * 2 * sizeof(int));
    int x_count = 0;
    for (int i = 0; i < rectanglesSize; i++) {
        x_coords[x_count++] = rectangles[i][0]; // xi1
        x_coords[x_count++] = rectangles[i][2]; // xi2
    }
    
    // Step 2: Sort and remove duplicates from x_coords
    qsort(x_coords, x_count, sizeof(int), compare);
    int unique_x_count = 0;
    for (int i = 0; i < x_count; i++) {
        if (i == 0 || x_coords[i] != x_coords[i - 1]) {
            x_coords[unique_x_count++] = x_coords[i];
        }
    }
    
    // Step 3: Create events for the sweep line algorithm
    typedef struct {
        int y;
        int type; // +1 for start, -1 for end
        int x_start;
        int x_end;
    } Event;
    
    Event* events = (Event*)malloc(rectanglesSize * 2 * sizeof(Event));
    int event_count = 0;
    
    for (int i = 0; i < rectanglesSize; i++) {
        events[event_count++] = (Event){rectangles[i][1], +1, rectangles[i][0], rectangles[i][2]}; // yi1, start
        events[event_count++] = (Event){rectangles[i][3], -1, rectangles[i][0], rectangles[i][2]}; // yi2, end
    }
    
    // Step 4: Sort events by y-coordinate, then by type
    qsort(events, event_count, sizeof(Event), compare_events);
    
    // Step 5: Sweep line algorithm to calculate area
    long long total_area = 0;
    int active_segments_count = 0;
    long long prev_y = events[0].y;
    
    for (int i = 0; i < event_count; i++) {
        Event current_event = events[i];
        
        // Calculate the length of active segments on the x-axis
        if (active_segments_count > 0) {
            long long active_length = calculate_active_length(x_coords, unique_x_count, events, i);
            total_area += active_length * (current_event.y - prev_y);
        }
        // Update active segments based on the current event
        update_active_segments(x_coords, unique_x_count, events, i);
        prev_y = current_event.y;
    }
    free(x_coords);
    free(events);
    return total_area % 1000000007;
}
