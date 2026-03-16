// Source: https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array bloomDay, an integer m and an integer k.
//
// You want to make m bouquets. To make a bouquet, you need to use k adjacent flowers from the garden.
//
// The garden consists of n flowers, the ith flower will bloom in the bloomDay[i] and then can be used in exactly one bouquet.
//
// Return the minimum number of days you need to wait to be able to make m bouquets from the garden. If it is impossible to make m bouquets return -1.
//
// Example:
// Input: bloomDay = [1,10,3,10,2], m = 3, k = 1
// Output: 3
// Explanation: Let us see what happened in the first three days. x means flower bloomed and _ means flower did not bloom in the garden.
// We need 3 bouquets each should contain 1 flower.
// After day 1: [x, _, _, _, _]   // we can only make one bouquet.
// After day 2: [x, _, _, _, x]   // we can only make two bouquets.
// After day 3: [x, _, x, _, x]   // we can make 3 bouquets. The answer is 3.
//
// Constraints:
// bloomDay.length == n
// 	1 <= n <= 105
// 	1 <= bloomDay[i] <= 109
// 	1 <= m <= 106
// 	1 <= k <= n
//

/**
 * @param {number[]} bloomDay
 * @param {number} m
 * @param {number} k
 * @return {number}
 */
var minDays = function(bloomDay, m, k) {
    const n = bloomDay.length;
    if (m * k > n) return -1;
        
    let left = 1;
    let right = Math.max(...bloomDay);

    const canMakeBouquets = (days) => {
        let bouquets = 0;
        let flowers = 0;
        for (let day of bloomDay) {
            if (day <= days) {
                flowers += 1;
                if (flowers === k) {
                    bouquets += 1;
                    flowers = 0;
                }
            } else {




                flowers = 0;
            }
            if (bouquets >= m) return true;
        }
        return false;
    };

    while (left < right) {
        const mid = Math.floor((left + right) / 2);
        if (canMakeBouquets(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;    
        
};
