#include <iostream>
#include <math.h>
#include <vector>


bool sum_is_equal_to(int term1, int term2, int possible_sum) // first task
{
    if (term1 > 0 && term2 > 0 && possible_sum < 0 ||
        term1 < 0 && term2 < 0 && possible_sum > 0)
    {
        return false;
    }
    if (term1 > 0 && term2 > 0 && possible_sum >= 0 ||
        term1 < 0 && term2 < 0 && possible_sum <= 0)
    {
        return possible_sum - term1 == term2;
    }
    return term1 + term2 == possible_sum;
}

double found_lenght_segment(double x1, double y1, double x2, double y2) // second task
{
    if (abs(x2 - x1) > abs(y2 - y1)) {
        return (abs(x2 - x1) * sqrt(1 + pow((y2 - y1) / (x2 - x1), 2)));
    }
    else {
        return (abs(y2 - y1) * sqrt(1 + pow((x2 - x1) / (y2 - y1), 2)));
    }
}

double found_area_of_triangle(double x1, double y1, double x2, double y2, double x3, double y3) // third task
{
    double side_a = found_lenght_segment(x1, y1, x2, y2);
    double side_b = found_lenght_segment(x2, y2, x3, y3);
    double side_c = found_lenght_segment(x3, y3, x1, y1);
    double half_of_perimeter = (side_a + side_b + side_c) / 2;
    return pow(half_of_perimeter, 2) * sqrt((1 - side_a / half_of_perimeter) 
        * (1 - side_b / half_of_perimeter) * (1 - side_c / half_of_perimeter));
}

struct point // fourth task
{
    double x, y;
    point() 
    {
        this->x = 0;
        this->y = 0;
    }
    point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

};

double found_lenght_segment(point start, point end)
{
    if (abs(end.x - start.x) > abs(end.y - start.y)) {
        return (abs(end.x - start.x) * sqrt(1 + pow((end.y - start.y) / (end.x - start.x), 2)));
    }
    else {
        return (abs(end.y - start.y) * sqrt(1 + pow((end.x - start.x) / (end.y - start.y), 2)));
    }
}

double found_area_of_triangle(point vertex1, point vertex2, point vertex3)
{
    double side_a = found_lenght_segment(vertex1, vertex2);
    double side_b = found_lenght_segment(vertex2, vertex3);
    double side_c = found_lenght_segment(vertex3, vertex1);
    double half_of_perimeter = (side_a + side_b + side_c) / 2;
    return pow(half_of_perimeter, 2) * sqrt((1 - side_a / half_of_perimeter)
        * (1 - side_b / half_of_perimeter) * (1 - side_c / half_of_perimeter));
}

double find_max_coordinate(std::vector<point> points)
{
    double max_coordinate = -10000000000000;
    for (int i = 0; i < points.size(); i++)
    {
        if (points[i].x > max_coordinate) 
        {
            max_coordinate = points[i].x;
        }
        if (points[i].y > max_coordinate)
        {
            max_coordinate = points[i].y;
        }
    }
    return max_coordinate;
}

double found_area_of_polygon(std::vector<point> vertexes)
{
    double max_coordinate = find_max_coordinate(vertexes);
    double area_of_polygon = 0;
    for (int i = 0; i < vertexes.size() - 1; i++)
    {   
        area_of_polygon += (vertexes[i].x * vertexes[i + 1].y) / max_coordinate;
        area_of_polygon -= (vertexes[i + 1].x * vertexes[i].y) / max_coordinate;
    }
    area_of_polygon += (vertexes[vertexes.size() - 1].x * vertexes[0].y) / max_coordinate;
    area_of_polygon -= (vertexes[vertexes.size() - 1].y * vertexes[0].x) / max_coordinate;
    return (abs(area_of_polygon) * abs(max_coordinate) / 2);
}

double found_total_area_of_rectangles(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) // sixth task
{   
    if (x1 > x4 || x3 > x2 || y1 > y4 || y3 > y2) 
    {
        return 0;
    }
    else
    {
        return ((std::min(x2, x4) - std::max(x1, x3)) * (std::min(y2, y4) - std::max(y1, y3)));
    }
}
    
int main()
{
    std::cout << found_lenght_segment(-1, 7, 7, 1) << std::endl << found_area_of_triangle(3, 3, 1, 4, -1, 1);
    std::cout << std::endl;
    std::cout << found_lenght_segment(point(-1,7), point(7,1)) << std::endl << found_area_of_triangle(point(3,3), point(1,4), point(-1,1));
    std::cout << std::endl;
    std::cout << found_total_area_of_rectangles(1., 1., 2., 2., 1.5, 1., 3., 2.);
    std::cout << std::endl;
    std::vector<point> vertexes = {point(3,4), point(5,11), point(12,8), point(9,5), point(5,6) };
    std::cout << found_area_of_polygon(vertexes);
}

