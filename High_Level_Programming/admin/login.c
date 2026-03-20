// Created by Github@TrialNeo(shenpanpro@gmail.com) 
// Created Time 2026/3/20.

#include "login.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/crypto.h"


typedef LOGIN_STATUS LOGIN_STATUS;

const char crypto_key[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};


//用户登录
LOGIN_STATUS login(const char *password) {
    //传入的是明文，我们要对此进行简单的加密，可惜不能用ECDH+Des，RSA之类的，不然还能更安全
    char *buffer = 0;
    unsigned len = 0;
    if (!encrypt(crypto_key,password, strlen(password), &buffer, &len)) {
        //这里没有成功申请内存，不用释放
        return ERROR;
    }
    FILE * file =  fopen("./password","r"); //这个反正不是很满意

    unsigned len2 = ftell(file);
    if (file==NULL||len2 == 0) {
        return PASSWORD_UNSET;
    }
    char * tmp = (char *)malloc(len2 * sizeof(char));
    //对比，由于好像没有api，直接来做吧，，
    if (len != len2) {
       fclose(file);
        free(buffer);
        free(tmp);
        return PASSWORD_INCORRECT;
    }
    bool logined = true;
    for (int i = 0;i<len;i++) {
        if (buffer[i]!= tmp[i]) {
            logined = false;
        }
    }

    free(buffer);
    free(tmp);
    fclose(file);
    if (logined) {
        return SUCCESS;
    }
    return PASSWORD_INCORRECT;
}


bool password_check_set() {

    return 0;
}