// Source: https://leetcode.com/problems/maximize-value-of-function-in-a-ball-passing-game/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array receiver of length n and an integer k. n players are playing a ball-passing game.
//
// You choose the starting player, i. The game proceeds as follows: player i passes the ball to player receiver[i], who then passes it to receiver[receiver[i]], and so on, for k passes in total. The game's score is the sum of the indices of the players who touched the ball, including repetitions, i.e. i + receiver[i] + receiver[receiver[i]] + ... + receiver(k)[i].
//
// Return the maximum possible score.
//
// Notes:
//
//
// 	receiver may contain duplicates.
// 	receiver[i] may be equal to i.
//
// Example:
// Input: receiver = [2,0,1], k = 4
//
// Output: 6
//
// Explanation:
//
// Starting with player i = 2 the initial score is 2:
//
//
// 	
// 		
// 			Pass
// 			Sender Index
// 			Receiver Index
// 			Score
// 		
// 		
// 			1
// 			2
// 			1
// 			3
// 		
// 		
// 			2
// 			1
// 			0
// 			3
// 		
// 		
// 			3
// 			0
// 			2
// 			5
// 		
// 		
// 			4
// 			2
// 			1
// 			6
//
// Constraints:
// 1 <= receiver.length == n <= 105
// 	0 <= receiver[i] <= n - 1
// 	1 <= k <= 1010
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

long long getMaxFunctionValue(int* receiver, int receiverSize, long long k) {
    long long maxScore = 0;
    for (int i = 0; i < receiverSize; i++) {
        long long score = 0;
        int currentPlayer = i;
        for (long long pass = 0; pass < k; pass++) {
            score += currentPlayer;
            currentPlayer = receiver[currentPlayer];
        }
        if (score > maxScore) {
            maxScore = score;
        }
    }
    return maxScore;        
}
