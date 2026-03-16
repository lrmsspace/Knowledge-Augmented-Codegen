// Source: https://leetcode.com/problems/stone-game-iii/   |   Difficulty: Hard
//
// Problem Description:
// Alice and Bob continue their games with piles of stones. There are several stones arranged in a row, and each stone has an associated value which is an integer given in the array stoneValue.
//
// Alice and Bob take turns, with Alice starting first. On each player's turn, that player can take 1, 2, or 3 stones from the first remaining stones in the row.
//
// The score of each player is the sum of the values of the stones taken. The score of each player is 0 initially.
//
// The objective of the game is to end with the highest score, and the winner is the player with the highest score and there could be a tie. The game continues until all the stones have been taken.
//
// Assume Alice and Bob play optimally.
//
// Return "Alice" if Alice will win, "Bob" if Bob will win, or "Tie" if they will end the game with the same score.
//
// Example:
// Input: stoneValue = [1,2,3,7]
// Output: "Bob"
// Explanation: Alice will always lose. Her best move will be to take three piles and the score become 6. Now the score of Bob is 7 and Bob wins.
//
// Constraints:
// 1 <= stoneValue.length <= 5 * 104
// 	-1000 <= stoneValue[i] <= 1000
//

class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<int> dp(n + 1, INT_MIN);
        dp[n] = 0;  // base case
        
        for (int i = n - 1; i >= 0; --i) {
            int take = 0;
            for (int k = 0; k < 3 && i + k < n; ++k) {
                take += stoneValue[i + k];
                dp[i] = max(dp[i], take - dp[i + k + 1]);
            }
        }
        
        if (dp[0] > 0) return "Alice";
        else if (dp[0] < 0) return "Bob";
        else return "Tie";          
    }
};
