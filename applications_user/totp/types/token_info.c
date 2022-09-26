#include "token_info.h"
#include "stdlib.h"

void token_info_free(TokenInfo* token_info) {
    if (token_info == NULL) return;
    free(token_info->name);
    free(token_info->token);
    free(token_info);
}
