typedef long double T;
const long double PI = acosl(-1);
const T eps = 1e-12;
#define Point std::complex<T>
#define Pointl std::complex<long double>
#define X real()
#define Y imag()
T dot(Point a, Point b){
    return (a * std::conj(b)).X;
}
T cross(Point a, Point b){
    return (a * std::conj(b)).Y;
}
T side(Point a, Point b, Point c){
    return cross(b-a, c-a);
}
void get2Points(T a, T b, T c, Point &p1, Point &p2){
    if(std::abs(b) < eps){
        p1 = Point(0, (long double)c/b);
        p2 = Point(1, (long double)(c-a)/b);
    }
    else {
        p1 = Point((long double)c/a, 0);
        p2 = Point((long double)c/a, 1);
    }
}
void getLine(Point p1, Point p2, T &a, T &b, T &c){
    T dx = p2.X - p1.X;
    T dy = p2.Y - p1.Y;
    a = -dy;
    b = dx;
    c = dx * p1.Y - dy * p1.X;
}
bool onRay(Point a, Point b, Point c){
    return std::abs(side(a, b, c)) <= eps && dot(b-a, c-a) >= -eps;
}
bool onSegment(Point a, Point b, Point c){
    return onRay(a, b, c) && onRay(b, a, c);
}
bool parallel(Point a, Point b, Point c, Point d){
    return std::abs(cross(b-a, d-c)) <= eps;
}
bool intersect(Point a, Point b, Point c, Point d){
    if(onSegment(a, b, c) || onSegment(a, b, d) || onSegment(c, d, a) || onSegment(c, d, b))
        return true;
    if(parallel(a, b, c, d))
        return false;
    T ff = side(a, b, c);
    T fs = side(a, b, d);
    T sf = side(c, d, a);
    T ss = side(c, d, b);
    bool f = (ff > 0 && fs < 0) || (ff < 0 && fs > 0);
    bool s = (sf > 0 && ss < 0) || (sf < 0 && ss > 0);
    return f && s;
}
long double cramer(T a1, T b1, T c1, T a2, T b2, T c2){
  //a.X + b.Y = c
  //d.X + e.Y = f
  long double det = a * e - b * d;
  long double x = ((ld)c * e - (ld)b * f) / det;
  return x;
}
Pointl intersection(T a1, T b1, T c1, T a2, T b2, T c2){
    Point a(a1, a2), b(b1, b2), c(c1, c2);
    if(std::abs(cross(a, b)) <= eps || std::abs(cross(a, b)) <= eps)
        return Pointl();
    return Pointl( (long double) cross(c, b) / cross(a, b), (long double) cross(a, c) / cross(a, b));
}
Pointl intersection(Point a, Point b, Point c, Point d){
    T a1, b1, c1, a2, b2, c2;
    getLine(a, b, a1, b1, c1);
    getLine(c, d, a2, b2, c2);
    return intersection(a1, b1, c1, a2, b2, c2);
}
std::pair<long double, Pointl> distance(Point a, Point b, Point c){
    if(onSegment(a, b, c)) return {0, {c.X, c.Y}};
    if(dot(b-a, c-a) <= eps) return {abs(c-a), {a.X, a.Y}};
    if(dot(a-b, c-b) <= eps) return {abs(c-b), {b.X, b.Y}};
    long double ans = std::abs(cross(c-a, c-b) / abs(a-b));
    Point d = Point((b-a).Y, (a-b).X) + c;
    Pointl pp= intersection(a, b, c, d);
    return {ans, pp};
}
