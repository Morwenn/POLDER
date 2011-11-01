////////////////////////////////////////////////////////////
///
/// POLDER Geo Vector - POLDER library providing the Vector class
/// Written by Morwenn Edrahir, 2011
///
////////////////////////////////////////////////////////////

#ifndef _POLDER_GEO_LINE_H
#define _POLDER_GEO_LINE_H

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <cstdlib>
#include "direction.h"
#include "limits.h"
#include "point.h"
#include "vector.h"


namespace polder
{
namespace geo
{


// Line definition
template<size_t N>
class Line
{
    public:

        ////////////////////////////////////////////////////////////
        // Constructors
        ////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////
        /// Default constructor
        ///
        ////////////////////////////////////////////////////////////
        Line() {}

        ////////////////////////////////////////////////////////////
        /// Copy constructor
        ///
        ////////////////////////////////////////////////////////////
        Line(const Line<N>& other):
            P(other.P),
            D(other.D)
        {}

        ////////////////////////////////////////////////////////////
        /// Construct a Line passing by two points
        ///
        /// \param P1: First point
        /// \param P2: Second point
        ///
        ////////////////////////////////////////////////////////////
        Line(const Point<N>& P1, const Point<N>& P2):
            P(P1),
            D(Direction<N>(P1, P2))
        {}

        Line(const Point<N>& P, const Vector<N>& V):
            P(P),
            D(Direction<N>(V))
        {}

        Line(const Point<N>& P, const Direction<N>& D):
            P(P),
            D(D)
        {}

        ////////////////////////////////////////////////////////////
        /// Elements accessor
        ///
        ////////////////////////////////////////////////////////////
        size_t dimension() const
        {
            return N;
        }

        Direction<N> direction() const
        {
            return D;
        }

        ////////////////////////////////////////////////////////////
        /// Operators
        ////////////////////////////////////////////////////////////

        // Assignement
        Line<N>& operator=(const Line<N>& other)
        {
            if (this != &other)
            {
                P = other.P;
                D = other.D;
            }
            return *this;
        }

        // Comparison
        bool operator==(const Line<N>& other) const
        {
            return D == other.D && other.includes(P);
        }

        bool operator!=(const Line<N>& other) const
        {
            return !(*this == other);
        }


        ////////////////////////////////////////////////////////////
        /// Miscellaneous functions
        ///
        ////////////////////////////////////////////////////////////

        bool includes(const Point<N>& P) const
        {
            // Line equation:
                // X = px + t * dx
                // Y = py + t * dy
                // Z = pz + t * dz
                // etc...
            // And so:
                // t = X - px (dx always equals 1)
                // t = (Y - py) / dy
                // t = (Z - pz) / dz
                // etc...
            // A point is included in the line if it satisfies the parametric
            // equation for all the coordinates

            const double t1 = P.x() - this->P.x();
            for (size_t i = 1 ; i < N ; ++i)
            {
                double t = (P[i] - this->P[i]) / D[i-1];
                if (!round_equal(t, t1))
                {
                    return false;
                }
            }
            return true;
        }

    private:

        // Member data
        Point<N> P;
        Direction<N> D;
};


} // namespace geo
} // namespace polder


#endif
