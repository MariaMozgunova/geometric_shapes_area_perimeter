#include "geometry.cpp"

int main() {
    // // intersecting edges
    // std::vector<Point> pp = {Point(1, 1), Point(5, 4), Point(2, 3), Point(3, 0)};
    // Polygon p(pp);

    // // 4-polygon
    // std::vector<Point> pp = {Point(3, 4), Point(5, 4), Point(6, 1), Point(1, 1)};
    // Polygon p(pp);
    // std::cout << p.perimeter() << ' ' << p.area() << '\n';

    // // сoncave polygon
    // std::vector<Point> pp = {
    //     Point(0, 0), Point(0, 1), Point(1, 1), Point(1, 2),
    //     Point(2, 2), Point(2, 1), Point(3, 1), Point(3, 2),
    //     Point(4, 2), Point(4, 1), Point(6, 1), Point(6, 0),
    // };
    // Polygon p(pp);
    // std::cout << p.perimeter() << ' ' << p.area() << "\n";

    std::vector<Polygon*> polygons;

    std::vector<Point> polygon_points = {Point(3, 4), Point(6, 5), Point(6, 1), Point(1, 1)};
    Polygon polygon(polygon_points);
    polygons.push_back(&polygon);

    std::vector<Point> triangle_points = {Point(1, 2), Point(4, 6), Point(4, 2)};
    Triangle triangle(triangle_points);
    polygons.push_back(&triangle);

    std::vector<Point> trapezoid_points = {Point(3, 4), Point(5, 4), Point(6, 1), Point(1, 1)};
    Trapezoid trapezoid(trapezoid_points);
    polygons.push_back(&trapezoid);

    std::vector<Point> regular_polygon_points = {Point(0, 0), Point(0, 2), Point(2, 2), Point(2, 0)};
    RegularPolygon regular_polygon(regular_polygon_points);
    polygons.push_back(&regular_polygon);

    for (Polygon *p : polygons) {
        p->describe_yourself();
    }
}