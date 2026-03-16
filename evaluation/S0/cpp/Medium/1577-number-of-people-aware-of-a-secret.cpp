// Source: https://leetcode.com/problems/number-of-people-aware-of-a-secret/   |   Difficulty: Medium
//
// Problem Description:
// On day 1, one person discovers a secret.
//
// You are given an integer delay, which means that each person will share the secret with a new person every day, starting from delay days after discovering the secret. You are also given an integer forget, which means that each person will forget the secret forget days after discovering it. A person cannot share the secret on the same day they forgot it, or on any day afterwards.
//
// Given an integer n, return the number of people who know the secret at the end of day n. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: n = 6, delay = 2, forget = 4
// Output: 5
// Explanation:
// Day 1: Suppose the first person is named A. (1 person)
// Day 2: A is the only person who knows the secret. (1 person)
// Day 3: A shares the secret with a new person, B. (2 people)
// Day 4: A shares the secret with a new person, C. (3 people)
// Day 5: A forgets the secret, and B shares the secret with a new person, D. (3 people)
// Day 6: B shares the secret with E, and C shares the secret with F. (5 people)
//
// Constraints:
// 2 <= n <= 1000
// 	1 <= delay < forget <= n
//

class Solution {
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        const int MOD = 1e9 + 7;
        vector<long long> dp(n + 1, 0);
        dp[1] = 1; // On day 1, one person knows the secret
        long long totalShares = 0; // Total number of people who can share the secret

        for (int day = 2; day <= n; ++day) {
            // People who can share the secret today
            if (day - delay >= 1) {
                totalShares = (totalShares + dp[day - delay]) % MOD;
            }
            // People who forget the secret today
            if (day - forget >= 1) {
                totalShares = (totalShares - dp[day - forget] + MOD) % MOD;
            }
            dp[day] = totalShares;
        }

        // Calculate the total number of people who still remember the secret on day n
        long long result = 0;
        for (int day = n - forget + 1; day <= n; ++day) {
            if (day >= 1) {
                result = (result + dp[day]) % MOD;
            }
        }

        return static_cast<int>(result);            
    }
};
