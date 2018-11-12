#include<bits/stdc++.h>
#include<fstream>
#include<chrono>
using namespace std;
using namespace std::chrono;
#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)
#define INSIDE 0
#define OUTSIDE 1

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};
int InsidePolygon(Point *polygon,int N,Point p)
{
  int counter = 0;
  int i;
  double xinters;
  Point p1,p2;

  p1 = polygon[0];
  for (i=1;i<=N;i++) {
    p2 = polygon[i % N];
    if (p.y > MIN(p1.y,p2.y)) {
      if (p.y <= MAX(p1.y,p2.y)) {
        if (p.x <= MAX(p1.x,p2.x)) {
          if (p1.y != p2.y) {
            xinters = (p.y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x;
            if (p1.x == p2.x || p.x <= xinters)
              counter++;
          }
        }
      }
    }
    p1 = p2;
  }

  if (counter % 2 == 0)
    return(OUTSIDE);
  else
    return(INSIDE);
}

void printpruningresultintofile(vector<Point>& points , string filename)
{
     ofstream offile;
    offile.open(filename,ios::trunc);
    for(int i = 0 ; i<points.size() ; i++)
    {
      offile<<points[i].x<<endl;
      offile<<points[i].y<<endl;
    }

    offile.close(); 
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
    for (int i = 0; i < n; i++)
    {

        if (points[i].x + points[i].y > a.x + a.y)
        {

            a = points[i];
        }
        if (points[i].x + points[i].y < b.x + b.y)
        {

            b = points[i];
        }
        if (points[i].x - points[i].y < c.x - c.y)
        {

            c = points[i];
        }
        if (points[i].x - points[i].y > d.x - d.y)
        {

            d = points[i];
        }
    }

    // cout << "1" << a.x << " " << a.y << endl;
    // cout << b.x << " " << b.y << endl;
    // cout << c.x << " " << c.y << endl;
    // cout << d.x << " " << d.y << endl;

    Point quad[] = {b,d,a,c};

    // ofstream offile;
    // offile.open("output.txt",ios::trunc);
    // offile<<b.x<<endl;
    // offile<<b.y<<endl;
    // offile<<d.x<<endl;
    // offile<<d.y<<endl;
    // offile<<a.x<<endl;
    // offile<<a.y<<endl;

    // offile<<c.x<<endl;
    // offile<<c.y<<endl;

    // offile.close(); 
    

    for (int i = 0; i < n; i++)
    {
        if (!InsidePolygon( quad , 4, points[i]))

        {
            prune[i] = true;
            //cout << "Is inside :" << points[i].x << " " << points[i].y << endl;
        }
        // else
        // {
        //     cout << "Is outside :" << points[i].x << " " << points[i].y << endl;
        // }
    }

    for (int i = 0; i < points.size(); i++)
    {
        if (prune[i] == false)
            results.push_back(points[i]);
    }
    results.push_back(a);
    results.push_back(b);
    results.push_back(c);
    results.push_back(d);
    return results;
}

  Point left_most (vector<Point>& points) {
        Point res;
        int l_m = INT_MAX;
        for (auto & p : points) {
            if (p.x < l_m) {
                l_m = p.x;
                res = p;
            }
        }
        return res;
    }
    bool visited(Point& l, vector<Point>& res) {
        for (auto & p : res) {
            if (p.x == l.x && p.y == l.y) return true;
        }
        return false;
    }
    double direction(Point & a, Point & b, Point & c) {
        Point ab (b.x - a.x, b.y - a.y);
        Point bc (c.x - b.x, c.y - b.y);
        return ab.x * bc.y - ab.y * bc.x;
    }
    bool inbetween(Point& a, Point & b, Point & c) {
        return (b.x >= a.x && b.x <= c.x || b.x >= c.x && b.x <= a.x) && (b.y >= a.y && b.y <= c.y || b.y >= c.y && b.y <= a.y);
    }

vector<Point> findconvexhull(vector<Point>& points) {
        if (points.size() <= 3) return points;
        vector<Point> res;
        res.push_back(left_most(points));
        Point pre = res[0], next;
        while (1) {
            next = pre;
            for (auto & p : points) {
                if (p.x == pre.x && p.y == pre.y) continue;
                double cur = direction(pre, p, next);
                if (cur == 0) {
                    if (next.x == pre.x && next.y == pre.y) next = p;
                    else if (inbetween(pre, p, next) || (visited(next, res) && next.x != res[0].x && next.y != res[0].y)) next = p;
                }
                else if (cur > 0) next = p;
            }
            if (visited(next, res)) return res;
            res.push_back(next);
            pre = next;
        }
    }


    
int main()
{
    // int n;
    // cout << "Enter n:";
    // cin >> n;
    // vector<Point> points;
    // int max = 10000;
    // int min = -10000;
    // int x, y;
    // ofstream offile;
    // offile.open("inp.txt",ios::trunc);
    // offile << n << endl;
    // for (int i = 0; i < n; i++)
    // {
    //     int x = min + (rand() % static_cast<int>(max - min + 1));
    //     int y = min + (rand() % static_cast<int>(max - min + 1));
    //     offile<<x<<endl;
    //     offile<<y<<endl;
    //     cout << x << " " << y << endl;
    //     Point p = {x, y};
    //     points.push_back(p);
    // }
    // points = prunePoints(points);
    // for (int i = 0; i < points.size(); i++)
    // {
    //     cout << points[i].x << " " << points[i].y << endl;
    // }
    // cout << points.size();
    // printpruningresultintofile(points,"afterpruning.txt");
    // points = prunePoints(points);
    // printpruningresultintofile(points,"finalresult.txt");
    // cout<<points.size()<<endl;
    int arr[20] = {10,100,500,1000,2000,4000,8000,16000,32000,64000,128000,256000,512000,1024000};
    int n ;
    vector<Point> points;
    vector<Point> results;
    
    for(int i = 0 ; i< 14 ; i++)
    {
    n = arr[i];
    int max = 9*n;
    int min = -7*n;
    int x, y;
    for (int i = 0; i < n; i++)
    {
        int x = min + (rand() % static_cast<int>(max - min + 1));
        int y = min + (rand() % static_cast<int>(max - min + 1));
   
        Point p = {x, y};
        points.push_back(p);
    }
    auto start = high_resolution_clock::now();
    points = prunePoints(points);
    results = findconvexhull(points);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << " micro seconds :  "<<duration.count() << endl;
    ofstream offile;
    offile.open("jarvisresults_pruned.txt",ios::app);
    offile<<duration.count()<<endl;
    
    // for (int i = 0; i < points.size(); i++)
    // {
    //     cout << points[i].x << " " << points[i].y << endl;
    // }
    cout << points.size();
    points.clear();
    n = n*10;

    }

}