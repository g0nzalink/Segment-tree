#include <iostream>
#include <vector>
using namespace std;

class segment_tree {
    vector<int> tree;
    int size_og = 1, size = 1;

    void build(const vector<int>& nums, int idx, int lx, int rx) {
        if(lx == rx) {
            tree[idx] = nums[lx];
            return;
        }
        int mid = (lx + rx)/2;
        build(nums, idx*2 + 1, lx, mid);
        build(nums, idx*2 + 2, mid + 1, rx);
        tree[idx] = tree[idx*2 + 1] + tree[idx*2+2];
    }

    int query(int l, int r, int idx, int lx, int rx) {
        if(rx < l || r < lx){return 0;}
        if(l <= lx && rx <= r){return tree[idx];}
        int mid = (lx + rx)/2;
        int left = query(l, r, idx*2 + 1, lx, mid);
        int right = query(l, r, idx*2 + 2, mid + 1, rx);
        return left+right;
    }

    void update(int pos, int val, int idx, int lx, int rx) {
        if(lx == rx){tree[idx] = val;}
        else {
            int mid = (lx + rx)/2;
            if(pos <= mid){update(pos, val, idx*2 + 1, lx, mid);}
            else {update(pos, val, idx*2 + 2, mid + 1, rx);}
            tree[idx] = tree[idx*2 + 1] + tree[idx*2 + 2];
        }
    }

public:
    //construccion
    explicit segment_tree(const vector<int>& nums) {
        size_og = nums.size();
        while (size < nums.size()) size *= 2;
        tree.resize(2*size - 1, 0);
        build(nums, 0, 0, size_og - 1);
    }

    //consulta
    int query(int l, int r) {
        return query(l, r, 0, 0, size_og - 1);
    }

    //actualizacion
    void update(int pos, int val) {
        update(pos, val, 0, 0, size_og - 1);
    }

    //eliminacion
    void eliminate(int pos) {
        update(pos, 0, 0, 0, size_og - 1);
    }

    void print() {
        for(int i = 0; i <= tree.size() - 1; i++) {
            cout<< i + 1 << ": " << tree[i] <<"\n";
        }
    }
};


int main() {
    //casos de prueba

    vector<int> nums = {1, 6, 4, 7, 2, 8};

    segment_tree t(nums);

    cout<<"segment tree construido: "<<"\n";

    t.print();

    cout<<"\n";
    cout<<"consulta en el rango [3,5]: "<<"\n";

    cout<< t.query(3, 5) << "\n";

    cout<<"\n";
    cout<<"actualizar dato de la posicion [0] a 10: "<<"\n";

    t.update(0, 10);

    t.print();

    cout<<"\n";
    cout<<"eliminar dato de la posicion [0]: "<<"\n";

    t.eliminate(0);

    t.print();

    return 0;
}