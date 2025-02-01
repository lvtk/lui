// Copyright 2022 Michael Fisher <mfisher@lvtk.org>
// SPDX-License-Identifier: ISC

#ifndef LUI_BYTES_H
#define LUI_BYTES_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _LvtkBytes {
    size_t size;
    uint8_t* data;
} LvtkBytes;

#ifdef __cplusplus
}
#endif

#endif
