// Source: https://leetcode.com/problems/peaks-in-array/   |   Difficulty: Hard
//
// Problem Description:
// A peak in an array arr is an element that is greater than its previous and next element in arr.
//
// You are given an integer array nums and a 2D integer array queries.
//
// You have to process queries of two types:
//
//
// 	queries[i] = [1, li, ri], determine the count of peak elements in the subarray nums[li..ri].
// 	queries[i] = [2, indexi, vali], change nums[indexi] to vali.
//
//
// Return an array answer containing the results of the queries of the first type in order.
//
// Input: nums = [3,1,4,2,5], queries = [[2,3,4],[1,0,4]]
//
// Output: [0]
//
// Explanation:
//
// First query: We change nums[3] to 4 and nums becomes [3,1,4,4,5].
//
// Second query: The number of peaks in the [3,1,4,4,5] is 0.
//
// Constraints:
// 3 <= nums.length <= 105
// 	1 <= nums[i] <= 105
// 	1 <= queries.length <= 105
// 	queries[i][0] == 1 or queries[i][0] == 2
// 	For all i that:
// 	
// 		queries[i][0] == 1: 0 <= queries[i][1] <= queries[i][2] <= nums.length - 1
// 		queries[i][0] == 2: 0 <= queries[i][1] <= nums.length - 1, 1 <= queries[i][2] <= 105
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> peaks(n, 0);
        for (int i = 1; i < n - 1; ++i) {
            if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) {
                peaks[i] = 1;
            }
        }
        
        // Prefix sum of peaks
        vector<int> prefixPeaks(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            prefixPeaks[i] = prefixPeaks[i - 1] + peaks[i - 1];
        }
        
        vector<int> result;
        
        for (const auto& query : queries) {
            if (query[0] == 1) {
                int l = query[1], r = query[2];
                int count = prefixPeaks[r + 1] - prefixPeaks[l];
                result.push_back(count);
            } else if (query[0] == 2) {
                int index = query[1], val = query[2];
                nums[index] = val;
                
                // Update peaks around index
                for (int i = max(1, index - 1); i <= min(n - 2, index + 1); ++i) {
                    if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) {
                        if (peaks[i] == 0) {
                            peaks[i] = 1;
                            for (int j = i + 1; j <= n; ++j) {
                                prefixPeaks[j]++;
                            }
                        }
                    } else {
                        if (peaks[i] == 1) {
                            peaks[i] = 0;
                            for (int j = i + 1; j <= n; ++j) {
                                prefixPeaks[j]--;
                            }
                        }
                    }
                }
            }
        }
        
        return result;          
    }
};
