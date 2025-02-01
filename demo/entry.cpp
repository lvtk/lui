// Copyright 2019 Michael Fisher <mfisher@lvtk.org>
// SPDX-License-Identifier: ISC

#include <lui/entry.hpp>
#include <lui/slider.hpp>
#include <lui/widget.hpp>

#include "demo.hpp"
#include "utils.hpp"

namespace lui {
namespace demo {

class EntryDemo : public DemoWidget {
public:
    EntryDemo() {
        add (entry);
        show_all();
        set_size (640, 360);
    }

    ~EntryDemo() {}

private:
    void update_text (Slider& slider) {
    }

    void resized() override {
        entry.set_bounds (10, 10, 120, 30);
    }

private:
    Entry entry;
};

std::unique_ptr<Widget> create_entry_demo() {
    return std::make_unique<EntryDemo>();
}

} // namespace demo
} // namespace lui
