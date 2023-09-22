#include "learning_0_1.h"

namespace niu2x::painter {

void Learning_0_1::paint(Image* image)
{
    auto size = image->size();
    for (int row = 0; row < size.height; row++) {
        for (int col = 0; col < size.width; col++) {
            image->set_pixel(row, col,
                Color(((float)row) / size.height * 255,
                    ((float)col) / size.width * 255, 0, 255));
        }
    }
}

} // namespace niu2x::painter