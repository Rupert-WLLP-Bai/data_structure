//Trie树
//使用字典树存储英文单词，使用的结构是26叉字典树。不区分单词的大小写
#pragma once
#include <cstring>
#include <iostream>

/* trie的节点类型 */
template <int Size>  //Size为字符表的大小
struct trie_node {
    int freq;                //当前节点是否可以作为字符串的结尾,如果是freq>0,如果存在重复单词，freq表示该单词的词频
    int node;                //子节点的个数
    trie_node* child[Size];  //指向子节点指针

    /* 构造函数 */
    trie_node()
        : freq(0), node(0) { memset(child, 0, sizeof(child)); }
};

/* trie */
template <int Size, typename Index>  //Size为字符表的大小，Index为字符表的哈希函数
class trie {
   public:
    /* 定义类型别名 */
    typedef trie_node<Size> node_type;
    typedef trie_node<Size>* link_type;

    /* 构造函数 */
    trie(Index i = Index())
        : index(i) {}

    /* 析构函数 */
    ~trie() { clear(); }

    /* 清空 */
    void clear() {
        clear_node(root);
        for (int i = 0; i < Size; ++i)
            root.child[i] = 0;
    }

    /* 插入字符串 */
    template <typename Iterator>
    void insert(Iterator begin, Iterator end) {
        link_type cur = &root;  //当前节点设置为根节点
        for (; begin != end; ++begin) {
            if (!cur->child[index[*begin]])  //若当前字符找不到匹配，则新建节点
            {
                cur->child[index[*begin]] = new node_type;
                ++cur->node;  //当前节点的子节点数加一
            }
            cur = cur->child[index[*begin]];  //将当前节点设置为当前字符对应的子节点
        }
        (cur->freq)++;  //设置存放最后一个字符的节点的可终止标志为真
    }

    /* 插入字符串，针对C风格字符串的重载版本 */
    void insert(const char* str) {
        insert(str, str + strlen(str));
    }

    /* 查找字符串，算法和插入类似 */
    template <typename Iterator>
    int getfreq(Iterator begin, Iterator end) {
        link_type cur = &root;
        for (; begin != end; ++begin) {
            if (!cur->child[index[*begin]])
                return false;
            cur = cur->child[index[*begin]];
        }
        return cur->freq;
    }

    /* 查找字符串，针对C风格字符串的重载版本 */
    bool find(const char* str) {
        int freq = getfreq(str, str + strlen(str));
        return freq > 0;
    }

    /* 查找字符串str的词频*/
    int getfreq(const char* str) {
        return getfreq(str, str + strlen(str));
    }

    /* 删除字符串 */
    template <typename Iterator>
    bool erase(Iterator begin, Iterator end) {
        bool result;  //用于存放搜索结果
        erase_node(begin, end, root, result);
        return result;
    }

    /* 删除字符串，针对C风格字符串的重载版本 */
    bool erase(const char* str) {
        return erase(str, str + strlen(str));
    }

    /* 按字典序遍历单词树的所有单词 */
    template <typename Functor>
    void traverse(Functor execute = Functor()) {
        char word[100] = {0};
        traverse_node(root, execute, word, 0);
    }

    /*输出字典树单词的总个数，包含重复字符串*/
    int sizeAll() {
        sizeAll(root);
    }

    int sizeAll(node_type& cur) {
        int size = cur.freq;
        for (int i = 0; i < Size; ++i) {
            if (cur.child[i] == 0)
                continue;
            size += sizeAll(*cur.child[i]);
        }
        return size;
    }

    /*输出字典树单词的总个数，重复字符串按一个处理*/
    int sizeNoneRedundant() {
        sizeNoneRedundant(root);
    }

    int sizeNoneRedundant(node_type& cur) {
        int size = cur.freq > 0 ? 1 : 0;
        for (int i = 0; i < Size; ++i) {
            if (cur.child[i] == 0)
                continue;
            size += sizeNoneRedundant(*cur.child[i]);
        }
        return size;
    }

    /*求字符串最长的公共前缀的长度*/
    int maxPrefix_length() {
        int length = maxPrefix_length(root);
        return length - 1;  //因为length包含了根节点，需要删除。
    }

    int maxPrefix_length(node_type& cur) {
        int length = 0;
        for (int i = 0; i < Size; ++i) {
            if (cur.child[i] != 0) {
                int tmp = maxPrefix_length(*cur.child[i]);
                if (tmp > length) {
                    length = tmp;
                }
            }
        }
        if (length > 0 || cur.node > 1 || cur.freq > 0 && cur.node > 0)  //cur.node >1 处理"abcde"与"abcdf"这种情况；cur.freq>0 && cur.node>0处理"abcde"与"abcdef"这种情况
        {
            length++;
        }
        return length;
    }
    /*求字符串最长的最共前缀*/
    void maxPrefix(std::string& prefix) {
        maxPrefix(root, prefix);
        std::string word(prefix);
        int size = word.size();
        for (int i = 0; i < size; ++i)
            prefix[i] = word[size - 1 - i];
        prefix.erase(size - 1);  //因为prefix包含了根节点字符，需要把它删除。
    }

