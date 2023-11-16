#include <yoga/Yoga.h>
#include <niu2x/gfx/gui/node.h>
#include <niu2x/unused.h>
// #include <niu2x/gfx/render_command_queue.h>
#include <niu2x/gfx/gfx_factory.h>

#define yoga() (reinterpret_cast<YGNodeRef>(yoga_))
#define other_yoga(ptr) (reinterpret_cast<YGNodeRef>((ptr)->yoga_))

namespace niu2x::gfx::gui {

Node::Node()
{
    vbo_ = GFX_Factory::get()->create_vertex_buffer();
    vbo_->resize(4);

    veo_ = GFX_Factory::get()->create_index_buffer();
    veo_->resize(6);

    uint16_t indexes[] = { 3, 1, 0, 3, 2, 1 };
    veo_->set(0, 6, indexes);

    yoga_ = YGNodeNew();
    if (!yoga_) {
        throw BadAlloc();
    }

    YGNodeSetContext(yoga(), this);
    YGNodeSetDirtiedFunc(yoga(), (YGDirtiedFunc)&Node::on_dirtied);
}

void Node::set_width_auto() { YGNodeStyleSetWidthAuto(yoga()); }
void Node::set_height_auto() { YGNodeStyleSetHeightAuto(yoga()); }

void Node::on_dirtied(void* yoga)
{
    auto node = reinterpret_cast<Node*>(YGNodeGetContext((YGNodeRef)yoga));
    node->dirtied_flag_ = true;
}

Node::~Node() { YGNodeFree(yoga()); }

void Node::set_min_width(float v) { YGNodeStyleSetMinWidth(yoga(), v); }

void Node::set_min_height(float v) { YGNodeStyleSetMinHeight(yoga(), v); }

void Node::set_max_width(float v) { YGNodeStyleSetMaxWidth(yoga(), v); }

void Node::set_max_height(float v) { YGNodeStyleSetMaxHeight(yoga(), v); }

void Node::set_width(float v) { YGNodeStyleSetWidth(yoga(), v); }

void Node::set_height(float v) { YGNodeStyleSetHeight(yoga(), v); }

void Node::set_width_percent(float v) { YGNodeStyleSetWidthPercent(yoga(), v); }

void Node::set_height_percent(float v)
{
    YGNodeStyleSetHeightPercent(yoga(), v);
}

float Node::layout_width() const { return YGNodeLayoutGetWidth(yoga()); }

float Node::layout_height() const { return YGNodeLayoutGetHeight(yoga()); }

float Node::layout_top() const { return YGNodeLayoutGetTop(yoga()); }

float Node::layout_bottom() const { return YGNodeLayoutGetBottom(yoga()); }

void Node::set_min_height_percent(float v)
{
    YGNodeStyleSetMinHeightPercent(yoga(), v);
}
void Node::set_min_width_percent(float v)
{
    YGNodeStyleSetMinWidthPercent(yoga(), v);
}

void Node::set_max_height_percent(float v)
{
    YGNodeStyleSetMaxHeightPercent(yoga(), v);
}
void Node::set_max_width_percent(float v)
{

    YGNodeStyleSetMaxWidthPercent(yoga(), v);
}

float Node::layout_left() const { return YGNodeLayoutGetLeft(yoga()); }

float Node::layout_right() const { return YGNodeLayoutGetRight(yoga()); }

Edge Node::layout_margin() const
{
    return {
        YGNodeLayoutGetMargin(yoga(), YGEdgeLeft),
        YGNodeLayoutGetMargin(yoga(), YGEdgeRight),
        YGNodeLayoutGetMargin(yoga(), YGEdgeTop),
        YGNodeLayoutGetMargin(yoga(), YGEdgeBottom),
    };
}
Edge Node::layout_border() const
{
    return {
        YGNodeLayoutGetBorder(yoga(), YGEdgeLeft),
        YGNodeLayoutGetBorder(yoga(), YGEdgeRight),
        YGNodeLayoutGetBorder(yoga(), YGEdgeTop),
        YGNodeLayoutGetBorder(yoga(), YGEdgeBottom),
    };
}
Edge Node::layout_padding() const
{
    return {
        YGNodeLayoutGetPadding(yoga(), YGEdgeLeft),
        YGNodeLayoutGetPadding(yoga(), YGEdgeRight),
        YGNodeLayoutGetPadding(yoga(), YGEdgeTop),
        YGNodeLayoutGetPadding(yoga(), YGEdgeBottom),
    };
}

void Node::update_canvas()
{

    // printf("update_canvas\n");
}

float Node::layout_world_top() const
{
    return layout_top() + (parent_ ? parent_->layout_top() : 0.0f);
}

float Node::layout_world_bottom() const
{
    return layout_bottom() + (parent_ ? parent_->layout_bottom() : 0.0f);
}

float Node::layout_world_left() const
{
    return layout_left() + (parent_ ? parent_->layout_left() : 0.0f);
}

float Node::layout_world_right() const
{
    return layout_right() + (parent_ ? parent_->layout_right() : 0.0f);
}

Rect Node::compute_self_rect()
{
    auto left = layout_world_left();
    auto top = layout_world_top();
    auto width = layout_width();
    auto height = layout_height();

    return { left, top, width, height };
}

void Node::set_position_type(PositionType pt)
{
    YGNodeStyleSetPositionType(yoga(),
        pt == PositionType::relative ? YGPositionTypeRelative
                                     : YGPositionTypeAbsolute);
}

void Node::add_child(UniquePtr<Node> child)
{
    YGNodeInsertChild(yoga(), other_yoga(child), children_.size());
    child->parent_ = this;
    children_.push_back(move(child));
}

static YGAlign align_convert[] = {
    YGAlignAuto,   YGAlignFlexStart,    YGAlignFlexEnd,  YGAlignStretch,
    YGAlignCenter, YGAlignSpaceBetween, YGAlignBaseline, YGAlignSpaceAround,
};

void Node::set_align_items(Align align)
{
    YGNodeStyleSetAlignItems(yoga(), align_convert[(int)align]);
}

void Node::set_justify_content(Justify j)
{
    static YGJustify convert[]
        = { YGJustifyFlexStart,    YGJustifyCenter,      YGJustifyFlexEnd,
            YGJustifySpaceBetween, YGJustifySpaceAround, YGJustifySpaceEvenly };

    YGNodeStyleSetJustifyContent(yoga(), convert[(int)j]);
}

void Node::set_align_self(Align align)
{

    YGNodeStyleSetAlignSelf(yoga(), align_convert[(int)align]);
}

void Node::draw()
{
    draw_self();
    for (auto& child : children_)
        child->draw();
}

void Node::draw_self()
{
    if (dirtied_flag_) {
        update_canvas();
        dirtied_flag_ = false;
    }
    canvas_.draw();
}

void Node::set_flex_direction(FlexDirection direction)
{
    switch (direction) {
        case FlexDirection::row: {
            YGNodeStyleSetFlexDirection(yoga(), YGFlexDirectionRow);
            break;
        }
        case FlexDirection::column: {
            YGNodeStyleSetFlexDirection(yoga(), YGFlexDirectionColumn);
            break;
        }

        case FlexDirection::reverse_row: {
            YGNodeStyleSetFlexDirection(yoga(), YGFlexDirectionRowReverse);
            break;
        }
        case FlexDirection::reverse_column: {
            YGNodeStyleSetFlexDirection(yoga(), YGFlexDirectionColumnReverse);
            break;
        }
    }
}

void Node::layout(float w, float h)
{
    // YGNodeMarkDirty(yoga());
    // set_width(w);
    // set_height(h);
    set_dirty_and_propagate_to_children();
    YGNodeCalculateLayout(yoga(), w, h, YGDirectionLTR);
}

void Node::set_dirty() { dirtied_flag_ = true; }

void Node::set_dirty_and_propagate_to_children()
{
    dirtied_flag_ = true;
    for (auto& child : children_)
        child->set_dirty_and_propagate_to_children();
}

void Node::set_left(float v) { YGNodeStyleSetPosition(yoga(), YGEdgeLeft, v); }

void Node::set_right(float v)
{
    YGNodeStyleSetPosition(yoga(), YGEdgeRight, v);
}

void Node::set_top(float v) { YGNodeStyleSetPosition(yoga(), YGEdgeTop, v); }

void Node::set_bottom(float v)
{
    YGNodeStyleSetPosition(yoga(), YGEdgeBottom, v);
}

void Node::set_left_percent(float v)
{
    YGNodeStyleSetPositionPercent(yoga(), YGEdgeLeft, v);
}
void Node::set_right_percent(float v)
{
    YGNodeStyleSetPositionPercent(yoga(), YGEdgeRight, v);
}
void Node::set_top_percent(float v)
{
    YGNodeStyleSetPositionPercent(yoga(), YGEdgeTop, v);
}

void Node::set_bottom_percent(float v)
{
    YGNodeStyleSetPositionPercent(yoga(), YGEdgeBottom, v);
}

// WIN_EXPORT YGDirection YGNodeLayoutGetDirection(YGNodeRef node);
// WIN_EXPORT bool YGNodeLayoutGetHadOverflow(YGNodeRef node);
// WIN_EXPORT float YGNodeLayoutGetMargin(YGNodeRef node, YGEdge edge);
// WIN_EXPORT float YGNodeLayoutGetBorder(YGNodeRef node, YGEdge edge);
// WIN_EXPORT float YGNodeLayoutGetPadding(YGNodeRef node, YGEdge edge);

} // namespace niu2x::gfx::gui