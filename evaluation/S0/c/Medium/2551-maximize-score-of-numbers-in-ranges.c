// Source: https://leetcode.com/problems/maximize-score-of-numbers-in-ranges/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers start and an integer d, representing n intervals [start[i], start[i] + d].
//
// You are asked to choose n integers where the ith integer must belong to the ith interval. The score of the chosen integers is defined as the minimum absolute difference between any two integers that have been chosen.
//
// Return the maximum possible score of the chosen integers.
//
// Example:
// Input: start = [6,0,3], d = 2
//
// Output: 4
//
// Explanation:
//
// The maximum possible score can be obtained by choosing integers: 8, 0, and 4. The score of these chosen integers is min(|8 - 0|, |8 - 4|, |0 - 4|) which equals 4.
//
// Constraints:
// 2 <= start.length <= 105
// 	0 <= start[i] <= 109
// 	0 <= d <= 109
//

int maxPossibleScore(int* start, int startSize, int d) {
    long long left = 0, right = 1e10, mid;
    int n = startSize;

    // Helper function to check if a given minimum difference 'diff' is feasible
    int canPlace(int diff) {
        long long lastPlaced = -1e15; // Initialize to a very small number
        for (int i = 0; i < n; i++) {
            long long minPos = start[i];
            long long maxPos = start[i] + d;
            // Calculate the next valid position to place the integer
            long long nextPos = lastPlaced + diff;
            if (nextPos < minPos) {
                nextPos = minPos;
            }
            if (nextPos > maxPos) {
                return 0; // Not feasible
            }
            lastPlaced = nextPos; // Update the last placed position
        }
        return 1; // Feasible
    }

    // Binary search to find the maximum possible score
    while (left < right) {
        mid = left + (right - left + 1) / 2; // Midpoint for upper bound search
        if (canPlace(mid)) {
            left = mid; // Try for a larger minimum difference
        } else {
            right = mid - 1; // Reduce the search space
        }
    }

    return (int)left; // The maximum possible score     
}
