// Source: https://leetcode.com/problems/masking-personal-information/   |   Difficulty: Medium
//
// Problem Description:
// You are given a personal information string s, representing either an email address or a phone number. Return the masked personal information using the below rules.
//
// Email address:
//
// An email address is:
//
//
// 	A name consisting of uppercase and lowercase English letters, followed by
// 	The '@' symbol, followed by
// 	The domain consisting of uppercase and lowercase English letters with a dot '.' somewhere in the middle (not the first or last character).
//
//
// To mask an email:
//
//
// 	The uppercase letters in the name and domain must be converted to lowercase letters.
// 	The middle letters of the name (i.e., all but the first and last letters) must be replaced by 5 asterisks "*****".
//
//
// Phone number:
//
// A phone number is formatted as follows:
//
//
// 	The phone number contains 10-13 digits.
// 	The last 10 digits make up the local number.
// 	The remaining 0-3 digits, in the beginning, make up the country code.
// 	Separation characters from the set {'+', '-', '(', ')', ' '} separate the above digits in some way.
//
//
// To mask a phone number:
//
//
// 	Remove all separation characters.
// 	The masked phone number should have the form:
// 	
// 		"***-***-XXXX" if the country code has 0 digits.
// 		"+*-***-***-XXXX" if the country code has 1 digit.
// 		"+**-***-***-XXXX" if the country code has 2 digits.
// 		"+***-***-***-XXXX" if the country code has 3 digits.
// 	
// 	
// 	"XXXX" is the last 4 digits of the local number.
//
// Example:
// Input: s = "LeetCode@LeetCode.com"
// Output: "l*****e@leetcode.com"
// Explanation: s is an email address.
// The name and domain are converted to lowercase, and the middle of the name is replaced by 5 asterisks.
//
// Constraints:
// s is either a valid email or a phone number.
// 	If s is an email:
// 	
// 		8 <= s.length <= 40
// 		s consists of uppercase and lowercase English letters and exactly one '@' symbol and '.' symbol.
// 	
// 	
// 	If s is a phone number:
// 	
// 		10 <= s.length <= 20
// 		s consists of digits, spaces, and the symbols '(', ')', '-', and '+'.
//

char* maskPII(char* s) {
    char* at_sign = strchr(s, '@');
    if (at_sign) {
        // Mask email
        int name_len = at_sign - s;
        char* domain = at_sign + 1;
        int domain_len = strlen(domain);
        char* masked_email = (char*)malloc(name_len + domain_len + 6); // 5 asterisks + null terminator
        masked_email[0] = tolower(s[0]);
        masked_email[1] = '*';
        masked_email[2] = '*';
        masked_email[3] = '*';
        masked_email[4] = '*';
        masked_email[5] = '*';
        masked_email[6] = tolower(s[name_len - 1]);
        masked_email[7] = '@';
        for (int i = 0; i < domain_len; i++) {
            masked_email[8 + i] = tolower(domain[i]);
        }
        masked_email[8 + domain_len] = '\0';
        return masked_email;
    } else {
        // Mask phone number
        int digit_count = 0;
        for (char* p = s; *p; p++) {
            if (isdigit(*p)) {
                digit_count++;
            }
        }
        
        char* masked_phone;
        if (digit_count == 10) {
            masked_phone = (char*)malloc(13); // "***-***-XXXX" + null terminator
            sprintf(masked_phone, "***-***-%c%c%c%c", s[strlen(s)-4], s[strlen(s)-3], s[strlen(s)-2], s[strlen(s)-1]);
        } else {
            int country_code_len = digit_count - 10;
            masked_phone = (char*)malloc(16 + country_code_len); // "+***-***-***-XXXX" + null terminator
            sprintf(masked_phone, "+");
            for (int i = 0; i < country_code_len; i++) {
                strcat(masked_phone, "*");
            }
            strcat(masked_phone, "-***-***-");
            strcat(masked_phone, &s[strlen(s)-4]);
        }
        
        return masked_phone;
    }       
}
