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
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* predictPartyVictory(char* senate) {
    int radiantCount = 0;
    int direCount = 0;
    int radiantBan = 0;
    int direBan = 0;
    int length = 0;

    // Calculate the length of the senate string
    while (senate[length] != '\0') {
        length++;
    }

    // Create a dynamic array to hold the current senators
    char* currentSenate = (char*)malloc((length + 1) * sizeof(char));
    for (int i = 0; i < length; i++) {
        currentSenate[i] = senate[i];
    }
    currentSenate[length] = '\0';

    while (1) {
        radiantCount = 0;
        direCount = 0;

        for (int i = 0; i < length; i++) {
            if (currentSenate[i] == 'R') {
                if (radiantBan > 0) {
                    radiantBan--;
                    currentSenate[i] = 'X'; // Mark as banned
                } else {
                    direBan++;
                    radiantCount++;
                }
            } else if (currentSenate[i] == 'D') {
                if (direBan > 0) {
                    direBan--;
                    currentSenate[i] = 'X'; // Mark as banned
                } else {
                    radiantBan++;
                    direCount++;
                }
            }
        }

        if (radiantCount == 0) {
            free(currentSenate);
            return "Dire";
        }
        if (direCount == 0) {
            free(currentSenate);
            return "Radiant";
        }
    }       
}
