// Source: https://leetcode.com/problems/find-occurrences-of-an-element-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums, an integer array queries, and an integer x.
//
// For each queries[i], you need to find the index of the queries[i]th occurrence of x in the nums array. If there are fewer than queries[i] occurrences of x, the answer should be -1 for that query.
//
// Return an integer array answer containing the answers to all queries.
//
// Example:
// Input: nums = [1,3,1,7], queries = [1,3,2,4], x = 1
//
// Output: [0,-1,2,-1]
//
// Explanation:
//
//
// 	For the 1st query, the first occurrence of 1 is at index 0.
// 	For the 2nd query, there are only two occurrences of 1 in nums, so the answer is -1.
// 	For the 3rd query, the second occurrence of 1 is at index 2.
// 	For the 4th query, there are only two occurrences of 1 in nums, so the answer is -1.
//
// Constraints:
// 1 <= nums.length, queries.length <= 105
// 	1 <= queries[i] <= 105
// 	1 <= nums[i], x <= 104
//

class Solution {
    public int[] occurrencesOfElement(int[] nums, int[] queries, int x) {
        List<Integer> positions = new ArrayList<>();
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] == x) {
                positions.add(i);
            }
        }

        int[] result = new int[queries.length];
        for (int i = 0; i < queries.length; i++) {
            int occurrenceIndex = queries[i] - 1; // Convert to 0-based index
            if (occurrenceIndex < positions.size()) {
                result[i] = positions.get(occurrenceIndex);
            } else {
                result[i] = -1;
            }
        }

        return result;          
    }
}
