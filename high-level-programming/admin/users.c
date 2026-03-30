// Created by Github@TrialNeo(shenpanpro@gmail.com)
// Created Time 2026/3/29 15:41.

#include "users.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/crypto.h"


struct user {
    char username[255];
    char password[255];
    ROLE role;
};

bool user_regist(user admin, const char *new_username, const char *new_password, char *error, size_t error_size) {
    if (admin.role != ROLE_ADMIN) {
        snprintf(error, error_size, "权限不足");
        return false;
    }
    char file_path[1024];
    snprintf(file_path, sizeof(file_path), "/data/users/%s", new_username);
    FILE *fp = fopen(file_path, "rb");
    if (fp != NULL) {
        fclose(fp);
        snprintf(error, error_size, "该用户已存在，无法注册");
        return false;
    }
    char *buffer = NULL;
    unsigned buffer_len = 0;
    if (!encrypt(crypto_key, new_password, strlen(new_password), &buffer, &buffer_len)) {
        snprintf(error, error_size, "密码加密失败");
        return false;
    }

    fp = fopen(file_path, "wb");
    fwrite(buffer, 1, buffer_len, fp);
    fclose(fp);
    free(buffer);
    return true;
}

bool user_login(user user, char *error, size_t error_size) {
    char file_path[1024];
    snprintf(file_path, sizeof(file_path), "/data/users/%s", user.username);
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        snprintf(error, error_size, "该用户不存在");
        return false;
    }

    char *buffer = NULL;
    unsigned len = 0;
    if (!encrypt(crypto_key, user.password, strlen(user.password), &buffer, &len)) {
        snprintf(error, error_size, "密码加密失败");
        fclose(file);
        return false;
    }

    fseek(file, 0, SEEK_END);
    long len2 = ftell(file);
    rewind(file);
    if ((long) len != len2) {
        free(buffer);
        fclose(file);
        snprintf(error, error_size, "密码错误");
        return false;
    }
    char *tmp = malloc(len2);
    fread(tmp, 1, len2, file);
    bool login_status = true;
    for (int i = 0; i < (int) len; i++) {
        if (buffer[i] != tmp[i]) {
            login_status = false;
            break;
        }
    }
    free(buffer);
    free(tmp);
    fclose(file);
    if (login_status) {
        return true;
    }
    snprintf(error, error_size, "密码错误");
    return false;
}

bool user_is_nil() {
    DIR *d = opendir("./data/users");
    if (d == NULL) {
        return true;
    }
    dirent *entry;
    int found = 0;
    while ((entry = readdir(d)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            found = 1;
            break;
        }
    }
    closedir(d);
    return !found;
}
