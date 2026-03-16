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
    public String nearestPalindromic(String n) {
        long num = Long.parseLong(n);
        int len = n.length();
        Set<Long> candidates = new HashSet<>();

        // Edge cases: 10..01 and 9..9
        candidates.add((long) Math.pow(10, len - 1) - 1);
        candidates.add((long) Math.pow(10, len) + 1);

        // Get the prefix
        long prefix = Long.parseLong(n.substring(0, (len + 1) / 2));

        // Generate palindromic candidates by modifying the prefix
        for (long i = prefix - 1; i <= prefix + 1; i++) {
            StringBuilder sb = new StringBuilder();
            sb.append(i);
            String rev = new StringBuilder(sb).reverse().toString();
            if (len % 2 == 1) {
                rev = rev.substring(1);
            }
            sb.append(rev);
            candidates.add(Long.parseLong(sb.toString()));
        }

        long closest = -1;
        for (long candidate : candidates) {
            if (candidate != num) {
                if (closest == -1 ||
                    Math.abs(candidate - num) < Math.abs(closest - num) ||
                    (Math.abs(candidate - num) == Math.abs(closest - num) && candidate < closest)) {
                    closest = candidate;
                }
            }
        }

        return Long.toString(closest);          
    }
}
