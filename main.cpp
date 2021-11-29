#define _CRT_SECURE_NO_WARNINGS

#include "..\..\Stack_dinamic\Stack_dinamic\stack.h"
#include "..\..\Sort_Onegin\Sort_Onegin\sort_text.h"
#include "consol_command.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int main()
{
    char file_name[] = "files/_quadratic_equation.txt";
    FILE* file = fopen(file_name, "rb");
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
    float* memory = (float*)calloc(20, sizeof(float));
    float* registers = (float*)calloc(3, sizeof(float));
    IdentifyData(stack, text, syms, memory, registers);
    Clear(stack);
}
