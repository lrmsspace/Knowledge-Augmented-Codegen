// Source: https://leetcode.com/problems/minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string num representing the digits of a very large integer and an integer k. You are allowed to swap any two adjacent digits of the integer at most k times.
//
// Return the minimum integer you can obtain also as a string.
//
// Example:
// Input: num = "4321", k = 4
// Output: "1342"
// Explanation: The steps to obtain the minimum integer from 4321 with 4 adjacent swaps are shown.
//
// Constraints:
// 1 <= num.length <= 3 * 104
// 	num consists of only digits and does not contain leading zeros.
// 	1 <= k <= 109
//

class Solution {
    public String minInteger(String num, int k) {
        int n = num.length();
        List<Deque<Integer>> pos = new ArrayList<>();
        for (int i = 0; i < 10; i++) {
            pos.add(new ArrayDeque<>());
        }
        for (int i = 0; i < n; i++) {
            pos.get(num.charAt(i) - '0').offerLast(i);
        }

        FenwickTree fenwickTree = new FenwickTree(n);
        StringBuilder result = new StringBuilder();

        for (int i = 0; i < n; i++) {
            for (int d = 0; d <= 9; d++) {
                if (!pos.get(d).isEmpty()) {
                    int index = pos.get(d).peekFirst();
                    int shifts = fenwickTree.query(index + 1, n - 1);
                    int cost = index + shifts - i;
                    if (cost <= k) {
                        k -= cost;
                        result.append((char) (d + '0'));
                        fenwickTree.update(0, index, 1);
                        pos.get(d).pollFirst();
                        break;
                    }
                }
            }
        }

        return result.toString();                   
    }
}
