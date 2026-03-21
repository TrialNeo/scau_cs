// Created by Github@TrialNeo(shenpanpro@gmail.com)
// Created Time 2026/3/21 12:08.


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../database/belong.h"
#include "../system/system.h"
#include "menu.h"
#include <time.h>


//二次确认
bool interact_comfirm() {
    char op;
    do {
        printf("请确认[y/n]:");
        scanf(" %c", &op);
    } while (op != 'y' && op != 'Y'&& op != 'n'&& op != 'N');
    return op == 'y' || op == 'Y';
}


// 录入新信息
void interact_enter() {
    system_cls();
    belong data ;
    printf("+============================================\n");
    printf("+ 您当前正在录入物品\n");
    printf("+--------------------------------------------\n");
    printf("- 请输入要录入的物品名称:");
    scanf(" %s", data.name);
    printf("- 请输入要录入的物品备注或描述:");
    scanf(" %s", data.desc);
    data.create_stamp = time(NULL);
    if (interact_comfirm()) {
        belong_add(data);
        system_cls();
        printf("- 物品:[%s] 录入成功\n", data.name);
    } else {
        printf("- 录入操作已取消\n");
    }
    system("pause");
}

void __interact_query(const belong data) {
    printf("[%s]%s %ld\n", data.name, data.desc, data.create_stamp);
}

void interact_query() {
    system_cls();
    belong_print(__interact_query);
    system("pause");
}


// 实现用户交互
void interact() {
    int op = 0;
    while (true) {
        system_cls();
        menu_welcome();
        printf("请输入您的功能编号:");
        scanf("%d", &op);
        switch (op) {
            case 1:
                interact_query();
                break;
            case 2:
                interact_enter();
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 0:
                return;
            default:
                break;
        }
    }
}
