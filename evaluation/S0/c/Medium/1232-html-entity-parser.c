// Source: https://leetcode.com/problems/html-entity-parser/   |   Difficulty: Medium
//
// Problem Description:
// HTML entity parser is the parser that takes HTML code as input and replace all the entities of the special characters by the characters itself.
//
// The special characters and their entities for HTML are:
//
//
// 	Quotation Mark: the entity is &quot; and symbol character is ".
// 	Single Quote Mark: the entity is &apos; and symbol character is '.
// 	Ampersand: the entity is &amp; and symbol character is &.
// 	Greater Than Sign: the entity is &gt; and symbol character is >.
// 	Less Than Sign: the entity is &lt; and symbol character is <.
// 	Slash: the entity is &frasl; and symbol character is /.
//
//
// Given the input text string to the HTML parser, you have to implement the entity parser.
//
// Return the text after replacing the entities by the special characters.
//
// Example:
// Input: text = "&amp; is an HTML entity but &ambassador; is not."
// Output: "& is an HTML entity but &ambassador; is not."
// Explanation: The parser will replace the &amp; entity by &
//
// Constraints:
// 1 <= text.length <= 105
// 	The string may contain any possible characters out of all the 256 ASCII characters.
//

char* entityParser(char* text) {
    struct {
        char *entity;
        char symbol;
    } entities[] = {
        {"&quot;", '\"'},
        {"&apos;", '\''},
        {"&amp;", '&'},
        {"&gt;", '>'},
        {"&lt;", '<'},
        {"&frasl;", '/'},
    };
    int n = sizeof(entities) / sizeof(entities[0]);

    int len = strlen(text);
    char *result = (char *)malloc(len + 1);
    int resIndex = 0;

    for (int i = 0; i < len;) {
        int replaced = 0;
        for (int j = 0; j < n; j++) {
            int entityLen = strlen(entities[j].entity);
            if (strncmp(&text[i], entities[j].entity, entityLen) == 0) {
                result[resIndex++] = entities[j].symbol;
                i += entityLen;
                replaced = 1;
                break;
            }
        }
        if (!replaced) {
            result[resIndex++] = text[i++];
        }
    }
    result[resIndex] = '\0';
    return result;      
}
