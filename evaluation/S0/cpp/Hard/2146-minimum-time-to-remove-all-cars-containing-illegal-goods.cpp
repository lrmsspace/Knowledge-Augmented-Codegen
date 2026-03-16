// Source: https://leetcode.com/problems/minimum-time-to-remove-all-cars-containing-illegal-goods/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed binary string s which represents a sequence of train cars. s[i] = '0' denotes that the ith car does not contain illegal goods and s[i] = '1' denotes that the ith car does contain illegal goods.
//
// As the train conductor, you would like to get rid of all the cars containing illegal goods. You can do any of the following three operations any number of times:
//
//
// 	Remove a train car from the left end (i.e., remove s[0]) which takes 1 unit of time.
// 	Remove a train car from the right end (i.e., remove s[s.length - 1]) which takes 1 unit of time.
// 	Remove a train car from anywhere in the sequence which takes 2 units of time.
//
//
// Return the minimum time to remove all the cars containing illegal goods.
//
// Note that an empty sequence of cars is considered to have no cars containing illegal goods.
//
// Example:
// Input: s = "1100101"
// Output: 5
// Explanation: 
// One way to remove all the cars containing illegal goods from the sequence is to
// - remove a car from the left end 2 times. Time taken is 2 * 1 = 2.
// - remove a car from the right end. Time taken is 1.
// - remove the car containing illegal goods found in the middle. Time taken is 2.
// This obtains a total time of 2 + 1 + 2 = 5. 
//
// An alternative way is to
// - remove a car from the left end 2 times. Time taken is 2 * 1 = 2.
// - remove a car from the right end 3 times. Time taken is 3 * 1 = 3.
// This also obtains a total time of 2 + 3 = 5.
//
// 5 is the minimum time taken to remove all the cars containing illegal goods. 
// There are no other ways to remove them with less time.
//
// Constraints:
// 1 <= s.length <= 2 * 105
// 	s[i] is either '0' or '1'.
//

class Solution {
public:
    int minimumTime(string s) {
        int n = s.length();
        vector<int> prefix(n + 1, 0);
        vector<int> suffix(n + 1, 0);
        
        // Calculate prefix costs
        for (int i = 1; i <= n; i++) {
            prefix[i] = prefix[i - 1];
            if (s[i - 1] == '1') {
                prefix[i] = min(prefix[i] + 2, i);
            }
        }
        
        // Calculate suffix costs
        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1];
            if (s[i] == '1') {
                suffix[i] = min(suffix[i] + 2, n - i);
            }
        }
        
        // Combine prefix and suffix to find minimum cost
        int minTime = INT_MAX;
        for (int i = 0; i <= n; i++) {
            minTime = min(minTime, prefix[i] + suffix[i]);
        }
        
        return minTime;         
    }
};
