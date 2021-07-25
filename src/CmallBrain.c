#include <stdlib.h>
#include <stdio.h>

char* buffer;
FILE* istream;
FILE* ostream;
char c;

int main( int argc, char * argv[] )
{
	if (argc == 3)
	{
		istream = fopen(argv[1], "r");
		if (istream)
		{
			ostream = fopen(argv[2], "w");
			fputs("#include <stdio.h>\nchar array[30000] = {0}; char* ptr = array;\nint main() {\n\t", ostream);
			while ((c = fgetc(istream)) != EOF)
			{
				switch (c)
				{
					case '>': fputs("++ptr; ", ostream); 		break;
					case '<': fputs("--ptr; ", ostream); 		break;
					case '+': fputs("++*ptr; ", ostream); 		break;
					case '-': fputs("--*ptr; ", ostream); 		break;
					case '.': fputs("putchar(*ptr); ", ostream); 	break;
					case ',': fputs("*ptr = getchar(); ", ostream); break;
					case '[': fputs("while (*ptr) { ", ostream);	break;
					case ']': fputs(" }", ostream);			break;
					default: 					break;
				}
			}
      fclose(istream);
			fputs("\n\treturn 0;\n}\n", ostream);
			fclose(ostream);
		}
		else
		{
			fprintf(stderr, "Could not open file: %s", argv[1]);
			exit(1);
		}
	}
	else
	{
		fprintf(stderr, "Expected source and output arguments");
		exit(1);
	}
	return 0;
}
