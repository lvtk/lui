// Copyright 2019-2024 Michael Fisher <mfisher@lvtk.org>
// SPDX-License-Identifier: ISC

#include <iostream>

#include <lui/main.hpp>
#include <lui/view.hpp>

#if LUI_DEMO_CAIRO
#    include <lui/cairo.hpp>
#elif LUI_DEMO_VULKAN
#    include <lui/vulkan.hpp>
#elif LUI_DEMO_OPENGL
#    include <lui/opengl.hpp>
#endif

#include "demo.hpp"

namespace lvtk {
namespace demo {

template <class Wgt>
static int run (lvtk::Main& context) {
    try {
        auto content = std::make_unique<Wgt>();
        if (auto view = context.elevate (*content, lvtk::View::RESIZABLE, 0)) {
            view->set_position ((1920 / 2) - (view->bounds().width / 2),
                                (1080 / 2) - (view->bounds().height / 2));
        }

        while (true) {
            context.loop (1.0 / 60.0);
            if (! context.running())
                break;
        }
    } catch (...) {
        std::cerr << "[demo] fatal error in main loop\n";
        context.set_exit_code (-1);
    }

    std::clog << "[demo] exiting with code: " << context.exit_code() << std::endl;
    return context.exit_code();
}

} // namespace demo
} // namespace lvtk

#ifdef _WIN32
#    include <windows.h>
int WinMain (HINSTANCE hInstance,
             HINSTANCE hPrevInstance,
             LPSTR lpCmdLine,
             int nShowCmd) {
     (hInstance, hPrevInstance, lpCmdLine, nShowCmd);

    struct ClogBuf : public std::stringbuf {
        ~ClogBuf() { sync(); }
        int sync() {
            ::OutputDebugStringA (str().c_str());
            str (std::string()); // Clear the string buffer
            return 0;
        }
    } dbgbuf;

    auto clogbuf = std::clog.rdbuf (&dbgbuf);

#    if LUI_DEMO_CAIRO
    lvtk::Main context (lvtk::Mode::PROGRAM, std::make_unique<lvtk::Cairo>());
#    elif LUI_DEMO_VULKAN
    lvtk::Main context (lvtk::Mode::PROGRAM, std::make_unique<lvtk::Vulkan>());
#    else
    lvtk::Main context (lvtk::Mode::PROGRAM, std::make_unique<lvtk::OpenGL>());
#    endif

    auto ret = lvtk::demo::run<lvtk::demo::Content> (context);

    std::clog.rdbuf (clogbuf);
    return ret;
}
#else
int main (int argc, char** argv) {
#    if LUI_DEMO_CAIRO
    lvtk::Main context (lvtk::Mode::PROGRAM, std::make_unique<lvtk::Cairo>());
#    elif LUI_DEMO_VULKAN
    lvtk::Main context (lvtk::Mode::PROGRAM, std::make_unique<lvtk::Vulkan>());
#    else
    lvtk::Main context (lvtk::Mode::PROGRAM, std::make_unique<lvtk::OpenGL>());
#    endif
    return lvtk::demo::run<lvtk::demo::Content> (context);
}
#endif
