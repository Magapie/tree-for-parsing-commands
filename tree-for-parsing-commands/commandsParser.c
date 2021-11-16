#pragma once
#include "commandsParser.h"

/**
* �������� ������ ���������� �������� �������
* �������� ���� baseNode �� ����� ��������� �������� � ����� ���� ��� ����������� ������, ������������ � ������ �������� � ���� ������
*/

Node* createTree(Command* commandsArr) {            
    Node* baseNode = (Node*)malloc(sizeof(Node));
    baseNode->sym = '\0';                           
    baseNode->func = NULL;
    baseNode->lowerNodes = calloc(1, sizeof(Node));
    baseNode->nodec = 0;
    baseNode->allocated = 1;

    for (int i = 0; i < commandsCount; ++i) {        // ����������� ���������� ������ � ������
        _parseCommand(baseNode, commandsArr[i]);
    }
    return baseNode;
}

/**
* ��������� ������� � ������� ������
* �������� ���������� _parseCommand
* ���������� 1 ��� �������� ���������� � 0 � ������ ����������� �������
*/
char runCommand(Node* baseNode, char* command, int argc, char* argv[]) {
    size_t commandLen = strlen(command);
    Node* currentNode = baseNode;

    for (size_t i = 0; i < commandLen; ++i) {
        Node* nextNode = _findLowerNode(currentNode, command[i]);
        if (!nextNode) {            // ����������� ������ � ������ �������������� ����
            return 0;
        }
        currentNode = nextNode;
    }
    if (currentNode->func) {             
        currentNode->func(argc, argv);
        return 1;
    }
    return 0;                      // ����������� ������ � ������ ������������� ������� � ����
}

/**
* ��������� ������� � ������
* ���������� �� ����� � ���� ���������� �������, ��� �� ���������� ������� �����
*/
void _parseCommand(Node* baseNode, Command command) {                  // ��������� ������� � ������
    size_t commandLen = strlen(command.name);
    Node* currentNode = baseNode;                                      // ��������� �� ������� �������, � ���������� ����� ���������� �� ������

    for (size_t i = 0; i < commandLen; ++i) {                          // ���������� ��������� �� ������ ����� ����� ���������� �������� � �������
        Node* newNode = _findLowerNode(currentNode, command.name[i]);  // ���� ���������� ���� � ��������
        if (!newNode) {                                                // ��� ��� ����������
            newNode = _createNewNode(currentNode, command.name[i]);    // ������� �����
        }
        currentNode = newNode;                                         // ������ ������� �� ��������� �������
    }
    currentNode->func = command.func;                                  // �������� � ��������� ������� ���������� � ��� �������
}

/**
* ����� ���� � �������� � ��������������� ��������
* ����� ��������, ����� ������� ������������������ ������� � �������� �����
* ���� ���� �� ������ ���������� NULL
*/
Node* _findLowerNode(Node* node, char sym) {         
    for (size_t i = 0; i < node->nodec; ++i) {
        Node* currentNode = node->lowerNodes[i];
        if (currentNode->sym == sym) {
            return currentNode;
        }
    }
    return NULL;
}


/**
* ������� ����� ���� � ��������� ��� � ������ ��������
*/
Node* _createNewNode(Node* currentNode, char sym) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->sym = sym;
    newNode->lowerNodes = (Node*)calloc(1, sizeof(Node));
    newNode->nodec = 0;
    newNode->allocated = 1;
    newNode->func = NULL;
    _addNode(currentNode, newNode);    // ���������� � ������ ��������

    return newNode;
}


/**
* ��������� ���� � ������ ��������
* ������� ��������� �� ������� ������, ��� �� ���������� �������� ����� ����� � 2 ���� ������ �����������
*/
void _addNode(Node* dstNode, Node* newNode) {
    if (dstNode->nodec >= dstNode->allocated) { // �������� �� ������� ������ � ��������� ����� ��� ����������
        dstNode->allocated *= 2;
        Node* newArr = (Node*)calloc(dstNode->allocated, sizeof(Node*));
        memcpy(newArr, dstNode->lowerNodes, dstNode->nodec * sizeof(Node*));
        free(dstNode->lowerNodes);
        dstNode->lowerNodes = newArr;
    }
    dstNode->lowerNodes[dstNode->nodec] = newNode; // ��������� ����� ���� � ����� ������
    ++(dstNode->nodec);                            // ����������� ���������� �����
}