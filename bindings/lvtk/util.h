// Copyright 2022 Michael Fisher <mfisher@lvtk.org>
// SPDX-License-Identifier: ISC

#ifndef LUI_UTIL_H
#define LUI_UTIL_H

#ifdef MIN
#    undef MIN
#endif

#ifdef MAX
#    undef MAX
#endif

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

#endif
