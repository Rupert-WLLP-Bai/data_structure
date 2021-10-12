//并查集实现
#pragma once
class Union_Set {
   private:
    int* pre;   //存储每个结点的前驱结点
    int* rank;  //树的高度
    int n;      //元素个数
   public:
    Union_Set(int N) {
        n = N;
        pre = new int[N];
        rank = new int[N];
        init(N);
    };
    ~Union_Set() {
        delete[] rank;
        delete[] pre;
    };
    void init(int n)  //初始化函数，对录入的 n个结点进行初始化
    {
        for (int i = 0; i < n; i++) {
            pre[i] = i;   //每个结点的上级都是自己
            rank[i] = 1;  //每个结点构成的树的高度为 1
        }
    }
    int _find(int x)  //查找结点 x的根结点
    {
        if (pre[x] == x)
            return x;         //递归出口：x的上级为 x本身，则 x为根结点
        return find(pre[x]);  //递归查找
    }

    int find(int x)  //改进查找算法：完成路径压缩，将 x的上级直接变为根结点，那么树的高度就会大大降低
    {
        if (pre[x] == x)
            return x;                  //递归出口：x的上级为 x本身，即 x为根结点
        return pre[x] = find(pre[x]);  //此代码相当于先找到根结点 rootx，然后 pre[x]=rootx
    }

    bool isSame(int x, int y)  //判断两个结点是否连通
    {
        return find(x) == find(y);  //判断两个结点的根结点（即代表元）是否相同
    }

    bool join(int x, int y) {
        x = find(x);  //寻找 x的代表元
        y = find(y);  //寻找 y的代表元
        if (x == y)
            return false;  //如果 x和 y的代表元一致，说明他们共属同一集合，则不需要合并，返回 false，表示合并失败；否则，执行下面的逻辑
        if (rank[x] > rank[y])
            pre[y] = x;  //如果 x的高度大于 y，则令 y的上级为 x
        else             //否则
        {
            if (rank[x] == rank[y])
                rank[y]++;  //如果 x的高度和 y的高度相同，则令 y的高度加1
            pre[x] = y;     //让 x的上级为 y
        }
        return true;  //返回 true，表示合并成功
    }

    void print() {
        cout << "----------------Print----------------" << endl;
        for (int i = 0; i < n; i++) {
            cout << dec;
            cout << "Point:" << setw(4) << i << " ";
            cout << "Pre  :" << setw(4) << pre[i] << " ";
            cout << "Rank :" << setw(4) << rank[i] << "██";
            if (i % 10 == 9)
                cout << endl;
        }
        cout << endl;
    }
};