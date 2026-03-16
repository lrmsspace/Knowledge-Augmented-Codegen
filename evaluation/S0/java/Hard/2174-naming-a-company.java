// Source: https://leetcode.com/problems/naming-a-company/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of strings ideas that represents a list of names to be used in the process of naming a company. The process of naming a company is as follows:
//
//
// 	Choose 2 distinct names from ideas, call them ideaA and ideaB.
// 	Swap the first letters of ideaA and ideaB with each other.
// 	If both of the new names are not found in the original ideas, then the name ideaA ideaB (the concatenation of ideaA and ideaB, separated by a space) is a valid company name.
// 	Otherwise, it is not a valid name.
//
//
// Return the number of distinct valid names for the company.
//
// Example:
// Input: ideas = ["coffee","donuts","time","toffee"]
// Output: 6
// Explanation: The following selections are valid:
// - ("coffee", "donuts"): The company name created is "doffee conuts".
// - ("donuts", "coffee"): The company name created is "conuts doffee".
// - ("donuts", "time"): The company name created is "tonuts dime".
// - ("donuts", "toffee"): The company name created is "tonuts doffee".
// - ("time", "donuts"): The company name created is "dime tonuts".
// - ("toffee", "donuts"): The company name created is "doffee tonuts".
// Therefore, there are a total of 6 distinct company names.
//
// The following are some examples of invalid selections:
// - ("coffee", "time"): The name "toffee" formed after swapping already exists in the original array.
// - ("time", "toffee"): Both names are still the same after swapping and exist in the original array.
// - ("coffee", "toffee"): Both names formed after swapping already exist in the original array.
//
// Constraints:
// 2 <= ideas.length <= 5 * 104
// 	1 <= ideas[i].length <= 10
// 	ideas[i] consists of lowercase English letters.
// 	All the strings in ideas are unique.
//

class Solution {
    public long distinctNames(String[] ideas) {
        // Group suffixes by their first letter
        HashSet<String>[] suffixGroups = new HashSet[26];
        for (int i = 0; i < 26; i++) {
            suffixGroups[i] = new HashSet<>();
        }
        for (String idea : ideas) {
            char firstChar = idea.charAt(0);
            String suffix = idea.substring(1);
            suffixGroups[firstChar - 'a'].add(suffix);
        }

        long totalNames = 0;

        // Compare each pair of groups
        for (int i = 0; i < 25; i++) {
            for (int j = i + 1; j < 26; j++) {
                HashSet<String> groupA = suffixGroups[i];
                HashSet<String> groupB = suffixGroups[j];

                // Count common suffixes
                int commonCount = 0;
                for (String suffix : groupA) {
                    if (groupB.contains(suffix)) {
                        commonCount++;
                    }
                }

                // Calculate valid combinations
                int uniqueA = groupA.size() - commonCount;
                int uniqueB = groupB.size() - commonCount;
                totalNames += 2L * uniqueA * uniqueB;
            }
        }

        return totalNames;          
    }
}
