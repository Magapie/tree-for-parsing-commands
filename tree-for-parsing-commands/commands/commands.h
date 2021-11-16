#pragma once
/**
* «десь описаны команды и соответствующие функции
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Command{             // структура, сопостовл€юща€ фукнцию и команду
    char* name;
    void (*func)(int, char**);
} Command;

int commandsCount;                  // количество команд, необходимо дл€ корректного построени€ дерева
Command* buildCommands();           // функци€, создающа€ вышеупом€нутые структуры
void func1(int argc, char* argv[]);
void func2(int argc, char* argv[]);
void func3(int argc, char* argv[]);
void func4(int argc, char* argv[]);
void func5(int argc, char* argv[]);
void func6(int argc, char* argv[]);

