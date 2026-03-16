// Source: https://leetcode.com/problems/magnetic-force-between-two-balls/   |   Difficulty: Medium
//
// Problem Description:
// In the universe Earth C-137, Rick discovered a special form of magnetic force between two balls if they are put in his new invented basket. Rick has n empty baskets, the ith basket is at position[i], Morty has m balls and needs to distribute the balls into the baskets such that the minimum magnetic force between any two balls is maximum.
//
// Rick stated that magnetic force between two different balls at positions x and y is |x - y|.
//
// Given the integer array position and the integer m. Return the required force.
//
// Example:
// Input: position = [1,2,3,4,7], m = 3
// Output: 3
// Explanation: Distributing the 3 balls into baskets 1, 4 and 7 will make the magnetic force between ball pairs [3, 3, 6]. The minimum magnetic force is 3. We cannot achieve a larger minimum magnetic force than 3.
//
// Constraints:
// n == position.length
// 	2 <= n <= 105
// 	1 <= position[i] <= 109
// 	All integers in position are distinct.
// 	2 <= m <= position.length
//

/**
 * @param {number[]} position
 * @param {number} m
 * @return {number}
 */
var maxDistance = function(position, m) {
    position.sort((a, b) => a - b);

    let left = 1;
    let right = position[position.length - 1] - position[0];
    let result = 0;

    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        let count = 1;
        let lastPosition = position[0];

        for (let i = 1; i < position.length; i++) {
            if (position[i] - lastPosition >= mid) {
                count++;
                lastPosition = position[i];
            }
        }

        if (count >= m) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
};