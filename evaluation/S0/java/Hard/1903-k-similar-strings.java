// Source: https://leetcode.com/problems/k-similar-strings/   |   Difficulty: Hard
//
// Problem Description:
// Strings s1 and s2 are k-similar (for some non-negative integer k) if we can swap the positions of two letters in s1 exactly k times so that the resulting string equals s2.
//
// Given two anagrams s1 and s2, return the smallest k for which s1 and s2 are k-similar.
//
// Example:
// Input: s1 = "ab", s2 = "ba"
// Output: 1
// Explanation: The two string are 1-similar because we can use one swap to change s1 to s2: "ab" --> "ba".
//
// Constraints:
// 1 <= s1.length <= 20
// 	s2.length == s1.length
// 	s1 and s2 contain only lowercase letters from the set {'a', 'b', 'c', 'd', 'e', 'f'}.
// 	s2 is an anagram of s1.
//

class Solution {
    public int kSimilarity(String s1, String s2) {
        Queue<String> queue = new LinkedList<>();
        Set<String> visited = new HashSet<>();
        queue.offer(s1);
        visited.add(s1);
        int level = 0;

        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                String curr = queue.poll();
                if (curr.equals(s2)) {
                    return level;
                }

                int j = 0;
                while (j < curr.length() && curr.charAt(j) == s2.charAt(j)) {
                    j++;
                }

                for (int k = j + 1; k < curr.length(); k++) {
                    if (curr.charAt(k) == s2.charAt(j) && curr.charAt(k) != s2.charAt(k)) {
                        String next = swap(curr, j, k);
                        if (!visited.contains(next)) {
                            visited.add(next);
                            queue.offer(next);
                        }
                    }
                }
            }
            level++;
        }

        return -1;          
    }
}
