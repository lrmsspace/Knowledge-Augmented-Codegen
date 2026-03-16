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
    public boolean gcdSort(int[] nums) {
        int n = nums.length;
        int maxNum = 100000;
        UnionFind uf = new UnionFind(maxNum + 1);

        for (int num : nums) {
            for (int factor = 2; factor * factor <= num; factor++) {
                if (num % factor == 0) {
                    uf.union(num, factor);
                    uf.union(num, num / factor);
                }
            }
        }

        int[] sortedNums = nums.clone();
        Arrays.sort(sortedNums);

        for (int i = 0; i < n; i++) {
            if (uf.find(nums[i]) != uf.find(sortedNums[i])) {
                return false;
            }
        }

        return true;            
    }
}
