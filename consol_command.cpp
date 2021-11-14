#define _CRT_SECURE_NO_WARNINGS
#include "consol_command.h"

#include <stdio.h>


bool CheckMoreTwoElem(Stack* stack)
{
    if (stack == NULL)
    {
        AssertFunction(stack);
    }
    return (stack->Data->size >= 2);
}


void Add(Stack* stack)
{
    if (stack == NULL)
    {
        AssertFunction(stack);
    }
    if (CheckMoreTwoElem(stack))
    {
        Push(stack, Pop(stack) + Pop(stack));
    }
    else
    {
        printf("Addition error! Few elements\n");
    }
}


void Sub(Stack* stack)
{
    if (stack == NULL)
    {
        AssertFunction(stack);
    }
    if (CheckMoreTwoElem(stack))
    {
        Push(stack, Pop(stack) - Pop(stack));
    }
    else
    {
        printf("Subtraction error! Few elements\n");
    }
}


void Mul(Stack* stack)
{
    if (stack == NULL)
    {
        AssertFunction(stack);
    }
    if (CheckMoreTwoElem(stack))
    {
        Push(stack, Pop(stack) * Pop(stack));
    }
    else
    {
        printf("Multiplication error! Few elements\n");
    }
}

void Div(Stack* stack)
{
    if (stack == NULL)
    {
        AssertFunction(stack);
    }
    if (CheckMoreTwoElem(stack))
    {
        int first = Pop(stack);
        int second = Pop(stack);
        if (second != 0)
        {
            Push(stack, first / second);
        }
        else
        {
            Push(stack, second);
            Push(stack, first);
            printf("Error! Division by zero\n");
        }
    }
    else
    {
        printf("Division error! Few elements\n");
    }
}


void Out(Stack* stack)
{
    for (int i = 0; i < stack->Data->size; i++)
    {
        printf("%d\n", stack->Data->data[i]);
    }
}

void IdentifyData(Stack* stack, char* data, int size, int* memory, int* registers)
{
    int number_commands[1000] = {};
    for (int i = 0, k = 0; i < size; i++, k++)
    {
        printf("%d\n", i);
        if (data[i] == 1)
        {
            bool reg = data[++i];
            bool constant = data[++i];
            bool operate_memory = data[++i];

            if (reg == 1)
            {
                char reg_value = data[++i];
                if (constant == 0)
                {
                    if (operate_memory == 0)
                    {
                        for (int i = 0; i < 3; i++)
                        {
                            if (reg_value == i + 1)
                            {
                                Push(stack, registers[i]);
                                break;
                            }
                        }
                    }
                    else if (operate_memory == 1)
                    {
                        for (int i = 0; i < 3; i++)
                        {
                            if (reg_value == i + 1)
                            {
                                Push(stack, memory[registers[i]]);
                                break;
                            }
                        }
                    }
                }
                else if (constant == 1)
                {
                    char value = data[++i];
                    if (operate_memory == 1)
                    {
                        for (int i = 0; i < 3; i++)
                        {
                            if (reg_value == i + 1)
                            {
                                Push(stack, memory[registers[i] + value]);
                                break;
                            }
                        }
                    }
                    else if (operate_memory == 0)
                    {
                        for (int i = 0; i < 3; i++)
                        {
                            if (reg_value == i + 1)
                            {
                                Push(stack, registers[0] + value);
                                break;
                            }
                        }
                    }
                    i += sizeof(int) - 1;
                }
            }
            else if (reg == 0)
            {
                if (constant == 1)
                {
                    char value = data[++i];
                    if (operate_memory == 0)
                    {
                        Push(stack, value);
                    }
                    else if (operate_memory == 1)
                    {
                        Push(stack, memory[value]);
                    }
                    i += sizeof(int) - 1;
                }
            }
        }
        else if (data[i] == 2)
        {
            bool reg = data[++i];
            bool constant = data[++i];
            bool operate_memory = data[++i];
            if (reg == 1)
            {
                char reg_value = data[++i];
                if (constant == 0)
                {
                    if (operate_memory == 0)
                    {
                        for (int i = 0; i < 3; i++)
                        {
                            if (reg_value == i + 1)
                            {
                                registers[i] = Pop(stack);
                                break;
                            }
                        }
                    }
                    else if (operate_memory == 1)
                    {
                        for (int i = 0; i < 3; i++)
                        {
                            if (reg_value == i + 1)
                            {
                                memory[registers[i]] = Pop(stack);
                            }
                        }
                    }
                }
                else if (constant == 1)
                {
                    char value = data[++i];
                    for (int i = 0; i < 3; i++)
                    {
                        if (reg_value == i + 1)
                        {
                            memory[registers[i] + value] = Pop(stack);
                        }
                    }
                    i += sizeof(int) - 1;
                }
            }
            else if (reg == 0)
            {
                if (constant == 0)
                {
                    if (operate_memory == 0)
                    {
                        Pop(stack);
                    }
                }
                else if (constant == 0 && operate_memory == 1)
                {
                    char value = data[++i];
                    memory[value] = Pop(stack);
                    i += sizeof(int) - 1;
                }
            }
        }
        else if (data[i] == 3)
        {
            Add(stack);
        }
        else if (data[i] == 4)
        {
            Sub(stack);
        }
        else if (data[i] == 5)
        {
            Mul(stack);
        }
        else if (data[i] == 6)
        {
            Div(stack);
        }
        else if (data[i] == 7)
        {
            Out(stack);
        }
        else if (data[i] == 8)
        {
            Dump(stack);
        }
        else if (data[i] == 9)
        {
            exit(0);
        }
        else if (data[i] == 11)
        {
            char reg_value = data[++i];
            char value = data[++i];
            for (int i = 0; i < 3; i++)
            {
                if (reg_value == i + 1)
                {
                    registers[i] = value;
                }
            }
            i += sizeof(int) - 1;
        }
        else if (data[i] == 12)
        {
            int jmp_comm = data[++i];
            i = jmp_comm - 1;
        }
        else if (data[i] == 13)
        {
            int ja_comm = data[++i];
            if (Size(stack) == 0)
            {
                i = ja_comm - 1;
            }
            else
            {
                i += sizeof(int) - 1;
            }
        }
        else
        {
            printf("Unknown command\n");
            exit(1);
        }
    }
}

int GetParametersFileInt(FILE* file, int* text, int syms)
{
    if (text == NULL)
    {
        fputs("Error memory allocation for *text\n", stderr);
        exit(2);
    }
    if (fread(text, sizeof(int), syms, file) != syms)
    {
        fputs("Error reading", stderr);
        exit(3);
    }
    int lines = 0;
    for (int i = 0; i < syms; i++)
    {
        if (text[i] == '\n')
        {
            lines++;
        }
    }
    lines++;

    return lines;
}

