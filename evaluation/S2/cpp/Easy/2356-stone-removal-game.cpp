// Source: https://leetcode.com/problems/stone-removal-game/   |   Difficulty: Easy
//
// Problem Description:
// Alice and Bob are playing a game where they take turns removing stones from a pile, with Alice going first.
//
//
// 	Alice starts by removing exactly 10 stones on her first turn.
// 	For each subsequent turn, each player removes exactly 1 fewer stone than the previous opponent.
//
//
// The player who cannot make a move loses the game.
//
// Given a positive integer n, return true if Alice wins the game and false otherwise.
//
// Example:
// Input: n = 12
//
// Output: true
//
// Explanation:
//
//
// 	Alice removes 10 stones on her first turn, leaving 2 stones for Bob.
// 	Bob cannot remove 9 stones, so Alice wins.
//
// Constraints:
// 1 <= n <= 50
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool canAliceWin(int n) {
        // Alice removes 10 stones on her first turn, leaving n - 10 stones for Bob.
        // Bob will then try to remove 9 stones, leaving n - 19 stones for Alice.
        // Alice will then try to remove 8 stones, leaving n - 27 stones for Bob.
        // This pattern continues until one player cannot make a move.
        //
        // The sequence of stones removed by Alice and Bob will be:
        // Alice: 10, 8, 6, 4, 2
        // Bob: 9, 7, 5, 3, 1
        //
        // The total number of stones removed after k turns (where k is the number of turns taken by Alice) can be calculated as:
        // Total removed = (10 + (10 - k)) + (9 + (9 - k)) + ... + (2 + (2 - k))
        //
        // We can simplify this to find the maximum number of turns Alice can take before she cannot make a move.
        
        int aliceStones = 10; // Initial stones removed by Alice
        int bobStones = 9;    // Initial stones removed by Bob
        
        while (n > aliceStones) {
            n -= aliceStones; // Alice removes her stones
            if (n <= bobStones) {
                return true; // Bob cannot remove his stones, Alice wins
            }
            n -= bobStones;   // Bob removes his stones
            
            aliceStones -= 2; // Next turn Alice will remove 2 fewer stones
            bobStones -= 2;   // Next turn Bob will remove 2 fewer stones
            
            if (aliceStones <= 0) {
                return false; // Alice cannot remove any more stones, Bob wins
            }
            if (bobStones <= 0) {
                return true; // Bob cannot remove any more stones, Alice wins
            }
        }
        
        return false; // If we exit the loop without returning, it means Alice cannot make the first move           
    }
};
