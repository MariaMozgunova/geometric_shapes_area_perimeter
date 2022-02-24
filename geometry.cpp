#include <iostream>
#include <vector>
#include <math.h>
#include <stdexcept>

#pragma once

class Point {
    double x_;
    double y_;
public:
    Point(double x=0, double y=0) :
        x_(x), y_(y) {}

    double diffx(const Point &point) {
        return x_ - point.x();
    }

    double diffy(const Point &point) {
        return y_ - point.y();
    }

    double distance(const Point &point) {
        double dx = diffx(point);
        double dy = diffy(point);

        return sqrt(dx * dx + dy * dy);
    }

    double x() const {
        return x_;
    }

    double y() const {
        return y_;
    }
};

class PolygonalChain {
protected:
    std::vector<Point> points_;
public:
    PolygonalChain(std::vector<Point> &p) 
        : points_(p) {}

    virtual void describe_yourself() {
        std::cout << "I am the polygonal chain\n";
    }
};

class ClosedPolygonalChain: public PolygonalChain {
public:
    ClosedPolygonalChain(std::vector<Point> &p) : PolygonalChain(p) {}

    virtual double perimeter() {

        double res = 0;
        Point prev = points_.back();

        for (Point cur : points_) {
            res += cur.distance(prev);
            prev = cur;
        }

        return res;
    }

    virtual void describe_yourself() {
        std::cout << "I am the closed polygonal chain with perimeter equal to " 
                  << perimeter() << "\n";
    }
};

class Polygon: public ClosedPolygonalChain {
public:
    Polygon(std::vector<Point> &p) : ClosedPolygonalChain(p) {
        int n = points_.size();

        for (int i = 0; i < n; ++i) {
            double x1 = points_[i].diffx(points_[(i + 1) % n]);
            double y1 = points_[i].diffy(points_[(i + 1) % n]);
            double x2 = points_[(i + 1) % n].diffx(points_[(i + 2) % n]);
            double y2 = points_[(i + 1) % n].diffy(points_[(i + 2) % n]);

            if (x1 * y2 == x2 * y1) {
                throw std::invalid_argument("two vertices lie on the same  line");
            }
        }

        for (int i = 0; i < n; ++i) { 
            for (int j = i + 2; j < n; ++j) {
                if ((i + 1) % n == j || (j + 1) % n == i) {
                    continue;
                }

                double x1 = points_[j].diffx(points_[i]);
                double y1 = points_[j].diffy(points_[i]);
                double x2 = points_[(j + 1) % n].diffx(points_[i]);
                double y2 = points_[(j + 1) % n].diffy(points_[i]);
                double x3 = points_[(i + 1) % n].diffx(points_[i]);
                double y3 = points_[(i + 1) % n].diffy(points_[i]);

                double x4 = points_[i].diffx(points_[(j + 1) % n]);
                double y4 = points_[i].diffy(points_[(j + 1) % n]);
                double x5 = points_[(i + 1) % n].diffx(points_[(j + 1) % n]);
                double y5 = points_[(i + 1) % n].diffy(points_[(j + 1) % n]);
                double x6 = points_[j].diffx(points_[(j + 1) % n]);
                double y6 = points_[j].diffy(points_[(j + 1) % n]);

                double prod1 = x1 * y3 - x3 * y1;
                double prod2 = x2 * y3 - x3 * y2;
                double prod3 = x4 * y6 - x6 * y4;
                double prod4 = x5 * y6 - x6 * y5;

                if (
                    (prod1 * prod2 < 0 || prod1 == 0 && prod2 != 0 || prod2 == 0 && prod1 != 0) && 
                    (prod3 * prod4 < 0 || prod3 == 0 && prod4 != 0 || prod4 == 0 && prod3 != 0)
                ) {
                    std::cout << i << ' ' << j << '\n';
                    std::cout << (x1 * y3 - x3 * y1) * (x2 * y3 - x3 * y2) << ' ' << (x4 * y6 - x6 * y4) * (x5 * y6 - x6 * y5) << '\n';
                    throw std::invalid_argument("two edges intersect");
                }
            }
        }
    }

    virtual double area() {
        double res = 0;
        Point start = points_[0];

        for (int i = 1; i < points_.size() - 1; ++i) {
            Point first = points_[i];
            Point second = points_[i + 1];
            double x1 = first.diffx(start);
            double y1 = first.diffy(start);
            double x2 = second.diffx(start);
            double y2 = second.diffy(start);

            res += x1 * y2 - x2 * y1;
        }

        return abs(res) / 2;
    }

    virtual void describe_yourself() {
        std::cout << "I am the polygon with perimeter equal to " 
                  << perimeter() << " and area equal to " << area() << "\n";
    }
};

class Triangle: public Polygon {
public:
    Triangle(std::vector<Point> &p) : Polygon(p) {
        if (points_.size() != 3) {
            throw std::invalid_argument("triangle should have three points");
        }
    }

    virtual void describe_yourself() {
        std::cout << "I am the triangle with perimeter equal to " 
                  << perimeter() << " and area equal to " << area() << "\n";
    }
};

class Trapezoid: public Polygon {
public:
    Trapezoid(std::vector<Point> &p) : Polygon(p) {
        if (points_.size() != 4) {
            throw std::invalid_argument("trapezoid should have four points");
        }

        double dx0 = points_[0].diffx(points_[1]);
        double dy0 = points_[0].diffy(points_[1]);
        double dx1 = points_[1].diffx(points_[2]);
        double dy1 = points_[1].diffy(points_[2]);
        double dx2 = points_[2].diffx(points_[3]);
        double dy2 = points_[2].diffy(points_[3]);
        double dx3 = points_[3].diffx(points_[0]);
        double dy3 = points_[3].diffy(points_[0]);

        if (dx0 * dy2 == -dy0 * dx2) {}
        else if (dx1 * dy3 == -dy1 * dx3) {
            Point tmp = points_[0];
            points_[0] = points_[2];
            points_[2] = tmp;
        } else {
            throw std::invalid_argument("not a trapezoid");
        }
    }

    virtual void describe_yourself() {
        std::cout << "I am the trapezoid with perimeter equal to " 
                  << perimeter() << " and area equal to " << area() << "\n";
    }
};

class RegularPolygon: public Polygon {   
public: 
    RegularPolygon(std::vector<Point> &p) : Polygon(p) {
        Point prev = points_.back();
        double edge = prev.distance(points_[0]);

        for (Point cur : points_) {
            if (cur.distance(prev) != edge) {
                throw std::invalid_argument("edges of unequal length");
            }

            prev = cur;
        }

    }

    virtual void describe_yourself() {
        std::cout << "I am the regular polygon with perimeter equal to " 
                  << perimeter() << " and area equal to " << area() << "\n";
    }
};