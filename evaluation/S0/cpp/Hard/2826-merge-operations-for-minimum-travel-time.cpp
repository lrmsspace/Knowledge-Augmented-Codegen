// Source: https://leetcode.com/problems/merge-operations-for-minimum-travel-time/   |   Difficulty: Hard
//
// Problem Description:
// You are given a straight road of length l km, an integer n, an integer k, and two integer arrays, position and time, each of length n.
//
// The array position lists the positions (in km) of signs in strictly increasing order (with position[0] = 0 and position[n - 1] = l).
//
// Each time[i] represents the time (in minutes) required to travel 1 km between position[i] and position[i + 1].
//
// You must perform exactly k merge operations. In one merge, you can choose any two adjacent signs at indices i and i + 1 (with i > 0 and i + 1 < n) and:
//
//
//  Update the sign at index i + 1 so that its time becomes time[i] + time[i + 1].
//  Remove the sign at index i.
//
//
// Return the minimum total travel time (in minutes) to travel from 0 to l after exactly k merges.
//
// Example:
// Input: l = 10, n = 4, k = 1, position = [0,3,8,10], time = [5,8,3,6]
//
// Output: 62
//
// Explanation:
//
//
//  
//  Merge the signs at indices 1 and 2. Remove the sign at index 1, and change the time at index 2 to 8 + 3 = 11.
//  
//  After the merge:
//  
//   position array: [0, 8, 10]
//   time array: [5, 11, 6]
//    
//  
//  
//  
//  
//   
//    
//     Segment
//     Distance (km)
//     Time per km (min)
//     Segment Travel Time (min)
//    
//   
//   
//    
//     0 → 8
//     8
//     5
//     8 × 5 = 40
//    
//    
//     8 → 10
//     2
//     11
//     2 × 11 = 22
//    
//   
//  
//  
//  Total Travel Time: 40 + 22 = 62, which is the minimum possible time after exactly 1 merge.
//
// Constraints:
// 1 <= l <= 105
//  2 <= n <= min(l + 1, 50)
//  0 <= k <= min(n - 2, 10)
//  position.length == n
//  position[0] = 0 and position[n - 1] = l
//  position is sorted in strictly increasing order.
//  time.length == n
//  1 <= time[i] <= 100​
//  1 <= sum(time) <= 100​​​​​​
//

class Solution {
public:
    int minTravelTime(int l, int n, int k, vector<int>& position, vector<int>& time) {
        // DP approach
        // dp[i][j]: minimum time to reach position i with j merges
        vector<vector<long long>> dp(n, vector<long long>(k + 1, LLONG_MAX));
        dp[0][0] = 0;
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= k; j++) {
                // Try all possible previous positions to jump from
                for (int p = 0; p < i; p++) {
                    int mergesNeeded = i - p - 1;
                    if (j >= mergesNeeded) {
                        long long travelTime = (long long)(position[i] - position[p]) * time[i];
                        dp[i][j] = min(dp[i][j], dp[p][j - mergesNeeded] + travelTime);
                    }
                }
            }
        }
        
        return dp[n - 1][k];            
    }
};
