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
public:
    int countLargestGroup(int n) {
        vector<int> digitSumCount(37, 0); // Maximum digit sum for n <= 10^4 is 36 (9999 -> 9+9+9+9)

        for (int i = 1; i <= n; ++i) {
            int sum = 0, num = i;
            while (num > 0) {
                sum += num % 10;
                num /= 10;
            }
            digitSumCount[sum]++;
        }

        int maxSize = *max_element(digitSumCount.begin(), digitSumCount.end());
        int largestGroupCount = count(digitSumCount.begin(), digitSumCount.end(), maxSize);

        return largestGroupCount;           
    }
};
