#include <yoga/Yoga.h>
#include <niu2x/gfx/gui/node.h>

#define yoga() (reinterpret_cast<YGNodeRef>(yoga_))

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

// WIN_EXPORT YGDirection YGNodeLayoutGetDirection(YGNodeRef node);
// WIN_EXPORT bool YGNodeLayoutGetHadOverflow(YGNodeRef node);
// WIN_EXPORT float YGNodeLayoutGetMargin(YGNodeRef node, YGEdge edge);
// WIN_EXPORT float YGNodeLayoutGetBorder(YGNodeRef node, YGEdge edge);
// WIN_EXPORT float YGNodeLayoutGetPadding(YGNodeRef node, YGEdge edge);

} // namespace niu2x::gfx::gui