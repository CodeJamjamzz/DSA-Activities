    void swap(node* node1, node* node2){
        node2->next->prev = node1;
        node1->prev->next = node2;

        node* temp = node1->next;
        node* temp2 = node2->prev;

        node2->prev = node1->prev;
        node1->next = node2->next;
        node1->prev = temp2;
        node2->next = temp;
        return;
    }