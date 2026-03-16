// Source: https://leetcode.com/problems/bag-of-tokens/   |   Difficulty: Medium
//
// Problem Description:
// You start with an initial power of power, an initial score of 0, and a bag of tokens given as an integer array tokens, where each tokens[i] denotes the value of tokeni.
//
// Your goal is to maximize the total score by strategically playing these tokens. In one move, you can play an unplayed token in one of the two ways (but not both for the same token):
//
//
// 	Face-up: If your current power is at least tokens[i], you may play tokeni, losing tokens[i] power and gaining 1 score.
// 	Face-down: If your current score is at least 1, you may play tokeni, gaining tokens[i] power and losing 1 score.
//
//
// Return the maximum possible score you can achieve after playing any number of tokens.
//
// Example:
// Input: tokens = [100], power = 50
//
// Output: 0
//
// Explanation: Since your score is 0 initially, you cannot play the token face-down. You also cannot play it face-up since your power (50) is less than tokens[0] (100).
//
// Constraints:
// 0 <= tokens.length <= 1000
// 	0 <= tokens[i], power < 104
//

int bagOfTokensScore(int* tokens, int tokensSize, int power) {
    // Sort tokens in ascending order
    qsort(tokens, tokensSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    int left = 0, right = tokensSize - 1;
    int score = 0, maxScore = 0;

    while (left <= right) {
        if (power >= tokens[left]) {
            power -= tokens[left++];
            score++;
            if (score > maxScore) {
                maxScore = score;
            }
        } else if (score > 0) {
            power += tokens[right--];
            score--;
        } else {
            break;
        }
    }

    return maxScore;        
}
