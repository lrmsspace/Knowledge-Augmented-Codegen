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

/**
 * @param {number[]} nums
 * @return {boolean}
 */
var gcdSort = function(nums) {
    const n = nums.length;
    const maxNum = Math.max(...nums);
    const primes = getPrimes(maxNum);
    const primeToIndex = new Map();
    for (let i = 0; i < primes.length; i += 1) {
        primeToIndex.set(primes[i], i);
    }

    const uf = new UnionFind(primes.length);
    for (const num of nums) {
        let x = num;
        for (const prime of primes) {
            if (prime * prime > x) {
                break;
            }
            if (x % prime === 0) {
                uf.union(primeToIndex.get(prime), primeToIndex.get(num));
                while (x % prime === 0) {
                    x /= prime;
                }
            }
        }
        if (x > 1) {
            uf.union(primeToIndex.get(x), primeToIndex.get(num));
        }
    }

    const sortedNums = [...nums].sort((a, b) => a - b);
    for (let i = 0; i < n; i += 1) {
        if (uf.find(primeToIndex.get(nums[i])) !== uf.find(primeToIndex.get(sortedNums[i]))) {
            return false;
        }
    }
    return true;    
};
