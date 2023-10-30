#ifndef NIU2X_GFX_INPUT_MANAGER_H
#define NIU2X_GFX_INPUT_MANAGER_H

#include <niu2x/singleton.h>
#include <niu2x/gfx/key_code.h>

namespace niu2x::gfx {

class InputManager : public Singleton<InputManager> {
public:
    InputManager();
};

} // namespace niu2x::gfx

#endif