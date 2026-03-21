// Created by Github@TrialNeo(shenpanpro@gmail.com)
// Created Time 2026/3/21 12:08.


#include <stdbool.h>
#include <stdio.h>
#include "../../../../IDE/CLion/bin/mingw/x86_64-w64-mingw32/include/stdlib.h"
#include "menu.h"


bool interact_comfirm() {
    printf("请确认[y/n]:");
    char op;
    scanf(" %c", &op);
    return op == 'y' || op == 'Y';
}


// 录入新信息
void interact_enter() {
    system("cls");
    char name[255] = {0}, desc[1024] = {0};
    printf("+============================================\n");
    printf("+ 您当前正在录入物品\n");
    printf("+--------------------------------------------\n");
    printf("- 请输入要录入的物品名称:");
    scanf(" %s", name);
    printf("- 请输入要录入的物品备注或描述:");
    scanf(" %s", desc);
    if (interact_comfirm()) {



        printf("- 物品:[%s] 录入成功\n", name);
    } else {
        printf("- 录入操作已取消\n");
    }
    system("pause");
}


// 实现用户交互
void interact() {
    int op = 0;
    while (true) {
        system("cls");
        menu_welcome();
        printf("请输入您的功能编号:");
        scanf("%d", &op);
        switch (op) {
            case 1:
                break;
            case 2:
                interact_enter();
                break;
            case 0:
                return;
            default:
                break;
        }
    }
}
