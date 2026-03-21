// Created by Github@TrialNeo(shenpanpro@gmail.com)
// Created Time 2026/3/21 14:04.

#ifndef PBM_TLV_H
#define PBM_TLV_H
void tlv_encode_bytes(unsigned char **buffer, unsigned *buffer_len, unsigned length, unsigned char *value);
void tlv_decode_bytes(char **buffer, const unsigned char *tlv_stream);

void tlv_encode_uint(unsigned char **buffer, unsigned *buffer_len, unsigned long value);
#endif // PBM_TLV_H
