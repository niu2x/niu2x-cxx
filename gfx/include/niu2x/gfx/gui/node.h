#ifndef NIU2X_GFX_GUI_NODE_H
#define NIU2X_GFX_GUI_NODE_H

#include <niu2x/noncopyable.h>
#include <niu2x/type/std_alias.h>
#include <niu2x/math/geometry.h>
#include <niu2x/gfx/hardward_resource.h>
#include <niu2x/gfx/gui/canvas.h>

namespace niu2x::gfx::gui {

enum class PositionType {
    absolute,
    relative,
};

enum class Align {
    AUTO,
    flex_start,
    flex_end,
    stretch,
    center,
    space_between,
    // space_evenly,
    baseline,
    space_around,
};

enum class FlexDirection {
    row,
    column,
    reverse_row,
    reverse_column,
};

// enum class FlexWrap {
//     no_wrap,
//     wrap,
//     reverse_wrap,
// };

// struct Percentage {
//     Percentage(float v): value(v) {}
//     float value;
// };

// struct Auto {};

struct Edge {
    float left, right, top, bottom;
};

class Node : private Noncopyable {
public:
    Node();
    virtual ~Node();

    void set_width(float v);
    void set_height(float v);

    void set_width_percent(float v);
    void set_height_percent(float v);

    void set_potition_type(PositionType pt);

    void set_flex_direction(FlexDirection direction);

    float layout_width() const;
    float layout_height() const;
    float layout_top() const;
    float layout_bottom() const;
    float layout_left() const;
    float layout_right() const;

    float layout_world_top() const;
    float layout_world_bottom() const;
    float layout_world_left() const;
    float layout_world_right() const;

    Edge layout_margin() const;
    Edge layout_border() const;
    Edge layout_padding() const;

    void set_left(float v);
    void set_right(float v);
    void set_top(float v);
    void set_bottom(float v);

    void set_align_items(Align align);

    void layout(float available_width, float available_height);

    void draw();
    void draw_self();

    void add_child(UniquePtr<Node> child);

    Canvas* canvas() { return &canvas_; }

    virtual void update_canvas();

    Rect compute_self_rect();

private:
    Rect rect_;

    // PositionType position_type_ = PositionType::relative;

    // float top_ = 0;
    // float bottom_ = 0;
    // float right_ = 0;
    // float left_ = 0;

    // Align align_content_ = Align::AUTO;
    // Align align_items_ = Align::AUTO;
    // Align align_self_ = Align::AUTO;
    // Align justify_content_ = Align::flex_start;

    // float aspect_ratio = 0;

    // FlexDirection flex_direction_ = FlexDirection::row;

    // FlexWrap flex_wrap_ = FlexWrap::no_wrap;

    // float flex_grow_ = 0;
    // float flex_shrink_ = 1;

    Vector<UniquePtr<Node>> children_;
    Node* parent_ = nullptr;

    // float padding_top_ = 0;
    // float padding_bottom_ = 0;
    // float padding_right_ = 0;
    // float padding_left_ = 0;

    // float margin_top_ = 0;
    // float margin_bottom_ = 0;
    // float margin_right_ = 0;
    // float margin_left_ = 0;

    // using Length = Variant<float, Percentage, Auto>;

    // float max_width_ = -1;
    // float min_width_ = -1;
    // float max_height_ = -1;
    // float min_height_ = -1;

    // float width_;
    // float height_;
    //
    Canvas canvas_;

    void* yoga_;
    UniquePtr<VertexBuffer> vbo_;
    UniquePtr<IndexBuffer> veo_;
    bool dirtied_flag_ = true;

    static void on_dirtied(void*);
};

static_assert(!type_pred::is_movable<Node>);

} // namespace niu2x::gfx::gui

#endif
