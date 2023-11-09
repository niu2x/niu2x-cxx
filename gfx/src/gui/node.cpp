#include <yoga/Yoga.h>
#include <niu2x/gfx/gui/node.h>
#include <niu2x/unused.h>
#include <niu2x/gfx/resource_manager.h>
#include <niu2x/gfx/render_command_queue.h>
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

void Node::on_dirtied(void* yoga)
{
    auto node = reinterpret_cast<Node*>(YGNodeGetContext((YGNodeRef)yoga));
    node->dirtied_flag_ = true;
}

Node::~Node() { YGNodeFree(yoga()); }

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
    canvas_.clear();
    canvas_.add_image(
        ResourceManager::get()->get_image_sheet_frame(
            "ui-pack", "blue_panel.png"),
        {
            layout_left(),
            layout_top(),
            layout_width(),
            layout_height(),
        });
}

void Node::set_potition_type(PositionType pt)
{
    YGNodeStyleSetPositionType(yoga(),
        pt == PositionType::relative ? YGPositionTypeRelative
                                     : YGPositionTypeAbsolute);
}

void Node::add_child(UniquePtr<Node> child)
{
    YGNodeInsertChild(yoga(), other_yoga(child), children_.size());
    children_.push_back(move(child));
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
    YGNodeCalculateLayout(yoga(), w, h, YGDirectionLTR);
}

// WIN_EXPORT YGDirection YGNodeLayoutGetDirection(YGNodeRef node);
// WIN_EXPORT bool YGNodeLayoutGetHadOverflow(YGNodeRef node);
// WIN_EXPORT float YGNodeLayoutGetMargin(YGNodeRef node, YGEdge edge);
// WIN_EXPORT float YGNodeLayoutGetBorder(YGNodeRef node, YGEdge edge);
// WIN_EXPORT float YGNodeLayoutGetPadding(YGNodeRef node, YGEdge edge);

} // namespace niu2x::gfx::gui