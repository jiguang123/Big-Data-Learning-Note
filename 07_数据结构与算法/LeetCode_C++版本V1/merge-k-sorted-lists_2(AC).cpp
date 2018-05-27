// 9CE, 1WA, 1AC, pointer can't be elements of priority_queue, might as well wrap it with a class.
// Seem so silly...
#include <queue>
using namespace std;
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class ListNodeSt{
public:
    ListNode *ptr;
    
    ListNodeSt(ListNode *_ptr = nullptr){
        ptr = _ptr;
    }
};

bool operator < (const ListNodeSt a, const ListNodeSt b) {
    return a.ptr->val > b.ptr->val;
}

class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int k;
        ListNode *root, *par, *tmp;
        ListNodeSt st;
        
        while(!pq.empty()){
            pq.pop();
        }
        k = lists.size();
        if(k <= 0){
            return nullptr;
        }
        
        
        int i;
        for(i = 0; i < k; ++i){
            if(lists[i] != nullptr){
                pq.push(ListNodeSt(lists[i]));
            }
        }
        root = nullptr;
        par = root;
        while(!pq.empty()){
            st = pq.top();
            tmp = st.ptr;
            pq.pop();
            if(par == nullptr){
                par = tmp;
                root = par;
            }else{
                par->next = tmp;
            }
            if(tmp->next != nullptr){
                pq.push(ListNodeSt(tmp->next));
            }
            tmp->next = nullptr;
            par = tmp;
        }
        
        return root;
    }
private:
    priority_queue<ListNodeSt> pq;
};