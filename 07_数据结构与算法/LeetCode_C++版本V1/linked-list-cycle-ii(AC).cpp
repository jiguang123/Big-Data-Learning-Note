// 1CE, 2TLE, 1AC, foolish mistake..
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        if(head == nullptr){
            return nullptr;
        }
        
        ListNode *ptr, *res;
        
        res = head;
        while(res != nullptr){
            ptr = head;
            // Forgot to check nullptr, added by the way later.
            while(ptr != res->next && ptr != nullptr){
                if(ptr == res){
                    // ptr reaches res first, not what we expect
                    break;
                }
                // 1TLE here, forgot to move forward...
                // 1CE here, ';' is missing!!!!
                ptr = ptr->next;
            }
            if(ptr == res->next){
                // $ptr reaches res->next first, that means $res->next is the start of the loop
                // while $res is the end of the loop, thus $ptr = $res->next is the result we want
                return ptr;
            }else{
                // 1TLE here, forgot to move forward..
                res = res->next;
            }
        }
        
        return nullptr;
    }
};