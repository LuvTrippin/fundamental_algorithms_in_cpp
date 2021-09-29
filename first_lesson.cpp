#include <iostream>
#include <math.h>
#include <vector>
#include <random>

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

double find_lenght_segment(double x1, double y1, double x2, double y2) // second task
{
    if (abs(x2 - x1) > abs(y2 - y1)) {
        return (abs(x2 - x1) * sqrt(1 + pow((y2 - y1) / (x2 - x1), 2)));
    }
    else {
        return (abs(y2 - y1) * sqrt(1 + pow((x2 - x1) / (y2 - y1), 2)));
    }
}

double find_area_of_triangle(double x1, double y1, double x2, double y2, double x3, double y3) // third task
{
    double side_a = find_lenght_segment(x1, y1, x2, y2);
    double side_b = find_lenght_segment(x2, y2, x3, y3);
    double side_c = find_lenght_segment(x3, y3, x1, y1);
    double half_of_perimeter = (side_a + side_b + side_c) / 2;
    return half_of_perimeter * sqrt((half_of_perimeter - side_a)
        * (half_of_perimeter - side_b) * (1 - side_c / half_of_perimeter));
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

    point operator-(const point& term1) const
    {
        return point(x - term1.x, y - term1.y);
    }

    void print_point()
    {
        std::cout << "(" << x << "," << y << ")";
    }

};

double find_lenght_segment(point start, point end)
{
    return find_lenght_segment(start.x, start.y, end.x, end.y);
}

double find_area_of_triangle(point vertex1, point vertex2, point vertex3)
{
    return find_area_of_triangle(vertex1.x, vertex1.y, vertex2.x, vertex2.y, vertex3.x, vertex3.y);
}


double find_area_of_polygon(const std::vector<point>& vertexes) //fifth task
{
    double area_of_polygon = 0;
    for (int i = 0; i < vertexes.size() - 1; i++)
    {
        area_of_polygon += (vertexes[i].x * vertexes[i + 1].y);
        area_of_polygon -= (vertexes[i + 1].x * vertexes[i].y);
    }
    area_of_polygon += (vertexes[vertexes.size() - 1].x * vertexes[0].y);
    area_of_polygon -= (vertexes[vertexes.size() - 1].y * vertexes[0].x);
    return (abs(area_of_polygon) / 2);
}

double find_total_area_of_rectangles(point vert1_1, point vert1_2, point vert2_1, point vert2_2) // sixth task
{
    double left_end1 = std::min(vert1_1.x, vert1_2.x);
    double right_end1 = std::max(vert1_1.x, vert1_2.x);
    double left_end2 = std::min(vert2_1.x, vert2_2.x);
    double right_end2 = std::max(vert2_1.x, vert2_2.x);
    double high_end1 = std::max(vert1_1.y, vert1_2.y);
    double low_end1 = std::min(vert1_1.y, vert1_2.y);
    double high_end2 = std::max(vert2_1.y, vert2_2.y);
    double low_end2 = std::min(vert2_1.y, vert2_2.y);
    if (std::min(right_end1, right_end2) < std::max(left_end1, left_end2) || std::min(high_end1, high_end2) < std::max(low_end1, low_end2))
    {
        return 0;
    }

    return ((std::min(right_end1, right_end2) - std::max(left_end1, left_end2)) * (std::min(high_end1, high_end2) - std::max(low_end1, low_end2)));
}



double direction(point p1, point p2, point p3)
{
    return ((p3.x - p1.x) * (p2.y - p1.y) - (p2.x - p1.x) * (p3.y - p1.y));
}

bool on_segment(point p1, point p2, point p3)
{
    return (std::min(p1.x, p2.x) <= p3.x && p3.x <= std::max(p1.x, p2.x) && std::min(p1.y, p2.y) <= p3.y && p3.y <= std::max(p1.y, p2.y));
}

