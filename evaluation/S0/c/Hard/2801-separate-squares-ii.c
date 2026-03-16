// Source: https://leetcode.com/problems/separate-squares-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array squares. Each squares[i] = [xi, yi, li] represents the coordinates of the bottom-left point and the side length of a square parallel to the x-axis.
//
// Find the minimum y-coordinate value of a horizontal line such that the total area covered by squares above the line equals the total area covered by squares below the line.
//
// Answers within 10-5 of the actual answer will be accepted.
//
// Note: Squares may overlap. Overlapping areas should be counted only once in this version.
//
// Example:
// Input: squares = [[0,0,1],[2,2,1]]
//
// Output: 1.00000
//
// Explanation:
//
//
//
// Any horizontal line between y = 1 and y = 2 results in an equal split, with 1 square unit above and 1 square unit below. The minimum y-value is 1.
//
// Constraints:
// 1 <= squares.length <= 5 * 104
// 	squares[i] = [xi, yi, li]
// 	squares[i].length == 3
// 	0 <= xi, yi <= 109
// 	1 <= li <= 109
// 	The total area of all the squares will not exceed 1015.
//

double separateSquares(int** squares, int squaresSize, int* squaresColSize) {
    typedef struct {
        long long x;
        long long y1;
        long long y2;
        int type; // 1 for start, -1 for end
    } Event;

    Event* events = (Event*)malloc(2 * squaresSize * sizeof(Event));
    for (int i = 0; i < squaresSize; i++) {
        long long x = squares[i][0];
        long long y = squares[i][1];
        long long l = squares[i][2];
        events[2 * i] = (Event){x, y, y + l, 1};
        events[2 * i + 1] = (Event){x + l, y, y + l, -1};
    }

    int compare(const void* a, const void* b) {
        Event* ea = (Event*)a;
        Event* eb = (Event*)b;
        if (ea->x != eb->x) return (ea->x < eb->x) ? -1 : 1;
        return ea->type - eb->type;
    }
    qsort(events, 2 * squaresSize, sizeof(Event), compare);

    // Sweep line algorithm to calculate total area
    long long totalArea = 0;
    long long prevX = events[0].x;
    int* activeY = (int*)calloc(2 * squaresSize, sizeof(int));
    int activeCount = 0;

    for (int i = 0; i < 2 * squaresSize; i++) {
        Event e = events[i];
        long long deltaX = e.x - prevX;

        // Calculate covered Y length
        long long coveredY = 0;
        if (activeCount > 0) {
            // Merge intervals
            qsort(activeY, activeCount, sizeof(int), compare);
            long long currentStart = activeY[0];
            long long currentEnd = activeY[1];
            for (int j = 2; j < activeCount; j += 2) {
                if (activeY[j] > currentEnd) {
                    coveredY += currentEnd - currentStart;
                    currentStart = activeY[j];
                    currentEnd = activeY[j + 1];
                } else {
                    if (activeY[j + 1] > currentEnd) {
                        currentEnd = activeY[j + 1];
                    }
                }
            }
            coveredY += currentEnd - currentStart;
        }
        totalArea += coveredY * deltaX;
        prevX = e.x;
        // Update active Y intervals
        if (e.type == 1) {
            activeY[activeCount++] = e.y1;
            activeY[activeCount++] = e.y2;
        } else {
            for (int j = 0; j < activeCount; j += 2) {
                if (activeY[j] == e.y1 && activeY[j + 1] == e.y2) {
                    // Remove this interval
                    for (int k = j; k < activeCount - 2; k++) {
                        activeY[k] = activeY[k + 2];
                    }
                    activeCount -= 2;
                    break;
                }
            }
        }
    }
    free(activeY);
    free(events);
    // Binary search for the separating line
    double left = 0, right = 1e9 + 1;
    double result = 0;
    for (int iter = 0; iter < 100; iter++) {
        double mid = (left + right) / 2;
        // Calculate area below mid
        long long areaBelow = 0;
        prevX = events[0].x;
        activeY = (int*)calloc(2 * squaresSize, sizeof(int));
        activeCount = 0;

        for (int i = 0; i < 2 * squaresSize; i++) {
            Event e = events[i];
            long long deltaX = e.x - prevX;

            // Calculate covered Y length below mid
            long long coveredY = 0;
            if (activeCount > 0) {
                // Merge intervals
                qsort(activeY, activeCount, sizeof(int), compare);
                long long currentStart = activeY[0];
                long long currentEnd = activeY[1];
                for (int j = 2; j < activeCount; j += 2) {
                    if (activeY[j] > currentEnd) {
                        coveredY += currentEnd - currentStart;
                        currentStart = activeY[j];
                        currentEnd = activeY[j + 1];
                    } else {
                        if (activeY[j + 1] > currentEnd) {
                            currentEnd = activeY[j + 1];
                        }
                    }
                }
                coveredY += currentEnd - currentStart;
            }
            areaBelow += coveredY * deltaX;
            prevX = e.x;
            // Update active Y intervals
            if (e.type == 1) {
                if (e.y1 < mid) {
                    activeY[activeCount++] = e.y1;
                    activeY[activeCount++] = (e.y2 < mid) ? e.y2 : mid;
                }
            } else {
                for (int j = 0; j < activeCount; j += 2) {
                    if (activeY[j] == e.y1 && activeY[j + 1] == ((e.y2 < mid) ? e.y2 : mid)) {
                        // Remove this interval
                        for (int k = j; k < activeCount - 2; k++) {
                            activeY[k] = activeY[k + 2];
                        }
                        activeCount -= 2;
                        break;
                    }
                }
            }
        }
        free(activeY);
        if (areaBelow * 2 < totalArea) {
            left = mid;
        } else {
            right = mid;
        }
        result = mid;
    }
    return result;
}
