// Source: https://leetcode.com/problems/minimum-consecutive-cards-to-pick-up/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array cards where cards[i] represents the value of the ith card. A pair of cards are matching if the cards have the same value.
//
// Return the minimum number of consecutive cards you have to pick up to have a pair of matching cards among the picked cards. If it is impossible to have matching cards, return -1.
//
// Example:
// Input: cards = [3,4,2,3,4,7]
// Output: 4
// Explanation: We can pick up the cards [3,4,2,3] which contain a matching pair of cards with value 3. Note that picking up the cards [4,2,3,4] is also optimal.
//
// Constraints:
// 1 <= cards.length <= 105
// 	0 <= cards[i] <= 106
//

/**
 * @param {number[]} cards
 * @return {number}
 */
var minimumCardPickup = function(cards) {
    const lastSeen = new Map();
    let minLength = Infinity;
    for (let i = 0; i < cards.length; i++) {
        if (lastSeen.has(cards[i])) {
            minLength = Math.min(minLength, i - lastSeen.get(cards[i]) + 1);
        }
        lastSeen.set(cards[i], i);
    }
    return minLength === Infinity ? -1 : minLength;
};