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

class Solution {
public:
    long long minOperations(vector<vector<int>>& queries) {
        long long totalOperations = 0;

        for (const auto& query : queries) {
            int l = query[0];
            int r = query[1];
            long long operations = 0;

            // Count the number of elements in each group based on their highest set bit
            vector<long long> count(32, 0);
            for (int num = l; num <= r; ++num) {
                int bitPos = 31 - __builtin_clz(num);
                count[bitPos]++;
            }

            // Calculate the number of operations needed
            long long carry = 0;
            for (int i = 31; i >= 0; --i) {
                long long total = count[i] + carry;
                operations += total / 2;
                carry = total % 2 + (total / 2);
            }

            totalOperations += operations;
        }

        return totalOperations;         
    }
};
