// Source: https://leetcode.com/problems/sequential-digits/   |   Difficulty: Medium
//
// Problem Description:
// An integer has sequential digits if and only if each digit in the number is one more than the previous digit.
//
// Return a sorted list of all the integers in the range [low, high] inclusive that have sequential digits.
//
// Example:
// Input: low = 100, high = 300
// Output: [123,234]
//
// Constraints:
// 10 <= low <= high <= 10^9
//

class Solution {
    public List<Integer> sequentialDigits(int low, int high) {
        List<Integer> result = new ArrayList<>();
        String digits = "123456789";

        int lowLength = String.valueOf(low).length();
        int highLength = String.valueOf(high).length();

        for (int length = lowLength; length <= highLength; length++) {
            for (int start = 0; start <= 9 - length; start++) {
                String numStr = digits.substring(start, start + length);
                int num = Integer.parseInt(numStr);
                if (num >= low && num <= high) {
                    result.add(num);
                }
            }
        }

        return result;          
    }
}
