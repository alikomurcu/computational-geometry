#include "utils.h"
#include <vector>

// p1 and p2 edge points of the clipping shape
void clip(std::vector<Point2D> &polygon, Point2D p1, Point2D p2)
{
    std::vector<Point2D> output_list;
    for (int i=0; i < polygon.size(); i++)
    {
        int k = (i + 1) % polygon.size();
        double ix = polygon[i].x, iy = polygon[i].y;
        double kx = polygon[k].x, ky = polygon[k].y;

        /* Check the point is left, right or on the line
        * This is basically the cross product of the 2D vectors
        * v1 = (p2 - p1), v2 = (ix - p1)
        * v1 x v2 = sin(theta) * |v1| * |v2|
        *
        * So, the sign of the result is equal to the sign of sin(theta)
        * if theta > 0, then sin(theta) > 0, so, the point is on the left of the edge
        * if theta < 0, then sin(theta) < 0, so, the point is on the right of the edge
        * if theta = 0, then sin(theta) = 0, so, the point is on the line
        *
        * Note that sin is defined on (-pi/2, pi/2), so, the sign of the result is enough to determine the side
        * In our case, being right of the edge means that the point is inside the clipping shape (because we iterate the clipping shape in CW order)
        */
        double i_pos = (p2.x - p1.x) * (iy - p1.y) - (p2.y - p1.y) * (ix - p1.x);
        double k_pos = (p2.x - p1.x) * (ky - p1.y) - (p2.y - p1.y) * (kx - p1.x);

        // Case 1: Both points are inside
        if (i_pos < 0 && k_pos < 0)
        {
            output_list.push_back(polygon[k]);
        }

        // Case 2: i is outside, k is inside
        else if (i_pos >= 0 && k_pos < 0)
        {
            Point2D p_int = {intersectX(p1.x, p1.y, p2.x, p2.y, ix, iy, kx, ky),
                            intersectY(p1.x, p1.y, p2.x, p2.y, ix, iy, kx, ky)};

            output_list.push_back({p_int.x, p_int.y});
            output_list.push_back(polygon[k]);
        }

        // Case 3: i is inside, k is outside
        else if (i_pos < 0 && k_pos >= 0)
        {
            Point2D p_int = {intersectX(p1.x, p1.y, p2.x, p2.y, ix, iy, kx, ky),
                            intersectY(p1.x, p1.y, p2.x, p2.y, ix, iy, kx, ky)};

            output_list.push_back({p_int.x, p_int.y});
        }
        // Case 4: Both points are outside, do not add anything
    }
    std::cout << "Output list size = " << output_list.size() << std::endl;
    polygon.clear();
    for (int i = 0; i < output_list.size(); i++)
    {
        polygon.push_back(output_list[i]);
    }
}

std::vector<Point2D> clipPolygonSutherlandHodgman(std::vector<Point2D> polygon, std::vector<Point2D> clipping_shape)
{
    std::cout << "Clipping shape size = " << clipping_shape.size() << std::endl;
    std::cout << "Polygon size = " << polygon.size() << std::endl;

    // Process clip shape edges as in clockwise order, so that, left of edge is outside, right of edge is inside
    for (int i=0; i<clipping_shape.size(); i++)
    {
        int k = (i + 1) % clipping_shape.size();
        clip(polygon, clipping_shape[i], clipping_shape[k]);
    }
    return polygon;
}

int main()
{
    std::cout << "Example clipping!" << std::endl;
    /*
    * x-----------------x
    * |                 |
    * |                 |
    * |                 |
    * |                 |
    * x-----------------x
    * Polygon
    */
    std::vector<Point2D> polygon = {{0, 0}, {0, 1}, {1, 1}, {1, 0}};
    /*
    *       x-----------------x
    *       |                 |
    *       |                 |
    *       |                 |
    *       x-----------------x
    * 
    * Clipping shape
    */
    std::vector<Point2D> clipping_shape = {{0.25, 0.25}, {0.25, 0.75}, {1.75, 0.75}, {1.75, 0.25}};

    /*
    *       x------------x
    *       |            |
    *       |            |
    *       |            |
    *       x------------x
    * Clipped polygon
    */
    std::vector<Point2D> clipped_polygon = clipPolygonSutherlandHodgman(polygon, clipping_shape);
    // print the clipped polygon
    for (int i = 0; i < clipped_polygon.size(); i++)
    {
        std::cout << clipped_polygon[i].x << " " << clipped_polygon[i].y << " " << std::endl;
    }
    std::cout << "Clipped polygon size = " << clipped_polygon.size() << std::endl;
    return 0;
}

