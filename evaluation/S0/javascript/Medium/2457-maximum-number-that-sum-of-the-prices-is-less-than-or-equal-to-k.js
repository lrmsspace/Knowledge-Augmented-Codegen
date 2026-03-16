// Source: https://leetcode.com/problems/maximum-number-that-sum-of-the-prices-is-less-than-or-equal-to-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer k and an integer x. The price of a number num is calculated by the count of set bits at positions x, 2x, 3x, etc., in its binary representation, starting from the least significant bit. The following table contains examples of how price is calculated.
//
//
// 	
// 		
// 			x
// 			num
// 			Binary Representation
// 			Price
// 		
// 		
// 			1
// 			13
// 			000001101
// 			3
// 		
// 		
// 			2
// 			13
// 			000001101
// 			1
// 		
// 		
// 			2
// 			233
// 			011101001
// 			3
// 		
// 		
// 			3
// 			13
// 			000001101
// 			1
// 		
// 		
// 			3
// 			362
// 			101101010
// 			2
// 		
// 	
//
//
// The accumulated price of num is the total price of numbers from 1 to num. num is considered cheap if its accumulated price is less than or equal to k.
//
// Return the greatest cheap number.
//
// Example:
// Input: k = 9, x = 1
//
// Output: 6
//
// Explanation:
//
// As shown in the table below, 6 is the greatest cheap number.
//
//
// 	
// 		
// 			x
// 			num
// 			Binary Representation
// 			Price
// 			Accumulated Price
// 		
// 		
// 			1
// 			1
// 			001
// 			1
// 			1
// 		
// 		
// 			1
// 			2
// 			010
// 			1
// 			2
// 		
// 		
// 			1
// 			3
// 			011
// 			2
// 			4
// 		
// 		
// 			1
// 			4
// 			100
// 			1
// 			5
// 		
// 		
// 			1
// 			5
// 			101
// 			2
// 			7
// 		
// 		
// 			1
// 			6
// 			110
// 			2
// 			9
// 		
// 		
// 			1
// 			7
// 			111
// 			3
// 			12
//
// Constraints:
// 1 <= k <= 1015
// 	1 <= x <= 8
//

/**
 * @param {number} k
 * @param {number} x
 * @return {number}
 */
var findMaximumNumber = function(k, x) {
    let left = 1;
    let right = 1e15;
    let result = 0;
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        let accumulatedPrice = 0;
        for (let num = 1; num <= mid; num++) {
            let price = 0;
            let bitPosition = x;
            while (bitPosition <= 60) {
                if ((num >> (bitPosition - 1)) & 1) {
                    price++;
                }
                bitPosition += x;
            }
            accumulatedPrice += price;
            if (accumulatedPrice > k) {
                break;
            }
        }
        if (accumulatedPrice <= k) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
};
