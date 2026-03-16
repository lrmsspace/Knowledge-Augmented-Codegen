// Source: https://leetcode.com/problems/count-the-repetitions/   |   Difficulty: Hard
//
// Problem Description:
// We define str = [s, n] as the string str which consists of the string s concatenated n times.
//
//
// 	For example, str == ["abc", 3] =="abcabcabc".
//
//
// We define that string s1 can be obtained from string s2 if we can remove some characters from s2 such that it becomes s1.
//
//
// 	For example, s1 = "abc" can be obtained from s2 = "abdbec" based on our definition by removing the bolded underlined characters.
//
//
// You are given two strings s1 and s2 and two integers n1 and n2. You have the two strings str1 = [s1, n1] and str2 = [s2, n2].
//
// Return the maximum integer m such that str = [str2, m] can be obtained from str1.
//
// Example:
// Input: s1 = "acb", n1 = 4, s2 = "ab", n2 = 2
// Output: 2
//
// Constraints:
// 1 <= s1.length, s2.length <= 100
// 	s1 and s2 consist of lowercase English letters.
// 	1 <= n1, n2 <= 106
//

int getMaxRepetitions(char* s1, int n1, char* s2, int n2) {
    int len1 = strlen(s1), len2 = strlen(s2);
    int *repeatCount = (int*)malloc((len2 + 1) * sizeof(int));
    int *nextIndex = (int*)malloc((len2 + 1) * sizeof(int));
    for (int i = 0; i <= len2; i++) {
        int index = i;
        for (int j = 0; j < len1; j++) {
            if (s1[j] == s2[index]) {
                index++;
                if (index == len2) index = 0;
            }
        }
        repeatCount[i] = index == 0 ? 1 : 0;
        nextIndex[i] = index;
    }

    int totalCount = 0;
    int currentIndex = 0;
    int *seenIndex = (int*)malloc((len2 + 1) * sizeof(int));
    int *seenCount = (int*)malloc((len2 + 1) * sizeof(int));
    memset(seenIndex, -1, (len2 + 1) * sizeof(int));

    for (int i = 0; i < n1; i++) {
        if (seenIndex[currentIndex] != -1) {
            int prevI = seenIndex[currentIndex];
            int cycleLength = i - prevI;
            int cycleCount = totalCount - seenCount[currentIndex];
            int remainingCycles = (n1 - i) / cycleLength;
            totalCount += remainingCycles * cycleCount;
            i += remainingCycles * cycleLength;
        }
        seenIndex[currentIndex] = i;
        seenCount[currentIndex] = totalCount;

        totalCount += repeatCount[currentIndex];
        currentIndex = nextIndex[currentIndex];
    }

    free(repeatCount);
    free(nextIndex);
    free(seenIndex);
    free(seenCount);

    return totalCount / n2;     
}
