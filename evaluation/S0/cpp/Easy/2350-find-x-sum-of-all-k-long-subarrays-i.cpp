// Source: https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array nums of n integers and two integers k and x.
//
// The x-sum of an array is calculated by the following procedure:
//
//
// 	Count the occurrences of all elements in the array.
// 	Keep only the occurrences of the top x most frequent elements. If two elements have the same number of occurrences, the element with the bigger value is considered more frequent.
// 	Calculate the sum of the resulting array.
//
//
// Note that if an array has less than x distinct elements, its x-sum is the sum of the array.
//
// Return an integer array answer of length n - k + 1 where answer[i] is the x-sum of the subarray nums[i..i + k - 1].
//
// Example:
// Input: nums = [1,1,2,2,3,4,2,3], k = 6, x = 2
//
// Output: [6,10,12]
//
// Explanation:
//
//
// 	For subarray [1, 1, 2, 2, 3, 4], only elements 1 and 2 will be kept in the resulting array. Hence, answer[0] = 1 + 1 + 2 + 2.
// 	For subarray [1, 2, 2, 3, 4, 2], only elements 2 and 4 will be kept in the resulting array. Hence, answer[1] = 2 + 2 + 2 + 4. Note that 4 is kept in the array since it is bigger than 3 and 1 which occur the same number of times.
// 	For subarray [2, 2, 3, 4, 2, 3], only elements 2 and 3 are kept in the resulting array. Hence, answer[2] = 2 + 2 + 2 + 3 + 3.
//
// Constraints:
// 1 <= n == nums.length <= 50
// 	1 <= nums[i] <= 50
// 	1 <= x <= k <= nums.length
//

class Solution {
public:
    vector<int> findXSum(vector<int>& nums, int k, int x) {
        vector<int> result;
        int n = nums.size();

        for (int i = 0; i <= n - k; ++i) {
            unordered_map<int, int> freqMap;
            for (int j = i; j < i + k; ++j) {
                freqMap[nums[j]]++;
            }

            // Create a vector of pairs (number, frequency)
            vector<pair<int, int>> freqVec;
            for (const auto& entry : freqMap) {
                freqVec.emplace_back(entry.first, entry.second);
            }

            // Sort by frequency descending, then by number descending
            sort(freqVec.begin(), freqVec.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
                if (a.second == b.second) {
                    return a.first > b.first; // Higher number first if frequencies are equal
                }
                return a.second > b.second; // Higher frequency first
            });

            // Calculate the x-sum
            int xSum = 0;
            for (int j = 0; j < min(x, static_cast<int>(freqVec.size())); ++j) {
                xSum += freqVec[j].first * freqVec[j].second;
            }

            result.push_back(xSum);
        }

        return result;          
    }
};
