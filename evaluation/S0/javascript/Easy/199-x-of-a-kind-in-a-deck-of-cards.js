// Source: https://leetcode.com/problems/x-of-a-kind-in-a-deck-of-cards/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array deck where deck[i] represents the number written on the ith card.
//
// Partition the cards into one or more groups such that:
//
//
// 	Each group has exactly x cards where x > 1, and
// 	All the cards in one group have the same integer written on them.
//
//
// Return true if such partition is possible, or false otherwise.
//
// Example:
// Input: deck = [1,2,3,4,4,3,2,1]
// Output: true
// Explanation: Possible partition [1,1],[2,2],[3,3],[4,4].
//
// Constraints:
// 1 <= deck.length <= 104
// 	0 <= deck[i] < 104
//

/**
 * @param {number[]} deck
 * @return {boolean}
 */
var hasGroupsSizeX = function(deck) {
    const countMap = new Map();
    for (const card of deck) {
        countMap.set(card, (countMap.get(card) || 0) + 1);
    }
    const gcd = (a, b) => {
        if (b === 0) return a;
        return gcd(b, a % b);
    };
    let x = 0;
    for (const count of countMap.values()) {
        x = gcd(x, count);
    }
    return x >= 2;
};