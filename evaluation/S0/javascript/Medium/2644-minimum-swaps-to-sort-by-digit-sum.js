// Source: https://leetcode.com/problems/minimum-swaps-to-sort-by-digit-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums of distinct positive integers. You need to sort the array in increasing order based on the sum of the digits of each number. If two numbers have the same digit sum, the smaller number appears first in the sorted order.
//
// Return the minimum number of swaps required to rearrange nums into this sorted order.
//
// A swap is defined as exchanging the values at two distinct positions in the array.
//
// Example:
// Input: nums = [37,100]
//
// Output: 1
//
// Explanation:
//
//
// 	Compute the digit sum for each integer: [3 + 7 = 10, 1 + 0 + 0 = 1] → [10, 1]
// 	Sort the integers based on digit sum: [100, 37]. Swap 37 with 100 to obtain the sorted order.
// 	Thus, the minimum number of swaps required to rearrange nums is 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	nums consists of distinct positive integers.
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var minSwaps = function(nums) {
    const n = nums.length;
    const digitSums = nums.map(num => {
        let sum = 0;
        while (num > 0) {
            sum += num % 10;
            num = Math.floor(num / 10);
        }
        return sum;
    });
    const pairs = nums.map((num, index) => [digitSums[index], num]);
    pairs.sort((a, b) => {
        if (a[0] === b[0]) {
            return a[1] - b[1];
        }
        return a[0] - b[0];
    });
    const visited = Array(n).fill(false);
    let swaps = 0;
    for (let i = 0; i < n; i++) {
        if (visited[i] || pairs[i][1] === nums[i]) {
            continue;
        }
        let cycleSize = 0;
        let j = i;
        while (!visited[j]) {
            visited[j] = true;
            j = pairs.findIndex(pair => pair[1] === nums[j]);
            cycleSize++;
        }
        if (cycleSize > 0) {
            swaps += (cycleSize - 1);
        }
    }
    return swaps;   
};
