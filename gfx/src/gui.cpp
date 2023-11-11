#include <niu2x/gfx/gui.h>
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

static void set_properties(Node* node, lua::LuaEngine* lua)
{
    auto width = lua->read_field("width");
    // std::cout << "width: " << width << std::endl;
    visit(
        [node](auto&& x) {
            if constexpr (type_pred::is_same_decay<decltype(x), String>) {
                std::cout << "string" << x << std::endl;
            }

            if constexpr (type_pred::is_same_decay<decltype(x), double>) {
                std::cout << "double" << x << std::endl;
            }
        },
        width);
    unused(node);
}

static UniquePtr<Node> create_node()
{
    auto node = make_unique<Node>();
    return node;
}
static UniquePtr<Node> create_panel()
{
    auto node = make_unique<Panel>();
    return node;
}

using NodeCreator = UniquePtr<Node> (*)();

static HashMap<String, NodeCreator> node_creators {
    { "Node", create_node },
    { "Panel", create_panel },
};

UniquePtr<Node> build_ui(lua::LuaEngine* lua)
{
    auto type = get<String>(lua->read_field("type"));
    auto node = node_creators[type]();

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
    set_properties(node.get(), lua);
    return node;
}

} // namespace niu2x::gfx::gui