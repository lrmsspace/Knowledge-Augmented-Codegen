// Source: https://leetcode.com/problems/jump-game-iv/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of integers arr, you are initially positioned at the first index of the array.
//
// In one step you can jump from index i to index:
//
//
// 	i + 1 where: i + 1 < arr.length.
// 	i - 1 where: i - 1 >= 0.
// 	j where: arr[i] == arr[j] and i != j.
//
//
// Return the minimum number of steps to reach the last index of the array.
//
// Notice that you can not jump outside of the array at any time.
//
// Example:
// Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
// Output: 3
// Explanation: You need three jumps from index 0 --> 4 --> 3 --> 9. Note that index 9 is the last index of the array.
//
// Constraints:
// 1 <= arr.length <= 5 * 104
// 	-108 <= arr[i] <= 108
//

/**
 * @param {number[]} arr
 * @return {number}
 */
var minJumps = function(arr) {
    const n = arr.length;
    if (n === 1) {
        return 0;
    }
    const graph = new Map();
    for (let i = 0; i < n; i++) {
        if (!graph.has(arr[i])) {
            graph.set(arr[i], []);
        }
        graph.get(arr[i]).push(i);
    }
    const visited = new Array(n).fill(false);
    visited[0] = true;
    const queue = [[0, 0]];
    while (queue.length > 0) {
        const [index, steps] = queue.shift();
        if (index === n - 1) {
            return steps;
        }
        const neighbors = [];
        if (index - 1 >= 0) neighbors.push(index - 1);
        if (index + 1 < n) neighbors.push(index + 1);
        if (graph.has(arr[index])) {
            neighbors.push(...graph.get(arr[index]));
            graph.delete(arr[index]);
        }
        for (const next of neighbors) {
            if (!visited[next]) {
                visited[next] = true;
                queue.push([next, steps + 1]);
            }
        }
    }
    return -1;
};
