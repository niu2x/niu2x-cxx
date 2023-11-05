#include <yoga/Yoga.h>
#include <niu2x/gfx/gui/node.h>
#include <niu2x/unused.h>
#include <niu2x/gfx/resource_manager.h>
#include <niu2x/gfx/render_command_queue.h>
#include <niu2x/gfx/hardward_resource.h>

#define yoga() (reinterpret_cast<YGNodeRef>(yoga_))
#define other_yoga(ptr) (reinterpret_cast<YGNodeRef>((ptr)->yoga_))

namespace niu2x::gfx::gui {

Node::Node()
{
    yoga_ = YGNodeNew();
    if (!yoga_) {
        throw BadAlloc();
    }
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

void Node::set_potition_type(PositionType pt)
{
    YGNodeStyleSetPositionType(yoga(),
        pt == PositionType::relative ? YGPositionTypeRelative
                                     : YGPositionTypeAbsolute);
}

// static void Edge_show(const Edge& self, const char* prefix)
// {
//     printf("%s\n", prefix);
//     printf("left: %f\n", self.left);
//     printf("right: %f\n", self.right);
//     printf("top: %f\n", self.top);
//     printf("bottom: %f\n", self.bottom);
// }

void Node::add_child(UniquePtr<Node> child)
{
    // printf("other_yoga(child) %p\n", other_yoga(child));
    // printf(  "yoga() %p\n", yoga());

    YGNodeInsertChild(yoga(), other_yoga(child), children_.size());
    children_.push_back(move(child));
}

void Node::draw() const
{
    draw_self();

    for (auto& child : children_)
        child->draw();
}

void Node::draw_self() const
{
    // if (children_.size() <= 0) {

    //     printf("layout_width: %f\n", layout_width());
    //     printf("layout_height: %f\n", layout_height());

    //     printf("layout_left: %f\n", layout_left());
    //     printf("layout_right: %f\n", layout_right());

    //     printf("layout_top: %f\n", layout_top());
    //     printf("layout_bottom: %f\n", layout_bottom());

    //     Edge_show(layout_margin(), "margin");
    //     Edge_show(layout_padding(), "padding");
    //     Edge_show(layout_border(), "border");
    // }

    auto rf = RenderCommandFactory::get();
    auto queue = RenderCommandQueue::get();
    auto cmd = rf->create_rect(
        { layout_left(), layout_top(), layout_width(), layout_height() },
        { 1, 1, 1, 1 });
    queue->enqueue(cmd);
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