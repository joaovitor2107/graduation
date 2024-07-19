#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 200

int count_format(const char *format) {
    int count = 0;
    while (*format) {
        if (*format == '%' && *(format + 1) != '%') {
            count++;
            format++;
        }
        format++;
    }
    return count;
}

int check_printf(const char *format, ...) {

    va_list args;
    va_start(args, format);


    int expected_args = count_format(format);

    int actual_args = 0;

    while (*format) {
        if (*format == '%' && *(format + 1) != '%') {
            actual_args++;
            switch (*(format + 1)) {
                case 'd': {
                    int d = va_arg(args, int);
                    (void)d;
                    break;
                }
                case 'f': {
                    double f = va_arg(args, double);
                    (void)f;
                    break;
                }
                case 'c': {
                    int c = va_arg(args, int);
                    (void)c;
                    break;
            
                }
                case 's': {
                    char *s = va_arg(args, char*);
                    (void)s;
                    break;
                }
                default:
                    va_end(args);
                    return 0;
            }
            format++;
        }
        format++;
    }

    va_end(args);

    return expected_args == actual_args;
}

bool check_scanf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    int expected_args = count_format(format);
    int actual_args = 0;

    while (*format) {
        if (*format == '%' && *(format + 1) != '%') {
            actual_args++;
            switch (*(format + 1)) {
                case 'd': {
                    int *d = va_arg( args, int*);
                    (void)d;
                    break;
                }
                case 'f': {
                    float *f = va_arg(args, float*);
                    (void)f;
                    break;
                }
                case 'c': {
                    char *c = va_arg(args, char*);
                    (void)c;
                    break;
                }
                case 's': {
                    char *s = va_arg(args, char*);
                    (void)s;
                    break;
                }
                default:
                    va_end(args);
                    return false;
            }
            format++;
        }
        format++;
    }

    va_end(args);

    return expected_args == actual_args;
}

bool check_loop(const char *code) {
    int parens = 0;
    int braces = 0;

    while (*code) {
        if (strncmp(code, "for", 3) == 0 && !isalnum(*(code + 3)) && *(code + 3) != '_') {
            code += 3;
            while (*code && isspace(*code)) code++;
            if (*code != '(' ) return false;
            parens++;
        } else if (strncmp(code, "while", 5) == 0 && !isalnum(*(code + 5)) && *(code + 5) != '_') {
            code += 5;
            while (*code && isspace(*code)) code++;
            if (*code != '(' ) return false;
            parens++;
        } else if (*code == '(') {
            parens++;
        } else if (*code == ')') {
            parens--;
            if (parens < 0) return false;
        } else if (*code == '{' ) {
            braces++;
        } else if (*code == '}' ) {
            braces--;
            if (braces < 0) return false;
        }
        code++;
    }

    return parens == 0 && braces == 0;
}

bool check_if_else(const char *code) {
    int if_count = 0;
    int else_count = 0;
    int parens = 0;

    while (*code) {
        if (strncmp(code, "if", 2) == 0 && !isalnum(*(code + 2)) && *(code + 2) != '_') {
            if_count++;
            code += 2;
            while (*code && isspace(*code)) code++;
            if (*code != '(' ) return false;
            parens++;
        } else if (strncmp(code, "else", 4) == 0 && !isalnum(*(code + 4)) && *(code + 4) != '_') {
            else_count++;
            code += 4;
            while (*code && isspace(*code)) code++;
            if (strncmp(code, "if", 2) == 0 && !isalnum(*(code + 2)) && *(code + 2) != '_') {
                code += 2;
                while (*code && isspace(*code)) code++;
                if (*code != '(' ) return false;
                parens++;
            }
        } else {
            if (*code == '(') {
                parens++;
            } else if (*code == ')') {
                parens--;
                if (parens < 0) return false;
            }
            code++;
        }
    }

    return parens == 0 && else_count <= if_count;
}

bool check_balance(const char *filename) {
    
    FILE *file = fopen(filename, "r");
    
    if (!file) {
        perror("Could not open file");
        return false;
    }

    char line[MAX_LINE_LENGTH];
    int parentheses = 0, braces = 0, brackets = 0, single_quotes = 0, double_quotes = 0;

    while (fgets(line, sizeof(line), file)) {
        for (int i = 0; line[i] != '\0'; i++) {
            switch (line[i]) {
                case '(': parentheses++; break;
                case ')': parentheses--; break;
                case '{': braces++; break;
                case '}': braces--; break;
                case '[': brackets++; break;
                case ']': brackets--; break;
                case '\'': single_quotes++; break;
                case '\"': double_quotes++; break;
            }
            if (parentheses < 0 || braces < 0 || brackets < 0) {
                fclose(file);
                return false;
        }
        }
    }

    fclose(file);

    return parentheses == 0 && braces == 0 && brackets == 0 && single_quotes % 2 == 0 && double_quotes % 2 == 0;
}

void check_syntax(const char *filename) {
    
    FILE *file = fopen(filename, "r");

    if (!file) {
        perror("Could not open file");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int line_number = 1;
    const char *keywords[] = {"#include", "main", "printf", "scanf", "if", "else", "for", "while", "switch", "case"};
    int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

    while (fgets(line, sizeof(line), file)) {
        for (int i = 0; i < num_keywords; i++) {
            if (strstr(line, keywords[i])) {
                if (strcmp(keywords[i], "printf") == 0) {
                    char *format = strchr(line, '(');
                    if (format){
                        format++;
                        char *end = strchr(format, ')' );
                        if (end) {
                            *end = '\0';
                            if (!check_printf(format)) {
                                printf("Error: Incorrect printf at line %d\n", line_number);
                            }
                        }
                    }
                } 
                else if (strcmp(keywords[i], "scanf") == 0) {
                    char *format = strchr(line, '(');
                    if (format) {
                        format++;
                        char *end = strchr(format, ')');
                        if (end) {
                            *end = '\0';
                            if (!check_scanf(format)) {
                                printf("Error: Incorrect scanf at line %d\n", line_number);
                            }
                        }
                    }

                } 
                else if (strcmp(keywords[i], "for") == 0 || strcmp(keywords[i], "while") == 0) {
                    if (!check_loop(line)) {
                        printf("Error: Incorrect loop syntax at line %d\n", line_number);
                    }
                } else if (strcmp(keywords[i], "if") == 0 || strcmp(keywords[i], "else") == 0) {
                    if (!check_if_else(line)) {
                        printf("Error: Incorrect if-else syntax at line %d\n", line_number);
                    }
                }
            }
        }
        line_number++;
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Correct usage is: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];

    if (check_balance(filename)) {
        printf("symbols are ok\n");
    } else {
        printf("are not ok.\n");
    }

    check_syntax(filename);

    return 0;
}
