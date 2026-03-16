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
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long getMaxFunctionValue(List<Integer> receiver, long k) {
        int n = receiver.size();
        long maxScore = 0;

        for (int start = 0; start < n; start++) {
            long currentScore = 0;
            int currentPlayer = start;
            Map<Integer, Integer> visited = new HashMap<>();
            List<Long> scores = new ArrayList<>();

            for (long pass = 0; pass < k; pass++) {
                if (visited.containsKey(currentPlayer)) {
                    int cycleStartIndex = visited.get(currentPlayer);
                    long cycleLength = pass - cycleStartIndex;
                    long cycleSum = 0;

                    for (int i = cycleStartIndex; i < scores.size(); i++) {
                        cycleSum += scores.get(i);
                    }

                    long remainingPasses = k - pass;
                    long fullCycles = remainingPasses / cycleLength;
                    long partialCycleLength = remainingPasses % cycleLength;

                    currentScore += fullCycles * cycleSum;

                    for (int i = 0; i < partialCycleLength; i++) {
                        currentScore += scores.get(cycleStartIndex + i);
                    }
                    break;
                }

                visited.put(currentPlayer, (int) pass);
                currentScore += currentPlayer;
                scores.add((long) currentPlayer);
                currentPlayer = receiver.get(currentPlayer);
            }

            maxScore = Math.max(maxScore, currentScore);
        }

        return maxScore;            
    }
}
