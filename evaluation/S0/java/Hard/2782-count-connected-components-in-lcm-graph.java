// Source: https://leetcode.com/problems/count-connected-components-in-lcm-graph/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of integers nums of size n and a positive integer threshold.
//
// There is a graph consisting of n nodes with the ith node having a value of nums[i]. Two nodes i and j in the graph are connected via an undirected edge if lcm(nums[i], nums[j]) <= threshold.
//
// Return the number of connected components in this graph.
//
// A connected component is a subgraph of a graph in which there exists a path between any two vertices, and no vertex of the subgraph shares an edge with a vertex outside of the subgraph.
//
// The term lcm(a, b) denotes the least common multiple of a and b.
//
// Example:
// Input: nums = [2,4,8,3,9], threshold = 5
//
// Output: 4
//
// Explanation: 
//
//
//
//  
//
// The four connected components are (2, 4), (3), (8), (9).
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	All elements of nums are unique.
// 	1 <= threshold <= 2 * 105
//

class Solution {
    public int countComponents(int[] nums, int threshold) {
        int n = nums.length;
        UnionFind uf = new UnionFind(n);
        Map<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < n; i++) {
            map.put(nums[i], i);
        }

        for (int i = threshold + 1; i <= 200000; i++) {
            int firstIndex = -1;
            for (int multiple = i; multiple <= 1000000000; multiple += i) {
                if (map.containsKey(multiple)) {
                    if (firstIndex == -1) {
                        firstIndex = map.get(multiple);
                    } else {
                        uf.union(firstIndex, map.get(multiple));
                    }
                }
            }
        }

        return uf.getCount();           
    }
}
