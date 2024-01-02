#ifndef NIU2X_COLOR_H
#define NIU2X_COLOR_H

#include <cstdint>
#include <niu2x/disable_windows_warning.h>

namespace niu2x {

/**
 * @brief      RGBA Color, 8 bit per channel
 */
struct Color4B {
    union {
        struct {
            uint8_t r, g, b, a;
        };
        uint32_t rgba8;
    };

    /**
     * @brief      constructor
     *
     * @param[in]  r     red
     * @param[in]  g     green
     * @param[in]  b     blue
     * @param[in]  a     alpha
     */
    Color4B(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    /**
     * @brief      constructor that all bits is set to zero
     */
    Color4B();

#if NIU2X_USE_THREE_WAY_COMPARE
    auto operator<=>(const Color4B& c) const;
#endif

    bool operator==(const Color4B& c) const;

    static const Color4B ALICE_BLUE;
    static const Color4B ANTIQUE_WHITE;
    static const Color4B AQUA;
    static const Color4B AQUAMARINE;
    static const Color4B AZURE;
    static const Color4B BEIGE;
    static const Color4B BISQUE;
    static const Color4B BLACK;
    static const Color4B BLANCHED_ALMOND;
    static const Color4B BLUE;
    static const Color4B BLUE_VIOLET;
    static const Color4B BROWN;
    static const Color4B BURLY_WOOD;
    static const Color4B CADET_BLUE;
    static const Color4B CHARTREUSE;
    static const Color4B CHOCOLATE;
    static const Color4B CORAL;
    static const Color4B CORN_FLOWER_BLUE;
    static const Color4B CORNSILK;
    static const Color4B CRIMSON;
    static const Color4B CYAN;
    static const Color4B DARK_BLUE;
    static const Color4B DARK_CYAN;
    static const Color4B DARK_GOLDEN_ROD;
    static const Color4B DARK_GRAY;
    static const Color4B DARK_GREEN;
    static const Color4B DARK_KHAKI;
    static const Color4B DARK_MAGENTA;
    static const Color4B DARK_OLIVE_GREEN;
    static const Color4B DARK_ORANGE;
    static const Color4B DARK_ORCHID;
    static const Color4B DARK_RED;
    static const Color4B DARK_SALMON;
    static const Color4B DARK_SEA_GREEN;
    static const Color4B DARK_SLATE_BLUE;
    static const Color4B DARK_SLATE_GRAY;
    static const Color4B DARK_TURQUOISE;
    static const Color4B DARK_VIOLET;
    static const Color4B DEEP_PINK;
    static const Color4B DEEP_SKY_BLUE;
    static const Color4B DIM_GRAY;
    static const Color4B DODGER_BLUE;
    static const Color4B FIRE_BRICK;
    static const Color4B FLORAL_WHITE;
    static const Color4B FOREST_GREEN;
    static const Color4B FUCHSIA;
    static const Color4B GAINSBORO;
    static const Color4B GHOST_WHITE;
    static const Color4B GOLD;
    static const Color4B GOLDENROD;
    static const Color4B GRAY;
    static const Color4B GREEN;
    static const Color4B GREEN_YELLOW;
    static const Color4B HONEYDEW;
    static const Color4B HOT_PINK;
    static const Color4B INDIAN_RED;
    static const Color4B INDIGO;
    static const Color4B IVORY;
    static const Color4B KHAKI;
    static const Color4B LAVENDER;
    static const Color4B LAVENDER_BLUSH;
    static const Color4B LAWN_GREEN;
    static const Color4B LEMON_CHIFFON;
    static const Color4B LIGHT_BLUE;
    static const Color4B LIGHT_CORAL;
    static const Color4B LIGHT_CYAN;
    static const Color4B LIGHT_GOLDENROD_YELLOW;
    static const Color4B LIGHT_GRAY;
    static const Color4B LIGHT_GREEN;
    static const Color4B LIGHT_PINK;
    static const Color4B LIGHT_SALMON;
    static const Color4B LIGHT_SEA_GREEN;
    static const Color4B LIGHT_SKY_BLUE;
    static const Color4B LIGHT_SLATE_GRAY;
    static const Color4B LIGHT_STEEL_BLUE;
    static const Color4B LIGHT_YELLOW;
    static const Color4B LIME_ELECTRIC_GREEN;
    static const Color4B LIME_GREEN;
    static const Color4B LINEN;
    static const Color4B MAGENTA;
    static const Color4B MAROON;
    static const Color4B MEDIUM_AQUAMARINE;
    static const Color4B MEDIUM_BLUE;
    static const Color4B MEDIUM_ORCHID;
    static const Color4B MEDIUM_PURPLE;
    static const Color4B MEDIUM_SEA_GREEN;
    static const Color4B MEDIUM_SLATE_BLUE;
    static const Color4B MEDIUM_SPRING_GREEN;
    static const Color4B MEDIUM_TURQUOISE;
    static const Color4B MEDIUM_VIOLET_RED;
    static const Color4B MIDNIGHT_BLUE;
    static const Color4B MINT_CREAM;
    static const Color4B MISTY_ROSE;
    static const Color4B MOCCASIN;
    static const Color4B NAVAJO_WHITE;
    static const Color4B NAVY;
    static const Color4B OLD_LACE;
    static const Color4B OLIVE;
    static const Color4B OLIVE_DRAB;
    static const Color4B ORANGE;
    static const Color4B ORANGE_RED;
    static const Color4B ORCHID;
    static const Color4B PALE_GOLDENROD;
    static const Color4B PALE_GREEN;
    static const Color4B PALE_TURQUOISE;
    static const Color4B PALE_VIOLET_RED;
    static const Color4B PAPAYA_WHIP;
    static const Color4B PEACH_PUFF;
    static const Color4B PERU;
    static const Color4B PINK;
    static const Color4B PLUM;
    static const Color4B POWDER_BLUE;
    static const Color4B PURPLE;
    static const Color4B RED;
    static const Color4B ROSY_BROWN;
    static const Color4B ROYAL_BLUE;
    static const Color4B SADDLE_BROWN;
    static const Color4B SALMON;
    static const Color4B SANDY_BROWN;
    static const Color4B SEA_GREEN;
    static const Color4B SEA_SHELL;
    static const Color4B SIENNA;
    static const Color4B SILVER;
    static const Color4B SKY_BLUE;
    static const Color4B SLATE_BLUE;
    static const Color4B SLATE_GRAY;
    static const Color4B SNOW;
    static const Color4B SPRING_GREEN;
    static const Color4B STEEL_BLUE;
    static const Color4B TAN;
    static const Color4B TEAL;
    static const Color4B THISTLE;
    static const Color4B TOMATO;
    static const Color4B TURQUOISE;
    static const Color4B VIOLET;
    static const Color4B WHEAT;
    static const Color4B WHITE;
    static const Color4B WHITE_SMOKE;
    static const Color4B YELLOW;
    static const Color4B YELLOW_GREEN;
};

struct Color4F {
    float r, g, b, a;
    Color4F();
    Color4F(float channels[4]);
    Color4F(float r, float g, float b, float a);

