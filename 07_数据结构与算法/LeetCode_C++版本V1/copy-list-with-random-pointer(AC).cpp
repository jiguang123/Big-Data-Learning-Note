// 1CE, 1RE, 2WA, 1AC, not easy~
#include <map>
using namespace std;
/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int n;
        
        if(nullptr == head){
            return nullptr;
        }
        
        n = 0;
        RandomListNode *ptr;
        
        mri.clear();
        mir.clear();
        
        ptr = head;
        while(ptr != nullptr){
            ++n;
            mri[ptr] = n;
            ptr = ptr->next;
        }
        
        RandomListNode *root = new RandomListNode(0), *tail;
        ptr = head;
        // 1CE here, undefined $i
        int i = 0;
        tail = root;
        while(ptr != nullptr){
            ++i;
            tail->next = new RandomListNode(ptr->label);
            tail = tail->next;
            mir[i] = tail;
            ptr = ptr->next;
        }
        
        RandomListNode *p1, *p2;
        
        p1 = head;
        p2 = root->next;
        while(p1 != nullptr){
            // 1RE here, mapping using nullptr doesn't work
            if(p1->random != nullptr){
                p2->random = mir[mri[p1->random]];
            }
            p1 = p1->next;
            // 2WA here, forgot to move $p2 forward
            p2 = p2->next;
        }
        
        head = root->next;
        delete root;
        mir.clear();
        mri.clear();
        
        return head;
    }
private:
    map<RandomListNode *, int> mri;
    map<int, RandomListNode *> mir;
};