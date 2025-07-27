int dcmp(T a, T b){
return(abs(a-b) < eps?0:a>b?1:-1);
}
T cross(point a, point b){
return (conj(a) * b).Y;
}

T dot(point a, point b){
return (conj(a) * b).X;
}

bool is_on_segment(point a, point b, point c){
	return (dcmp(dot(a-b, c-b),0)>=0 and dcmp(dot(b-a, c-a),0) >=0 and dcmp(cross(c-a, b-a),0) == 0);
}

bool is_in_tri(point a, point b, point c, point d){
	T area1 = cross(a, b) + cross(b, c) + cross(c, a);
	a-=d;
	b-=d;
	c-=d;
	T area2 = abs(cross(a, b)) + abs(cross(b, c)) + abs(cross(c, a));
	return (dcmp(abs(area1), area2) == 0);
}

// assuming that that the polygon is convex,
// and the points are sorted ccw
// and the first point is the bottom left
bool point_in_polygon(point a, vector<point> &poly){
point x = poly[0]; //bottom left
int sz = poly.size();
int l=1, r=sz-2, ans = -1;
while(l<=r){
	int m = (l+r)/2;
	T cr = cross(poly[m]-x, a-x);
	if(cr <= 0){
		r = m-1;
	}else{
		ans = m;
		l = m+1;
	}
}

return (ans != -1 and is_in_tri(x, poly[ans], poly[ans+1], a)) or
		is_on_segment(poly[sz-1], poly[0], a) or
		is_on_segment(poly[1], poly[0], a);
}

int isInsidePoly(vector<point> p, point p0) {  int wn = 0;  // the winding number counter

  for (int i = 0; i < sz(p); i++) {
 point cur = p[i], nxt = p[(i + 1) % sz(p)];
 if (isPointOnSegment(cur, nxt, p0))
   return true;
 if (cur.Y <= p0.Y) {    // Upward edge
   if (nxt.Y > p0.Y && cp(nxt-cur, p0-cur) > EPS)
  ++wn;
 } else {                // Downward edge
   if (nxt.Y <= p0.Y && cp(nxt-cur, p0-cur) < -EPS)
  --wn;
 }
  }
  return wn != 0;
}

