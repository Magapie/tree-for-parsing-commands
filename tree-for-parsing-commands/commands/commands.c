#include "commands.h"

char* reverseString(char* str) {                       // просто разворот строки для демонстрации
    size_t l = strlen(str);
    char* ans = (char*)calloc(l + 1, sizeof(char));
    for (int i = 0; i < l; i++) {
        ans[i] = str[l - 1 - i];
    }
    ans[l] = '\0';
    return ans;
}

void func1(int argc, char* argv[]) {
    printf("Hello, I'm func1 and I do nothing!\n");
}

void func2(int argc, char* argv[]) {
    printf("Hello, I'm func2 and I do nothing at all!\n");
}

void func3(int argc, char* argv[]) {
    printf("Hello, I'm func3 and I just print all args\n");
    for (size_t i = 0; i < argc; ++i) {
        printf("%s ", argv[i]);
    }
    printf("\n");
}

void func4(int argc, char* argv[]) {
    printf("Hello, I'm func4 and I print argc value\n");
    printf("%d\n", argc);
}

void func5(int argc, char* argv[]) {
    printf("Hello, I'm work and I print args in reverse order\n");
    for (int i = argc - 1; i >= 0; --i) {
        printf("%s ", argv[i]);
    }
    printf("\n");
}

void func6(int argc, char* argv[]) {
    printf("Hello, I'm just func and I reverse all args\n");
    for (size_t i = 0; i < argc; ++i) {
        char* reversedStr = reverseString(argv[i]);
        printf("%s ", reversedStr);
        free(reversedStr);
    }
    printf("\n");
}

Command* buildCommands() {
    commandsCount = 6;
    Command* commandsArr = (Command*)calloc(6, sizeof(Command));
    commandsArr[0] = (Command){ "func1" , func1 };
    commandsArr[1] = (Command){ "func2" , func2 };
    commandsArr[2] = (Command){ "func3" , func3 };
    commandsArr[3] = (Command){ "func4" , func4 };
    commandsArr[4] = (Command){ "work" , func5 };
    commandsArr[5] = (Command){ "func" , func6 };
    return commandsArr;
}