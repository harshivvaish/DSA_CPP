/**
 * Definition for singly-linked list.
 * struct ListNode {
 * int val;
 * ListNode *next;
 * ListNode() : val(0), next(nullptr) {}
 * ListNode(x) : val(x), next(nullptr) {}
 * ListNode(x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // Create a dummy node to easily construct and return the head of the new list
        ListNode* dummyHead = new ListNode(0);
        ListNode* current = dummyHead;
        int carry = 0;
        
        // Loop while there are nodes to process in either list OR a carry remains
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            // Extract values, default to 0 if the list has already ended
            int val1 = (l1 != nullptr) ? l1->val : 0;
            int val2 = (l2 != nullptr) ? l2->val : 0;
            
            // Calculate the sum of current digits and the carry
            int sum = val1 + val2 + carry;
            carry = sum / 10;          // Calculate new carry
            int outVal = sum % 10;      // Calculate value for the new node
            
            // Create the new node and advance the current pointer
            current->next = new ListNode(outVal);
            current = current->next;
            
            // Move to the next nodes in the input lists if they exist
            if (l1 != nullptr) l1 = l1->next;
            if (l2 != nullptr) l2 = l2->next;
        }
        
        // The actual head is next to the dummy head
        ListNode* result = dummyHead->next;
        delete dummyHead; // Free the temporary dummy memory to prevent leaks
        return result;
    }
};