// Source: https://leetcode.com/problems/count-largest-group/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer n.
//
// We need to group the numbers from 1 to n according to the sum of its digits. For example, the numbers 14 and 5 belong to the same group, whereas 13 and 3 belong to different groups.
//
// Return the number of groups that have the largest size, i.e. the maximum number of elements.
//
// Example:
// Input: n = 13
// Output: 4
// Explanation: There are 9 groups in total, they are grouped according sum of its digits of numbers from 1 to 13:
// [1,10], [2,11], [3,12], [4,13], [5], [6], [7], [8], [9].
// There are 4 groups with largest size.
//
// Constraints:
// 1 <= n <= 104
//

class Solution {
    public int countLargestGroup(int n) {
        int[] count = new int[37]; // Maximum sum of digits for n <= 10^4 is 36 (9999 -> 9+9+9+9)

        for (int i = 1; i <= n; i++) {
            int sum = digitSum(i);
            count[sum]++;
        }

        int maxSize = 0;
        int numberOfLargestGroups = 0;

        for (int size : count) {
            if (size > maxSize) {
                maxSize = size;
                numberOfLargestGroups = 1;
            } else if (size == maxSize && size != 0) {
                numberOfLargestGroups++;
            }
        }

        return numberOfLargestGroups;           
    }
}
