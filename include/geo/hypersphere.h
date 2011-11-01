
////////////////////////////////////////////////////////////
///
/// POLDER Geo Hypersphere - POLDER library providing the Hypersphere class
/// Written by Morwenn Edrahir, 2011
///
////////////////////////////////////////////////////////////

#ifndef _POLDER_GEO_HYPERSPHERE_H
#define _POLDER_GEO_HYPERSPHERE_H

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <cmath>
#include <cstdlib>
#include "point.h"
#include "vector.h"


namespace polder
{
namespace geo
{


// Line definition
template<size_t N>
class Hypersphere
{
    public:

        ////////////////////////////////////////////////////////////
        // Constructors
        ////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////
        /// Default constructor
        ///
        ////////////////////////////////////////////////////////////
        Hypersphere() {}

        ////////////////////////////////////////////////////////////
        /// Copy constructor
        ///
        ////////////////////////////////////////////////////////////
        Hypersphere(const Hypersphere<N>& other):
            Center(other.Center),
            Radius(other.Radius)
        {}

        ////////////////////////////////////////////////////////////
        /// Construct an hypersphere from other objects
        ///
        ////////////////////////////////////////////////////////////
        Hypersphere(const Point<N>& Center, double Radius):
            Center(Center),
            Radius(Radius)
        {}

        Hypersphere(const Point<N>& Center, const Vector<N>& V):
            Center(Center),
            Radius(V.norm())
        {}

        Hypersphere(const Point<N>& Center, const Point<N>& P):
            Center(Center),
            Radius(0)
        {
            for (size_t i = 0 ; i < N ; ++i)
            {
                double tmp = P[i] - Center[i];
                Radius += tmp * tmp;
            }
            Radius = sqrt(Radius);
        }

        ////////////////////////////////////////////////////////////
        /// Elements accessors
        ///
        ////////////////////////////////////////////////////////////
        size_t dimension() const
        {
            return N;
        }

        Point<N> center() const
        {
            return Center;
        }

        double radius() const
        {
            return Radius;
        }

        ////////////////////////////////////////////////////////////
        /// Operators
        ////////////////////////////////////////////////////////////

        // Assignement
        Hypersphere& operator=(const Hypersphere<N>& other)
        {
            if (this != &other)
            {
                Center = other.Center;
                Radius = other.Radius;
            }
            return *this;
        }

        // Comparison
        bool operator==(const Hypersphere<N>& other) const
        {
            return Center == other.Center && round_equal(Radius, other.Radius);
        }

        bool operator!=(const Hypersphere<N>& other) const
        {
            return !(*this = other);
        }

    private:

        // Member data
        Point<N> Center;
        double Radius;
};


} // namespace geo
} // namespace polder


#endif
