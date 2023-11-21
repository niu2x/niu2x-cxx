#ifndef NIU2X_GFX_GUI_NODE_H
#define NIU2X_GFX_GUI_NODE_H

#include <niu2x/noncopyable.h>
#include <niu2x/unused.h>
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
    baseline,
    space_around,
};

enum class Justify {
    flex_start,
    center,
    flex_end,
    space_between,
    space_around,
    space_evenly,

};

enum class FlexDirection {
    row,
    column,
    reverse_row,
    reverse_column,
};

enum class FlexWrap {
    wrap,
    no_wrap,
    reverse_wrap,
};

struct Edge {
    float left, right, top, bottom;
};

class Node : private Noncopyable {
public:
    Node();
    virtual ~Node();

    void set_width(float v);
    void set_height(float v);

    void set_min_width(float v);
    void set_min_height(float v);
    void set_min_height_percent(float v);
    void set_min_width_percent(float v);

    void set_max_height_percent(float v);
    void set_max_width_percent(float v);

    void set_max_width(float v);
    void set_max_height(float v);

    void set_width_auto();
    void set_height_auto();

    void set_width_percent(float v);
    void set_height_percent(float v);

    void set_position_type(PositionType pt);

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

    void set_margin_left(float v);
    void set_margin_right(float v);
    void set_margin_top(float v);
    void set_margin_bottom(float v);

    void set_margin_left_auto();
    void set_margin_right_auto();
    void set_margin_top_auto();
    void set_margin_bottom_auto();

    void set_margin_left_percent(float v);
    void set_margin_right_percent(float v);
    void set_margin_top_percent(float v);
    void set_margin_bottom_percent(float v);

    void set_margin(float v);
    void set_margin_auto();
    void set_margin_percent(float v);

    void set_left_percent(float v);
    void set_right_percent(float v);
    void set_top_percent(float v);
    void set_bottom_percent(float v);

    void set_align_items(Align align);
    void set_align_self(Align align);
    void set_justify_content(Justify align);

    void set_flex_wrap(FlexWrap);

    void layout(float available_width, float available_height);

    void draw();
    void draw_self();
    void set_visible(bool v);

    void add_child(UniquePtr<Node> child);

    Canvas* canvas() { return &canvas_; }

    virtual void update_canvas();

    Rect compute_self_rect();
    void set_dirty_and_propagate_to_children();
    void set_dirty();

    struct SizeRange {
        math::Size<float> min;
        math::Size<float> max;
    };

    virtual math::Size<float> measure(const SizeRange& size_range)
    {
        unused(size_range);
        return { 0, 0 };
    }
    // void set_measure()
    void set_measure();
    void set_no_measure();

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
    bool visible_ = true;

    static void on_dirtied(void*);
};

static_assert(!type_pred::is_movable<Node>);

} // namespace niu2x::gfx::gui

#endif
