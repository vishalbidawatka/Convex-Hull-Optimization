#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;
struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};
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
    printpruningresultintofile(points,"afterpruning.txt");
    auto start = high_resolution_clock::now();
    points = findconvexhull(points);
    auto stop = high_resolution_clock::now();
    printpruningresultintofile(points,"finalresult.txt");
    auto duration = duration_cast<microseconds>(stop - start);
    cout << " micro seconds :  "<<duration.count() << "n :"<<n<< endl;
    ofstream offile;
    offile.open("quickhullresults.txt",ios::app);
    offile<<duration.count()<<endl;
    
    // for (int i = 0; i < points.size(); i++)
    // {
    //     cout << points[i].x << " " << points[i].y << endl;
    // }
    cout << points.size();
 

    }
   

}

