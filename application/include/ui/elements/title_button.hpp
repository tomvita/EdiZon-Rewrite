/**
 * Copyright (C) 2019 WerWolv
 * 
 * This file is part of EdiZon.
 * 
 * EdiZon is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * EdiZon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with EdiZon.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <borealis.hpp>

#include <string>
#include <vector>
#include <save/title.hpp>

namespace edz::ui::element {

    class TitleButton : public brls::View {
    public:
        TitleButton(unsigned char *buffer, size_t bufferSize, u8 column);
        ~TitleButton();

        void draw(NVGcontext *vg, int x, int y, unsigned width, unsigned height, brls::Style *style, brls::FrameContext *ctx) override;
        void layout(NVGcontext* vg, brls::Style *style, brls::FontStash *stash) override;
        brls::View* requestFocus(brls::FocusDirection direction, View *oldFocus, bool fromUp = false) override;
        bool onClick() override;

        void setClickListener(brls::EventListener listener);

        u8 getColumn();
    private:
        brls::Image *m_image;
        u8 m_column;

        brls::EventListener m_clickListener = nullptr;
    };

    class HorizontalTitleList : public brls::BoxLayout {
        public:
            HorizontalTitleList();
            ~HorizontalTitleList();

            std::vector<brls::BoxLayoutChild*> getChildren();
            void addTitle(save::Title *title);
            brls::View* defaultFocus(brls::View *oldFocus);
            
    };

}
