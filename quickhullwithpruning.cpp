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
vector<Point> ret;
 static bool mycmp(Point &a, Point &b) {
        return a.x < b.x;
    }
    
    int testSide(Point &a, Point &b, Point &c) {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }
    
    double distPointLine(Point &A, Point &B, Point &C) {
        int a = B.y - A.y, b = B.x - A.x;
        return abs((a*C.x - b*C.y + B.x*A.y - B.y*A.x)/sqrt(a*a + b*b));
    }
    
    void FindHull(vector<Point> &points, Point &A, Point &B) {
        if (points.empty())
            return;
        
        int idx = 0;
        double dist = distPointLine(A, B, points[0]);
        for (int i=1; i<points.size(); i++) {
            if (distPointLine(A, B, points[i]) > dist) {
                dist = distPointLine(A, B, points[i]);
                idx = i;
            }
        }
        ret.push_back(points[idx]);
        
        vector<Point> R, T;
        for (int i=0; i<points.size(); i++) {
            if (i != idx) {
                int tmp = testSide(A, points[idx], points[i]);
                if (tmp >= 0)
                    R.push_back(points[i]);
                else {
                    tmp = testSide(points[idx], B, points[i]);
                    if (tmp >= 0)
                        T.push_back(points[i]);
                }
            }
        }
        FindHull(R, A, points[idx]);
        FindHull(T, points[idx], B);
        
        return;
    }
    

    
    vector<Point> findconvexhull(vector<Point>& points) {
        // find the convex hull; use QuickHull algorithm
        if (points.size() <= 1)
            return points;
        
        // find the left most and right most two points
        sort(points.begin(), points.end(), mycmp);
        ret.push_back(points[0]);
        ret.push_back(points.back());
        
        // test whether a point on the left side right side or on the line
        vector<Point> Left, Right, Online;
        for (int i=1; i<points.size()-1; i++) {
            int tmp = testSide(points[0], points.back(), points[i]);
            if (tmp < 0)
                Right.push_back(points[i]);
            else if (tmp > 0)
                Left.push_back(points[i]);
            else
                Online.push_back(points[i]);
        }
        // if Upper or Down is empty, Online should be pushed into ret
        if (Left.empty() || Right.empty())
            for (int i=0; i<Online.size(); i++)
                ret.push_back(Online[i]);

        FindHull(Left, points[0], points.back());
        FindHull(Right, points.back(), points[0]);
        
        return ret;
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
    offile.open("quickhullresults_pruned.txt",ios::app);
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