bool segments_intersect(point start1, point end1, point start2, point end2) // eighth task
{
    double d1 = direction(start2, end2, start1);
    double d2 = direction(start2, end2, end1);
    double d3 = direction(start1, end1, start2);
    double d4 = direction(start2, end2, end2);

    return ((d1 > 0 && d2 < 0 || d1 < 0 && d2 > 0) && (d3 > 0 && d4 < 0 || d3 < 0 && d4 > 0) || d1 == 0 && on_segment(start2, end2, start1)
        || d2 == 0 && on_segment(start2, end2, end1)) || d3 == 0 && on_segment(start1, end1, start2) || d4 == 0 && on_segment(start1, end1, end2);
}

// прямоугольники вектора задаются парой углов : левым нижним и правым верхним, 
//функция возвращает примерную площадь, найденную методом монте-карло
double polygon_union_square_by_MK(const std::vector<std::pair<point, point>>& rects, int trials)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    double low_x = DBL_MAX, low_y = DBL_MAX, hi_x = DBL_MIN, hi_y = DBL_MIN;
    for (auto r : rects)
    {
        low_x = std::min(low_x, r.first.x);
        low_y = std::min(low_y, r.first.y);
        hi_x = std::max(hi_x, r.second.x);
        hi_y = std::max(hi_y, r.second.y);
    }
    std::uniform_real_distribution<> dis_x(low_x, hi_x);
    std::uniform_real_distribution<> dis_y(low_y, hi_y);

    int inside = 0;
    for (size_t i = 0; i < trials; i++)
    {
        double a = dis_x(gen), b = dis_y(gen);
        for (auto& r : rects)
        {
            if (r.first.x <= a && r.first.y <= b && r.second.x >= a && r.second.y >= b)
            {
                inside++;
                break;
            }
        }
    }
    return inside * (hi_x - low_x) * (hi_y - low_y) / trials;
}

int nod(int a, int b)
{
    while (a != 0 and b != 0)
    {
        if (a > b)
        {
            a = a % b;
        }
        else
        {
            b = b % a;
        }
    }
    return (a + b);
}

int count_of_points_inside_polygon(const std::vector<point>& vertexes)
{
    double S = find_area_of_polygon(vertexes);
    point delta = point();
    int count_points = 0;
    for (int i = 0; i < vertexes.size() - 1; i++)
    {
        delta = vertexes[i] - vertexes[i + 1];
        count_points += nod(abs(delta.x), abs(delta.y));
    }
    delta = vertexes.back() - vertexes[0];
    count_points += nod(abs(delta.x), abs(delta.y));
    return  S - count_points / 2. + 1;
}

int main()
{
    std::cout << find_lenght_segment(-1, 7, 7, 1) << std::endl << find_area_of_triangle(3, 3, 1, 4, -1, 1);
    std::cout << std::endl;
    std::cout << find_lenght_segment(point(-1, 7), point(7, 1)) << std::endl << find_area_of_triangle(point(3, 3), point(1, 4), point(-1, 1));
    std::cout << std::endl;
    std::cout << find_total_area_of_rectangles(point(1, 1), point(2, 2), point(1.5, 1), point(3, 2));
    std::cout << std::endl;
    std::vector<point> vertexes = { point(3,4), point(5,11), point(12,8), point(9,5), point(5,6) };
    std::cout << find_area_of_polygon(vertexes) << std::endl;
    (point(12, 4) - point(9, 1)).print_point();
    std::cout << std::endl << segments_intersect(point(0, 0), point(1, 2), point(1, 0), point(2, 2)) << std::endl;

    std::vector<std::pair<point, point>> rects;
    rects.push_back({ point(), point(1, 1) });
    rects.push_back({ point(2, 2), point(3, 3) });
   // std::cout << polygon_union_square_by_MK(rects, 1000);
    std::vector<point> new_vertexes = { {2, 0}, {3, 1}, {2, 3}, {5, 4}, {6, 1}, {8, 4}, {6, 6}, {7, 8}, {3, 7}, {1, 8}, {1, 6}, {4, 5}, {0, 4} };
    std::cout << count_of_points_inside_polygon(new_vertexes);

}
