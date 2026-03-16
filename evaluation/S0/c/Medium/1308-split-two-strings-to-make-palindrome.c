// Source: https://leetcode.com/problems/split-two-strings-to-make-palindrome/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings a and b of the same length. Choose an index and split both strings at the same index, splitting a into two strings: aprefix and asuffix where a = aprefix + asuffix, and splitting b into two strings: bprefix and bsuffix where b = bprefix + bsuffix. Check if aprefix + bsuffix or bprefix + asuffix forms a palindrome.
//
// When you split a string s into sprefix and ssuffix, either ssuffix or sprefix is allowed to be empty. For example, if s = "abc", then "" + "abc", "a" + "bc", "ab" + "c" , and "abc" + "" are valid splits.
//
// Return true if it is possible to form a palindrome string, otherwise return false.
//
// Notice that x + y denotes the concatenation of strings x and y.
//
// Example:
// Input: a = "x", b = "y"
// Output: true
// Explaination: If either a or b are palindromes the answer is true since you can split in the following way:
// aprefix = "", asuffix = "x"
// bprefix = "", bsuffix = "y"
// Then, aprefix + bsuffix = "" + "y" = "y", which is a palindrome.
//
// Constraints:
// 1 <= a.length, b.length <= 105
// 	a.length == b.length
// 	a and b consist of lowercase English letters
//

bool checkPalindromeFormation(char* a, char* b) {
    int len = strlen(a);
    int left, right, i;

    // Helper function to check if a palindrome can be formed
    bool canFormPalindrome(char* s1, char* s2) {
        left = 0;
        right = len - 1;

        while (left < right && s1[left] == s2[right]) {
            left++;
            right--;
        }

        // Check if the remaining substring in either s1 or s2 is a palindrome
        for (i = left, j = right; i < j; i++, j--) {
            if (s1[i] != s1[j]) break;
        }
        if (i >= j) return true;

        for (i = left, j = right; i < j; i++, j--) {
            if (s2[i] != s2[j]) break;
        }
        return i >= j;
    }

    return canFormPalindrome(a, b) || canFormPalindrome(b, a);      
}
