// Copyright 2024 Michael Fisher <mfisher@lvtk.org>
// SPDX-License-Identifier: ISC

#pragma once

#include <lui/lui.h>
#include <lui/main.hpp>

namespace lvtk {

class Main;
class Widget;

/** The Vulkan graphics backend.
    Using this backend requires linking with lvtk-cairo-3.0

    @ingroup widgets
    @ingroup graphics
    @headerfile lvtk/ui/cairo.hpp 
*/
struct LUI_API Cairo : public Backend {
    Cairo() : Backend ("Cairo") {}
    std::unique_ptr<View> create_view (Main& c, Widget& w) override;
};

} // namespace lvtk
