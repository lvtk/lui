// Copyright 2022 Michael Fisher <mfisher@lvtk.org>
// SPDX-License-Identifier: ISC

#pragma once

#if __cplusplus > 201402L
#    include <optional>
#    define LUI_STD_EXPERIMENTAL_OPTIONAL 0
#else
#    if __has_include(<experimental/optional>)
#        include <experimental/optional>
#        define LUI_STD_EXPERIMENTAL_OPTIONAL 1
#    else
#        error "Header <optional> or <expermental/optional> is required."
#    endif
#endif

namespace lvtk {

// clang-format off
#if defined(LUI_STD_EXPERIMENTAL_OPTIONAL)
#if LUI_STD_EXPERIMENTAL_OPTIONAL
    template <typename T>
    using Optional = std::experimental::optional<T>;
#else
    /** Alias of std::optional */
    template <typename T>
    using Optional = std::optional<T>;
#endif
#undef LUI_STD_EXPERIMENTAL_OPTIONAL
#endif
// clang format-on

} // namespace lvtk
