#define _CRT_SECURE_NO_WARNINGS
#include "consol_command.h"
#include "commands.h"
#include "..\..\Stack_dinamic\Stack_dinamic\stack.h"
#include "stdio.h"
#include <stdio.h>
#include <stdlib.h>

#define SafetyPop(stack, value) if(Pop(stack, &value)){exit(1);}



bool CheckMoreTwoElem(Stack* stack)
{
    return (stack->data->size >= 2);
}


void Add(Stack* stack)
{
    if (CheckMoreTwoElem(stack))
    {
        int fn = 0;
        int sn = 0;
        SafetyPop(stack, fn);
        SafetyPop(stack, sn);
        Push(stack, fn + sn);
    }
    else
    {
        printf("Addition error! Few elements\n");
    }
}


void Sub(Stack* stack)
{
    if (CheckMoreTwoElem(stack))
    {
        int fn = 0;
        int sn = 0;
        SafetyPop(stack, fn);
        SafetyPop(stack, sn);
        Push(stack, fn - sn);
    }
    else
    {
        printf("Subtraction error! Few elements\n");
    }
}


void Mul(Stack* stack)
{
    if (CheckMoreTwoElem(stack))
    {
        int fn = 0;
        int sn = 0;
        SafetyPop(stack, fn);
        SafetyPop(stack, sn);
        Push(stack, fn * sn);
    }
    else
    {
        printf("Multiplication error! Few elements\n");
    }
}

void Div(Stack* stack)
{
    if (CheckMoreTwoElem(stack))
    {
        int fn = 0;
        int sn = 0;
        SafetyPop(stack, fn);
        SafetyPop(stack, sn);
        if (sn != 0)
        {
            Push(stack, fn / sn);
        }
        else
        {
            Push(stack, sn);
            Push(stack, fn);
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
    for (int i = 0; i < stack->data->size; i++)
    {
        printf("%d\n", stack->data->data[i]);
    }
}

void IdentifyData(Stack* stack, char* data, int size, int* memory, int* registers)
{
    Stack* stack_ret = CreateStack("ReturnIndexes");
    for (int i = 0, k = 0; i < size; i++, k++)
    {
        printf("errno %d DATA %d i %d\n", errno, data[i], i);
        if (data[i] == PUSH)
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
                    int* value = (int*)&data[++i];
                    if (operate_memory == 1)
                    {
                        for (int i = 0; i < 3; i++)
                        {
                            if (reg_value == i + 1)
                            {
                                Push(stack, memory[registers[i] + *value]);
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
                                Push(stack, registers[0] + *value);
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
                    int* value = (int*)&data[++i];
                    if (operate_memory == 0)
                    {
                        Push(stack, *value);
                    }
                    else if (operate_memory == 1)
                    {
                        Push(stack, memory[*value]);
                    }
                    i += sizeof(int) - 1;
                }
            }
        }
        else if (data[i] == POP)
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
                                SafetyPop(stack, registers[i]);
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
                                SafetyPop(stack, memory[registers[i]]);
                            }
                        }
                    }
                }
                else if (constant == 1)
                {
                    int* value = (int*)&data[++i];
                    for (int i = 0; i < 3; i++)
                    {
                        if (reg_value == i + 1)
                        {
                            SafetyPop(stack, memory[registers[i] + *value]);
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
                        int nothing = 0;
                        SafetyPop(stack, nothing);
                    }
                }
                else if (constant == 0 && operate_memory == 1)
                {
                    int* value = (int*)&data[++i];
                    SafetyPop(stack, memory[*value]);
                    i += sizeof(int) - 1;
                }
            }
        }
        else if (data[i] == ADD)
        {
            Add(stack);
        }
        else if (data[i] == SUB)
        {
            Sub(stack);
        }
        else if (data[i] == MUL)
        {
            Mul(stack);
        }
        else if (data[i] == DIV)
        {
            Div(stack);
        }
        else if (data[i] == OUT)
        {
            Out(stack);
        }
        else if (data[i] == DMP)
        {
            Dump(stack);
        }
        else if (data[i] == HLT)
        {
            printf("The end of this programm\n");
            exit(0);
        }
        else if (data[i] == IN)
        {
            char reg_value = data[++i];
            int* value = (int*)&data[++i];
            for (int i = 0; i < 3; i++)
            {
                if (reg_value == i + 1)
                {
                    registers[i] = *value;
                }
            }
            i += sizeof(int) - 1;
        }
        else if (data[i] == JMP)
        {
            int* jmp_comm = (int*)&data[++i];
            i = *jmp_comm - 1;
        }
        else if (data[i] == JA)
        {
            int* ja_comm = (int*)&data[++i];
            int size = 0;
            Size(stack, &size);
            if (size == 0)
            {
                i = *ja_comm - 1;
            }
            else
            {
                i += sizeof(int) - 1;
            }
        }
        else if (data[i] == CALL)
        {
            Push(stack_ret, i);
            i = data[++i];
        }
        else if (data[i] == RET)
        {
            int fn = 0;
            SafetyPop(stack_ret, fn);
            i = fn + sizeof(int);
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

