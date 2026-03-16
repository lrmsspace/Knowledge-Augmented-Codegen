// Source: https://leetcode.com/problems/sorted-gcd-pair-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums of length n and an integer array queries.
//
// Let gcdPairs denote an array obtained by calculating the GCD of all possible pairs (nums[i], nums[j]), where 0 <= i < j < n, and then sorting these values in ascending order.
//
// For each query queries[i], you need to find the element at index queries[i] in gcdPairs.
//
// Return an integer array answer, where answer[i] is the value at gcdPairs[queries[i]] for each query.
//
// The term gcd(a, b) denotes the greatest common divisor of a and b.
//
// Example:
// Input: nums = [2,3,4], queries = [0,2,2]
//
// Output: [1,2,2]
//
// Explanation:
//
// gcdPairs = [gcd(nums[0], nums[1]), gcd(nums[0], nums[2]), gcd(nums[1], nums[2])] = [1, 2, 1].
//
// After sorting in ascending order, gcdPairs = [1, 1, 2].
//
// So, the answer is [gcdPairs[queries[0]], gcdPairs[queries[1]], gcdPairs[queries[2]]] = [1, 2, 2].
//
// Constraints:
// 2 <= n == nums.length <= 105
// 	1 <= nums[i] <= 5 * 104
// 	1 <= queries.length <= 105
// 	0 <= queries[i] < n * (n - 1) / 2
//

class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        const int MAX_NUM = 50000;
        vector<int> freq(MAX_NUM + 1, 0);
        
        // Count frequency of each number
        for (int num : nums) {
            freq[num]++;
        }
        
        // Count occurrences of each GCD
        vector<long long> gcdCount(MAX_NUM + 1, 0);
        
        for (int g = 1; g <= MAX_NUM; g++) {
            long long count = 0;
            for (int multiple = g; multiple <= MAX_NUM; multiple += g) {
                count += freq[multiple];
            }
            if (count >= 2) {
                gcdCount[g] = count * (count - 1) / 2;
            }
        }
        
        // Prepare prefix sums
        for (int i = 1; i <= MAX_NUM; i++) {
            gcdCount[i] += gcdCount[i - 1];
        }
        
        // Answer queries
        vector<int> result;
        for (long long q : queries) {
            // Binary search to find the GCD value for the query
            int left = 1, right = MAX_NUM;
            while (left < right) {
                int mid = left + (right - left) / 2;
                if (gcdCount[mid] > q) {
                    right = mid;
                } else {
                    left = mid + 1;
                }
            }
            result.push_back(left);
        }
        
        return result;          
    }
};
