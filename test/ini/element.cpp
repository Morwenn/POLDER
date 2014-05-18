/*
 * Copyright (C) 2014 Morwenn
 *
 * POLDER is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * POLDER is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
 */
#include <string>
#include <typeindex>
#include <POLDER/ini/element.h>

int main()
{
    using namespace polder;
    using namespace ini;

    Element a;
    POLDER_ASSERT(a.type_id == typeid(std::string));
    POLDER_ASSERT(std::string(a) == "");

    Element b(std::string("foobar"));
    POLDER_ASSERT(b.type_id == typeid(std::string));
    POLDER_ASSERT(std::string(b) == "foobar");

    Element c("hameggs");
    POLDER_ASSERT(c.type_id == typeid(std::string));
    POLDER_ASSERT(std::string(c) == "hameggs");

    Element d(45);
    POLDER_ASSERT(d.type_id == typeid(int));
    POLDER_ASSERT(std::string(d) == "45");

    Element e(-84L);
    POLDER_ASSERT(e.type_id == typeid(long));
    POLDER_ASSERT(std::string(e) == "-84");

    Element f(0LL);
    POLDER_ASSERT(f.type_id == typeid(long long));
    POLDER_ASSERT(std::string(f) == "0");

    Element g(456U);
    POLDER_ASSERT(g.type_id == typeid(unsigned));
    POLDER_ASSERT(std::string(g) == "456");

    Element h(199UL);
    POLDER_ASSERT(h.type_id == typeid(unsigned long));
    POLDER_ASSERT(std::string(h) == "199");

    Element i(78ULL);
    POLDER_ASSERT(i.type_id == typeid(unsigned long long));
    POLDER_ASSERT(std::string(i) == "78");

    Element j(3.52f);
    POLDER_ASSERT(j.type_id == typeid(float));
    //POLDER_ASSERT(std::string(j) == "3.52");

    Element k(85.23);
    POLDER_ASSERT(k.type_id == typeid(double));
    //POLDER_ASSERT(std::string(k) == "85.23");

    Element l(21.57l);
    POLDER_ASSERT(l.type_id == typeid(long double));
    //POLDER_ASSERT(std::string(l) == "21.27");
}
