// Source: https://leetcode.com/problems/dota2-senate/   |   Difficulty: Medium
//
// Problem Description:
// In the world of Dota2, there are two parties: the Radiant and the Dire.
//
// The Dota2 senate consists of senators coming from two parties. Now the Senate wants to decide on a change in the Dota2 game. The voting for this change is a round-based procedure. In each round, each senator can exercise one of the two rights:
//
//
// 	Ban one senator's right: A senator can make another senator lose all his rights in this and all the following rounds.
// 	Announce the victory: If this senator found the senators who still have rights to vote are all from the same party, he can announce the victory and decide on the change in the game.
//
//
// Given a string senate representing each senator's party belonging. The character 'R' and 'D' represent the Radiant party and the Dire party. Then if there are n senators, the size of the given string will be n.
//
// The round-based procedure starts from the first senator to the last senator in the given order. This procedure will last until the end of voting. All the senators who have lost their rights will be skipped during the procedure.
//
// Suppose every senator is smart enough and will play the best strategy for his own party. Predict which party will finally announce the victory and change the Dota2 game. The output should be "Radiant" or "Dire".
//
// Example:
// Input: senate = "RD"
// Output: "Radiant"
// Explanation: 
// The first senator comes from Radiant and he can just ban the next senator's right in round 1. 
// And the second senator can't exercise any rights anymore since his right has been banned. 
// And in round 2, the first senator can just announce the victory since he is the only guy in the senate who can vote.
//
// Constraints:
// n == senate.length
// 	1 <= n <= 104
// 	senate[i] is either 'R' or 'D'.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public String predictPartyVictory(String senate) {
        int rCount = 0;
        int dCount = 0;
        int rBan = 0;
        int dBan = 0;

        char[] senators = senate.toCharArray();
        boolean changed;

        do {
            changed = false;
            for (int i = 0; i < senators.length; i++) {
                if (senators[i] == 'R') {
                    if (rBan > 0) {
                        senators[i] = 'X'; // Banned
                        rBan--;
                        changed = true;
                    } else {
                        dBan++;
                    }
                } else if (senators[i] == 'D') {
                    if (dBan > 0) {
                        senators[i] = 'X'; // Banned
                        dBan--;
                        changed = true;
                    } else {
                        rBan++;
                    }
                }
            }

            rCount = 0;
            dCount = 0;
            for (char senator : senators) {
                if (senator == 'R') rCount++;
                else if (senator == 'D') dCount++;
            }
        } while (changed && rCount > 0 && dCount > 0);

        return rCount > 0 ? "Radiant" : "Dire";         
    }
}
