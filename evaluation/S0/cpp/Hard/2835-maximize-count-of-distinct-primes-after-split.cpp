// Source: https://leetcode.com/problems/maximize-count-of-distinct-primes-after-split/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums having length n and a 2D integer array queries where queries[i] = [idx, val].
//
// For each query:
//
//
// 	Update nums[idx] = val.
// 	Choose an integer k with 1 <= k < n to split the array into the non-empty prefix nums[0..k-1] and suffix nums[k..n-1] such that the sum of the counts of distinct prime values in each part is maximum.
//
//
// Note: The changes made to the array in one query persist into the next query.
//
// Return an array containing the result for each query, in the order they are given.
//
// Example:
// Input: nums = [2,1,3,1,2], queries = [[1,2],[3,3]]
//
// Output: [3,4]
//
// Explanation:
//
//
// 	Initially nums = [2, 1, 3, 1, 2].
// 	After 1st query, nums = [2, 2, 3, 1, 2]. Split nums into [2] and [2, 3, 1, 2]. [2] consists of 1 distinct prime and [2, 3, 1, 2] consists of 2 distinct primes. Hence, the answer for this query is 1 + 2 = 3.
// 	After 2nd query, nums = [2, 2, 3, 3, 2]. Split nums into [2, 2, 3] and [3, 2] with an answer of 2 + 2 = 4.
// 	The output is [3, 4].
//
// Constraints:
// 2 <= n == nums.length <= 5 * 104
// 	1 <= queries.length <= 5 * 104
// 	1 <= nums[i] <= 105
// 	0 <= queries[i][0] < nums.length
// 	1 <= queries[i][1] <= 105
//

class Solution {
public:
    vector<int> maximumCount(vector<int>& nums, vector<vector<int>>& queries) {
        const int MAX_VAL = 100000;
        vector<int> spf(MAX_VAL + 1, 0);  // Smallest prime factor
        for (int i = 2; i <= MAX_VAL; i++) {
            if (spf[i] == 0) {
                for (int j = i; j <= MAX_VAL; j += i) {
                    if (spf[j] == 0) {
                        spf[j] = i;
                    }
                }
            }
        }

        auto getDistinctPrimesCount = [&](int val) {
            unordered_set<int> primes;
            while (val > 1) {
                primes.insert(spf[val]);
                val /= spf[val];
            }
            return primes.size();
        };

        int n = nums.size();
        vector<int> prefixDistinctCount(n + 1, 0);
        unordered_set<int> seenPrimes;
        for (int i = 0; i < n; i++) {
            int countBefore = seenPrimes.size();
            int val = nums[i];
            while (val > 1) {
                seenPrimes.insert(spf[val]);
                val /= spf[val];
            }
            prefixDistinctCount[i + 1] = seenPrimes.size();
        }

        vector<int> result;
        for (const auto& query : queries) {
            int idx = query[0];
            int val = query[1];

            // Update nums[idx]
            int oldVal = nums[idx];
            nums[idx] = val;

            // Recalculate distinct primes count
            seenPrimes.clear();
            for (int i = 0; i < n; i++) {
                int currentVal = nums[i];
                while (currentVal > 1) {
                    seenPrimes.insert(spf[currentVal]);
                    currentVal /= spf[currentVal];
                }
                prefixDistinctCount[i + 1] = seenPrimes.size();
            }

            // Find maximum count after split
            int maxCount = 0;
            for (int k = 1; k < n; k++) {
                int count = prefixDistinctCount[k] + (seenPrimes.size() - prefixDistinctCount[k]);
                maxCount = max(maxCount, count);
            }
            result.push_back(maxCount);
        }

        return result;          
    }
};
