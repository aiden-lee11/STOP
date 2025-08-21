#pragma once

#ifndef COLORS_H
#define COLORS_H

#include "ftxui/screen/color.hpp"
#include <array>

// TODO borrow some color schemes and make a tui for picking scheme
extern const std::array<ftxui::Color, 11> color_array = {
    ftxui::Color::Red,
    ftxui::Color::DodgerBlue2,
    ftxui::Color::DeepPink1Bis,
    ftxui::Color::Violet,
    ftxui::Color::Green,
    ftxui::Color::Gold1,
    ftxui::Color::RGB(191, 255, 0),
    ftxui::Color::Orange1,
    ftxui::Color::Cyan,
    ftxui::Color::Yellow,
    ftxui::Color::Magenta};

#endif
