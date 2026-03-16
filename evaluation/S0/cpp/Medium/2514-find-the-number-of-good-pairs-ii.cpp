// Source: https://leetcode.com/problems/find-the-number-of-good-pairs-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given 2 integer arrays nums1 and nums2 of lengths n and m respectively. You are also given a positive integer k.
//
// A pair (i, j) is called good if nums1[i] is divisible by nums2[j] * k (0 <= i <= n - 1, 0 <= j <= m - 1).
//
// Return the total number of good pairs.
//
// Example:
// Input: nums1 = [1,3,4], nums2 = [1,3,4], k = 1
//
// Output: 5
//
// Explanation:
// The 5 good pairs are (0, 0), (1, 0), (1, 1), (2, 0), and (2, 2).
//
// Constraints:
// 1 <= n, m <= 105
// 	1 <= nums1[i], nums2[j] <= 106
// 	1 <= k <= 103
//

class Solution {
public:
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        unordered_map<int, long long> freqMap;
        for (int num : nums2) {
            freqMap[num]++;
        }

        long long totalPairs = 0;
        for (int num : nums1) {
            for (const auto& [num2, count] : freqMap) {
                if (num % (num2 * k) == 0) {
                    totalPairs += count;
                }
            }
        }

        return totalPairs;          
    }
};
