// Source: https://leetcode.com/problems/gcd-sort-of-an-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums, and you can perform the following operation any number of times on nums:
//
//
// 	Swap the positions of two elements nums[i] and nums[j] if gcd(nums[i], nums[j]) > 1 where gcd(nums[i], nums[j]) is the greatest common divisor of nums[i] and nums[j].
//
//
// Return true if it is possible to sort nums in non-decreasing order using the above swap method, or false otherwise.
//
// Example:
// Input: nums = [7,21,3]
// Output: true
// Explanation: We can sort [7,21,3] by performing the following operations:
// - Swap 7 and 21 because gcd(7,21) = 7. nums = [21,7,3]
// - Swap 21 and 3 because gcd(21,3) = 3. nums = [3,7,21]
//
// Constraints:
// 1 <= nums.length <= 3 * 104
// 	2 <= nums[i] <= 105
//

class Solution {
public:
    bool gcdSort(vector<int>& nums) {
        int n = nums.size();
        vector<int> sortedNums = nums;
        sort(sortedNums.begin(), sortedNums.end());
        
        // Union-Find data structure
        vector<int> parent(100001);
        for (int i = 0; i <= 100000; i++) {
            parent[i] = i;
        }
        
        function<int(int)> find = [&](int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };
        
        auto unite = [&](int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX != rootY) {
                parent[rootY] = rootX;
            }
        };
        
        // Sieve of Eratosthenes to find primes
        vector<int> spf(100001); // smallest prime factor
        for (int i = 2; i <= 100000; i++) {
            if (spf[i] == 0) {
                for (int j = i; j <= 100000; j += i) {
                    if (spf[j] == 0) {
                        spf[j] = i;
                    }
                }
            }
        }
        
        // Union numbers by their prime factors
        for (int num : nums) {
            int x = num;
            while (x > 1) {
                int primeFactor = spf[x];
                unite(num, primeFactor);
                while (x % primeFactor == 0) {
                    x /= primeFactor;
                }
            }
        }
        
        // Check if each number can be connected to its sorted position
        for (int i = 0; i < n; i++) {
            if (find(nums[i]) != find(sortedNums[i])) {
                return false;
            }
        }
        
        return true;            
    }
};
