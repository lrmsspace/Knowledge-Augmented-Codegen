// Source: https://leetcode.com/problems/frog-jump-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array stones sorted in strictly increasing order representing the positions of stones in a river.
//
// A frog, initially on the first stone, wants to travel to the last stone and then return to the first stone. However, it can jump to any stone at most once.
//
// The length of a jump is the absolute difference between the position of the stone the frog is currently on and the position of the stone to which the frog jumps.
//
//
// 	More formally, if the frog is at stones[i] and is jumping to stones[j], the length of the jump is |stones[i] - stones[j]|.
//
//
// The cost of a path is the maximum length of a jump among all jumps in the path.
//
// Return the minimum cost of a path for the frog.
//
// Example:
// Input: stones = [0,2,5,6,7]
// Output: 5
// Explanation: The above figure represents one of the optimal paths the frog can take.
// The cost of this path is 5, which is the maximum length of a jump.
// Since it is not possible to achieve a cost of less than 5, we return it.
//
// Constraints:
// 2 <= stones.length <= 105
// 	0 <= stones[i] <= 109
// 	stones[0] == 0
// 	stones is sorted in a strictly increasing order.
//

/**
 * @param {number[]} stones
 * @return {number}
 */
var maxJump = function(stones) {
    let maxJumpLength = 0;
    for (let i = 2; i < stones.length; i++) {
        const jumpLength = stones[i] - stones[i - 2];
        maxJumpLength = Math.max(maxJumpLength, jumpLength);
    }
    return maxJumpLength;
};
