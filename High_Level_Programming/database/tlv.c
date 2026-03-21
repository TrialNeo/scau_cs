// Created by Github@TrialNeo(shenpanpro@gmail.com)
// Created Time 2026/3/21 14:04.

#include "tlv.h"

#include "stdlib.h"
#include "string.h"

enum TLV_TYPE { TLV_TYPE_BYTES, TLV_TYPE_UINT32 };


#include <stdio.h>

// 将belong数据流序列化为tlv数据,记得释放buffer
void tlv_encode_bytes(unsigned char **buffer, unsigned *buffer_len, unsigned length, unsigned char *value) {
    if (0 < length && length <= 0b11111111) {
        *buffer_len = 2 + length;
        *buffer = malloc(*buffer_len);
        //(00010000)2  = (2^5)10
        (*buffer)[0] = TLV_TYPE_BYTES | 0b00010000;
        (*buffer)[1] = (char) (length & 0b00001111);
        memmove(*buffer + 2, value, length);
    } else if (length <= 0b1111111111111111) { // 2^16，对于现在这个玩具程序来说应该不会比这个还多的了
        *buffer_len = 3 + length;
        *buffer = malloc(*buffer_len);
        (*buffer)[0] = TLV_TYPE_BYTES | 0b00100000;
        (*buffer)[1] = (char) (length >> 8); // 0001 0001 0000 0000 => 0001 0001
        (*buffer)[2] = (char) length; //         0001 0001 0000 0000 => 0000 0000
        memmove(*buffer + 3, value, length);
    }
}

void tlv_encode_uint(unsigned char **buffer, unsigned *buffer_len, unsigned long value) {
    unsigned char val_buffer[16] = {0};
    unsigned offset = 1;
    do {
        unsigned char bit = value;
        val_buffer[16 - offset++] = bit;
    } while ((value >>= 8) != 0);
    // 我们把长度直接塞到高四位去。
    *buffer = malloc(offset);
    (*buffer)[0] = ((offset - 1) << 4) | TLV_TYPE_UINT32;
    *buffer_len = offset;
    offset--;
    memmove((*buffer) + 1, val_buffer + 16 - offset, offset);
}

// 将数据流序列化为普通数据
void tlv_decode_(void *buffer, const unsigned char *tlv_stream) {
    printf("%d\n", tlv_stream[0]);
    char type = tlv_stream[0] & 0b00001111;
    switch (type) {
        case TLV_TYPE_BYTES:
            unsigned char bit_len = tlv_stream[0] >> 4;
            unsigned len = 0;
            switch (bit_len) {
                case 1:
                    len = tlv_stream[1];
                    break;
                case 2:
                    len = (tlv_stream[1] << 8) + tlv_stream[2];
                    break;
                default:
                    break;
            }
            unsigned char *b = malloc(len);
            memmove(b, tlv_stream + 1 + bit_len, len);

            break;
        default:
            break;
    }
}

int main(int argc, char *argv[]) {
    unsigned char *buffer = 0;
    unsigned len = 0;
    tlv_encode_uint(&buffer, &len, 0b111111111); // 0b1 1111 1111
    for (int i = 0; i < len; i++) {
        printf("%d ", buffer[i]);
    }
}
