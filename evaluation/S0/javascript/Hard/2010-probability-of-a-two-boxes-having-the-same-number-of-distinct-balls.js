// Source: https://leetcode.com/problems/probability-of-a-two-boxes-having-the-same-number-of-distinct-balls/   |   Difficulty: Hard
//
// Problem Description:
// Given 2n balls of k distinct colors. You will be given an integer array balls of size k where balls[i] is the number of balls of color i.
//
// All the balls will be shuffled uniformly at random, then we will distribute the first n balls to the first box and the remaining n balls to the other box (Please read the explanation of the second example carefully).
//
// Please note that the two boxes are considered different. For example, if we have two balls of colors a and b, and two boxes [] and (), then the distribution [a] (b) is considered different than the distribution [b] (a) (Please read the explanation of the first example carefully).
//
// Return the probability that the two boxes have the same number of distinct balls. Answers within 10-5 of the actual value will be accepted as correct.
//
// Example:
// Input: balls = [1,1]
// Output: 1.00000
// Explanation: Only 2 ways to divide the balls equally:
// - A ball of color 1 to box 1 and a ball of color 2 to box 2
// - A ball of color 2 to box 1 and a ball of color 1 to box 2
// In both ways, the number of distinct colors in each box is equal. The probability is 2/2 = 1
//
// Constraints:
// 1 <= balls.length <= 8
// 	1 <= balls[i] <= 6
// 	sum(balls) is even.
//

/**
 * @param {number[]} balls
 * @return {number}
 */
var getProbability = function(balls) {
        const totalBalls = balls.reduce((a, b) => a + b, 0);
    const n = totalBalls / 2;
    let favorable = 0;
    let total = 0;
    const backtrack = (index, box1, box2) => {
        if (index === balls.length) {
            if (box1.length === box2.length) {
                favorable++;
            }
            total++;
            return;
        }
        for (let i = 0; i <= balls[index]; i++) {
            if (box1.length + i > n || box2.length + (balls[index] - i) > n) {
                continue;
            }
            backtrack(index + 1, box1.concat(Array(i).fill(index)), box2.concat(Array(balls[index] - i).fill(index)));
        }
    };
    backtrack(0, [], []);
    return favorable / total;
};
