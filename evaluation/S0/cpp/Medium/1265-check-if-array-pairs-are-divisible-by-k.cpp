// Source: https://leetcode.com/problems/check-if-array-pairs-are-divisible-by-k/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers arr of even length n and an integer k.
//
// We want to divide the array into exactly n / 2 pairs such that the sum of each pair is divisible by k.
//
// Return true If you can find a way to do that or false otherwise.
//
// Example:
// Input: arr = [1,2,3,4,5,10,6,7,8,9], k = 5
// Output: true
// Explanation: Pairs are (1,9),(2,8),(3,7),(4,6) and (5,10).
//
// Constraints:
// arr.length == n
// 	1 <= n <= 105
// 	n is even.
// 	-109 <= arr[i] <= 109
// 	1 <= k <= 105
//

class Solution {
public:
    bool canArrange(vector<int>& arr, int k) {
        unordered_map<int, int> remainderCount;
        for (int num : arr) {
            int rem = ((num % k) + k) % k; // Handle negative numbers
            remainderCount[rem]++;
        }

        for (const auto& [rem, count] : remainderCount) {
            if (rem == 0) {
                if (count % 2 != 0) return false;
            } else {
                int complement = k - rem;
                if (remainderCount[complement] != count) return false;
            }
        }

        return true;            
    }
};
