// Source: https://leetcode.com/problems/longest-common-prefix-of-k-strings-after-removal/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of strings words and an integer k.
//
// For each index i in the range [0, words.length - 1], find the length of the longest common prefix among any k strings (selected at distinct indices) from the remaining array after removing the ith element.
//
// Return an array answer, where answer[i] is the answer for ith element. If removing the ith element leaves the array with fewer than k strings, answer[i] is 0.
//
// Example:
// Input: words = ["jump","run","run","jump","run"], k = 2
//
// Output: [3,4,4,3,4]
//
// Explanation:
//
//
// 	Removing index 0 ("jump"):
//
// 	
// 		words becomes: ["run", "run", "jump", "run"]. "run" occurs 3 times. Choosing any two gives the longest common prefix "run" (length 3).
// 	
// 	
// 	Removing index 1 ("run"):
// 	
// 		words becomes: ["jump", "run", "jump", "run"]. "jump" occurs twice. Choosing these two gives the longest common prefix "jump" (length 4).
// 	
// 	
// 	Removing index 2 ("run"):
// 	
// 		words becomes: ["jump", "run", "jump", "run"]. "jump" occurs twice. Choosing these two gives the longest common prefix "jump" (length 4).
// 	
// 	
// 	Removing index 3 ("jump"):
// 	
// 		words becomes: ["jump", "run", "run", "run"]. "run" occurs 3 times. Choosing any two gives the longest common prefix "run" (length 3).
// 	
// 	
// 	Removing index 4 ("run"):
// 	
// 		words becomes: ["jump", "run", "run", "jump"]. "jump" occurs twice. Choosing these two gives the longest common prefix "jump" (length 4).
//
// Constraints:
// 1 <= k <= words.length <= 105
// 	1 <= words[i].length <= 104
// 	words[i] consists of lowercase English letters.
// 	The sum of words[i].length is smaller than or equal 105.
//

class Solution {
    public int[] longestCommonPrefix(String[] words, int k) {
        int n = words.length;
        int[] result = new int[n];
        if (n < k) {
            return result; // If there are fewer than k strings, all results are 0
        }

        // Step 1: Count frequency of each word
        Map<String, Integer> frequencyMap = new HashMap<>();
        for (String word : words) {
            frequencyMap.put(word, frequencyMap.getOrDefault(word, 0) + 1);
        }

        // Step 2: Create a list of unique words sorted by frequency
        List<String> uniqueWords = new ArrayList<>(frequencyMap.keySet());
        uniqueWords.sort((a, b) -> frequencyMap.get(b) - frequencyMap.get(a));

        // Step 3: Precompute longest common prefixes for top k frequent words
        String[] topKWords = new String[Math.min(k, uniqueWords.size())];
        for (int i = 0; i < topKWords.length; i++) {
            topKWords[i] = uniqueWords.get(i);
        }

        int lcpLength = computeLCP(topKWords);

        // Step 4: Calculate result for each word removal
        for (int i = 0; i < n; i++) {
            String currentWord = words[i];
            int freq = frequencyMap.get(currentWord);

            if (freq > 1 || uniqueWords.size() < k) {
                result[i] = lcpLength;
            } else {
                // If removing the current word reduces the count below k
                List<String> reducedTopKWords = new ArrayList<>(Arrays.asList(topKWords));
                reducedTopKWords.remove(currentWord);
                if (reducedTopKWords.size() < k) {
                    result[i] = 0;
                } else {
                    result[i] = computeLCP(reducedTopKWords.subList(0, k).toArray(new String[0]));
                }
            }
        }

        return result;          
    }
}
