// Source: https://leetcode.com/problems/jump-game-iii/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of non-negative integers arr, you are initially positioned at start index of the array. When you are at index i, you can jump to i + arr[i] or i - arr[i], check if you can reach any index with value 0.
//
// Notice that you can not jump outside of the array at any time.
//
// Example:
// Input: arr = [4,2,3,0,3,1,2], start = 5
// Output: true
// Explanation: 
// All possible ways to reach at index 3 with value 0 are: 
// index 5 -> index 4 -> index 1 -> index 3 
// index 5 -> index 6 -> index 4 -> index 1 -> index 3
//
// Constraints:
// 1 <= arr.length <= 5 * 104
// 	0 <= arr[i] < arr.length
// 	0 <= start < arr.length
//

/**
 * @param {number[]} arr
 * @param {number} start
 * @return {boolean}
 */
var canReach = function(arr, start) {
    const n = arr.length;
    const visited = new Array(n).fill(false);
    const queue = [start];
        

    while (queue.length > 0) {
        const index = queue.shift();
        if (arr[index] === 0) {
            return true;
        }
        visited[index] = true;
        const forward = index + arr[index];
        const backward = index - arr[index];
        if (forward < n && !visited[forward]) {
            queue.push(forward);
        }
        if (backward >= 0 && !visited[backward]) {
            queue.push(backward);
        }
    }
    return false;   
            
};
