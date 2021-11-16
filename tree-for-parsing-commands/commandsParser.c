#pragma once
#include "commandsParser.h"

/**
* Собирает дерево поочередно добавляя команды
* Корневой узел baseNode не несет смысловой нагрузки и нужен лишь для объединения команд, начинающихся с разных символов в одно дерево
*/

Node* createTree(Command* commandsArr) {            
    Node* baseNode = (Node*)malloc(sizeof(Node));
    baseNode->sym = '\0';                           
    baseNode->func = NULL;
    baseNode->lowerNodes = calloc(1, sizeof(Node));
    baseNode->nodec = 0;
    baseNode->allocated = 1;

    for (int i = 0; i < commandsCount; ++i) {        // поочередное добавление команд в дерево
        _parseCommand(baseNode, commandsArr[i]);
    }
    return baseNode;
}

/**
* Запускает команду в готовом дереве
* Работает аналогично _parseCommand
* Возвращает 1 при успешном выполнении и 0 в случае неизвестной команды
*/
char runCommand(Node* baseNode, char* command, int argc, char* argv[]) {
    size_t commandLen = strlen(command);
    Node* currentNode = baseNode;

    for (size_t i = 0; i < commandLen; ++i) {
        Node* nextNode = _findLowerNode(currentNode, command[i]);
        if (!nextNode) {            // заканчивает работу в случае отсутствующего узла
            return 0;
        }
        currentNode = nextNode;
    }
    if (currentNode->func) {             
        currentNode->func(argc, argv);
        return 1;
    }
    return 0;                      // заканчивает работу в случае отсутствующей функции в узле
}

/**
* Добавляет команду к дереву
* Спускается от корня и ищет подходящие вершины, при их отсутствии создает новые
*/
void _parseCommand(Node* baseNode, Command command) {                  // добавляет команды в дерево
    size_t commandLen = strlen(command.name);
    Node* currentNode = baseNode;                                      // указатель на текущую вершину, в дальнейшем будет спускаться по дереву

    for (size_t i = 0; i < commandLen; ++i) {                          // количество переходов по дереву будет равно количеству символов в команде
        Node* newNode = _findLowerNode(currentNode, command.name[i]);  // ищет подходящий узел в потомках
        if (!newNode) {                                                // при его отсутствии
            newNode = _createNewNode(currentNode, command.name[i]);    // создает новый
        }
        currentNode = newNode;                                         // делает переход на следующую вершину
    }
    currentNode->func = command.func;                                  // находясь в последней вершине записывает в нее функцию
}

/**
* Поиск узла в потомках с соответствующим символом
* Поиск линейный, можно сделать лексикографический порядок и бинарный поиск
* Если узел не найден возвращает NULL
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
* Создает новый узел и добавляет его в список потомков
*/
Node* _createNewNode(Node* currentNode, char sym) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->sym = sym;
    newNode->lowerNodes = (Node*)calloc(1, sizeof(Node));
    newNode->nodec = 0;
    newNode->allocated = 1;
    newNode->func = NULL;
    _addNode(currentNode, newNode);    // добавление в список потомков

    return newNode;
}


/**
* Добавляет узла в список потомков
* Сначала проверяет на наличие памяти, при ее отсутствии выделяет новый объем в 2 раза больше предыдущего
*/
void _addNode(Node* dstNode, Node* newNode) {
    if (dstNode->nodec >= dstNode->allocated) { // проверка на наличие памяти и выделение новой при отсутствии
        dstNode->allocated *= 2;
        Node* newArr = (Node*)calloc(dstNode->allocated, sizeof(Node*));
        memcpy(newArr, dstNode->lowerNodes, dstNode->nodec * sizeof(Node*));
        free(dstNode->lowerNodes);
        dstNode->lowerNodes = newArr;
    }
    dstNode->lowerNodes[dstNode->nodec] = newNode; // добавляем новый узел в конец списка
    ++(dstNode->nodec);                            // увеличиваем количество узлов
}