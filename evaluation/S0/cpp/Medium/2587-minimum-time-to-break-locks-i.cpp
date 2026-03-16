// Source: https://leetcode.com/problems/minimum-time-to-break-locks-i/   |   Difficulty: Medium
//
// Problem Description:
// Bob is stuck in a dungeon and must break n locks, each requiring some amount of energy to break. The required energy for each lock is stored in an array called strength where strength[i] indicates the energy needed to break the ith lock.
//
// To break a lock, Bob uses a sword with the following characteristics:
//
//
// 	The initial energy of the sword is 0.
// 	The initial factor x by which the energy of the sword increases is 1.
// 	Every minute, the energy of the sword increases by the current factor x.
// 	To break the ith lock, the energy of the sword must reach at least strength[i].
// 	After breaking a lock, the energy of the sword resets to 0, and the factor x increases by a given value k.
//
//
// Your task is to determine the minimum time in minutes required for Bob to break all n locks and escape the dungeon.
//
// Return the minimum time required for Bob to break all n locks.
//
// Example:
// Input: strength = [3,4,1], k = 1
//
// Output: 4
//
// Explanation:
//
//
// 	
// 		
// 			Time
// 			Energy
// 			x
// 			Action
// 			Updated x
// 		
// 		
// 			0
// 			0
// 			1
// 			Nothing
// 			1
// 		
// 		
// 			1
// 			1
// 			1
// 			Break 3rd Lock
// 			2
// 		
// 		
// 			2
// 			2
// 			2
// 			Nothing
// 			2
// 		
// 		
// 			3
// 			4
// 			2
// 			Break 2nd Lock
// 			3
// 		
// 		
// 			4
// 			3
// 			3
// 			Break 1st Lock
// 			3
// 		
// 	
//
//
// The locks cannot be broken in less than 4 minutes; thus, the answer is 4.
//
// Constraints:
// n == strength.length
// 	1 <= n <= 8
// 	1 <= K <= 10
// 	1 <= strength[i] <= 106
//

class Solution {
public:
    int findMinimumTime(vector<int>& strength, int k) {
        int n = strength.size();
        vector<bool> visited(n, false);
        int minTime = INT_MAX;

        function<void(int, int, int, int)> backtrack = [&](int time, int energy, int factor, int brokenLocks) {
            if (brokenLocks == n) {
                minTime = min(minTime, time);
                return;
            }

            for (int i = 0; i < n; ++i) {
                if (!visited[i]) {
                    visited[i] = true;
                    int requiredEnergy = strength[i];
                    int additionalTime = 0;
                    int currentEnergy = energy;

                    while (currentEnergy < requiredEnergy) {
                        additionalTime++;
                        currentEnergy += factor;
                    }

                    backtrack(time + additionalTime, 0, factor + k, brokenLocks + 1);
                    visited[i] = false;
                }
            }
        };

        backtrack(0, 0, 1, 0);
        return minTime;         
    }
};
