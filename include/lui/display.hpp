// Copyright 2022 Michael Fisher <mfisher@lvtk.org>
// SPDX-License-Identifier: ISC

#pragma once

#include <lui/lui.hpp>
#include <lui/rectangle.hpp>

namespace lvtk {

struct LUI_API Display {
    bool primary { false };
    double scale { 1.0 };
    double dpi { 96.0 };
};

} // namespace lvtk
