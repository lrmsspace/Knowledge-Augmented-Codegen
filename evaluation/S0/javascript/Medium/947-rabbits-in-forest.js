// Source: https://leetcode.com/problems/rabbits-in-forest/   |   Difficulty: Medium
//
// Problem Description:
// There is a forest with an unknown number of rabbits. We asked n rabbits "How many rabbits have the same color as you?" and collected the answers in an integer array answers where answers[i] is the answer of the ith rabbit.
//
// Given the array answers, return the minimum number of rabbits that could be in the forest.
//
// Example:
// Input: answers = [1,1,2]
// Output: 5
// Explanation:
// The two rabbits that answered "1" could both be the same color, say red.
// The rabbit that answered "2" can't be red or the answers would be inconsistent.
// Say the rabbit that answered "2" was blue.
// Then there should be 2 other blue rabbits in the forest that didn't answer into the array.
// The smallest possible number of rabbits in the forest is therefore 5: 3 that answered plus 2 that didn't.
//
// Constraints:
// 1 <= answers.length <= 1000
// 	0 <= answers[i] < 1000
//

/**
 * @param {number[]} answers
 * @return {number}
 */
var numRabbits = function(answers) {
    const countMap = new Map();
    for (let answer of answers) {
        countMap.set(answer, (countMap.get(answer) || 0) + 1);
    }

    let result = 0;
    for (let [answer, count] of countMap.entries()) {
        const groupSize = answer + 1;
        const groups = Math.ceil(count / groupSize);
        result += groups * groupSize;
    }

    return result;
};