#ifndef NIU2X_LUA_LUA_ENGINE_H
#define NIU2X_LUA_LUA_ENGINE_H

#include <niu2x/api.h>
#include <niu2x/noncopyable.h>
#include <niu2x/fs.h>

namespace niu2x::lua {

struct NIL {
};
using LuaValue = Variant<String, double, NIL>;

class NXAPI LuaEngine : Noncopyable {
public:
    LuaEngine();
    ~LuaEngine();
    int main(int argc, char* argv[]);
    bool execute_file(const fs::Path& path);
    // void fetch_config();

    // high-level api

    /**
     * @brief      Reads a field of table at stack top
     *
     * @param[in]  field  The field name
     *
     * @return     The file value.
     */
    LuaValue read_field(const String& field);

    // low-level lua api

    /**
     * @brief      place _G[field] at stack top. [top += 1]
     *
     * @param[in]  field  The field name
     */
    void get_global(const String& field);

    /**
     * @brief      set _G[field] to stack top's value. [top -= 1]
     *
     * @param[in]  field  The field
     */
    void set_global(const String& field);

    /**
     * @brief      place stack_top_table[field] at stack top. [top += 1]
     *
     * @param[in]  field  The field
     */
    void get_field(const String& field);

    /**
     * @brief      place stack_stop_table[index] at stack top. [top += 1]
     *
     * @param[in]  i     the index
     */
    void get_field(Index i);

    /**
     * @brief      pop n value from stack. [top -= n]
     *
     * @param[in]  n   count of poped value
     */
    void pop(NR n);

    /**
     * @brief      convert stack top value to string
     *
     * @return     String value of the stack top value.
     */
    String to_string();

    /**
     * @brief      convert stack top value to number
     *
     * @return     Number value of the stack top value.
     */
    double to_number();

    /**
     * @brief      Determines if stack top is nil
     *
     * @return     True if nil, False otherwise.
     */
    bool is_nil();

    /**
     * @brief      Determines if stack top is string.
     *
     * @return     True if string, False otherwise.
     */
    bool is_string();

    /**
     * @brief      Determines if stack top is number.
     *
     * @return     True if number, False otherwise.
     */
    bool is_number();

    /**
     * @brief      get length of stack top value.
     *
     * @return     the length of stack top value.
     */
    NR len();

private:
    void* L_;
};

} // namespace niu2x::lua

#endif