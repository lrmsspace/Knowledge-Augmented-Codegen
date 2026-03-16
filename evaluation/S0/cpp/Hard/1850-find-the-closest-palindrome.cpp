// Source: https://leetcode.com/problems/find-the-closest-palindrome/   |   Difficulty: Hard
//
// Problem Description:
// Given a string n representing an integer, return the closest integer (not including itself), which is a palindrome. If there is a tie, return the smaller one.
//
// The closest is defined as the absolute difference minimized between two integers.
//
// Example:
// Input: n = "123"
// Output: "121"
//
// Constraints:
// 1 <= n.length <= 18
// 	n consists of only digits.
// 	n does not have leading zeros.
// 	n is representing an integer in the range [1, 1018 - 1].
//

class Solution {
public:
    string nearestPalindromic(string n) {
        long long num = stoll(n);
        int len = n.size();
        vector<long long> candidates;

        // Edge cases: 10..01 and 9..9
        candidates.push_back((long long)pow(10, len - 1) - 1);
        candidates.push_back((long long)pow(10, len) + 1);

        // Get the prefix
        long long prefix = stoll(n.substr(0, (len + 1) / 2));

        // Generate candidates by modifying the prefix
        for (long long i = prefix - 1; i <= prefix + 1; i++) {
            string left = to_string(i);
            string palin;
            if (len % 2 == 0) {
                palin = left + string(left.rbegin(), left.rend());
            } else {
                palin = left + string(left.rbegin() + 1, left.rend());
            }
            candidates.push_back(stoll(palin));
        }

        // Find the closest palindrome
        long long closest = -1;
        for (long long cand : candidates) {
            if (cand == num) continue;
            if (closest == -1 ||
                abs(cand - num) < abs(closest - num) ||
                (abs(cand - num) == abs(closest - num) && cand < closest)) {
                closest = cand;
            }
        }

        return to_string(closest);          
    }
};
