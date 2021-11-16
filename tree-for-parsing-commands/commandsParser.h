#pragma once

#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "commands/commands.h"

// ������� ������
typedef struct Node {
    char sym;                    // ������, ��������������� ������ �������
    void (*func)(int, char**);   // �������, ��������������� �������
    size_t nodec;                // ���������� �������� ����
    size_t allocated;            // ���������� ������, ���������� ��� ��������, ���������� ��� ���������� ���������� ������������� ������
    struct Node** lowerNodes;    // ������� ����
} Node;

Node* createTree(Command* commandsArr);  // �������� ������ �� �������� commadsArr
char runCommand(Node* baseNode, char* command, int argc, char* argv[]);  // ��������� ������� command � ����������� ������ baseNode, ��������� ��������� argv � ���������� argc
void _parseCommand(Node* baseNode, Command command);  // ��������� ���� ������� � ������
Node* _findLowerNode(Node* node, char sym);  // ���� ������������ ������� ����, ������ �������, ����� �������� ������� ������������������ ������� � ��������
Node* _createNewNode(Node* currentNode, char sym); // ������� ������ �������
void _addNode(Node* dstNode, Node* newNode); // ��������� ���� � ������ ��������