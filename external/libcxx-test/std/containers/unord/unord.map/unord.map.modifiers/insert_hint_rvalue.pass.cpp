/****************************************************************************
 *
 * Copyright 2018 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/
//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++98, c++03

// <unordered_map>

// template <class Key, class T, class Hash = hash<Key>, class Pred = equal_to<Key>,
//           class Alloc = allocator<pair<const Key, T>>>
// class unordered_map

// template <class P,
//           class = typename enable_if<is_convertible<P, value_type>::value>::type>
//     iterator insert(const_iterator p, P&& x);

#include <unordered_map>
#include <cassert>

#include "MoveOnly.h"

int main()
{
    {
        typedef std::unordered_map<double, int> C;
        typedef C::iterator R;
        typedef std::pair<double, short> P;
        C c;
        C::const_iterator e = c.end();
        R r = c.insert(e, P(3.5, static_cast<short>(3)));
        assert(c.size() == 1);
        assert(r->first == 3.5);
        assert(r->second == 3);

        r = c.insert(c.end(), P(3.5, static_cast<short>(4)));
        assert(c.size() == 1);
        assert(r->first == 3.5);
        assert(r->second == 3);

        r = c.insert(c.end(), P(4.5, static_cast<short>(4)));
        assert(c.size() == 2);
        assert(r->first == 4.5);
        assert(r->second == 4);

        r = c.insert(c.end(), P(5.5, static_cast<short>(4)));
        assert(c.size() == 3);
        assert(r->first == 5.5);
        assert(r->second == 4);
    }
    {
        typedef std::unordered_map<MoveOnly, MoveOnly> C;
        typedef C::iterator R;
        typedef std::pair<MoveOnly, MoveOnly> P;
        C c;
        C::const_iterator e = c.end();
        R r = c.insert(e, P(3, 3));
        assert(c.size() == 1);
        assert(r->first == 3);
        assert(r->second == 3);

        r = c.insert(c.end(), P(3, 4));
        assert(c.size() == 1);
        assert(r->first == 3);
        assert(r->second == 3);

        r = c.insert(c.end(), P(4, 4));
        assert(c.size() == 2);
        assert(r->first == 4);
        assert(r->second == 4);

        r = c.insert(c.end(), P(5, 4));
        assert(c.size() == 3);
        assert(r->first == 5);
        assert(r->second == 4);
    }
    {
        typedef std::unordered_map<double, MoveOnly> C;
        typedef C::iterator R;
        C c;
        C::const_iterator e = c.end();
        R r = c.insert(e, {3.5, 3});
        assert(c.size() == 1);
        assert(r->first == 3.5);
        assert(r->second == 3);

        r = c.insert(c.end(), {3.5, 4});
        assert(c.size() == 1);
        assert(r->first == 3.5);
        assert(r->second == 3);

        r = c.insert(c.end(), {4.5, 4});
        assert(c.size() == 2);
        assert(r->first == 4.5);
        assert(r->second == 4);

        r = c.insert(c.end(), {5.5, 4});
        assert(c.size() == 3);
        assert(r->first == 5.5);
        assert(r->second == 4);
    }
}
