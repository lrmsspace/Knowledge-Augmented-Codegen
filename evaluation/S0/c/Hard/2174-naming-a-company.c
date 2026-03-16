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

long long distinctNames(char** ideas, int ideasSize) {
    int suffixes[26][26] = {0};
    int exist[26][10000] = {0}; // assuming max 10000 unique suffixes per first letter
    int suffixCount[26] = {0};

    for (int i = 0; i < ideasSize; ++i) {
        char *idea = ideas[i];
        int firstCharIdx = idea[0] - 'a';
        // Check if this suffix already exists for this first character
        int found = 0;
        for (int j = 0; j < suffixCount[firstCharIdx]; ++j) {
            if (strcmp(idea + 1, ideas[exist[firstCharIdx][j]] + 1) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            exist[firstCharIdx][suffixCount[firstCharIdx]++] = i;
        }
    }

    for (int i = 0; i < ideasSize; ++i) {
        char *idea = ideas[i];
        int firstCharIdx = idea[0] - 'a';
        for (int j = 0; j < 26; ++j) {
            if (j == firstCharIdx) continue;
            // Check if the swapped idea exists
            int found = 0;
            for (int k = 0; k < suffixCount[j]; ++k) {
                if (strcmp(idea + 1, ideas[exist[j][k]] + 1) == 0) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                suffixes[firstCharIdx][j]++;
            }
        }
    }

    long long result = 0;
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (i != j) {
                result += (long long)suffixes[i][j] * suffixes[j][i];
            }
        }
    }

    return result;      
}
