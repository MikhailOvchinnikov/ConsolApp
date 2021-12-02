#define _CRT_SECURE_NO_WARNINGS
#include "consol_command.h"
#include "..\..\Stack_dinamic\Stack_dinamic\stack.h"
#include "stdio.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

#define CMD_Push(stack, expression) Push(stack, expression)

#define CMD_ADD(stack, val1, val2) CMD_Push(stack, val1 + val2)
#define CMD_SUB(stack, val1, val2) CMD_Push(stack, val2 - val1)
#define CMD_MUL(stack, val1, val2) CMD_Push(stack, val2*val1)
#define CMD_DIV(stack, val1, val2) \
if (val1 == 0){\
    printf("Division by zero\n");\
    errno = ErrorCode::DIVISIONERROR;\
} else {\
    CMD_Push(stack, val2 / val1);\
}


#define DEF_CMD(stack, name)\
{\
if (CheckMoreTwoElem(stack)) {\
    float fn = 0;\
    float sn = 0;\
    Pop(stack, &fn);\
    Pop(stack, &sn);\
    CMD_##name(stack, fn, sn);\
} else {\
    printf("Operation error! Few elements\n");\
}\
}


bool CheckMoreTwoElem(Stack* stack)
{
    return stack->data->size >= 2;
}


void Sqrt(Stack* stack)
{
    float value = 0;
    Pop(stack, &value);
    float sq = (float)sqrt(value);
    Push(stack, sq);
}


void Out(Stack* stack)
{
    float value = 0;
    Pop(stack, &value);
    printf("%f\n", value);
}


char SwitchMaskReg(int mask, char* data, int* ind)
{
    switch (mask)
    {
    case Mask::IOO:
    case Mask::IOI:
    case Mask::III:
    case Mask::IIO:
        return data[++*ind];
    }
    return 0;
}


float SwitchMaskVal(int mask, char* data, int* ind)
{
    switch (mask)
    {
    case Mask::III:
    case Mask::IIO:
    case Mask::OIO:
    case Mask::OII:
        return *(float*)&data[++*ind];
    }
    return 0;
}


int IdentifyData(Stack* stack, char* data, int size, float* memory, float* registers)
{
    Stack* stack_ret = CreateStack("ReturnIndexes");
    for (int i = 0, k = 0; i < size; i++, k++)
    {
        //printf("errno %d DATA %d i %d\n", errno, data[i], i);
        int dsplmt = sizeof(int) - 1;
        switch (data[i])
        {
        case Command::PUSH:
            {
                bool reg = data[++i];
                bool constant = data[++i];
                bool operate_memory = data[++i];

                int mask = reg * 100 + constant * 10 + operate_memory;
                int mem_index = 0;

                char reg_value = SwitchMaskReg(mask, data, &i);
                float value = SwitchMaskVal(mask, data, &i);

                
                switch (mask)
                {
                case Mask::IOO:
                    Push(stack, registers[reg_value - 1]);
                    break;
                case Mask::IOI:
                    mem_index = (int)registers[reg_value - 1];
                    Push(stack, memory[mem_index]);
                    break;
                case Mask::III:
                    mem_index = (int)registers[reg_value - 1] + (int)value;
                    Push(stack, memory[mem_index]);
                    i += dsplmt;
                    break;
                case Mask::IIO:
                    Push(stack, registers[reg_value - 1] + value);
                    i += dsplmt;
                    break;
                case Mask::OIO:
                    Push(stack, value);
                    i += dsplmt;
                    break;
                case Mask::OII:
                    Push(stack, memory[(int)value]);
                    i += dsplmt;
                    break;
                }
                break;
            }
        case Command::POP:
            {
                bool reg = data[++i];
                bool constant = data[++i];
                bool operate_memory = data[++i];

                int mask = reg * 100 + constant * 10 + operate_memory;
                int mem_index = 0;

                char reg_value = SwitchMaskReg(mask, data, &i);
                float value = SwitchMaskVal(mask, data, &i);

                switch (mask)
                {
                case Mask::OOO:
                    Pop(stack, NULL);
                case Mask::IOO:
                    Pop(stack, &registers[reg_value - 1]);
                    break;
                case Mask::IOI:
                    mem_index = (int)registers[reg_value - 1];
                    Pop(stack, &memory[mem_index]);
                    break;
                case Mask::IIO:
                    mem_index = (int)registers[reg_value - 1] + (int)value;
                    Pop(stack, &memory[mem_index]);
                    break;
                }
                
                break;
            }
        case Command::ADD:
            {
                DEF_CMD(stack, ADD);
                break;
            }
        case Command::SUB:
            {
                DEF_CMD(stack, SUB);
                break;
            }
        case Command::MUL:
            {
                DEF_CMD(stack, MUL);
                break;
            }
        case Command::DIV:
            {
                DEF_CMD(stack, DIV);
                if (errno)
                {
                    return errno;
                }
                break;
            }
        case Command::SQRT:
            {
                Sqrt(stack);
                break;
            }
        case Command::OUT:
            {
                Out(stack);
                break;
            }
        case Command::DMP:
            {
                Dump(stack);
                break;
            }
        case Command::HLT:
            {
                printf("The end of the programm\n");
                exit(0);
            }
        case Command::IN:
            {
                char reg_value = data[++i];
                float* value = (float*)&data[++i];
                registers[reg_value - 1] = *value;
                i += dsplmt;
                break;
            }
        case Command::JMP:
            {
                int* jmp_comm = (int*)&data[++i];
                i = *jmp_comm - 1;
                break;
            }
        case Command::JA:
            {
                int* ja_comm = (int*)&data[++i];
                float f_value = 0;
                float s_value = 0;
                Pop(stack, &f_value);
                Pop(stack, &s_value);
                if (f_value > s_value)
                {
                    i = *ja_comm - 1;
                }
                else
                {
                    i += dsplmt;
                }
                break;
            }
        case Command::CALL:
            {
                Push(stack_ret, (float)i);
                i = data[++i];
                break;
            }
        case Command::RET:
            {
                float fn = 0;
                Pop(stack_ret, &fn);
                i = int(&fn) + dsplmt + 1;
                break;
            }
        default:
            {
                printf("Unknown command\n");
                errno = ErrorCode::COMMANDERROR;
                return errno;
            }
        }
    }
    return errno;
}

int GetParametersFileInt(FILE* file, int* text, int syms)
{
    if (text == NULL)
    {
        fputs("Error memory allocation for *text\n", stderr);
        errno = ErrorCode::MEMORYERROR;
        return 0;
    }
    if (fread(text, sizeof(int), syms, file) != syms)
    {
        fputs("Error reading", stderr);
        errno = ErrorCode::FILEERROR;
        return 0;
    }
    int lines = 0;
    for (int i = 0; i < syms; i++)
    {
        lines += text[i] == '\n';
    }
    lines++;

    return lines;
}

