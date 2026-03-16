// Source: https://leetcode.com/problems/matchsticks-to-square/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array matchsticks where matchsticks[i] is the length of the ith matchstick. You want to use all the matchsticks to make one square. You should not break any stick, but you can link them up, and each matchstick must be used exactly one time.
//
// Return true if you can make this square and false otherwise.
//
// Example:
// Input: matchsticks = [1,1,2,2,2]
// Output: true
// Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.
//
// Constraints:
// 1 <= matchsticks.length <= 15
// 	1 <= matchsticks[i] <= 108
//

bool makesquare(int* matchsticks, int matchsticksSize) {
    int totalLength = 0;
    for (int i = 0; i < matchsticksSize; i++) {
        totalLength += matchsticks[i];
    }
    if (totalLength % 4 != 0) {
        return false;
    }
    int sideLength = totalLength / 4;
    int sides[4] = {0};

    // Sort matchsticks in descending order to optimize backtracking
    qsort(matchsticks, matchsticksSize, sizeof(int), [](const void* a, const void* b) {
        return (*(int*)b - *(int*)a);
    });

    bool backtrack(int index) {
        if (index == matchsticksSize) {
            return sides[0] == sideLength && sides[1] == sideLength &&
                   sides[2] == sideLength && sides[3] == sideLength;
        }
        for (int i = 0; i < 4; i++) {
            if (sides[i] + matchsticks[index] <= sideLength) {
                sides[i] += matchsticks[index];
                if (backtrack(index + 1)) {
                    return true;
                }
                sides[i] -= matchsticks[index];
            }
        }
        return false;
    }

    return backtrack(0);        
}
