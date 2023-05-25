#include <stdlib.h>
#include <stdio.h>

FILE* istream;
FILE* ostream;
char c;

int main( int argc, char * argv[] ) {

    if (argc != 3) {
        fprintf(stderr, "Expected source and output arguments");
        return 1;
    }

    istream = fopen(argv[1], "r");
    if (!istream) {
        fprintf(stderr, "Could not open file: %s", argv[1]);
        return 1;
    }

    ostream = fopen(argv[2], "w");
    if (!ostream) {
        fprintf(stderr, "Could not open file: %s", argv[2]);
        return 1;
    }
    
    fputs("#include <stdio.h>\n", ostream);
    fputs("char array[30000] = {0}; char* ptr = array;\n", ostream);
    fputs("int main() {\n\t", ostream);

    while ((c = fgetc(istream)) != EOF) {
        process_char();
    }

    fputs("\n\treturn 0;\n}\n", ostream);
    fclose(istream);
    fclose(ostream);

    return 0;
}

void process_char() {
    switch (c) {
        case '>':
            fputs("++ptr; ", ostream);
            break;
        case '<':
            fputs("--ptr; ", ostream);
            break;
        case '+':
            fputs("++*ptr; ", ostream);
            break;
        case '-':
            fputs("--*ptr; ", ostream);
            break;
        case '.':
            fputs("putchar(*ptr); ", ostream);
            break;
        case ',':
            fputs("*ptr = getchar(); ", ostream);
            break;
        case '[':
            fputs("while (*ptr) { ", ostream);
            break;
        case ']':
            fputs(" }", ostream);
            break;
        default:
            break;
    }
}
