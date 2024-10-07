//
// Created by Admin on 15/8/2024.
//
// pair.cpp

#include "Pair.h"

template<class T1, class T2>
Pair<T1, T2>::Pair(T1 k, T2 v) : key(k), value(v)
{}

template<class T1, class T2>
bool Pair<T1, T2>::operator < (const Pair<T1, T2>& p) const
{
    return key < p.key;
}