#pragma once

#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "commands/commands.h"

// вершина дерева
typedef struct Node {
    char sym;                    // символ, соответствующий данной вершине
    void (*func)(int, char**);   // функция, соответствующая команде
    size_t nodec;                // количество потомков узла
    size_t allocated;            // количество памяти, выделенной для потомков, необходимо для уменьшения количества перевыделений памяти
    struct Node** lowerNodes;    // потомки узла
} Node;

Node* createTree(Command* commandsArr);  // собирает дерево по командам commadsArr
char runCommand(Node* baseNode, char* command, int argc, char* argv[]);  // запускает команду command в построенном дереве baseNode, передавая аргументы argv в количистве argc
void _parseCommand(Node* baseNode, Command command);  // добавляет одну команду в дерево
Node* _findLowerNode(Node* node, char sym);  // ищет необходимого потомка узла, сделан линейно, можно ускорить добавив лексикографический порядок и бинпоиск
Node* _createNewNode(Node* currentNode, char sym); // создает нового потомка
void _addNode(Node* dstNode, Node* newNode); // добавляет узел в список потомков