#ifndef NIU2X_PREPROCESS_CAT_H
#define NIU2X_PREPROCESS_CAT_H

/**
 * @brief       concat two things
 * @param       a     one thing
 * @param       b     another thing
 * @return      ab
 */
#define NIU2X_PP_CAT(a, b)   NIU2X_PP_CAT_I(a, b)
#define NIU2X_PP_CAT_I(a, b) a##b

#endif