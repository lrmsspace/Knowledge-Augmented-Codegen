// Source: https://leetcode.com/problems/bulls-and-cows/   |   Difficulty: Medium
//
// Problem Description:
// You are playing the Bulls and Cows game with your friend.
//
// You write down a secret number and ask your friend to guess what the number is. When your friend makes a guess, you provide a hint with the following info:
//
//
// 	The number of "bulls", which are digits in the guess that are in the correct position.
// 	The number of "cows", which are digits in the guess that are in your secret number but are located in the wrong position. Specifically, the non-bull digits in the guess that could be rearranged such that they become bulls.
//
//
// Given the secret number secret and your friend's guess guess, return the hint for your friend's guess.
//
// The hint should be formatted as "xAyB", where x is the number of bulls and y is the number of cows. Note that both secret and guess may contain duplicate digits.
//
// Example:
// Input: secret = "1807", guess = "7810"
// Output: "1A3B"
// Explanation: Bulls are connected with a '|' and cows are underlined:
// "1807"
//   |
// "7810"
//
// Constraints:
// 1 <= secret.length, guess.length <= 1000
// 	secret.length == guess.length
// 	secret and guess consist of digits only.
//

class Solution {
public:
    string getHint(string secret, string guess) {
        int bulls = 0;
        int cows = 0;
        vector<int> secretCount(10, 0);
        vector<int> guessCount(10, 0);

        for (size_t i = 0; i < secret.length(); ++i) {
            if (secret[i] == guess[i]) {
                ++bulls;
            } else {
                ++secretCount[secret[i] - '0'];
                ++guessCount[guess[i] - '0'];
            }
        }

        for (int i = 0; i < 10; ++i) {
            cows += min(secretCount[i], guessCount[i]);
        }

        return to_string(bulls) + "A" + to_string(cows) + "B";          
    }
};
