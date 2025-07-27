std::pair<Pointl, long double> getCircle(Point p1, Point p2, Point p3){
    Point a = p2-p1;
    a /= 2;
    a += p1;
    Point b = Point(-(p2-a).Y, (p2-a).X) + a;
    Point c = p3-p1;
    c /= 2;
    c += p1;
    Point d = Point(-(p3-c).Y, (p3-c).X) + c;
    Point center = intersection(a, b, c, d);
    return {center, abs(p1 - center)};
}
