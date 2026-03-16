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

int rectangleArea(int** rectangles, int rectanglesSize, int* rectanglesColSize) {
    #define MOD 1000000007
    typedef struct {
        int x;
        int y1;
        int y2;
        int type; // 1 for start, -1 for end
    } Event;

    Event* events = (Event*)malloc(sizeof(Event) * rectanglesSize * 2);
    int eventCount = 0;

    for (int i = 0; i < rectanglesSize; i++) {
        events[eventCount++] = (Event){rectangles[i][0], rectangles[i][1], rectangles[i][3], 1}; // Start of rectangle
        events[eventCount++] = (Event){rectangles[i][2], rectangles[i][1], rectangles[i][3], -1}; // End of rectangle
    }

    // Sort events by x coordinate
    int compare(const void* a, const void* b) {
        Event* e1 = (Event*)a;
        Event* e2 = (Event*)b;
        return e1->x - e2->x;
    }
    qsort(events, eventCount, sizeof(Event), compare);

    // Active intervals and area calculation
    int* activeY = (int*)calloc(eventCount * 2, sizeof(int));
    int activeCount = 0;
    long long totalArea = 0;
    int prevX = events[0].x;

    for (int i = 0; i < eventCount; i++) {
        int currX = events[i].x;

        // Calculate the total height covered by active intervals
        long long totalHeight = 0;
        int currentStart = -1, currentEnd = -1;
        for (int j = 0; j < activeCount; j += 2) {
            if (activeY[j] > currentEnd) {
                totalHeight += currentEnd - currentStart > 0 ? currentEnd - currentStart : 0;
                currentStart = activeY[j];
                currentEnd = activeY[j + 1];
            } else if (activeY[j + 1] > currentEnd) {
                currentEnd = activeY[j + 1];
            }
        }
        totalHeight += currentEnd - currentStart > 0 ? currentEnd - currentStart : 0;

        // Update total area
        totalArea = (totalArea + totalHeight * (currX - prevX)) % MOD;
        prevX = currX;
        // Update active intervals
        if (events[i].type == 1) {
            // Add interval
            activeY[activeCount++] = events[i].y1;
            activeY[activeCount++] = events[i].y2;
        } else {
            // Remove interval
            for (int j = 0; j < activeCount; j += 2) {
                if (activeY[j] == events[i].y1 && activeY[j + 1] == events[i].y2) {
                    // Shift remaining intervals left
                    for (int k = j; k < activeCount - 2; k++) {
                        activeY[k] = activeY[k + 2];
                    }
                    activeCount -= 2;
                    break;
                }
            }
        }
        free(activeY);
        free(events);
        return (int)totalArea;
}
