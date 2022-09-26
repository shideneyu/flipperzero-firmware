#ifndef _TOTP_TOKEN_INFO_H_
#define _TOTP_TOKEN_INFO_H_

#include <inttypes.h>

typedef struct {
    uint8_t* token;
    uint8_t token_length;
    char* name;
} TokenInfo;

void token_info_free(TokenInfo* token_info);

#endif
