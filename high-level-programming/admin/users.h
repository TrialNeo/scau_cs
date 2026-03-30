// Created by Github@TrialNeo(shenpanpro@gmail.com)
// Created Time 2026/3/20.

#ifndef PBM_ADMIN
#define PBM_ADMIN
#include <string>

// 职责
enum ROLE { ROLE_ADMIN, ROLE_USER };

typedef struct user user;
const char crypto_key[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

#ifdef __cplusplus
extern "C" {
#endif
using namespace std;
#include <stdbool.h>
bool user_is_nil();
#ifdef __cplusplus
}
#endif
#endif // PBM_ADMIN
