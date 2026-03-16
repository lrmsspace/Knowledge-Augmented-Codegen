// Source: https://leetcode.com/problems/minimum-operations-to-make-array-elements-zero/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D array queries, where queries[i] is of the form [l, r]. Each queries[i] defines an array of integers nums consisting of elements ranging from l to r, both inclusive.
//
// In one operation, you can:
//
//
// 	Select two integers a and b from the array.
// 	Replace them with floor(a / 4) and floor(b / 4).
//
//
// Your task is to determine the minimum number of operations required to reduce all elements of the array to zero for each query. Return the sum of the results for all queries.
//
// Example:
// Input: queries = [[1,2],[2,4]]
//
// Output: 3
//
// Explanation:
//
// For queries[0]:
//
//
// 	The initial array is nums = [1, 2].
// 	In the first operation, select nums[0] and nums[1]. The array becomes [0, 0].
// 	The minimum number of operations required is 1.
//
//
// For queries[1]:
//
//
// 	The initial array is nums = [2, 3, 4].
// 	In the first operation, select nums[0] and nums[2]. The array becomes [0, 3, 1].
// 	In the second operation, select nums[1] and nums[2]. The array becomes [0, 0, 0].
// 	The minimum number of operations required is 2.
//
//
// The output is 1 + 2 = 3.
//
// Constraints:
// 1 <= queries.length <= 105
// 	queries[i].length == 2
// 	queries[i] == [l, r]
// 	1 <= l < r <= 109
//

long long minOperations(int** queries, int queriesSize, int* queriesColSize) {
    long long totalOps = 0;

    for (int q = 0; q < queriesSize; ++q) {
        int l = queries[q][0];
        int r = queries[q][1];
        long long ops = 0;

        int count[4] = {0}; // count[0]: mod 0, count[1]: mod 1, count[2]: mod 2, count[3]: mod 3

        for (int num = l; num <= r; ++num) {
            count[num % 4]++;
        }

        // Pair mod 1 and mod 3
        int pairs13 = (count[1] < count[3]) ? count[1] : count[3];
        ops += pairs13;
        count[1] -= pairs13;
        count[3] -= pairs13;

        // Pair mod 2
        ops += count[2] / 2;
        count[2] %= 2;

        // Handle remaining mod 1
        if (count[1] > 0) {
            ops += (count[1] + 3) / 4 * 3; // Each group of 4 mod 1 needs 3 operations
        }

        // Handle remaining mod 3
        if (count[3] > 0) {
            ops += (count[3] + 3) / 4 * 3; // Each group of 4 mod 3 needs 3 operations
        }

        // Handle remaining mod 2
        if (count[2] > 0) {
            ops += 2; // One mod 2 needs 2 operations
        }

        totalOps += ops;
    }

    return totalOps;        
}
