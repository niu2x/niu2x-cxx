#ifndef NIU2X_JSON_H
#define NIU2X_JSON_H

namespace niu2x {

class JSON {
public:
    bool is_number();
    bool is_boolean();
    bool is_string();
    bool is_object();
    bool is_array();

private:
};

} // namespace niu2x

#endif