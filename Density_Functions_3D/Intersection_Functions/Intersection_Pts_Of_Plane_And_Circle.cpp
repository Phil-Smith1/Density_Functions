// http://mathforum.org/library/drmath/view/69136.html
// http://mathforum.org/library/drmath/view/65138.html

#include "Circle3D.h"
#include "Norm3D.h"

typedef K::Plane_3 Pl3;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

void Intersection_Pts_Of_Plane_And_Circle ( Pl3 const& p, Circle3D const& c, P3& pt1, P3& pt2 )
{
    P3 pt = p.point();
    V3 v = p.orthogonal_vector() / (double)Norm( p.orthogonal_vector() );
    V3 b1 = c.v1;
    V3 b2 = c.v2;
    
    double k1 = (c.c.x() - pt.x()) * v.x() + (c.c.y() - pt.y()) * v.y() + (c.c.z() - pt.z()) * v.z();
    double k2 = b1.x() * v.x() + b1.y() * v.y() + b1.z() * v.z();
    double k3 = b2.x() * v.x() + b2.y() * v.y() + b2.z() * v.z();
    
    double alpha = acos( k2 / (double)sqrt( k2 * k2 + k3 * k3 ) );
    double thetaplusalpha;
    double theta1, theta2, theta1b, theta2b;
    
    if (-k1 / (double)sqrt( k2 * k2 + k3 * k3 ) < -1 || -k1 / (double)sqrt( k2 * k2 + k3 * k3 ) > 1)
    {
        if (-k1 / (double)sqrt( k2 * k2 + k3 * k3 ) < -1) thetaplusalpha = asin( -1 );
        else thetaplusalpha = asin( 1 );
    }
    
    else thetaplusalpha = asin( -k1 / (double)sqrt( k2 * k2 + k3 * k3 ) );
    
    theta1 = thetaplusalpha - alpha;
    theta1b = thetaplusalpha + alpha;
    
    if (abs( k2 * sin( theta1 ) + k3 * cos( theta1 ) + k1 ) > abs( k2 * sin( theta1b ) + k3 * cos( theta1b ) + k1 ) + tiny_num) // Changed for T2 dataset.
    {
        alpha *= -1;
        theta1 = thetaplusalpha - alpha;
    }
    
    int n = (thetaplusalpha >= 0) ? 2 : 1;
    
    theta2 = pow( -1, n ) * PI - thetaplusalpha - alpha;
    theta2b = pow( -1, n ) * PI - thetaplusalpha + alpha;
    
    if (abs( k2 * sin( theta2 ) + k3 * cos( theta2 ) + k1 ) > abs( k2 * sin( theta2b ) + k3 * cos( theta2b ) + k1 ) + tiny_num)
    {
        alpha *= -1;
        theta1 = thetaplusalpha - alpha;
        theta2 = pow( -1, n ) * PI - thetaplusalpha - alpha;
    }
    
    pt1 = c.c + sin( theta1 ) * b1 + cos( -theta1 ) * b2;
    pt2 = c.c + sin( theta2 ) * b1 + cos( -theta2 ) * b2;
}
