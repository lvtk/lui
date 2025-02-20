// Copyright 2022 Michael Fisher <mfisher@lvtk.org>
// SPDX-License-Identifier: ISC

#pragma once

#include <lui/graphics.hpp>
#include <lui/slider.hpp>
#include <lui/style.hpp>

namespace lui {
namespace detail {

class DefaultStyle : public Style {
public:
    DefaultStyle() {
        // orange
        set_color (ColorID::FOREGROUND, Color (0xFF, 0xA4, 0x00, 255));
        const auto fg = find_color (ColorID::FOREGROUND);

        set_color (ColorID::BUTTON_BASE, Color (0xff464646));
        set_color (ColorID::BUTTON_ON, fg.with_alpha (0.5f).darker (0.1f));
        set_color (ColorID::BUTTON_TEXT_OFF, Color (0xffeeeeee));
        set_color (ColorID::BUTTON_TEXT_ON, Color (0xffdddddd));

        set_color (ColorID::SLIDER_BASE, Color (0xff141414));
        set_color (ColorID::SLIDER_TRACK, Color (0xff090909));
        set_color (ColorID::SLIDER_THUMB, fg.darker (0.52f));

        set_color (ColorID::VIEW_BACKGROUND, Color (0xff000000));
    }

    ~DefaultStyle() {}

    void draw_button_shape (Graphics& g, lui::Button& w, bool highlight, bool down) override {
        auto bc = w.toggled() ? find_color (ColorID::BUTTON_ON) : find_color (ColorID::BUTTON_BASE);
        if (! w.toggled() && (highlight || down)) {
            if (! down)
                bc = bc.brighter (-0.015f);
            else
                bc = bc.brighter (-0.035f);
        }

        auto line_width = 1.2;
        auto r          = w.bounds().at (0).reduced (1);
        auto cs         = 4.f;

        g.set_color (bc);
        g.fill_rounded_rect (r, cs);

        g.set_color (w.toggled()
                         ? Color (0xFF, 0xA4, 0x00, 255).with_alpha (.70f)
                         : bc.darker (0.07f));
        g.context().set_line_width (line_width);
        g.draw_rounded_rect (r, cs);
    }

    void draw_button_text (Graphics& g, lui::TextButton& w, bool highlight, bool down) override {
        auto c = find_color (w.toggled() ? ColorID::BUTTON_TEXT_ON : ColorID::BUTTON_TEXT_OFF);
        if (! w.toggled() && (highlight || down))
            c = c.brighter (0.05f);
        else if (w.toggled()) {
            c = Color (0xff090909);
        }

        g.set_color (c);
        g.set_font (std::min (13.f, w.height() * 0.55f));
        auto r = w.bounds().at (0).as<float>();
        g.draw_text (w.text(), r, Justify::CENTERED);
    }

    void draw_slider (Graphics& g, lui::Slider& slider, Bounds bounds, float pos) override {
        auto r = bounds.as<float>();

        switch (slider.type()) {
            case lui::Slider::HORIZONTAL_BAR:
            case lui::Slider::VERTICAL_BAR: {
                g.set_color (find_color (ColorID::SLIDER_BASE));
                g.fill_rect (r);

                if (slider.vertical()) {
                    r.slice_top (pos);
                } else {
                    r = r.slice_left (pos);
                }

                g.set_color (find_color (ColorID::SLIDER_THUMB));
                g.fill_rect (r);
                break;
            }

            case lui::Slider::HORIZONTAL:
            case lui::Slider::VERTICAL: {
                g.save();
                draw_slider_background (g, slider, bounds, pos);
                g.restore();
                draw_slider_thumb (g, slider, bounds, pos);
                break;
            }
        }
    }

    void draw_slider_background (Graphics& g, lui::Slider& slider, Bounds bounds, float pos) override {
        (void) pos;

        int track_size = 4;

        if (slider.vertical()) {
            bounds.reduce ((slider.width() - track_size) / 2, 0);
        } else {
            bounds.reduce (0, (slider.height() - track_size) / 2);
        }

        g.set_color (find_color (ColorID::SLIDER_TRACK));
        g.fill_rect (bounds);
    }

    void draw_slider_thumb (Graphics& g, lui::Slider& slider, Bounds bounds, float pos) override {
        float thumb_size  = 16.f;
        float corner_size = 6.f;
        float x = 0.f, y = 0.f;

        Range<float> pixel_range (0.f, (float) (slider.vertical() ? bounds.height : bounds.width));
        float max_pixel = (float) (slider.vertical() ? bounds.height : bounds.width) - thumb_size;
        Range<float> thumb_range (4.f, max_pixel);
        pos = thumb_range.convert (pixel_range, pos);

        if (slider.vertical()) {
            x = ((float) slider.width() / 2.f) - (thumb_size / 2.f);
            y = pos;
        } else {
            x = pos;
            y = ((float) slider.height() / 2.f) - (thumb_size / 2.f);
        }

        g.set_color (find_color (ColorID::SLIDER_THUMB));
        g.fill_rounded_rect (x, y, thumb_size, thumb_size, corner_size);
    }
};

} // namespace detail
} // namespace lui
