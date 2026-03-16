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
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long getMaxFunctionValue(vector<int>& receiver, long long k) {
        int n = receiver.size();
        long long maxScore = 0;

        for (int start = 0; start < n; ++start) {
            vector<bool> visited(n, false);
            vector<long long> pathScores;
            int current = start;
            long long currentScore = 0;

            // Detect cycle and calculate scores
            while (!visited[current]) {
                visited[current] = true;
                currentScore += current;
                pathScores.push_back(currentScore);
                current = receiver[current];
            }

            // Find the cycle start index
            int cycleStartIndex = 0;
            for (int i = 0; i < pathScores.size(); ++i) {
                if (receiver[(start + i) % n] == current) {
                    cycleStartIndex = i;
                    break;
                }
            }

            long long cycleSum = 0;
            for (int i = cycleStartIndex; i < pathScores.size(); ++i) {
                cycleSum += (receiver[(start + i) % n]);
            }

            long long totalScore = 0;
            if (k <= pathScores.size()) {
                totalScore = pathScores[k - 1];
            } else {
                totalScore = pathScores[cycleStartIndex - 1];
                k -= cycleStartIndex;

                if (cycleSum > 0) {
                    long long fullCycles = k / (pathScores.size() - cycleStartIndex);
                    totalScore += fullCycles * cycleSum;
                    k %= (pathScores.size() - cycleStartIndex);
                }

                for (int i = 0; i < k; ++i) {
                    totalScore += receiver[(start + cycleStartIndex + i) % n];
                }
            }

            maxScore = max(maxScore, totalScore);
        }

        return maxScore;            
    }
};
