#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 定义四叉树节点
struct QuadtreeNode {
    float x_min, x_max, y_min, y_max; // 当前节点的区域边界
    pair<float, float> point;         // 节点包含的点（如果是叶子节点）
    QuadtreeNode* children[4];        // 四个子节点，分别对应左下、左上、右下、右上
    bool isLeaf;                      // 是否为叶子节点

    // 构造函数初始化
    QuadtreeNode(float x_min, float x_max, float y_min, float y_max)
        : x_min(x_min), x_max(x_max), y_min(y_min), y_max(y_max), isLeaf(true) {
        point = {-1, -1}; // 初始没有点
        fill(begin(children), end(children), nullptr); // 子节点指针初始化为空
    }

    // 分裂当前节点
    void split() {
        float xm = (x_min + x_max) / 2;
        float ym = (y_min + y_max) / 2;
        
        // 创建四个子节点
        children[0] = new QuadtreeNode(x_min, xm, y_min, ym); // 左下
        children[1] = new QuadtreeNode(x_min, xm, ym, y_max); // 左上
        children[2] = new QuadtreeNode(xm, x_max, y_min, ym); // 右下
        children[3] = new QuadtreeNode(xm, x_max, ym, y_max); // 右上
        isLeaf = false;
    }

    // 判断点是否在当前区域内
    bool contains(float x, float y) {
        return x >= x_min && x <= x_max && y >= y_min && y <= y_max;
    }
};

// 四叉树类
class Quadtree {
public:
    QuadtreeNode* root;

    // 构造函数初始化四叉树的根节点
    Quadtree() {
        root = new QuadtreeNode(0, 10, 0, 10); // 空间范围是 [0, 10] x [0, 10]
    }

    // 插入一个点到四叉树
    void insert(float x, float y) {
        insert(root, x, y);
    }

    // 层序遍历四叉树
    void levelOrder() {
        queue<QuadtreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            QuadtreeNode* node = q.front();
            q.pop();
            
            if (node->isLeaf) {
                // 输出叶子节点的点
                if (node->point.first != -1) {
                    cout << node->point.first << " " << node->point.second << endl;
                }
            } else {
                // 非叶子节点，加入其子节点到队列
                for (int i = 0; i < 4; ++i) {
                    if (node->children[i]) {
                        q.push(node->children[i]);
                    }
                }
            }
        }
    }

private:
    // 插入一个点到四叉树的递归函数
    void insert(QuadtreeNode* node, float x, float y) {
        if (!node->contains(x, y)) return; // 如果点不在当前区域内，返回
        
        if (node->isLeaf) {
            if (node->point.first == -1) {
                node->point = {x, y}; // 如果是叶节点且没有点，直接插入
            } else {
                node->split(); // 分裂节点
                insert(node, node->point.first, node->point.second); // 将原来的点重新插入
                node->point = {-1, -1}; // 清空当前节点的点
                insert(node, x, y); // 插入新的点
            }
        } else {
            for (int i = 0; i < 4; ++i) {
                insert(node->children[i], x, y); // 插入到子节点
            }
        }
    }
};

// 主函数
int main() {
    int K;
    cin >> K;
    
    Quadtree qt;

    // 输入K个点，并插入到四叉树中
    for (int i = 0; i < K; ++i) {
        float x, y;
        cin >> x >> y;
        qt.insert(x, y);
    }

    // 输出四叉树的层序遍历结果
    qt.levelOrder();

    return 0;
}