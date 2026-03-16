// Source: https://leetcode.com/problems/the-number-of-beautiful-subsets/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums of positive integers and a positive integer k.
//
// A subset of nums is beautiful if it does not contain two integers with an absolute difference equal to k.
//
// Return the number of non-empty beautiful subsets of the array nums.
//
// A subset of nums is an array that can be obtained by deleting some (possibly none) elements from nums. Two subsets are different if and only if the chosen indices to delete are different.
//
// Example:
// Input: nums = [2,4,6], k = 2
// Output: 4
// Explanation: The beautiful subsets of the array nums are: [2], [4], [6], [2, 6].
// It can be proved that there are only 4 beautiful subsets in the array [2,4,6].
//
// Constraints:
// 1 <= nums.length <= 18
// 	1 <= nums[i], k <= 1000
//

class Solution {
    public int beautifulSubsets(int[] nums, int k) {
        Map<Integer, Integer> countMap = new HashMap<>();
        for (int num : nums) {
            countMap.put(num, countMap.getOrDefault(num, 0) + 1);
        }

        List<List<Integer>> groups = new ArrayList<>();
        Set<Integer> visited = new HashSet<>();

        for (int num : countMap.keySet()) {
            if (visited.contains(num)) {
                continue;
            }

            List<Integer> group = new ArrayList<>();
            int current = num;
            while (countMap.containsKey(current)) {
                group.add(current);
                visited.add(current);
                current += k;
            }
            groups.add(group);
        }

        int result = 1;
        for (List<Integer> group : groups) {
            int m = group.size();
            int groupWays = 1 << m; // Total subsets

            // Subtract invalid subsets
            int invalidWays = 0;
            for (int mask = 0; mask < (1 << m); mask++) {
                boolean isValid = true;
                for (int i = 0; i < m - 1; i++) {
                    if (((mask >> i) & 1) == 1 && ((mask >> (i + 1)) & 1) == 1) {
                        isValid = false;
                        break;
                    }
                }
                if (!isValid) {
                    invalidWays++;
                }
            }

            groupWays -= invalidWays;

            // Calculate the number of ways considering counts
            int waysWithCounts = 1;
            for (int i = 0; i < m; i++) {
                int count = countMap.get(group.get(i));
                waysWithCounts *= (count + 1);
            }

            result *= (waysWithCounts - (groupWays - 1));
        }

        return result - 1; // Exclude empty subset          
    }
}
