// Source: https://leetcode.com/problems/best-poker-hand/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array ranks and a character array suits. You have 5 cards where the ith card has a rank of ranks[i] and a suit of suits[i].
//
// The following are the types of poker hands you can make from best to worst:
//
//
// 	"Flush": Five cards of the same suit.
// 	"Three of a Kind": Three cards of the same rank.
// 	"Pair": Two cards of the same rank.
// 	"High Card": Any single card.
//
//
// Return a string representing the best type of poker hand you can make with the given cards.
//
// Note that the return values are case-sensitive.
//
// Example:
// Input: ranks = [13,2,3,1,9], suits = ["a","a","a","a","a"]
// Output: "Flush"
// Explanation: The hand with all the cards consists of 5 cards with the same suit, so we have a "Flush".
//
// Constraints:
// ranks.length == suits.length == 5
// 	1 <= ranks[i] <= 13
// 	'a' <= suits[i] <= 'd'
// 	No two cards have the same rank and suit.
//

char* bestHand(int* ranks, int ranksSize, char* suits, int suitsSize) {
    int rankCount[14] = {0};
    int suitCount[4] = {0};

    for (int i = 0; i < ranksSize; i++) {
        rankCount[ranks[i]]++;
        suitCount[suits[i] - 'a']++;
    }

    for (int i = 0; i < 4; i++) {
        if (suitCount[i] == 5) {
            return "Flush";
        }
    }

    for (int i = 1; i <= 13; i++) {
        if (rankCount[i] >= 3) {
            return "Three of a Kind";
        }
    }

    for (int i = 1; i <= 13; i++) {
        if (rankCount[i] == 2) {
            return "Pair";
        }
    }

    return "High Card";     
}
