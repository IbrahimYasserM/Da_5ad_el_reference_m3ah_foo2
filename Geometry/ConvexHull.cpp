point center;

bool compare_ccw(point &a, point &b)
{
  T cr = cross(a - center, b - center);
  if (dcmp(cr, 0) == 0)
  {
    if (a.Y == b.Y)
      return a.X < b.X;
    return a.Y < b.Y;
  }
  else
    return cr > 0;
}
bool iseq(point a, point b)
{
  return dcmp(a.Y, b.Y) == 0 and dcmp(a.X, b.X) == 0;
}
vector<point> convex_hull(vector<point> points)
{
  int sz = points.size();
  for (int i = 1; i < sz; i++)
  {
    if (points[i].Y < points[0].Y)
      swap(points[i], points[0]);
    else if (points[i].Y == points[0].Y and points[i].X < points[0].X)
      swap(points[i], points[0]);
  }
  center = points[0];
  sort(points.begin() + 1, points.end(), compare_ccw);
  points.push_back(center);
  // cerr << "convex hull: sorted\n";
  vector<point> hull = {center};
  for (int i = 1; i <= sz; i++)
  {
    while (!hull.empty() and iseq(hull.back(), points[i]))
      hull.pop_back();
    while (hull.size() > 1 and cross(points[i] - hull[hull.size() - 2], hull.back() - hull[hull.size() - 2]) >= 0)
      {hull.pop_back();}
    hull.push_back(points[i]);
  }
  if (hull.size() > 1)
    hull.pop_back();
  return hull;
}

bool is_collinear(point a , point b , point c){
  return fabs(cross(a-b , a-c)) < eps;
}

  

vector<point> deleteCollinear(vector<point> points){
  vector<point> p;
  int sz = points.size();
  for(int i=0; i<sz; i++){
    if (p.size() > 1 && is_collinear(p.back() , p[(int)p.size()-2] , points[i]) ){
      p.back() = points[i];
    }else
      p.push_back(points[i]);
    }
  return p;
  }
}