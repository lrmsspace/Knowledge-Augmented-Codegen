// Source: https://leetcode.com/problems/count-the-number-of-square-free-subsets/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer 0-indexed array nums.
//
// A subset of the array nums is square-free if the product of its elements is a square-free integer.
//
// A square-free integer is an integer that is divisible by no square number other than 1.
//
// Return the number of square-free non-empty subsets of the array nums. Since the answer may be too large, return it modulo 109 + 7.
//
// A non-empty subset of nums is an array that can be obtained by deleting some (possibly none but not all) elements from nums. Two subsets are different if and only if the chosen indices to delete are different.
//
// Example:
// Input: nums = [3,4,4,5]
// Output: 3
// Explanation: There are 3 square-free subsets in this example:
// - The subset consisting of the 0th element [3]. The product of its elements is 3, which is a square-free integer.
// - The subset consisting of the 3rd element [5]. The product of its elements is 5, which is a square-free integer.
// - The subset consisting of 0th and 3rd elements [3,5]. The product of its elements is 15, which is a square-free integer.
// It can be proven that there are no more than 3 square-free subsets in the given array.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 30
//

class Solution {
public:
    int squareFreeSubsets(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
        vector<int> count(1 << primes.size(), 0);
        count[0] = 1; // empty subset

        for (int num : nums) {
            int mask = 0;
            bool isSquareFree = true;
            for (int i = 0; i < primes.size(); ++i) {
                int prime = primes[i];
                int primeCount = 0;
                while (num % prime == 0) {
                    num /= prime;
                    primeCount++;
                }
                if (primeCount > 1) {
                    isSquareFree = false;
                    break;
                }
                if (primeCount == 1) {
                    mask |= (1 << i);
                }
            }
            if (!isSquareFree) continue;

            for (int state = (1 << primes.size()) - 1; state >= 0; --state) {
                if ((state & mask) == 0) {
                    count[state | mask] = (count[state | mask] + count[state]) % MOD;
                }
            }
        }

        int result = 0;
        for (int state = 1; state < (1 << primes.size()); ++state) {
            result = (result + count[state]) % MOD;
        }

        return result;          
    }
};
