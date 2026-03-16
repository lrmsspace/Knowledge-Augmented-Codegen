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

class Solution {
    public String bestHand(int[] ranks, char[] suits) {
        boolean isFlush = true;
        for (int i = 1; i < suits.length; i++) {
            if (suits[i] != suits[0]) {
                isFlush = false;
                break;
            }
        }
        if (isFlush) {
            return "Flush";
        }

        int[] rankCount = new int[14];
        for (int rank : ranks) {
            rankCount[rank]++;
        }

        for (int count : rankCount) {
            if (count >= 3) {
                return "Three of a Kind";
            }
        }

        for (int count : rankCount) {
            if (count == 2) {
                return "Pair";
            }
        }

        return "High Card";         
    }
}
