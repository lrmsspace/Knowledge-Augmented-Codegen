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

/**
 * @param {number} divisor1
 * @param {number} divisor2
 * @param {number} uniqueCnt1
 * @param {number} uniqueCnt2
 * @return {number}
 */
var minimizeSet = function(divisor1, divisor2, uniqueCnt1, uniqueCnt2) {
    const gcd = (a, b) => {
        while (b !== 0) {
            [a, b] = [b, a % b];
        }
        return a;
    };

    const lcm = (a, b) => (a * b) / gcd(a, b);
    const lcmDiv = lcm(divisor1, divisor2);

    const countValidNumbers = (x) => {
        const total = x;
        const div1Count = Math.floor(x / divisor1);
        const div2Count = Math.floor(x / divisor2);
        const bothDivCount = Math.floor(x / lcmDiv);
        const notDiv1 = total - div1Count;
        const notDiv2 = total - div2Count;
        const notEither = total - div1Count - div2Count + bothDivCount;
        return { notDiv1, notDiv2, notEither };
    }
    let left = 1;
    let right = 1e18;
    let result = right;
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        const { notDiv1, notDiv2, notEither } = countValidNumbers(mid);
        if (notDiv1 >= uniqueCnt1 && notDiv2 >= uniqueCnt2 && notEither >= uniqueCnt1 + uniqueCnt2) {
            result = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return result;  
};
