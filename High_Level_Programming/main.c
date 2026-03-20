// Created by Github@TrialNeo(shenpanpro@gmail.com) 
// Created Time 2026/3/20.

#include <stdio.h>

#include "menu/menu.h"
#include <stdbool.h>

#include "admin/login.h"

int main() {

    if (login("hhhhhhhhh") == PASSWORD_UNSET) {
        printf("你是第一次用吧，请先设置密码：");

    }

    char op = 0;
    while (true) {
        menu_welcome();
        printf("请输入您的功能编号:");
        op  = getchar();

        switch (op) {

            case 0:
                return 0;
            default:
                break;
        }
    }
}
