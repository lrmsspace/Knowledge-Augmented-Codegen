// Source: https://leetcode.com/problems/count-the-number-of-winning-sequences/   |   Difficulty: Hard
//
// Problem Description:
// Alice and Bob are playing a fantasy battle game consisting of n rounds where they summon one of three magical creatures each round: a Fire Dragon, a Water Serpent, or an Earth Golem. In each round, players simultaneously summon their creature and are awarded points as follows:
//
//
// 	If one player summons a Fire Dragon and the other summons an Earth Golem, the player who summoned the Fire Dragon is awarded a point.
// 	If one player summons a Water Serpent and the other summons a Fire Dragon, the player who summoned the Water Serpent is awarded a point.
// 	If one player summons an Earth Golem and the other summons a Water Serpent, the player who summoned the Earth Golem is awarded a point.
// 	If both players summon the same creature, no player is awarded a point.
//
//
// You are given a string s consisting of n characters 'F', 'W', and 'E', representing the sequence of creatures Alice will summon in each round:
//
//
// 	If s[i] == 'F', Alice summons a Fire Dragon.
// 	If s[i] == 'W', Alice summons a Water Serpent.
// 	If s[i] == 'E', Alice summons an Earth Golem.
//
//
// Bob’s sequence of moves is unknown, but it is guaranteed that Bob will never summon the same creature in two consecutive rounds. Bob beats Alice if the total number of points awarded to Bob after n rounds is strictly greater than the points awarded to Alice.
//
// Return the number of distinct sequences Bob can use to beat Alice.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: s = "FFF"
//
// Output: 3
//
// Explanation:
//
// Bob can beat Alice by making one of the following sequences of moves: "WFW", "FWF", or "WEW". Note that other winning sequences like "WWE" or "EWW" are invalid since Bob cannot make the same move twice in a row.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s[i] is one of 'F', 'W', or 'E'.
//

int countWinningSequences(char* s) {
    const int MOD = 1000000007;
    int n = strlen(s);
    int dp[n + 1][3][2]; // dp[i][j][k]: number of ways up to i-th round, Bob's last creature j, result k (0: tie/loss, 1: win)
    memset(dp, 0, sizeof(dp));
    // Initial condition: before any round, Bob can be considered to have no last creature and tied
    dp[0][0][0] = 1;
    dp[0][1][0] = 1;
    dp[0][2][0] = 1;

    for (int i = 0; i < n; ++i) {
        for (int last = 0; last < 3; ++last) {
            for (int res = 0; res < 2; ++res) {
                for (int curr = 0; curr < 3; ++curr) {
                    if (curr == last) continue; // Bob cannot summon the same creature consecutively
                    int outcome = 0; // 0: tie/loss, 1: win
                    if ((s[i] == 'F' && curr == 1) || // Bob's Water Serpent beats Alice's Fire Dragon
                        (s[i] == 'W' && curr == 2) || // Bob's Earth Golem beats Alice's Water Serpent
                        (s[i] == 'E' && curr == 0)) { // Bob's Fire Dragon beats Alice's Earth Golem
                        outcome = 1;
                    }
                    int newRes = res | outcome; // Update result status
                    dp[i + 1][curr][newRes] = (dp[i + 1][curr][newRes] + dp[i][last][res]) % MOD;
                }
            }
        }
    }

    int result = 0;
    for (int last = 0; last < 3; ++last) {
        result = (result + dp[n][last][1]) % MOD; // Sum all winning sequences
    }
    return result;      
}
