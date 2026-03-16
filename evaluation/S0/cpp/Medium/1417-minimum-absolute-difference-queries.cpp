// Source: https://leetcode.com/problems/minimum-absolute-difference-queries/   |   Difficulty: Medium
//
// Problem Description:
// The minimum absolute difference of an array a is defined as the minimum value of |a[i] - a[j]|, where 0 <= i < j < a.length and a[i] != a[j]. If all elements of a are the same, the minimum absolute difference is -1.
//
//
// 	For example, the minimum absolute difference of the array [5,2,3,7,2] is |2 - 3| = 1. Note that it is not 0 because a[i] and a[j] must be different.
//
//
// You are given an integer array nums and the array queries where queries[i] = [li, ri]. For each query i, compute the minimum absolute difference of the subarray nums[li...ri] containing the elements of nums between the 0-based indices li and ri (inclusive).
//
// Return an array ans where ans[i] is the answer to the ith query.
//
// A subarray is a contiguous sequence of elements in an array.
//
// The value of |x| is defined as:
//
//
// 	x if x >= 0.
// 	-x if x < 0.
//
// Example:
// Input: nums = [1,3,4,8], queries = [[0,1],[1,2],[2,3],[0,3]]
// Output: [2,1,4,1]
// Explanation: The queries are processed as follows:
// - queries[0] = [0,1]: The subarray is [1,3] and the minimum absolute difference is |1-3| = 2.
// - queries[1] = [1,2]: The subarray is [3,4] and the minimum absolute difference is |3-4| = 1.
// - queries[2] = [2,3]: The subarray is [4,8] and the minimum absolute difference is |4-8| = 4.
// - queries[3] = [0,3]: The subarray is [1,3,4,8] and the minimum absolute difference is |3-4| = 1.
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i] <= 100
// 	1 <= queries.length <= 2 * 104
// 	0 <= li < ri < nums.length
//

class Solution {
public:
    vector<int> minDifference(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<vector<int>> prefixCount(n + 1, vector<int>(101, 0));

        for (int i = 0; i < n; ++i) {
            for (int num = 1; num <= 100; ++num) {
                prefixCount[i + 1][num] = prefixCount[i][num];
            }
            prefixCount[i + 1][nums[i]]++;
        }

        vector<int> result;
        for (const auto& query : queries) {
            int left = query[0];
            int right = query[1];

            vector<int> presentNumbers;
            for (int num = 1; num <= 100; ++num) {
                if (prefixCount[right + 1][num] - prefixCount[left][num] > 0) {
                    presentNumbers.push_back(num);
                }
            }

            int minDiff = INT_MAX;
            for (size_t i = 1; i < presentNumbers.size(); ++i) {
                minDiff = min(minDiff, presentNumbers[i] - presentNumbers[i - 1]);
            }

            result.push_back(minDiff == INT_MAX ? -1 : minDiff);
        }

        return result;          
    }
};
