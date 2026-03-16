// Source: https://leetcode.com/problems/maximum-sum-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed integer arrays nums1 and nums2, each of length n, and a 1-indexed 2D array queries where queries[i] = [xi, yi].
//
// For the ith query, find the maximum value of nums1[j] + nums2[j] among all indices j (0 <= j < n), where nums1[j] >= xi and nums2[j] >= yi, or -1 if there is no j satisfying the constraints.
//
// Return an array answer where answer[i] is the answer to the ith query.
//
// Example:
// Input: nums1 = [4,3,1,2], nums2 = [2,4,9,5], queries = [[4,1],[1,3],[2,5]]
// Output: [6,10,7]
// Explanation: 
// For the 1st query xi = 4 and yi = 1, we can select index j = 0 since nums1[j] >= 4 and nums2[j] >= 1. The sum nums1[j] + nums2[j] is 6, and we can show that 6 is the maximum we can obtain.
//
// For the 2nd query xi = 1 and yi = 3, we can select index j = 2 since nums1[j] >= 1 and nums2[j] >= 3. The sum nums1[j] + nums2[j] is 10, and we can show that 10 is the maximum we can obtain. 
//
// For the 3rd query xi = 2 and yi = 5, we can select index j = 3 since nums1[j] >= 2 and nums2[j] >= 5. The sum nums1[j] + nums2[j] is 7, and we can show that 7 is the maximum we can obtain.
//
// Therefore, we return [6,10,7].
//
// Constraints:
// nums1.length == nums2.length 
// 	n == nums1.length 
// 	1 <= n <= 105
// 	1 <= nums1[i], nums2[i] <= 109 
// 	1 <= queries.length <= 105
// 	queries[i].length == 2
// 	xi == queries[i][1]
// 	yi == queries[i][2]
// 	1 <= xi, yi <= 109
//

class Solution {
public:
    vector<int> maximumSumQueries(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        int n = nums1.size();
        int q = queries.size();
        vector<int> result(q, -1);
        
        // Combine nums1 and nums2 into pairs and sort by nums1 descending
        vector<pair<int, int>> numPairs(n);
        for (int i = 0; i < n; i++) {
            numPairs[i] = {nums1[i], nums2[i]};
        }
        sort(numPairs.rbegin(), numPairs.rend());
        
        // Prepare queries with their original indices and sort by xi descending
        vector<tuple<int, int, int>> queryList(q);
        for (int i = 0; i < q; i++) {
            queryList[i] = {queries[i][0], queries[i][1], i};
        }
        sort(queryList.rbegin(), queryList.rend());
        
        // Use a map to maintain the maximum sums for nums2 values
        map<int, int> maxSums;
        int idx = 0;
        
        for (const auto& [xi, yi, queryIdx] : queryList) {
            // Add all valid numPairs to the map
            while (idx < n && numPairs[idx].first >= xi) {
                int sum = numPairs[idx].first + numPairs[idx].second;
                auto it = maxSums.lower_bound(numPairs[idx].second);
                if (it == maxSums.end() || it->second < sum) {
                    maxSums[numPairs[idx].second] = sum;
                    // Remove dominated entries
                    it = maxSums.upper_bound(numPairs[idx].second);
                    while (it != maxSums.end() && it->second <= sum) {
                        it = maxSums.erase(it);
                    }
                }
                idx++;
            }
            
            // Find the maximum sum for the current query
            auto it = maxSums.lower_bound(yi);
            if (it != maxSums.end()) {
                result[queryIdx] = it->second;
            }
        }
        
        return result;          
    }
};
