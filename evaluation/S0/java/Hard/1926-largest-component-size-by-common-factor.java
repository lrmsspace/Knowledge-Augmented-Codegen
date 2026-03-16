// Source: https://leetcode.com/problems/largest-component-size-by-common-factor/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array of unique positive integers nums. Consider the following graph:
//
//
// 	There are nums.length nodes, labeled nums[0] to nums[nums.length - 1],
// 	There is an undirected edge between nums[i] and nums[j] if nums[i] and nums[j] share a common factor greater than 1.
//
//
// Return the size of the largest connected component in the graph.
//
// Example:
// Input: nums = [4,6,15,35]
// Output: 4
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	1 <= nums[i] <= 105
// 	All the values of nums are unique.
//

class Solution {
    public int largestComponentSize(int[] nums) {
        int n = nums.length;
        UnionFind uf = new UnionFind(n);
        Map<Integer, Integer> factorToIndex = new HashMap<>();

        for (int i = 0; i < n; i++) {
            int num = nums[i];
            for (int factor = 2; factor * factor <= num; factor++) {
                if (num % factor == 0) {
                    factorToIndex.putIfAbsent(factor, i);
                    uf.union(i, factorToIndex.get(factor));

                    int complementFactor = num / factor;
                    factorToIndex.putIfAbsent(complementFactor, i);
                    uf.union(i, factorToIndex.get(complementFactor));
                }
            }
            if (num > 1) {
                factorToIndex.putIfAbsent(num, i);
                uf.union(i, factorToIndex.get(num));
            }
        }

        return uf.getMaxComponentSize();                    
    }
}
