// Source: https://leetcode.com/problems/maximize-the-minimum-game-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array points of size n and an integer m. There is another array gameScore of size n, where gameScore[i] represents the score achieved at the ith game. Initially, gameScore[i] == 0 for all i.
//
// You start at index -1, which is outside the array (before the first position at index 0). You can make at most m moves. In each move, you can either:
//
//
// 	Increase the index by 1 and add points[i] to gameScore[i].
// 	Decrease the index by 1 and add points[i] to gameScore[i].
//
//
// Note that the index must always remain within the bounds of the array after the first move.
//
// Return the maximum possible minimum value in gameScore after at most m moves.
//
// Example:
// Input: points = [2,4], m = 3
//
// Output: 4
//
// Explanation:
//
// Initially, index i = -1 and gameScore = [0, 0].
//
//
// 	
// 		
// 			Move
// 			Index
// 			gameScore
// 		
// 	
// 	
// 		
// 			Increase i
// 			0
// 			[2, 0]
// 		
// 		
// 			Increase i
// 			1
// 			[2, 4]
// 		
// 		
// 			Decrease i
// 			0
// 			[4, 4]
// 		
// 	
//
//
// The minimum value in gameScore is 4, and this is the maximum possible minimum among all configurations. Hence, 4 is the output.
//
// Constraints:
// 2 <= n == points.length <= 5 * 104
// 	1 <= points[i] <= 106
// 	1 <= m <= 109
//

/**
 * @param {number[]} points
 * @param {number} m
 * @return {number}
 */
var maxScore = function(points, m) {
    const n = points.length;

    const canAchieve = (target) => {
        let movesLeft = m;
        let score = Array(n).fill(0);
        let currentIndex = -1;
        while (movesLeft > 0) {
            if (currentIndex + 1 < n && score[currentIndex + 1] + points[currentIndex + 1] <= target) {
                currentIndex++;
                score[currentIndex] += points[currentIndex];
                movesLeft--;
            }
            else if (currentIndex - 1 >= 0 && score[currentIndex - 1] + points[currentIndex - 1] <= target) {
                currentIndex--;
                score[currentIndex] += points[currentIndex];
                movesLeft--;
            }
            else {
                break;
            }
        }
        return Math.min(...score) >= target;
    }
    let left = 0, right = 1e9;
    let result = 0;
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        if (canAchieve(mid)) {
            result = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return result;  
};
