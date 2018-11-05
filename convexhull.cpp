#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Point
{
  public:
    int x;
    int y;

    Point()
    {
    }
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    int get_x()
    {
        return x;
    }
    void set_x(int x)
    {
        this->x = x;
    }
    int get_y()
    {
        return y;
    }
    void set_y(int y)
    {
        this->y = y;
    }
};

bool onSegment(Point p, Point q, Point r) 
{ 
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && 
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
        return true; 
    return false; 
} 
  
// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(Point p, Point q, Point r) 
{ 
    int val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y); 
  
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 
  
// The function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
bool doIntersect(Point p1, Point q1, Point p2, Point q2) 
{ 
    // Find the four orientations needed for general and 
    // special cases 
    int o1 = orientation(p1, q1, p2); 
    int o2 = orientation(p1, q1, q2); 
    int o3 = orientation(p2, q2, p1); 
    int o4 = orientation(p2, q2, q1); 
  
    // General case 
    if (o1 != o2 && o3 != o4) 
        return true; 
  
    // Special Cases 
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1 
    if (o1 == 0 && onSegment(p1, p2, q1)) return true; 
  
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1 
    if (o2 == 0 && onSegment(p1, q2, q1)) return true; 
  
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2 
    if (o3 == 0 && onSegment(p2, p1, q2)) return true; 
  
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2 
    if (o4 == 0 && onSegment(p2, q1, q2)) return true; 
  
    return false; // Doesn't fall in any of the above cases 
} 
  
// Returns true if the point p lies inside the polygon[] with n vertices 
bool isInside(Point polygon[], int n, Point p) 
{ 
    // There must be at least 3 vertices in polygon[] 
    if (n < 3)  return false; 
  
    // Create a point for line segment from p to infinite 
    Point extreme = {-99999, p.y}; 
  
    // Count intersections of the above line with sides of polygon 
    int count = 0, i = 0; 
    do
    { 
        int next = (i+1)%n; 
  
        // Check if the line segment from 'p' to 'extreme' intersects 
        // with the line segment from 'polygon[i]' to 'polygon[next]' 
        if (doIntersect(polygon[i], polygon[next], p, extreme)) 
        { 
            // If the point 'p' is colinear with line segment 'i-next', 
            // then check if it lies on segment. If it lies, return true, 
            // otherwise false 
            if (orientation(polygon[i], p, polygon[next]) == 0) 
               return onSegment(polygon[i], p, polygon[next]); 
  
            count++; 
        } 
        i = next; 
    } while (i != 0); 
  
    // Return true if count is odd, false otherwise 
    return count&1;  // Same as (count%2 == 1) 
} 



vector<Point> prunePoints(vector<Point> &points)
{

    Point a, b, c, d;
    int n = points.size();
    vector<Point> results;
    a = points[0];
    b = points[1];
    c = points[2];
    d = points[3];
    bool prune[n] = {false};
    int x1, y1, x2, y2;
    x1 = max(c.x, d.x);
    x2 = min(a.x, b.x);
    y1 = max(a.y, d.y);
    y2 = min(b.y, c.y);

    for (int i = 0; i < n; i++)
    {
        Point quad[4] = { a, b,c, d };

        if (prune[i])
            continue;
        if (points[i].x > x1 && points[i].x < x2 && points[i].y > y1 && points[i].y < y2)
        {
            prune[i] = true;
        }
        else if(isInside(quad, 4, points[i]) == false)

        {

            if ((points[i].x - points[i].y) > (a.x - a.y))
            {

                a = points[i];
            }
            if ((points[i].x + points[i].y) > (b.x + b.y))
            {

                b = points[i];
            }
            if ((points[i].x - points[i].y) < (c.x - c.y))
            {

                c = points[i];
            }
            if ((points[i].x + points[i].y) < (d.x + d.y))
            {

                d = points[i];
            }
            x1 = max(c.x, d.x);
            x2 = min(a.x, b.x);
            y1 = max(a.y, d.y);
            y2 = min(b.y, c.y);
        }
    }

    cout<<a.x<<" "<<a.y<<endl;
    cout<<b.x<<" "<<b.y<<endl;
    cout<<c.x<<" "<<c.y<<endl;
    cout<<d.x<<" "<<d.y<<endl;

    for (int i = 0; i < n; i++)
    {

        if (prune[i])
            continue;
        Point quad[4] = { a, b,c, d };
        if (points[i].x > x1 && points[i].x < x2 && points[i].y > y1 && points[i].y < y2)
        {
            prune[i] = true;
        }
        // else if(isInside(quad, 4, points[i]) == false)
        // {

        //     if ((points[i].x - points[i].y) > (a.x - a.y))
        //     {

        //         a = points[i];
        //     }
        //     if ((points[i].x + points[i].y) > (b.x + b.y))
        //     {

        //         b = points[i];
        //     }
        //     if ((points[i].x - points[i].y) < (c.x - c.y))
        //     {

        //         c = points[i];
        //     }
        //     if ((points[i].x + points[i].y) < (d.x + d.y))
        //     {

        //         d = points[i];
        //     }
        //     x1 = max(c.x, d.x);
        //     x2 = min(a.x, b.x);
        //     y1 = max(a.y, d.y);
        //     y2 = min(b.y, c.y);
        // }
    }
    cout<<a.x<<" "<<a.y<<endl;
    cout<<b.x<<" "<<b.y<<endl;
    cout<<c.x<<" "<<c.y<<endl;
    cout<<d.x<<" "<<d.y<<endl;
    for (int i = 0; i < points.size(); i++)
    {
        if (prune[i] == false)
            results.push_back(points[i]);
    }
    return results;
}

int main()
{
    int n;
    cout << "Enter n:";
    cin >> n;
    vector<Point> points;
    for (int i = 0; i < n; i++)
    {
        int x = rand() % 1000000007;
        int y = rand() % 1000000007;
        // if (i % 3 == 0)
        //     x = -x;
        // if (i % 7 == 0)
        //     y = -y;
        Point p(x, y);
        points.push_back(p);
    }
    points = prunePoints(points);
    cout<< n - points.size();
    
}
