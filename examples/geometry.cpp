// Headers
#include <cstdlib>
#include <iostream>
#include <utility>
#include <POLDER/geometry.h>
#include <POLDER/utility.h>

using namespace polder;
using namespace geometry;
using std::cout;
using std::endl;


int main()
{
    ////////////////////////////////////////////////////////////
    // Construction of simple objects
    {
        Point<3> P1(2.0, 2.5, 5.2);
        Point<3> P2 = { 0.1, 2.9, 9.000001 };

        Vector<3> V1(2.0, 2.1, 2.2);
        Vector<3> V2 = { 2.5, 8.3, 6. };
        Vector<3> V3 = { P1, P2 };

        Line<3> L1 = { P1, P2 };

        Direction<3> D1 = V1.direction();
        Direction<3> D2 = L1.direction();

        Hypersphere<3> HS(P1, 5.0);
        Hypersphere<3> HF = HS;

        ignore(V2, V3, D1, D2, HF);
    }


    ////////////////////////////////////////////////////////////
    // Intersection
    {
        Line<2> L = {
            Point<2>(15.0, 1.0),
            Point<2>(23.7, 1.0)
        };

        Hypersphere<2> C = {
            Point<2>(0.0, 1.0), // Center
            1.0                 // Radius
        };

        const Direction<2>& D = L.direction();

        Object O = intersection(L, C);

        std::pair<Point<2>, Point<2>> res;

        cout << O.assign(res) << endl;

        cout << res.first.x() << " " << res.first.y() << endl;    //  1, 1
        cout << res.second.x() << " " << res.second.y() << endl;  // -1, 1

        ignore(D);
    }

    ////////////////////////////////////////////////////////////
    // Distance
    {
        Point<2> a = { 4.5, 6.3 };
        Point<2> b = { 8.9, 25.3 };
        std::cout << distance(a, b) << std::endl;

        POLDER_ASSERT(distance(a, b) == distance(b, a));
        POLDER_ASSERT(distance(a, a) == distance(b, b));
        POLDER_ASSERT(distance(a, a) == 0.0);
    }
}
