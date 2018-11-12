#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;
struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};
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
int main()
{   
    int arr[20] = {10,100,500,1000,2000,4000,8000,16000,32000,64000,128000,256000,512000,1024000};
    int n ;
    for(int i = 0 ; i< 14 ; i++)
    {
    n = arr[i];
    vector<Point> points;
    int max = 9*n;
    int min = -7*n;
    int x, y;
    for (int i = 0; i < n; i++)
    {
        int x = min + (rand() % static_cast<int>(max - min + 1));
        int y = min + (rand() % static_cast<int>(max - min + 1));
       // cout << x << " " << y << endl;
        Point p = {x, y};
        points.push_back(p);
    }
   // printpruningresultintofile(points,"afterpruning.txt");
    auto start = high_resolution_clock::now();
    points = findconvexhull(points);
    auto stop = high_resolution_clock::now();
   // printpruningresultintofile(points,"finalresult.txt");
    auto duration = duration_cast<microseconds>(stop - start);
    cout << " micro seconds :  "<<duration.count() << "n :"<<n<< endl;
    ofstream offile;
    offile.open("jarvisresults.txt",ios::app);
    offile<<duration.count()<<endl;
    
    // for (int i = 0; i < points.size(); i++)
    // {
    //     cout << points[i].x << " " << points[i].y << endl;
    // }
    cout << points.size();
    n = n*10;

    }

}
