//���鼯ʵ��
#pragma once
class Union_Set {
   private:
    int* pre;   //�洢ÿ������ǰ�����
    int* rank;  //���ĸ߶�
    int n;      //Ԫ�ظ���
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
    void init(int n)  //��ʼ����������¼��� n�������г�ʼ��
    {
        for (int i = 0; i < n; i++) {
            pre[i] = i;   //ÿ�������ϼ������Լ�
            rank[i] = 1;  //ÿ����㹹�ɵ����ĸ߶�Ϊ 1
        }
    }
    int _find(int x)  //���ҽ�� x�ĸ����
    {
        if (pre[x] == x)
            return x;         //�ݹ���ڣ�x���ϼ�Ϊ x������ xΪ�����
        return find(pre[x]);  //�ݹ����
    }

    int find(int x)  //�Ľ������㷨�����·��ѹ������ x���ϼ�ֱ�ӱ�Ϊ����㣬��ô���ĸ߶Ⱦͻ��󽵵�
    {
        if (pre[x] == x)
            return x;                  //�ݹ���ڣ�x���ϼ�Ϊ x������ xΪ�����
        return pre[x] = find(pre[x]);  //�˴����൱�����ҵ������ rootx��Ȼ�� pre[x]=rootx
    }

    bool isSame(int x, int y)  //�ж���������Ƿ���ͨ
    {
        return find(x) == find(y);  //�ж��������ĸ���㣨������Ԫ���Ƿ���ͬ
    }

    bool join(int x, int y) {
        x = find(x);  //Ѱ�� x�Ĵ���Ԫ
        y = find(y);  //Ѱ�� y�Ĵ���Ԫ
        if (x == y)
            return false;  //��� x�� y�Ĵ���Ԫһ�£�˵�����ǹ���ͬһ���ϣ�����Ҫ�ϲ������� false����ʾ�ϲ�ʧ�ܣ�����ִ��������߼�
        if (rank[x] > rank[y])
            pre[y] = x;  //��� x�ĸ߶ȴ��� y������ y���ϼ�Ϊ x
        else             //����
        {
            if (rank[x] == rank[y])
                rank[y]++;  //��� x�ĸ߶Ⱥ� y�ĸ߶���ͬ������ y�ĸ߶ȼ�1
            pre[x] = y;     //�� x���ϼ�Ϊ y
        }
        return true;  //���� true����ʾ�ϲ��ɹ�
    }

    void print() {
        cout << "----------------Print----------------" << endl;
        for (int i = 0; i < n; i++) {
            cout << dec;
            cout << "Point:" << setw(4) << i << " ";
            cout << "Pre  :" << setw(4) << pre[i] << " ";
            cout << "Rank :" << setw(4) << rank[i] << "����";
            if (i % 10 == 9)
                cout << endl;
        }
        cout << endl;
    }
};