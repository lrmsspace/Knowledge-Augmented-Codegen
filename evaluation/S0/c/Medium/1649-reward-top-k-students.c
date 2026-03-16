// Source: https://leetcode.com/problems/reward-top-k-students/   |   Difficulty: Medium
//
// Problem Description:
// You are given two string arrays positive_feedback and negative_feedback, containing the words denoting positive and negative feedback, respectively. Note that no word is both positive and negative.
//
// Initially every student has 0 points. Each positive word in a feedback report increases the points of a student by 3, whereas each negative word decreases the points by 1.
//
// You are given n feedback reports, represented by a 0-indexed string array report and a 0-indexed integer array student_id, where student_id[i] represents the ID of the student who has received the feedback report report[i]. The ID of each student is unique.
//
// Given an integer k, return the top k students after ranking them in non-increasing order by their points. In case more than one student has the same points, the one with the lower ID ranks higher.
//
// Example:
// Input: positive_feedback = ["smart","brilliant","studious"], negative_feedback = ["not"], report = ["this student is studious","the student is smart"], student_id = [1,2], k = 2
// Output: [1,2]
// Explanation: 
// Both the students have 1 positive feedback and 3 points but since student 1 has a lower ID he ranks higher.
//
// Constraints:
// 1 <= positive_feedback.length, negative_feedback.length <= 104
// 	1 <= positive_feedback[i].length, negative_feedback[j].length <= 100
// 	Both positive_feedback[i] and negative_feedback[j] consists of lowercase English letters.
// 	No word is present in both positive_feedback and negative_feedback.
// 	n == report.length == student_id.length
// 	1 <= n <= 104
// 	report[i] consists of lowercase English letters and spaces ' '.
// 	There is a single space between consecutive words of report[i].
// 	1 <= report[i].length <= 100
// 	1 <= student_id[i] <= 109
// 	All the values of student_id[i] are unique.
// 	1 <= k <= n
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* topStudents(char** positive_feedback, int positive_feedbackSize, char** negative_feedback, int negative_feedbackSize, char** report, int reportSize, int* student_id, int student_idSize, int k, int* returnSize) {
    // Create hash sets for positive and negative feedback words
    #define HASH_SIZE 20011
    typedef struct HashSet {
        char** table;
        int size;
    } HashSet;

    HashSet* createHashSet(char** words, int wordsSize) {
        HashSet* set = (HashSet*)malloc(sizeof(HashSet));
        set->table = (char**)calloc(HASH_SIZE, sizeof(char*));
        set->size = wordsSize;
        for (int i = 0; i < wordsSize; i++) {
            unsigned long hash = 5381;
            for (char* c = words[i]; *c; c++) {
                hash = ((hash << 5) + hash) + (*c);
            }
            hash %= HASH_SIZE;
            while (set->table[hash]) {
                hash = (hash + 1) % HASH_SIZE;
            }
            set->table[hash] = words[i];
        }
        return set;
    }

    int contains(HashSet* set, char* word) {
        unsigned long hash = 5381;
        for (char* c = word; *c; c++) {
            hash = ((hash << 5) + hash) + (*c);
        }
        hash %= HASH_SIZE;
        while (set->table[hash]) {
            if (strcmp(set->table[hash], word) == 0) {
                return 1;
            }
            hash = (hash + 1) % HASH_SIZE;
        }
        return 0;
    }

    HashSet* posSet = createHashSet(positive_feedback, positive_feedbackSize);
    HashSet* negSet = createHashSet(negative_feedback, negative_feedbackSize);

    // Calculate scores for each student
    typedef struct Student {
        int id;
        int score;
    } Student;

    Student* students = (Student*)malloc(reportSize * sizeof(Student));
    for (int i = 0; i < reportSize; i++) {
        int score = 0;
        char* feedback = strdup(report[i]);
        char* token = strtok(feedback, " ");
        while (token) {
            if (contains(posSet, token)) {
                score += 3;
            } else if (contains(negSet, token)) {
                score -= 1;
            }
            token = strtok(NULL, " ");
        }
        free(feedback);
        students[i].id = student_id[i];
        students[i].score = score;
    }
    // Sort students by score (desc) and id (asc)
    int compare(const void* a, const void* b) {
        Student* studentA = (Student*)a;
        Student* studentB = (Student*)b;
        if (studentA->score != studentB->score) {
            return studentB->score - studentA->score; // Descending score
        }
        return studentA->id - studentB->id; // Ascending id
    }
    qsort(students, reportSize, sizeof(Student), compare);
    // Prepare the result
    int* result = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        result[i] = students[i].id;
    }
    *returnSize = k;
    // Free allocated memory
    free(students);
    free(posSet->table);
    free(posSet);
    free(negSet->table);
    free(negSet);
    return result;
}
