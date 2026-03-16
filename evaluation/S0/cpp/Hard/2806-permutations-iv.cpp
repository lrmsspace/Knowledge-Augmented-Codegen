// Source: https://leetcode.com/problems/permutations-iv/   |   Difficulty: Hard
//
// Problem Description:
// Given two integers, n and k, an alternating permutation is a permutation of the first n positive integers such that no two adjacent elements are both odd or both even.
//
// Return the k-th alternating permutation sorted in lexicographical order. If there are fewer than k valid alternating permutations, return an empty list.
//
// Example:
// Input: n = 4, k = 6
//
// Output: [3,4,1,2]
//
// Explanation:
//
// The lexicographically-sorted alternating permutations of [1, 2, 3, 4] are:
//
//
// 	[1, 2, 3, 4]
// 	[1, 4, 3, 2]
// 	[2, 1, 4, 3]
// 	[2, 3, 4, 1]
// 	[3, 2, 1, 4]
// 	[3, 4, 1, 2] ← 6th permutation
// 	[4, 1, 2, 3]
// 	[4, 3, 2, 1]
//
//
// Since k = 6, we return [3, 4, 1, 2].
//
// Constraints:
// 1 <= n <= 100
// 	1 <= k <= 1015
//

class Solution {
public:
    vector<int> permute(int n, long long k) {
        vector<int> odd, even;
        for (int i = 1; i <= n; i++) {
            if (i % 2 == 1) odd.push_back(i);
            else even.push_back(i);
        }
        
        int oddCount = odd.size();
        int evenCount = even.size();
        
        // Precompute factorials
        vector<long long> fact(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            fact[i] = fact[i - 1] * i;
        }
        
        auto countPermutations = [&](int o, int e) -> long long {
            if (abs(o - e) > 1) return 0;
            long long res = fact[o] * fact[e];
            return res;
        };
        
        vector<int> result;
        for (int i = 0; i < n; i++) {
            bool needOdd = (i % 2 == 0) ? (oddCount >= evenCount) : (oddCount < evenCount);
            vector<int>& pool = needOdd ? odd : even;
            
            bool found = false;
            for (int j = 0; j < pool.size(); j++) {
                int val = pool[j];
                
                // Temporarily remove val from pool
                pool.erase(pool.begin() + j);
                
                long long cnt = countPermutations(oddCount - (needOdd ? 1 : 0), evenCount - (needOdd ? 0 : 1));
                
                if (cnt >= k) {
                    result.push_back(val);
                    if (needOdd) oddCount--;
                    else evenCount--;
                    found = true;
                    break;
                } else {
                    k -= cnt;
                    // Restore val to pool
                    pool.insert(pool.begin() + j, val);
                }
            }
            
            if (!found) return {};
        }
        
        return result;          
    }
};
