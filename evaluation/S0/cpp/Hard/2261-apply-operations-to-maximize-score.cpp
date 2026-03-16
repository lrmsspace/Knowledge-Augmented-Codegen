// Source: https://leetcode.com/problems/apply-operations-to-maximize-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums of n positive integers and an integer k.
//
// Initially, you start with a score of 1. You have to maximize your score by applying the following operation at most k times:
//
//
// 	Choose any non-empty subarray nums[l, ..., r] that you haven't chosen previously.
// 	Choose an element x of nums[l, ..., r] with the highest prime score. If multiple such elements exist, choose the one with the smallest index.
// 	Multiply your score by x.
//
//
// Here, nums[l, ..., r] denotes the subarray of nums starting at index l and ending at the index r, both ends being inclusive.
//
// The prime score of an integer x is equal to the number of distinct prime factors of x. For example, the prime score of 300 is 3 since 300 = 2 * 2 * 3 * 5 * 5.
//
// Return the maximum possible score after applying at most k operations.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [8,3,9,3,8], k = 2
// Output: 81
// Explanation: To get a score of 81, we can apply the following operations:
// - Choose subarray nums[2, ..., 2]. nums[2] is the only element in this subarray. Hence, we multiply the score by nums[2]. The score becomes 1 * 9 = 9.
// - Choose subarray nums[2, ..., 3]. Both nums[2] and nums[3] have a prime score of 1, but nums[2] has the smaller index. Hence, we multiply the score by nums[2]. The score becomes 9 * 9 = 81.
// It can be proven that 81 is the highest score one can obtain.
//
// Constraints:
// 1 <= nums.length == n <= 105
// 	1 <= nums[i] <= 105
// 	1 <= k <= min(n * (n + 1) / 2, 109)
//

class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        const int MOD = 1e9 + 7;
        const int MAX_N = 1e5 + 5;
        
        // Precompute smallest prime factors
        vector<int> spf(MAX_N, 0);
        for (int i = 2; i < MAX_N; i++) {
            if (spf[i] == 0) {
                for (int j = i; j < MAX_N; j += i) {
                    if (spf[j] == 0) spf[j] = i;
                }
            }
        }
        
        // Function to compute prime score
        auto primeScore = [&](int x) {
            unordered_set<int> primes;
            while (x > 1) {
                primes.insert(spf[x]);
                x /= spf[x];
            }
            return primes.size();
        };
        
        int n = nums.size();
        vector<int> left(n), right(n);
        stack<int> stk;
        
        // Next greater element to the left
        for (int i = 0; i < n; i++) {
            while (!stk.empty() && primeScore(nums[stk.top()]) < primeScore(nums[i])) {
                stk.pop();
            }
            left[i] = stk.empty() ? -1 : stk.top();
            stk.push(i);
        }
        
        while (!stk.empty()) stk.pop();
        
        // Next greater element to the right
        for (int i = n - 1; i >= 0; i--) {
            while (!stk.empty() && primeScore(nums[stk.top()]) <= primeScore(nums[i])) {
                stk.pop();
            }
            right[i] = stk.empty() ? n : stk.top();
            stk.push(i);
        }
        
        // Create array of indices sorted by nums values in descending order
        vector<int> indices(n);
        iota(indices.begin(), indices.end(), 0);
        sort(indices.begin(), indices.end(), [&](int a, int b) {
            return nums[a] > nums[b];
        });
        
        long long result = 1;
        
        for (int idx : indices) {
            long long count = (long long)(idx - left[idx]) * (right[idx] - idx);
            long long use = min(count, (long long)k);
            result = (result * modPow(nums[idx], use, MOD)) % MOD;
            k -= use;
            if (k == 0) break;
        }
        return (int)result;
    }
};
