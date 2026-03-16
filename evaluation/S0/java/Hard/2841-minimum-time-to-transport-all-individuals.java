// Source: https://leetcode.com/problems/minimum-time-to-transport-all-individuals/   |   Difficulty: Hard
//
// Problem Description:
// You are given n individuals at a base camp who need to cross a river to reach a destination using a single boat. The boat can carry at most k people at a time. The trip is affected by environmental conditions that vary cyclically over m stages.
//
// Each stage j has a speed multiplier mul[j]:
//
//
// 	If mul[j] > 1, the trip slows down.
// 	If mul[j] < 1, the trip speeds up.
//
//
// Each individual i has a rowing strength represented by time[i], the time (in minutes) it takes them to cross alone in neutral conditions.
//
// Rules:
//
//
// 	A group g departing at stage j takes time equal to the maximum time[i] among its members, multiplied by mul[j] minutes to reach the destination.
// 	After the group crosses the river in time d, the stage advances by floor(d) % m steps.
// 	If individuals are left behind, one person must return with the boat. Let r be the index of the returning person, the return takes time[r] × mul[current_stage], defined as return_time, and the stage advances by floor(return_time) % m.
//
//
// Return the minimum total time required to transport all individuals. If it is not possible to transport all individuals to the destination, return -1.
//
// Example:
// Input: n = 1, k = 1, m = 2, time = [5], mul = [1.0,1.3]
//
// Output: 5.00000
//
// Explanation:
//
//
// 	Individual 0 departs from stage 0, so crossing time = 5 × 1.00 = 5.00 minutes.
// 	All team members are now at the destination. Thus, the total time taken is 5.00 minutes.
//
// Constraints:
// 1 <= n == time.length <= 12
// 	1 <= k <= 5
// 	1 <= m <= 5
// 	1 <= time[i] <= 100
// 	m == mul.length
// 	0.5 <= mul[i] <= 2.0
//

class Solution {
    public double minTime(int n, int k, int m, int[] time, double[] mul) {
        int N = 1 << n;
        double[][] dp = new double[N][m];
        for (double[] row : dp) {
            Arrays.fill(row, Double.MAX_VALUE);
        }
        dp[0][0] = 0.0;

        for (int mask = 0; mask < N; mask++) {
            for (int stage = 0; stage < m; stage++) {
                if (dp[mask][stage] == Double.MAX_VALUE) continue;

                List<Integer> remaining = new ArrayList<>();
                for (int i = 0; i < n; i++) {
                    if ((mask & (1 << i)) == 0) {
                        remaining.add(i);
                    }
                }

                int rSize = remaining.size();
                for (int size = 1; size <= Math.min(k, rSize); size++) {
                    combine(remaining, size, 0, new ArrayList<>(), (group) -> {
                        int nextMask = mask;
                        double maxTime = 0.0;
                        for (int idx : group) {
                            nextMask |= (1 << idx);
                            maxTime = Math.max(maxTime, time[idx]);
                        }

                        double crossTime = maxTime * mul[stage];
                        int nextStage = (stage + (int) Math.floor(crossTime)) % m;

                        if (nextMask == N - 1) {
                            dp[nextMask][nextStage] = Math.min(dp[nextMask][nextStage], dp[mask][stage] + crossTime);
                        } else {
                            for (int retIdx : group) {
                                double returnTime = time[retIdx] * mul[nextStage];
                                int returnStage = (nextStage + (int) Math.floor(returnTime)) % m;
                                dp[nextMask ^ (1 << retIdx)][returnStage] = Math.min(dp[nextMask ^ (1 << retIdx)][returnStage], dp[mask][stage] + crossTime + returnTime);
                            }
                        }
                    });
                }
            }
        }

        double result = Double.MAX_VALUE;
        for (int stage = 0; stage < m; stage++) {
            result = Math.min(result, dp[N - 1][stage]);
        }

        return result == Double.MAX_VALUE ? -1 : result;            
    }
}
