// Source: https://leetcode.com/problems/minimize-the-maximum-of-two-arrays/   |   Difficulty: Medium
//
// Problem Description:
// We have two arrays arr1 and arr2 which are initially empty. You need to add positive integers to them such that they satisfy all the following conditions:
//
//
// 	arr1 contains uniqueCnt1 distinct positive integers, each of which is not divisible by divisor1.
// 	arr2 contains uniqueCnt2 distinct positive integers, each of which is not divisible by divisor2.
// 	No integer is present in both arr1 and arr2.
//
//
// Given divisor1, divisor2, uniqueCnt1, and uniqueCnt2, return the minimum possible maximum integer that can be present in either array.
//
// Example:
// Input: divisor1 = 2, divisor2 = 7, uniqueCnt1 = 1, uniqueCnt2 = 3
// Output: 4
// Explanation: 
// We can distribute the first 4 natural numbers into arr1 and arr2.
// arr1 = [1] and arr2 = [2,3,4].
// We can see that both arrays satisfy all the conditions.
// Since the maximum value is 4, we return it.
//
// Constraints:
// 2 <= divisor1, divisor2 <= 105
// 	1 <= uniqueCnt1, uniqueCnt2 < 109
// 	2 <= uniqueCnt1 + uniqueCnt2 <= 109
//

class Solution {
public:
    int minimizeSet(int divisor1, int divisor2, int uniqueCnt1, int uniqueCnt2) {
        long long left = 1, right = 2e18;
        long long lcm = (long long)divisor1 * divisor2 / gcd(divisor1, divisor2);

        while (left < right) {
            long long mid = left + (right - left) / 2;

            long long notDivByDivisor1 = mid - mid / divisor1;
            long long notDivByDivisor2 = mid - mid / divisor2;
            long long notDivByBoth = mid - mid / lcm;

            long long canUseForArr1 = notDivByDivisor1 - (notDivByBoth - notDivByDivisor2);
            long long canUseForArr2 = notDivByDivisor2 - (notDivByBoth - notDivByDivisor1);

            if (canUseForArr1 >= uniqueCnt1 && canUseForArr2 >= uniqueCnt2) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return (int)left;           
    }
};
