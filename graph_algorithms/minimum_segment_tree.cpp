#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

class minimumSegTree {
    int originalLength;
    vector<int> treeValues;
public:
    minimumSegTree(vector<int>& nums) {
        originalLength = getNearestTwopower(nums.size());
        treeValues = vector<int>(2 * originalLength, INT_MAX);
        
        for (int i = 0; i < nums.size(); ++i) {
            update(0, 0, originalLength-1, i, nums[i]);
        }
    }
    
    int getMin(int left, int right) {
        return getMin(0, 0, originalLength-1, left, right);
    }

    void update(int index, int value) {
        if (index < 0 && index >= originalLength) {
            throw runtime_error("Invalid Input");
        }

        update(0, 0, originalLength-1, index, value);
    }
    
private:
    int getMin(int root, int left, int right, int nl, int nr) {
        if (nr < left || nl > right) {
            return INT_MAX;
        }
        
        if (left>=nl && right <= nr) {
            return treeValues[root];
        }
        
        int mid = (left+right)/2;
        
        return min(getMin(2*root+1, left, mid, nl, nr), getMin(2*root+2, mid+1, right, nl, nr));
    }
    
    void update(int root, int left, int right, int index, int value) {
        if (left == right) {
            treeValues[root] = value;
            return;
        }
        
        int mid = (left+right)/2;
        
        if (index <= mid) {
            update(2*root+1, left, mid, index, value);
        } else {
            update(2*root+2, mid+1, right, index, value);
        }
        
        treeValues[root] = min(treeValues[2*root+1], treeValues[2*root+2]);
    }
    
    int getNearestTwopower(int num) {
        int x = 1;
        while (x < num) {
            x <<=1;
        }
        return x;
    }
};

int main() {
    vector<int> values = {1,4,3,7,4,5};

    auto segTree = minimumSegTree(values);

    cout << segTree.getMin(0, 3) << endl;
    cout <<segTree.getMin(1, 5) << endl;
    cout <<segTree.getMin(4, 4) << endl;
    
    segTree.update(0, 10);
    
    cout <<segTree.getMin(0, 4) << endl;
    cout <<segTree.getMin(7, 7) << endl;
    return 0;
}