#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;
struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};
    bool isRightTurn(Point &a, Point &b, Point &c) {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) <= 0;
    }

 vector<Point> findconvexhull(vector<Point>& points) {
        if(points.size() < 3) return points;
        auto cmp = [](Point& a, Point& b) -> bool {
            return a.x < b.x || (a.x == b.x && a.y < b.y);
        };
        sort(points.begin(), points.end(), cmp);
        vector<Point> stack;
        stack.push_back(points[0]);
        stack.push_back(points[1]);
        //left to right;
        for(int i = 2; i < points.size(); ++i) {
            while(stack.size() > 1) {
                auto &t1 = stack.back();
                auto &t2 = stack[stack.size() - 2];
                if(isRightTurn(t2, t1, points[i])) break;
                else stack.pop_back();
            }
            stack.push_back(points[i]);
        }
        int n = stack.size();
        if(n == points.size()) return stack; //check if linear
        stack.push_back(points[points.size() - 2]);
        //right to left;
        for(int i = points.size() - 3; i >= 0; --i) {
            while(stack.size() > n) {
                auto &t1 = stack.back();
                auto &t2 = stack[stack.size() - 2];
                if(isRightTurn(t2, t1, points[i])) break;
                else stack.pop_back();
            }
            stack.push_back(points[i]);
        }
        stack.pop_back();
        return stack;
    }
    

int main()
{   
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
    results = findconvexhull(points);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << " micro seconds :  "<<duration.count() << endl;
    ofstream offile;
    offile.open("grahamresults.txt",ios::app);
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
