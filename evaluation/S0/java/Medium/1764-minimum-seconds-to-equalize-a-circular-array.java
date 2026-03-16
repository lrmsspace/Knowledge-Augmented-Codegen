// Source: https://leetcode.com/problems/minimum-seconds-to-equalize-a-circular-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums containing n integers.
//
// At each second, you perform the following operation on the array:
//
//
// 	For every index i in the range [0, n - 1], replace nums[i] with either nums[i], nums[(i - 1 + n) % n], or nums[(i + 1) % n].
//
//
// Note that all the elements get replaced simultaneously.
//
// Return the minimum number of seconds needed to make all elements in the array nums equal.
//
// Example:
// Input: nums = [1,2,1,2]
// Output: 1
// Explanation: We can equalize the array in 1 second in the following way:
// - At 1st second, replace values at each index with [nums[3],nums[1],nums[3],nums[3]]. After replacement, nums = [2,2,2,2].
// It can be proven that 1 second is the minimum amount of seconds needed for equalizing the array.
//
// Constraints:
// 1 <= n == nums.length <= 105
// 	1 <= nums[i] <= 109
//

class Solution {
    public int minimumSeconds(List<Integer> nums) {
        int n = nums.size();
        Map<Integer, List<Integer>> positionsMap = new HashMap<>();

        // Store positions of each number in the map
        for (int i = 0; i < n; i++) {
            positionsMap.computeIfAbsent(nums.get(i), k -> new ArrayList<>()).add(i);
        }

        int minSeconds = Integer.MAX_VALUE;

        // Calculate minimum seconds for each unique number
        for (List<Integer> positions : positionsMap.values()) {
            int maxGap = 0;
            int size = positions.size();

            // Calculate gaps between consecutive positions
            for (int i = 0; i < size; i++) {
                int current = positions.get(i);
                int next = positions.get((i + 1) % size);
                if (next <= current) {
                    next += n; // Wrap around for circular array
                }
                int gap = next - current - 1; // Exclude the positions themselves
                maxGap = Math.max(maxGap, gap);
            }

            // Calculate seconds needed for this number
            int secondsNeeded = (maxGap + 1) / 2;
            minSeconds = Math.min(minSeconds, secondsNeeded);
        }

        return minSeconds;          
    }
}