    static const Color4F ALICE_BLUE;
    static const Color4F ANTIQUE_WHITE;
    static const Color4F AQUA;
    static const Color4F AQUAMARINE;
    static const Color4F AZURE;
    static const Color4F BEIGE;
    static const Color4F BISQUE;
    static const Color4F BLACK;
    static const Color4F BLANCHED_ALMOND;
    static const Color4F BLUE;
    static const Color4F BLUE_VIOLET;
    static const Color4F BROWN;
    static const Color4F BURLY_WOOD;
    static const Color4F CADET_BLUE;
    static const Color4F CHARTREUSE;
    static const Color4F CHOCOLATE;
    static const Color4F CORAL;
    static const Color4F CORN_FLOWER_BLUE;
    static const Color4F CORNSILK;
    static const Color4F CRIMSON;
    static const Color4F CYAN;
    static const Color4F DARK_BLUE;
    static const Color4F DARK_CYAN;
    static const Color4F DARK_GOLDEN_ROD;
    static const Color4F DARK_GRAY;
    static const Color4F DARK_GREEN;
    static const Color4F DARK_KHAKI;
    static const Color4F DARK_MAGENTA;
    static const Color4F DARK_OLIVE_GREEN;
    static const Color4F DARK_ORANGE;
    static const Color4F DARK_ORCHID;
    static const Color4F DARK_RED;
    static const Color4F DARK_SALMON;
    static const Color4F DARK_SEA_GREEN;
    static const Color4F DARK_SLATE_BLUE;
    static const Color4F DARK_SLATE_GRAY;
    static const Color4F DARK_TURQUOISE;
    static const Color4F DARK_VIOLET;
    static const Color4F DEEP_PINK;
    static const Color4F DEEP_SKY_BLUE;
    static const Color4F DIM_GRAY;
    static const Color4F DODGER_BLUE;
    static const Color4F FIRE_BRICK;
    static const Color4F FLORAL_WHITE;
    static const Color4F FOREST_GREEN;
    static const Color4F FUCHSIA;
    static const Color4F GAINSBORO;
    static const Color4F GHOST_WHITE;
    static const Color4F GOLD;
    static const Color4F GOLDENROD;
    static const Color4F GRAY;
    static const Color4F GREEN;
    static const Color4F GREEN_YELLOW;
    static const Color4F HONEYDEW;
    static const Color4F HOT_PINK;
    static const Color4F INDIAN_RED;
    static const Color4F INDIGO;
    static const Color4F IVORY;
    static const Color4F KHAKI;
    static const Color4F LAVENDER;
    static const Color4F LAVENDER_BLUSH;
    static const Color4F LAWN_GREEN;
    static const Color4F LEMON_CHIFFON;
    static const Color4F LIGHT_BLUE;
    static const Color4F LIGHT_CORAL;
    static const Color4F LIGHT_CYAN;
    static const Color4F LIGHT_GOLDENROD_YELLOW;
    static const Color4F LIGHT_GRAY;
    static const Color4F LIGHT_GREEN;
    static const Color4F LIGHT_PINK;
    static const Color4F LIGHT_SALMON;
    static const Color4F LIGHT_SEA_GREEN;
    static const Color4F LIGHT_SKY_BLUE;
    static const Color4F LIGHT_SLATE_GRAY;
    static const Color4F LIGHT_STEEL_BLUE;
    static const Color4F LIGHT_YELLOW;
    static const Color4F LIME_ELECTRIC_GREEN;
    static const Color4F LIME_GREEN;
    static const Color4F LINEN;
    static const Color4F MAGENTA;
    static const Color4F MAROON;
    static const Color4F MEDIUM_AQUAMARINE;
    static const Color4F MEDIUM_BLUE;
    static const Color4F MEDIUM_ORCHID;
    static const Color4F MEDIUM_PURPLE;
    static const Color4F MEDIUM_SEA_GREEN;
    static const Color4F MEDIUM_SLATE_BLUE;
    static const Color4F MEDIUM_SPRING_GREEN;
    static const Color4F MEDIUM_TURQUOISE;
    static const Color4F MEDIUM_VIOLET_RED;
    static const Color4F MIDNIGHT_BLUE;
    static const Color4F MINT_CREAM;
    static const Color4F MISTY_ROSE;
    static const Color4F MOCCASIN;
    static const Color4F NAVAJO_WHITE;
    static const Color4F NAVY;
    static const Color4F OLD_LACE;
    static const Color4F OLIVE;
    static const Color4F OLIVE_DRAB;
    static const Color4F ORANGE;
    static const Color4F ORANGE_RED;
    static const Color4F ORCHID;
    static const Color4F PALE_GOLDENROD;
    static const Color4F PALE_GREEN;
    static const Color4F PALE_TURQUOISE;
    static const Color4F PALE_VIOLET_RED;
    static const Color4F PAPAYA_WHIP;
    static const Color4F PEACH_PUFF;
    static const Color4F PERU;
    static const Color4F PINK;
    static const Color4F PLUM;
    static const Color4F POWDER_BLUE;
    static const Color4F PURPLE;
    static const Color4F RED;
    static const Color4F ROSY_BROWN;
    static const Color4F ROYAL_BLUE;
    static const Color4F SADDLE_BROWN;
    static const Color4F SALMON;
    static const Color4F SANDY_BROWN;
    static const Color4F SEA_GREEN;
    static const Color4F SEA_SHELL;
    static const Color4F SIENNA;
    static const Color4F SILVER;
    static const Color4F SKY_BLUE;
    static const Color4F SLATE_BLUE;
    static const Color4F SLATE_GRAY;
    static const Color4F SNOW;
    static const Color4F SPRING_GREEN;
    static const Color4F STEEL_BLUE;
    static const Color4F TAN;
    static const Color4F TEAL;
    static const Color4F THISTLE;
    static const Color4F TOMATO;
    static const Color4F TURQUOISE;
    static const Color4F VIOLET;
    static const Color4F WHEAT;
    static const Color4F WHITE;
    static const Color4F WHITE_SMOKE;
    static const Color4F YELLOW;
    static const Color4F YELLOW_GREEN;
};

} // namespace niu2x

#endif