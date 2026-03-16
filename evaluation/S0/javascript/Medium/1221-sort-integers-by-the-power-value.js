// Source: https://leetcode.com/problems/sort-integers-by-the-power-value/   |   Difficulty: Medium
//
// Problem Description:
// The power of an integer x is defined as the number of steps needed to transform x into 1 using the following steps:
//
//
// 	if x is even then x = x / 2
// 	if x is odd then x = 3 * x + 1
//
//
// For example, the power of x = 3 is 7 because 3 needs 7 steps to become 1 (3 --> 10 --> 5 --> 16 --> 8 --> 4 --> 2 --> 1).
//
// Given three integers lo, hi and k. The task is to sort all integers in the interval [lo, hi] by the power value in ascending order, if two or more integers have the same power value sort them by ascending order.
//
// Return the kth integer in the range [lo, hi] sorted by the power value.
//
// Notice that for any integer x (lo <= x <= hi) it is guaranteed that x will transform into 1 using these steps and that the power of x is will fit in a 32-bit signed integer.
//
// Example:
// Input: lo = 12, hi = 15, k = 2
// Output: 13
// Explanation: The power of 12 is 9 (12 --> 6 --> 3 --> 10 --> 5 --> 16 --> 8 --> 4 --> 2 --> 1)
// The power of 13 is 9
// The power of 14 is 17
// The power of 15 is 17
// The interval sorted by the power value [12,13,14,15]. For k = 2 answer is the second element which is 13.
// Notice that 12 and 13 have the same power value and we sorted them in ascending order. Same for 14 and 15.
//
// Constraints:
// 1 <= lo <= hi <= 1000
// 	1 <= k <= hi - lo + 1
//

/**
 * @param {number} lo
 * @param {number} hi
 * @param {number} k
 * @return {number}
 */
var getKth = function(lo, hi, k) {
    const powerMap = new Map();
    const getPower = (n) => {
        if (powerMap.has(n)) return powerMap.get(n);
        let power = 0;
        let originalN = n;
        while (n !== 1) {
            if (n % 2 === 0) {
                n = n / 2;
            } else {
                n = 3 * n + 1;
            }
            power++;
        }
        powerMap.set(originalN, power);
        return power;
    };

    const arr = [];
    for (let i = lo; i <= hi; i++) {
        arr.push(i);
    }
    arr.sort((a, b) => {
        const powerA = getPower(a);
        const powerB = getPower(b);
        if (powerA === powerB) {
            return a - b;
        }
        return powerA - powerB;
    }
    );
    return arr[k - 1];  
            
};
