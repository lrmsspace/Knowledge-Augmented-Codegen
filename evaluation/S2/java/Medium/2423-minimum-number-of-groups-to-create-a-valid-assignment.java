// Source: https://leetcode.com/problems/minimum-number-of-groups-to-create-a-valid-assignment/   |   Difficulty: Medium
//
// Problem Description:
// You are given a collection of numbered balls and instructed to sort them into boxes for a nearly balanced distribution. There are two rules you must follow:
//
//
// 	Balls with the same box must have the same value. But, if you have more than one ball with the same number, you can put them in different boxes.
// 	The biggest box can only have one more ball than the smallest box.
//
//
// ​Return the fewest number of boxes to sort these balls following these rules.
//
// Example:
// Input:   balls = [3,2,3,2,3] 
//
// Output:   2 
//
// Explanation:
//
// We can sort balls into boxes as follows:
//
//
// 	[3,3,3]
// 	[2,2]
//
//
// The size difference between the two boxes doesn't exceed one.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minGroupsForValidAssignment(int[] balls) {
        Map<Integer, Integer> countMap = new HashMap<>();
        for (int ball : balls) {
            countMap.put(ball, countMap.getOrDefault(ball, 0) + 1);
        }

        int maxCount = Collections.max(countMap.values());
        return maxCount;            
    }
}
