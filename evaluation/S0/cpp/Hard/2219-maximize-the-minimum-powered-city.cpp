// Source: https://leetcode.com/problems/maximize-the-minimum-powered-city/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array stations of length n, where stations[i] represents the number of power stations in the ith city.
//
// Each power station can provide power to every city in a fixed range. In other words, if the range is denoted by r, then a power station at city i can provide power to all cities j such that |i - j| <= r and 0 <= i, j <= n - 1.
//
//
// 	Note that |x| denotes absolute value. For example, |7 - 5| = 2 and |3 - 10| = 7.
//
//
// The power of a city is the total number of power stations it is being provided power from.
//
// The government has sanctioned building k more power stations, each of which can be built in any city, and have the same range as the pre-existing ones.
//
// Given the two integers r and k, return the maximum possible minimum power of a city, if the additional power stations are built optimally.
//
// Note that you can build the k power stations in multiple cities.
//
// Example:
// Input: stations = [1,2,4,5,0], r = 1, k = 2
// Output: 5
// Explanation: 
// One of the optimal ways is to install both the power stations at city 1. 
// So stations will become [1,4,4,5,0].
// - City 0 is provided by 1 + 4 = 5 power stations.
// - City 1 is provided by 1 + 4 + 4 = 9 power stations.
// - City 2 is provided by 4 + 4 + 5 = 13 power stations.
// - City 3 is provided by 5 + 4 = 9 power stations.
// - City 4 is provided by 5 + 0 = 5 power stations.
// So the minimum power of a city is 5.
// Since it is not possible to obtain a larger power, we return 5.
//
// Constraints:
// n == stations.length
// 	1 <= n <= 105
// 	0 <= stations[i] <= 105
// 	0 <= r <= n - 1
// 	0 <= k <= 109
//

class Solution {
public:
    long long maxPower(vector<int>& stations, int r, int k) {
        int n = stations.size();
        long long left = 0, right = 1e15;
        long long result = 0;
        
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            vector<long long> added(n, 0);
            long long needed = 0;
            long long windowSum = 0;
            
            // Initialize window sum for first city
            for (int i = 0; i <= min(n - 1, r); i++) {
                windowSum += stations[i];
            }
            
            bool canAchieve = true;
            
            for (int i = 0; i < n; i++) {
                if (i - r - 1 >= 0) {
                    windowSum -= stations[i - r - 1] + added[i - r - 1];
                }
                
                if (i + r < n) {
                    windowSum += stations[i + r] + added[i + r];
                }
                
                if (windowSum < mid) {
                    long long diff = mid - windowSum;
                    needed += diff;
                    if (needed > k) {
                        canAchieve = false;
                        break;
                    }
                    added[min(n - 1, i + r)] += diff;
                    windowSum += diff;
                }
            }
            
            if (canAchieve) {
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;          
    }
};
