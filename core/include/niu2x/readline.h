#ifndef NIU2X_READLINE_H
#define NIU2X_READLINE_H

#include <niu2x/api.h>

namespace niu2x {
/**
 * @brief      readline
 *
 * @param[in]  prompt  The prompt
 * @param      buf     The buffer
 * @param[in]  size    The size
 *
 * @return     { description_of_the_return_value }
 */
char* readline(const char* prompt, char* buf, int size);

} // namespace niu2x

#endif