    void maxPrefix(node_type& cur, std::string& prefix) {
        std::string word;
        int length = 0;
        int k = 0;
        for (int i = 0; i < Size; ++i) {
            if (cur.child[i] != 0) {
                maxPrefix(*cur.child[i], word);
                if (word.size() > length) {
                    length = word.size();
                    prefix.swap(word);
                    k = i;
                }
            }
        }
        if (length > 0 || cur.node > 1 || cur.freq > 0 && cur.node > 0)  //cur.node >1 处理"abcde"与"abcdf"这种情况；cur.freq>0 && cur.node>0处理"abcde"与"abcdef"这种情况
        {
            prefix.push_back(k + 'a');
        }
    }

   private:
    template <typename Functor>
    void traverse_node(node_type& cur, Functor execute, char* word, int index) {
        if (cur.freq) {
            std::string str = word;
            execute(str, cur.freq);
        }
        for (int i = 0; i < Size; ++i) {
            if (cur.child[i] != 0) {
                word[index++] = 'a' + i;
                traverse_node(*cur.child[i], execute, word, index);
                word[index] = 0;
                index--;
            }
        }
    }

    /* 清除某个节点的所有子节点 */
    void clear_node(node_type& cur) {
        for (int i = 0; i < Size; ++i) {
            if (cur.child[i] == 0)
                continue;
            clear_node(*cur.child[i]);
            delete cur.child[i];
            cur.child[i] = 0;
            if (--cur.node == 0)
                break;
        }
    }

    /* 边搜索边删除冗余节点，返回值用于向其父节点声明是否该删除该节点 */
    template <typename Iterator>
    bool erase_node(Iterator begin, Iterator end, node_type& cur, bool& result) {
        if (begin == end)  //当到达字符串结尾：递归的终止条件
        {
            result = (cur.freq > 0);  //如果当前节点的频率>0,则当前节点可以作为终止字符，那么结果为真
            if (cur.freq)
                cur.freq--;                         //如果当前节点为终止字符，词频减一
            return cur.freq == 0 && cur.node == 0;  //若该节点为树叶，那么通知其父节点删除它
        }
        //当无法匹配当前字符时，将结果设为假并返回假，即通知其父节点不要删除它
        if (cur.child[index[*begin]] == 0)
            return result = false;
        //判断是否应该删除该子节点
        else if (erase_node((++begin)--, end, *(cur.child[index[*begin]]), result)) {
            delete cur.child[index[*begin]];  //删除该子节点
            cur.child[index[*begin]] = 0;     //子节点数减一
            //若当前节点为树叶，那么通知其父节点删除它
            if (--cur.node == 0 && cur.freq == 0)
                return true;
        }
        return false;  //其他情况都返回假
    }

    /* 根节点 */
    node_type root;

    /* 将字符转换为索引的转换表或函数对象 */
    Index index;
};

//index function object
class IndexClass {
   public:
    int operator[](const char key) {
        if (key >= 'a' && key <= 'z')
            return key - 'a';
        else if (key >= 'A' && key <= 'Z')
            return key - 'A';
    }
};

class StringExe {
   public:
    void operator()(std::string& str, int freq) {
        std::cout << str << ":" << freq << std::endl;
    }
};
/*
void test() {
    trie<26, IndexClass> t;
    t.insert("tree");
    t.insert("tree");
    t.insert("tea");
    t.insert("A");
    t.insert("BABCDEGG");
    t.insert("BABCDEFG");

    t.traverse<StringExe>();

    int sizeall = t.sizeAll();
    std::cout << "sizeAll:" << sizeall << std::endl;

    int size = t.sizeNoneRedundant();
    std::cout << "size:" << size << std::endl;

    std::string prefix;
    int deep = t.maxPrefix_length();
    t.maxPrefix(prefix);
    std::cout << "deep:" << deep << " prefix:" << prefix << std::endl;

    if (t.find("tree"))
        std::cout << "find tree" << std::endl;
    else
        std::cout << "not find tree" << std::endl;

    int freq = t.getfreq("tree");
    std::cout << "tree freq:" << freq << std::endl;

    if (t.erase("tree"))
        std::cout << "delete tree" << std::endl;
    else
        std::cout << "not find tree" << std::endl;

    freq = t.getfreq("tree");
    std::cout << "tree freq:" << freq << std::endl;

    if (t.erase("tree"))
        std::cout << "delete tree" << std::endl;
    else
        std::cout << "not find tree" << std::endl;

    if (t.erase("tree"))
        std::cout << "delete tree" << std::endl;
    else
        std::cout << "not find tree" << std::endl;

    sizeall = t.sizeAll();
    std::cout << "sizeAll:" << sizeall << std::endl;

    size = t.sizeNoneRedundant();
    std::cout << "size:" << size << std::endl;

    if (t.find("tre"))
        std::cout << "find tre" << std::endl;
    else
        std::cout << "not find tre" << std::endl;

    t.traverse<StringExe>();

    return;
}
*/