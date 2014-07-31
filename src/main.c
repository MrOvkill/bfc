/*
	Author: Samuel "MrOverkill" Meyers
	License: The Unlicense
	Project: bfc
*/

#include <stdio.h>
#include <stdlib.h>

void compile(char* name)
{
	char* cmd = (char*)malloc(sizeof(char)*1024);
	sprintf(cmd, "gcc .temp.c -o %s", name);
	system(cmd);
	system("rm .temp.c");
	free(cmd);
}

void parse(FILE* f, char* name)
{
    FILE* out = fopen(".temp.c", "w");
    fprintf(out, "#include <stdio.h>\n\
#include <stdlib.h>\n\
\n\
int bfIncrement(int curr)\n\
{\n\
    if(curr >= 1024)\n\
    {\n\
        return 0;\n\
    }\n\
    else\n\
    {\n\
        return curr+1;\n\
    }\n\
}\n\
\n\
int bfDecrement(int curr)\n\
{\n\
    if(curr <= 0)\n\
    {\n\
        return 1024;\n\
    }\n\
    else\n\
    {\n\
        return curr-1;\n\
    }\n\
}\n\
\n\
int main(int argc, char* argv[])\n\
{\n\
	char* ptr = (char*)malloc(sizeof(char)*1024);\n\
	int index = 0;\n");
    
    char c = '/';
    
    while(c != EOF)
    {
        if(c == '>')
        {
            fprintf(out, "index = bfIncrement(index);\n");
        }
        if(c == '<')
        {
            fprintf(out, "index = bfDecrement(index);\n");
        }
        if(c == '+')
        {
            fprintf(out, "ptr[index]++;\n");
        }
        if(c == '-')
        {
            fprintf(out, "ptr[index]--;\n");
        }
        if(c == '.')
        {
            fprintf(out, "fputc(ptr[index], stdout);\n");
        }
        if(c == ',')
        {
            fprintf(out, "ptr[index] = fgetc(stdin);\n");
        }
        if(c == '[')
        {
            fprintf(out, "while(ptr[index])\n{\n");
        }
        if(c == ']')
        {
            fprintf(out, "}\n");
        }
        c = fgetc(f);
    }
    
    fprintf(out, "return 0;\n");
    fprintf(out, "}\n");
    fclose(out);
    compile(name);
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("Usage: %s <file.bf> [output]\n", argv[0]);
    }
    if(argc >= 3)
    {
    	parse(fopen(argv[1], "r"), argv[2]);
    }
    else
    {
        parse(fopen(argv[1], "r"), "a.out");
    }
}
