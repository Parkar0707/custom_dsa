#include <iostream> 
#include <vector>
using namespace std;

struct Interval {
    int start; 
    int end; 
    
    Interval(int s, int e): start(s), end(e){};
};

void sortIntervals(vector<Interval> &intervals){
    for(int i=0; i<intervals.size(); i++){
        for(int j=0; j<intervals.size()-i-1; j++){
            if(intervals[j].start > intervals[j+1].start){
                Interval temp = intervals[j]; 
                intervals[j] = intervals[j+1]; 
                intervals[j+1] = temp; 
            }
        }
    }
}

vector<Interval> findCollisons(vector<Interval> intervals){
    vector<Interval> collisonIntervals; 
    
    for(int i=0; i<intervals.size() - 1; i++){
        if(intervals[i].end > intervals[i+1].start){ 
            Interval collison = Interval(intervals[i+1].start, intervals[i].end);
            collisonIntervals.push_back(collison);
        }
    } 
    
    return collisonIntervals;
}

int main() { 
    
    vector<Interval> intervals = {{1, 4}, {3, 6}, {5, 7}, {8, 10}}; 
    
    sortIntervals(intervals); 
    
    vector<Interval> collisonIntervals = findCollisons(intervals); 
    
    for(Interval &interval: collisonIntervals){
        cout<<"{"<<interval.start<<", "<<interval.end<<"}"<<"\n";
    }

    return 0;
}
