#include "Sphere_Plane_Distance.h"
#include "Norm3D.h"
#include "Circle3D.h"

Circle3D Circular_Intersection_Of_Sphere_And_Plane ( Sphere const& s, Pl3 const& p )
{
    double sphere_plane_distance = Sphere_Plane_Distance( s, p );
    
    double r = sqrt( s.r * s.r - sphere_plane_distance * sphere_plane_distance );
    P3 c = s.c - sphere_plane_distance * p.orthogonal_vector() / (double)Norm( p.orthogonal_vector() );
    V3 v1 = p.base1() / (double)Norm( p.base1() );
    V3 v2 = p.base2() / (double)Norm( p.base2() );
    
    return Circle3D( c, r, v1, v2 );
}
