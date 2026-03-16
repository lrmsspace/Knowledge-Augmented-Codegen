// Source: https://leetcode.com/problems/maximize-value-of-function-in-a-ball-passing-game/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array receiver of length n and an integer k. n players are playing a ball-passing game.
//
// You choose the starting player, i. The game proceeds as follows: player i passes the ball to player receiver[i], who then passes it to receiver[receiver[i]], and so on, for k passes in total. The game's score is the sum of the indices of the players who touched the ball, including repetitions, i.e. i + receiver[i] + receiver[receiver[i]] + ... + receiver(k)[i].
//
// Return the maximum possible score.
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
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long getMaxFunctionValue(int* receiver, int receiverSize, long long k) {
    long long maxScore = 0;
    for (int start = 0; start < receiverSize; ++start) {
        long long score = 0;
        int current = start;
        long long steps = 0;
        int *visited = (int *)calloc(receiverSize, sizeof(int));
        int *path = (int *)malloc(receiverSize * sizeof(int));
        int pathLen = 0;

        while (steps < k) {
            if (visited[current]) {
                int cycleStart = visited[current] - 1;
                long long cycleLength = pathLen - cycleStart;
                long long cycleSum = 0;
                for (int i = cycleStart; i < pathLen; ++i) {
                    cycleSum += path[i];
                }

                long long remainingSteps = k - steps;
                long long fullCycles = remainingSteps / cycleLength;
                score += fullCycles * cycleSum;
                steps += fullCycles * cycleLength;

                for (int i = 0; i < remainingSteps % cycleLength; ++i) {
                    score += path[cycleStart + i];
                    steps++;
                }
                break;
            }

            visited[current] = pathLen + 1;
            path[pathLen++] = current;
            score += current;
            current = receiver[current];
            steps++;
        }

        if (steps == k) {
            maxScore = (score > maxScore) ? score : maxScore;
        } else {
            maxScore = (score > maxScore) ? score : maxScore;
        }

        free(visited);
        free(path);
    }

    return maxScore;        
}
