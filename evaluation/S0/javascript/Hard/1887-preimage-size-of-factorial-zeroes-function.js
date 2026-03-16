// Source: https://leetcode.com/problems/preimage-size-of-factorial-zeroes-function/   |   Difficulty: Hard
//
// Problem Description:
// Let f(x) be the number of zeroes at the end of x!. Recall that x! = 1 * 2 * 3 * ... * x and by convention, 0! = 1.
//
//
// 	For example, f(3) = 0 because 3! = 6 has no zeroes at the end, while f(11) = 2 because 11! = 39916800 has two zeroes at the end.
//
//
// Given an integer k, return the number of non-negative integers x have the property that f(x) = k.
//
// Example:
// Input: k = 0
// Output: 5
// Explanation: 0!, 1!, 2!, 3!, and 4! end with k = 0 zeroes.
//
// Constraints:
// 0 <= k <= 109
//

/**
 * @param {number} k
 * @return {number}
 */
var preimageSizeFZF = function(k) {
    // The number of trailing zeroes in x! is determined by the number of times 10 is a factor in the numbers from 1 to x. Since 10 = 2 * 5, and there are usually more factors of 2 than 5 in a factorial, we can focus on counting the number of factors of 5.
    // The formula to calculate the number of trailing zeroes in x! is:
    // f(x) = x // 5 + x // 25 + x // 125 + ... until x // 5^n is 0.
    // To find the number of non-negative integers x such that f(x) = k, we can use binary search to find the smallest x (let's call it low) such that f(low) >= k and the largest x (let's call it high) such that f(high) <= k. The number of integers x such that f(x) = k will be high - low + 1 if f(low) == k, otherwise it will be 0.
    const countTrailingZeroes = (x) => {
        let count = 0;
        while (x > 0) {
            x = Math.floor(x / 5);
            count += x;
        }
        return count;
    };
    
    let low = 0;
    let high = 5 * (k + 1);
    while (low < high) {
        const mid = Math.floor((low + high) / 2);
        if (countTrailingZeroes(mid) < k) {
            low = mid + 1;
        }
        else {            high = mid;
        }
    }
    if (countTrailingZeroes(low) !== k) {
        return 0;
    }
    let highBound = low;
    while (countTrailingZeroes(highBound) === k) {
        highBound++;
    }
    return highBound - low;
            
};
