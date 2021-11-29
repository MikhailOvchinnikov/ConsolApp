#pragma once
#include "..\..\Stack_dinamic\Stack_dinamic\stack.h"

/// <summary>
/// Check appropriate size of data for operations
/// </summary>
/// <param name="stack">Transmitted stack</param>
/// <returns>1 if size of data is equal or over 2, else - 0</returns>
bool CheckMoreTwoElem(Stack* stack);


/// <summary>
/// Addition of two last elements of stack
/// </summary>
/// <param name="stack">Transmitted stack</param>
void Add(Stack* stack);


/// <summary>
/// Subtraction of two last elements of stack
/// </summary>
/// <param name="stack">Transmitted syack</param>
void Sub(Stack* stack);


/// <summary>
/// Multiplication of two last elements of stack
/// </summary>
/// <param name="stack">Transmitted stack</param>
void Mul(Stack* stack);


/// <summary>
/// Division of two last elements of stack
/// </summary>
/// <param name="stack">Transmitted stack</param>
void Div(Stack* stack);


/// <summary>
/// Replace last value in the stack to its square root
/// </summary>
/// <param name="stack">Transmitted stack</param>
void Sqrt(Stack* stack);


/// <summary>
/// Print all elements of stack
/// </summary>
/// <param name="stack">Transmitted stack</param>
void Out(Stack* stack);


/// <summary>
/// Verify transmitted command and implement it
/// </summary>
/// <param name="stack">Transmitted stack</param>
/// <param name="command">String of command</param>
void IdentifyData(Stack* stack, char* data, int size, float* memory, float* registers);