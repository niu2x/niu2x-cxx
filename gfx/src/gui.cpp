#include <niu2x/gfx/gui.h>
#include <niu2x/string_utils.h>
#include <niu2x/gfx/resource_manager.h>
#include <iostream>

namespace niu2x::gfx::gui {

Mat4 ui_view_mat4;
Mat4 ui_projection_mat4;

void update_view_projection(IntSize window_size)
{
    float half_width = window_size.width * 0.5;
    float half_height = window_size.height * 0.5;

    auto eye = Vec3(half_width, -half_height, 10);
    auto target = Vec3(half_width, -half_height, 0);

    ui_view_mat4 = math::lookat_matrix(eye, target, Vec3(0, 1, 0));

    ui_projection_mat4 = math::frustum_matrix(
        -half_width, half_width, -half_height, half_height, -100.0f, 100.0f);
}

using SetNumber = void (Node::*)(float);
using SetAuto = void (Node::*)();

static void set_num_or_percent(
    Node* node, const lua::LuaValue& value, SetNumber set_number,
    SetNumber set_percent, SetAuto set_auto)
{
    visit(
        [node, set_number, set_percent, set_auto](auto&& v) {
            if constexpr (type_pred::is_same_decay<decltype(v), double>) {
                (node->*set_number)(v);
            }
            if constexpr (type_pred::is_same_decay<decltype(v), String>) {
                if (v == "auto") {
                    (node->*set_auto)();
                } else if (v.size() > 0 && v.back() == '%') {
                    float w;
                    sscanf(v.c_str(), "%f%%", &w);
                    (node->*set_percent)(w);
                } else {
                    float w;
                    sscanf(v.c_str(), "%f", &w);
                    (node->*set_number)(w);
                }
            }
        },
        value);
}

static void set_width(Node* node, const lua::LuaValue& value)
{
    set_num_or_percent(
        node,
        value,
        &Node::set_width,
        &Node::set_width_percent,
        &Node::set_width_auto);
}

static void set_min_width(Node* node, const lua::LuaValue& value)
{
    set_num_or_percent(
        node,
        value,
        &Node::set_min_width,
        &Node::set_min_width_percent,
        nullptr);
}

static void set_min_height(Node* node, const lua::LuaValue& value)
{
    set_num_or_percent(
        node,
        value,
        &Node::set_min_height,
        &Node::set_min_height_percent,
        nullptr);
}

static void set_max_width(Node* node, const lua::LuaValue& value)
{
    set_num_or_percent(
        node,
        value,
        &Node::set_max_width,
        &Node::set_max_width_percent,
        nullptr);
}

static void set_max_height(Node* node, const lua::LuaValue& value)
{
    set_num_or_percent(
        node,
        value,
        &Node::set_max_height,
        &Node::set_max_height_percent,
        nullptr);
}

static void set_height(Node* node, const lua::LuaValue& value)
{
    set_num_or_percent(
        node,
        value,
        &Node::set_height,
        &Node::set_height_percent,
        &Node::set_height_auto);
}

static void set_left(Node* node, const lua::LuaValue& value)
{
    set_num_or_percent(
        node,
        value,
        &Node::set_left,
        &Node::set_left_percent,
        nullptr);
}

static void set_right(Node* node, const lua::LuaValue& value)
{
    set_num_or_percent(
        node,
        value,
        &Node::set_right,
        &Node::set_right_percent,
        nullptr);
}

static void set_top(Node* node, const lua::LuaValue& value)
{
    set_num_or_percent(
        node,
        value,
        &Node::set_top,
        &Node::set_top_percent,
        nullptr);
}

static void set_bottom(Node* node, const lua::LuaValue& value)
{
    set_num_or_percent(
        node,
        value,
        &Node::set_bottom,
        &Node::set_bottom_percent,
        nullptr);
}

static void set_position_type(Node* node, const lua::LuaValue& value)
{
    visit(
        [node](auto&& v) {
            if constexpr (type_pred::is_same_decay<decltype(v), String>) {
                if (v == "absolute")
                    node->set_position_type(PositionType::absolute);
                else if (v == "relative")
                    node->set_position_type(PositionType::relative);
            }
        },
        value);
}

static void set_flex_direction(Node* node, const lua::LuaValue& value)
{
    static HashMap<String, FlexDirection> flex_direction_map {
        {
            "row",
            FlexDirection::row,
        },
        {
            "column",
            FlexDirection::column,
        },
        {
            "reverse_row",
            FlexDirection::reverse_row,
        },
        {
            "reverse_column",
            FlexDirection::reverse_column,
        },
    };
    visit(
        [node](auto&& v) {
            if constexpr (type_pred::is_same_decay<decltype(v), String>) {
                auto it = flex_direction_map.find(v);
                if (it != flex_direction_map.end()) {
                    node->set_flex_direction(it->second);
                }
            }
        },
        value);
}

using SetAlign = void (Node::*)(Align);

static void set_align(Node* node, const lua::LuaValue& value, SetAlign setter)
{
    static HashMap<String, Align> align_map {
        {
            "auto",
            Align::AUTO,
        },
        {
            "flex_start",
            Align::flex_start,
        },
        {
            "flex_end",
            Align::flex_end,
        },
        {
            "stretch",
            Align::stretch,
        },
        {
            "center",
            Align::center,
        },

        {
            "space_between",
            Align::space_between,
        },

        {
            "space_around",
            Align::space_around,
        },
        {
            "baseline",
            Align::baseline,
        },
    };
    visit(
        [node, setter](auto&& v) {
            if constexpr (type_pred::is_same_decay<decltype(v), String>) {
                auto it = align_map.find(v);
                if (it != align_map.end()) {
                    (node->*setter)(it->second);
                }
            }
        },
        value);
}

static void set_align_items(Node* node, const lua::LuaValue& value)
{
    set_align(node, value, &Node::set_align_items);
}

static void set_align_self(Node* node, const lua::LuaValue& value)
{
    set_align(node, value, &Node::set_align_self);
}

static void set_justify_content(Node* node, const lua::LuaValue& value)
{
    static HashMap<String, Justify> justify_map {
        {
            "flex_start",
            Justify::flex_start,
        },
        {
            "flex_end",
            Justify::flex_end,
        },
        {
            "center",
            Justify::center,
        },

        {
            "space_between",
            Justify::space_between,
        },

        {
            "space_around",
            Justify::space_around,
        },
        {
            "space_evenly",
            Justify::space_evenly,
        },
    };
    visit(
        [node](auto&& v) {
            if constexpr (type_pred::is_same_decay<decltype(v), String>) {
                auto it = justify_map.find(v);
                if (it != justify_map.end()) {
                    node->set_justify_content(it->second);
                }
            }
        },
        value);
}

static void set_node_properties(Node* node, lua::LuaEngine* lua)
{
    set_width(node, lua->read_field("width"));
    set_height(node, lua->read_field("height"));

    set_min_width(node, lua->read_field("min_width"));
    set_min_height(node, lua->read_field("min_height"));

    set_max_width(node, lua->read_field("max_width"));
    set_max_height(node, lua->read_field("max_height"));

    set_left(node, lua->read_field("left"));
    set_right(node, lua->read_field("right"));
    set_bottom(node, lua->read_field("bottom"));
    set_top(node, lua->read_field("top"));

    set_position_type(node, lua->read_field("position_type"));
    set_flex_direction(node, lua->read_field("flex_direction"));
    set_align_items(node, lua->read_field("align_items"));
    set_align_self(node, lua->read_field("align_self"));
    set_justify_content(node, lua->read_field("justify_content"));

    // set_right(node, lua->read_field("right"));
    // set_top(node, lua->read_field("top"));
    // set_bottom(node, lua->read_field("bottom"));
    //
    //

    lua->get_field("children");
    if (!lua->is_nil()) {
        auto children_count = lua->len();
        for (Index i = 0; i < children_count; i++) {
            lua->get_field(i + 1);
            auto child = build_ui(lua);
            node->add_child(move(child));
            lua->pop(1);
        }
    }
    lua->pop(1);
}

void set_panel_background(Panel* panel, const lua::LuaValue& value)
{
    visit(
        [panel](auto&& v) {
            if constexpr (type_pred::is_same_decay<decltype(v), String>) {
                auto bg_fields = string_utils::split(v, ',');
                panel->set_background(bg_fields[0], bg_fields[1]);
            }
        },
        value);
}

static void set_panel_properties(Panel* panel, lua::LuaEngine* lua)
{
    set_panel_background(panel, lua->read_field("background"));
    set_node_properties(panel, lua);
}

template <class T>
static void set_font(const lua::LuaValue& value, T&& setter)
{
    visit(
        [&setter](auto&& v) {
            if constexpr (type_pred::is_same_decay<decltype(v), String>) {
                auto font = ResourceManager::get()->get_font(v);
                setter(font);
            }
        },
        value);
}

template <class T>
static void set_string(const lua::LuaValue& value, T&& setter)
{
    visit(
        [&setter](auto&& v) {
            if constexpr (type_pred::is_same_decay<decltype(v), String>) {
                setter((v));
            }
        },
        value);
}

static void set_text_properties(Text* text, lua::LuaEngine* lua)
{
    set_font(lua->read_field("font"), [text](Font* font) {
        text->set_font(font);
    });
    set_string(lua->read_field("text"), [text](auto&& sz) {
        text->set_text(sz);
    });
    set_node_properties(text, lua);
}

static UniquePtr<Node> create_node(lua::LuaEngine* lua)
{
    auto node = make_unique<Node>();
    set_node_properties(node.get(), lua);
    return node;
}

static UniquePtr<Node> create_panel(lua::LuaEngine* lua)
{
    auto panel = make_unique<Panel>();
    set_panel_properties(panel.get(), lua);
    return panel;
}

static UniquePtr<Node> create_text(lua::LuaEngine* lua)
{
    auto text = make_unique<Text>();
    set_text_properties(text.get(), lua);
    return text;
}

using NodeCreator = UniquePtr<Node> (*)(lua::LuaEngine*);

static HashMap<String, NodeCreator> node_creators {
    { "Node", create_node },
    { "Panel", create_panel },
    { "Text", create_text },
};

UniquePtr<Node> build_ui(lua::LuaEngine* lua)
{
    auto type = get<String>(lua->read_field("type"));
    auto node = node_creators.at(type)(lua);
    return node;
}

} // namespace niu2x::gfx::gui