// Source: https://leetcode.com/problems/mark-elements-on-array-by-performing-queries/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums of size n consisting of positive integers.
//
// You are also given a 2D array queries of size m where queries[i] = [indexi, ki].
//
// Initially all elements of the array are unmarked.
//
// You need to apply m queries on the array in order, where on the ith query you do the following:
//
//
// 	Mark the element at index indexi if it is not already marked.
// 	Then mark ki unmarked elements in the array with the smallest values. If multiple such elements exist, mark the ones with the smallest indices. And if less than ki unmarked elements exist, then mark all of them.
//
//
// Return an array answer of size m where answer[i] is the sum of unmarked elements in the array after the ith query.
//
// Example:
// Input: nums = [1,2,2,1,2,3,1], queries = [[1,2],[3,3],[4,2]]
//
// Output: [8,3,0]
//
// Explanation:
//
// We do the following queries on the array:
//
//
// 	Mark the element at index 1, and 2 of the smallest unmarked elements with the smallest indices if they exist, the marked elements now are nums = [1,2,2,1,2,3,1]. The sum of unmarked elements is 2 + 2 + 3 + 1 = 8.
// 	Mark the element at index 3, since it is already marked we skip it. Then we mark 3 of the smallest unmarked elements with the smallest indices, the marked elements now are nums = [1,2,2,1,2,3,1]. The sum of unmarked elements is 3.
// 	Mark the element at index 4, since it is already marked we skip it. Then we mark 2 of the smallest unmarked elements with the smallest indices if they exist, the marked elements now are nums = [1,2,2,1,2,3,1]. The sum of unmarked elements is 0.
//
// Constraints:
// n == nums.length
// 	m == queries.length
// 	1 <= m <= n <= 105
// 	1 <= nums[i] <= 105
// 	queries[i].length == 2
// 	0 <= indexi, ki <= n - 1
//

class Solution {
public:
    vector<long long> unmarkedSumArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<long long> result;
        long long totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }

        vector<bool> marked(n, false);
        vector<vector<int>> valueIndices(100001);
        for (int i = 0; i < n; ++i) {
            valueIndices[nums[i]].push_back(i);
        }

        int currentValue = 1;
        int currentIndexInValueList = 0;

        for (const auto& query : queries) {
            int indexToMark = query[0];
            int k = query[1];

            if (!marked[indexToMark]) {
                marked[indexToMark] = true;
                totalSum -= nums[indexToMark];
            }

            while (k > 0 && currentValue <= 100000) {
                while (currentIndexInValueList < valueIndices[currentValue].size() && k > 0) {
                    int idx = valueIndices[currentValue][currentIndexInValueList];
                    if (!marked[idx]) {
                        marked[idx] = true;
                        totalSum -= currentValue;
                        --k;
                    }
                    ++currentIndexInValueList;
                }
                if (currentIndexInValueList >= valueIndices[currentValue].size()) {
                    ++currentValue;
                    currentIndexInValueList = 0;
                }
            }

            result.push_back(totalSum);
        }

        return result;          
    }
};
