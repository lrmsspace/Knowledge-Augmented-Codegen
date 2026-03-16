// Source: https://leetcode.com/problems/hand-of-straights/   |   Difficulty: Medium
//
// Problem Description:
// Alice has some number of cards and she wants to rearrange the cards into groups so that each group is of size groupSize, and consists of groupSize consecutive cards.
//
// Given an integer array hand where hand[i] is the value written on the ith card and an integer groupSize, return true if she can rearrange the cards, or false otherwise.
//
// Example:
// Input: hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
// Output: true
// Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8]
//
// Constraints:
// 1 <= hand.length <= 104
// 	0 <= hand[i] <= 109
// 	1 <= groupSize <= hand.length
//
//
//  
// Note: This question is the same as 1296: https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/
//

/**
 * @param {number[]} hand
 * @param {number} groupSize
 * @return {boolean}
 */
var isNStraightHand = function(hand, groupSize) {
    if (hand.length % groupSize !== 0) {
        return false;
    }
    hand.sort((a, b) => a - b);
    const countMap = new Map();
    for (const card of hand) {
        countMap.set(card, (countMap.get(card) || 0) + 1);
    }
    for (const card of hand) {
        if (countMap.get(card) === 0) continue;
        for (let i = 0; i < groupSize; i++) {
            const currentCard = card + i;
            if (!countMap.has(currentCard) || countMap.get(currentCard) === 0) {
                return false;
            }
            countMap.set(currentCard, countMap.get(currentCard) - 1);
        }
    }
    return true;
};