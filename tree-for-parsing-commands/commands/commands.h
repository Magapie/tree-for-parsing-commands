#pragma once
/**
* ����� ������� ������� � ��������������� �������
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Command{             // ���������, �������������� ������� � �������
    char* name;
    void (*func)(int, char**);
} Command;

int commandsCount;                  // ���������� ������, ���������� ��� ����������� ���������� ������
Command* buildCommands();           // �������, ��������� �������������� ���������
void func1(int argc, char* argv[]);
void func2(int argc, char* argv[]);
void func3(int argc, char* argv[]);
void func4(int argc, char* argv[]);
void func5(int argc, char* argv[]);
void func6(int argc, char* argv[]);

