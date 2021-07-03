#include <bits/stdc++.h>

using namespace std;

#include <bits/stdc++.h>

using namespace std;
const int N = 3e4+10;

struct Node{
    int l , r ;
    int lsum , rsum , sum;    //区间最大前缀和，后缀和，区间和
    int tsum ;                 //区间最大子串和
}st[4*N];


void pushup(Node &u , Node &l , Node &r){
    //父节点的sum = 左子树的sum + 右子树的sum
    u.sum = l.sum + r.sum;   
    //父节点的最大前缀和 = max(左子树的前缀和 , 左子树的sum+右子树的lsum)
    u.lsum = max(l.lsum , l.sum+r.lsum);  
    //同理
    u.rsum = max(r.rsum , r.sum+l.rsum);
    //父节点是子序和 = 左边的 与 右边的 与 中间的取一个最大值
    u.tsum = max(max(l.tsum , r.tsum),l.rsum+r.lsum);
}

void pushup(int u){
    pushup( st[u] , st[u<<1] , st[u<<1|1] );
}

void build(int l  , int r , int u , vector<int> nums){
    if(l==r) st[u] = {l,r,nums[l-1],nums[l-1],nums[l-1],nums[l-1]};
    else {
        st[u] = {l,r};
        int mid = l+r>>1;
        build(l,mid,u<<1,nums);
        build(mid+1,r,u<<1|1,nums);
        pushup(u);
    }
}

Node query(int u , int l , int r){
    if(st[u].l >= l && st[u].r <= r) return st[u];
    else {
        int mid = st[u].l + st[u].r  >> 1;
        if(r<= mid) return query(u<<1 , l , r);     // 全部在左
        else if (l > mid) return query(u << 1|1, l, r);  //全部在右
        else {      //中间
            auto left = query(u << 1, l, r);
            auto right = query(u << 1|1, l, r);
            Node res;
            pushup(res, left, right);
            return res;
        }
    }
}

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        build(1,nums.size(),1,nums);   //建树
        return query(1,1,nums.size()).tsum;   //查询最大子序和
    }
};


/*
给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

 

示例 1：

输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
输出：6
解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。
示例 2：

输入：nums = [1]
输出：1
示例 3：

输入：nums = [0]
输出：0
示例 4：

输入：nums = [-1]
输出：-1
示例 5：

输入：nums = [-100000]
输出：-100000
 

提示：

1 <= nums.length <= 3 * 104
-105 <= nums[i] <= 105
 

进阶：如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的 分治法 求解。


*/
