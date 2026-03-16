// Source: https://leetcode.com/problems/maximum-score-of-non-overlapping-intervals/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array intervals, where intervals[i] = [li, ri, weighti]. Interval i starts at position li and ends at ri, and has a weight of weighti. You can choose up to 4 non-overlapping intervals. The score of the chosen intervals is defined as the total sum of their weights.
//
// Return the lexicographically smallest array of at most 4 indices from intervals with maximum score, representing your choice of non-overlapping intervals.
//
// Two intervals are said to be non-overlapping if they do not share any points. In particular, intervals sharing a left or right boundary are considered overlapping.
//
// Example:
// Input: intervals = [[1,3,2],[4,5,2],[1,5,5],[6,9,3],[6,7,1],[8,9,1]]
//
// Output: [2,3]
//
// Explanation:
//
// You can choose the intervals with indices 2, and 3 with respective weights of 5, and 3.
//
// Constraints:
// 1 <= intevals.length <= 5 * 104
// 	intervals[i].length == 3
// 	intervals[i] = [li, ri, weighti]
// 	1 <= li <= ri <= 109
// 	1 <= weighti <= 109
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maximumWeight(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize) {
    // Sort intervals by end time
    int compare(const void* a, const void* b) {
        return ((int*)a)[1] - ((int*)b)[1];
    }
    qsort(intervals, intervalsSize, sizeof(int*), compare);

    // DP array to store max weight and indices
    typedef struct {
        long long weight;
        int indices[4];
        int count;
    } DPEntry;

    DPEntry* dp = (DPEntry*)malloc((intervalsSize + 1) * sizeof(DPEntry));
    for (int i = 0; i <= intervalsSize; i++) {
        dp[i].weight = 0;
        dp[i].count = 0;
    }

    for (int i = 1; i <= intervalsSize; i++) {
        int l = intervals[i - 1][0];
        int r = intervals[i - 1][1];
        int w = intervals[i - 1][2];

        // Find the last non-overlapping interval
        int j = i - 1;
        while (j > 0 && intervals[j - 1][1] >= l) {
            j--;
        }

        // Option 1: Do not take the current interval
        dp[i] = dp[i - 1];

        // Option 2: Take the current interval
        long long newWeight = dp[j].weight + w;
        if (newWeight > dp[i].weight) {
            dp[i].weight = newWeight;
            memcpy(dp[i].indices, dp[j].indices, dp[j].count * sizeof(int));
            dp[i].indices[dp[j].count] = i - 1;
            dp[i].count = dp[j].count + 1;
        } else if (newWeight == dp[i].weight) {
            // Check lexicographical order
            int tempIndices[4];
            memcpy(tempIndices, dp[j].indices, dp[j].count * sizeof(int));
            tempIndices[dp[j].count] = i - 1;
            if (dp[i].count == 0 || memcmp(tempIndices, dp[i].indices, (dp[j].count + 1) * sizeof(int)) < 0) {
                memcpy(dp[i].indices, tempIndices, (dp[j].count + 1) * sizeof(int));
                dp[i].count = dp[j].count + 1;
            }
        }
    }
    *returnSize = dp[intervalsSize].count;
    int* result = (int*)malloc((*returnSize) * sizeof(int));
    for (int i = 0; i < *returnSize; i++) {
        result[i] = dp[intervalsSize].indices[i];
    }
    free(dp);
    return result;
}
