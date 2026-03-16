// Source: https://leetcode.com/problems/count-number-of-texts/   |   Difficulty: Medium
//
// Problem Description:
// Alice is texting Bob using her phone. The mapping of digits to letters is shown in the figure below.
//
// In order to add a letter, Alice has to press the key of the corresponding digit i times, where i is the position of the letter in the key.
//
//
// 	For example, to add the letter 's', Alice has to press '7' four times. Similarly, to add the letter 'k', Alice has to press '5' twice.
// 	Note that the digits '0' and '1' do not map to any letters, so Alice does not use them.
//
//
// However, due to an error in transmission, Bob did not receive Alice's text message but received a string of pressed keys instead.
//
//
// 	For example, when Alice sent the message "bob", Bob received the string "2266622".
//
//
// Given a string pressedKeys representing the string received by Bob, return the total number of possible text messages Alice could have sent.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: pressedKeys = "22233"
// Output: 8
// Explanation:
// The possible text messages Alice could have sent are:
// "aaadd", "abdd", "badd", "cdd", "aaae", "abe", "bae", and "ce".
// Since there are 8 possible messages, we return 8.
//
// Constraints:
// 1 <= pressedKeys.length <= 105
// 	pressedKeys only consists of digits from '2' - '9'.
//

class Solution {
public:
    int countTexts(string pressedKeys) {
        const int MOD = 1e9 + 7;
        int n = pressedKeys.size();
        vector<long long> dp(n + 1, 0);
        dp[0] = 1;

        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[i - 1]; // Single press

            // Check for double presses
            if (i >= 2 && pressedKeys[i - 1] == pressedKeys[i - 2]) {
                dp[i] = (dp[i] + dp[i - 2]) % MOD;

                // Check for triple presses
                if (i >= 3 && pressedKeys[i - 1] == pressedKeys[i - 3]) {
                    dp[i] = (dp[i] + dp[i - 3]) % MOD;

                    // Check for quadruple presses (only for '7' and '9')
                    if (i >= 4 && pressedKeys[i - 1] == pressedKeys[i - 4] &&
                        (pressedKeys[i - 1] == '7' || pressedKeys[i - 1] == '9')) {
                        dp[i] = (dp[i] + dp[i - 4]) % MOD;
                    }
                }
            }
        }

        return dp[n];           
    }
};
