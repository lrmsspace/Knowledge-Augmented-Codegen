// Source: https://leetcode.com/problems/closest-equal-element-queries/   |   Difficulty: Medium
//
// Problem Description:
// You are given a circular array nums and an array queries.
//
// For each query i, you have to find the following:
//
//
// 	The minimum distance between the element at index queries[i] and any other index j in the circular array, where nums[j] == nums[queries[i]]. If no such index exists, the answer for that query should be -1.
//
//
// Return an array answer of the same size as queries, where answer[i] represents the result for query i.
//
// Example:
// Input: nums = [1,3,1,4,1,3,2], queries = [0,3,5]
//
// Output: [2,-1,3]
//
// Explanation:
//
//
// 	Query 0: The element at queries[0] = 0 is nums[0] = 1. The nearest index with the same value is 2, and the distance between them is 2.
// 	Query 1: The element at queries[1] = 3 is nums[3] = 4. No other index contains 4, so the result is -1.
// 	Query 2: The element at queries[2] = 5 is nums[5] = 3. The nearest index with the same value is 1, and the distance between them is 3 (following the circular path: 5 -> 6 -> 0 -> 1).
//
// Constraints:
// 1 <= queries.length <= nums.length <= 105
// 	1 <= nums[i] <= 106
// 	0 <= queries[i] < nums.length
//

class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        unordered_map<int, vector<int>> indexMap;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            indexMap[nums[i]].push_back(i);
        }

        vector<int> result;
        for (int query : queries) {
            int target = nums[query];
            const auto& indices = indexMap[target];
            if (indices.size() == 1) {
                result.push_back(-1);
                continue;
            }

            // Binary search to find the closest indices
            auto it = lower_bound(indices.begin(), indices.end(), query);
            int dist1 = INT_MAX, dist2 = INT_MAX;

            if (it != indices.end() && *it == query) {
                // Exact match found
                if (it != indices.begin()) {
                    dist1 = query - *(it - 1);
                }
                if (it + 1 != indices.end()) {
                    dist2 = *(it + 1) - query;
                }
            } else {
                // No exact match, check neighbors
                if (it != indices.begin()) {
                    dist1 = query - *(it - 1);
                }
                if (it != indices.end()) {
                    dist2 = *it - query;
                }
            }

            // Consider circular distances
            if (!indices.empty()) {
                dist1 = min(dist1, query + n - indices.back());
                dist2 = min(dist2, indices.front() + n - query);
            }

            result.push_back(min(dist1, dist2));
        }

        return result;          
    }
};
