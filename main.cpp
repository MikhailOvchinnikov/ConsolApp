#define _CRT_SECURE_NO_WARNINGS

#include "..\..\Stack_dinamic\Stack_dinamic\stack.h"
#include "..\..\Sort_Onegin\Sort_Onegin\sort_text.h"
#include "consol_command.h"
#include "compiler.h"

#include <stdio.h>
#include <string.h>



int main()
{
    CompilingFile();
    FILE* file = fopen("files/_commands.txt", "rb");
    if (file == NULL)
    {
        fputs("Error file open\n", stderr);
        exit(1);
    }

    int syms = CountSymbols(file);
    char* text = (char*)calloc((syms + 1), sizeof(char));

    GetParametersFile(file, text, syms);
    fclose(file);
    Stack* stack = CreateStack("Stack");
    int* memory = (int*)calloc(20, sizeof(int));
    int* registers = (int*)calloc(3, sizeof(int));
    IdentifyData(stack, text, syms, memory, registers);
    Clear(&stack);
}
