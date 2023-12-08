#ifndef NIU2X_ALIAS_H
#define NIU2X_ALIAS_H
#include <niu2x/type.h>
#include <niu2x/preprocess.h>
template <class K, class V>
using HashMap = niu2x::HashMap<K, V>;
using String = niu2x::String;
using Noncopyable = niu2x::Noncopyable;

template <class T>
using Vector = niu2x::Vector<T>;

template <class T>
using UPtr = niu2x::UPtr<T>;

#endif