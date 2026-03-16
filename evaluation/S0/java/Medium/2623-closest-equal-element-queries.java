// Source: https://leetcode.com/problems/closest-equal-element-queries/   |   Difficulty: Medium
//
// Problem Description:
// You are given a circular array nums and an array queries.
//
// For each query i, you have to find the following:
//
//
// 	The minimum distance between the element at index queries[i] and any other index j in the circular array, where nums[j] == nums[queries[i]]. If no such index exists, the answer for that query should be -1.
//
//
// Return an array answer of the same size as queries, where answer[i] represents the result for query i.
//
// Example:
// Input: nums = [1,3,1,4,1,3,2], queries = [0,3,5]
//
// Output: [2,-1,3]
//
// Explanation:
//
//
// 	Query 0: The element at queries[0] = 0 is nums[0] = 1. The nearest index with the same value is 2, and the distance between them is 2.
// 	Query 1: The element at queries[1] = 3 is nums[3] = 4. No other index contains 4, so the result is -1.
// 	Query 2: The element at queries[2] = 5 is nums[5] = 3. The nearest index with the same value is 1, and the distance between them is 3 (following the circular path: 5 -> 6 -> 0 -> 1).
//
// Constraints:
// 1 <= queries.length <= nums.length <= 105
// 	1 <= nums[i] <= 106
// 	0 <= queries[i] < nums.length
//

class Solution {
    public List<Integer> solveQueries(int[] nums, int[] queries) {
        int n = nums.length;
        Map<Integer, List<Integer>> indexMap = new HashMap<>();

        // Build a map of number to its indices in the array
        for (int i = 0; i < n; i++) {
            indexMap.computeIfAbsent(nums[i], k -> new ArrayList<>()).add(i);
        }

        List<Integer> result = new ArrayList<>();

        // Process each query
        for (int query : queries) {
            int targetNum = nums[query];
            List<Integer> indices = indexMap.get(targetNum);

            if (indices.size() == 1) {
                // Only one occurrence of the number
                result.add(-1);
                continue;
            }

            // Find the closest index using binary search
            int pos = Collections.binarySearch(indices, query);
            if (pos < 0) {
                pos = -(pos + 1);
            }

            int leftIndex = (pos - 1 + indices.size()) % indices.size();
            int rightIndex = pos % indices.size();

            int leftDistance = Math.abs(query - indices.get(leftIndex));
            int rightDistance = Math.abs(indices.get(rightIndex) - query);

            // Since it's a circular array, consider wrap-around distances
            leftDistance = Math.min(leftDistance, n - leftDistance);
            rightDistance = Math.min(rightDistance, n - rightDistance);

            result.add(Math.min(leftDistance, rightDistance));
        }

        return result;          
    }
}
