// Source: https://leetcode.com/problems/minimize-hamming-distance-after-swap-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays, source and target, both of length n. You are also given an array allowedSwaps where each allowedSwaps[i] = [ai, bi] indicates that you are allowed to swap the elements at index ai and index bi (0-indexed) of array source. Note that you can swap elements at a specific pair of indices multiple times and in any order.
//
// The Hamming distance of two arrays of the same length, source and target, is the number of positions where the elements are different. Formally, it is the number of indices i for 0 <= i <= n-1 where source[i] != target[i] (0-indexed).
//
// Return the minimum Hamming distance of source and target after performing any amount of swap operations on array source.
//
// Example:
// Input: source = [1,2,3,4], target = [2,1,4,5], allowedSwaps = [[0,1],[2,3]]
// Output: 1
// Explanation: source can be transformed the following way:
// - Swap indices 0 and 1: source = [2,1,3,4]
// - Swap indices 2 and 3: source = [2,1,4,3]
// The Hamming distance of source and target is 1 as they differ in 1 position: index 3.
//
// Constraints:
// n == source.length == target.length
// 	1 <= n <= 105
// 	1 <= source[i], target[i] <= 105
// 	0 <= allowedSwaps.length <= 105
// 	allowedSwaps[i].length == 2
// 	0 <= ai, bi <= n - 1
// 	ai != bi
//

class Solution {
    public int minimumHammingDistance(int[] source, int[] target, int[][] allowedSwaps) {
        int n = source.length;
        UnionFind uf = new UnionFind(n);

        for (int[] swap : allowedSwaps) {
            uf.union(swap[0], swap[1]);
        }

        Map<Integer, List<Integer>> groups = new HashMap<>();
        for (int i = 0; i < n; i++) {
            int root = uf.find(i);
            groups.computeIfAbsent(root, k -> new ArrayList<>()).add(i);
        }

        int hammingDistance = 0;
        for (List<Integer> group : groups.values()) {
            Map<Integer, Integer> countMap = new HashMap<>();
            for (int index : group) {
                countMap.put(source[index], countMap.getOrDefault(source[index], 0) + 1);
            }
            for (int index : group) {
                int targetValue = target[index];
                if (countMap.getOrDefault(targetValue, 0) > 0) {
                    countMap.put(targetValue, countMap.get(targetValue) - 1);
                } else {
                    hammingDistance++;
                }
            }
        }

        return hammingDistance;         
    }
}
