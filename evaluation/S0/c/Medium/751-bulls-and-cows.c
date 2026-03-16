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

char* getHint(char* secret, char* guess) {
    int bulls = 0, cows = 0;
    int secret_count[10] = {0};
    int guess_count[10] = {0};
    
    for (int i = 0; secret[i] != '\0'; i++) {
        if (secret[i] == guess[i]) {
            bulls++;
        } else {
            secret_count[secret[i] - '0']++;
            guess_count[guess[i] - '0']++;
        }
    }
    
    for (int i = 0; i < 10; i++) {
        cows += (secret_count[i] < guess_count[i]) ? secret_count[i] : guess_count[i];
    }
    
    // Allocate memory for the result string
    char* result = (char*)malloc(20 * sizeof(char));
    sprintf(result, "%dA%dB", bulls, cows);
    
    return result;      
}
