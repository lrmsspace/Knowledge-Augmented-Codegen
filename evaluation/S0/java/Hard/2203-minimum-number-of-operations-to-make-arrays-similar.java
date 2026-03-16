// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-arrays-similar/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integer arrays nums and target, of the same length.
//
// In one operation, you can choose any two distinct indices i and j where 0 <= i, j < nums.length and:
//
//
// 	set nums[i] = nums[i] + 2 and
// 	set nums[j] = nums[j] - 2.
//
//
// Two arrays are considered to be similar if the frequency of each element is the same.
//
// Return the minimum number of operations required to make nums similar to target. The test cases are generated such that nums can always be similar to target.
//
// Example:
// Input: nums = [8,12,6], target = [2,14,10]
// Output: 2
// Explanation: It is possible to make nums similar to target in two operations:
// - Choose i = 0 and j = 2, nums = [10,12,4].
// - Choose i = 1 and j = 2, nums = [10,14,2].
// It can be shown that 2 is the minimum number of operations needed.
//
// Constraints:
// n == nums.length == target.length
// 	1 <= n <= 105
// 	1 <= nums[i], target[i] <= 106
// 	It is possible to make nums similar to target.
//

class Solution {
    public long makeSimilar(int[] nums, int[] target) {
        List<Integer> evenNums = new ArrayList<>();
        List<Integer> oddNums = new ArrayList<>();
        List<Integer> evenTarget = new ArrayList<>();
        List<Integer> oddTarget = new ArrayList<>();

        for (int num : nums) {
            if (num % 2 == 0) {
                evenNums.add(num);
            } else {
                oddNums.add(num);
            }
        }

        for (int num : target) {
            if (num % 2 == 0) {
                evenTarget.add(num);
            } else {
                oddTarget.add(num);
            }
        }

        Collections.sort(evenNums);
        Collections.sort(oddNums);
        Collections.sort(evenTarget);
        Collections.sort(oddTarget);

        long operations = 0;

        for (int i = 0; i < evenNums.size(); i++) {
            operations += Math.abs(evenNums.get(i) - evenTarget.get(i)) / 2;
        }

        for (int i = 0; i < oddNums.size(); i++) {
            operations += Math.abs(oddNums.get(i) - oddTarget.get(i)) / 2;
        }

        return operations / 2;          
    }
}
