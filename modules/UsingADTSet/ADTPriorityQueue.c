///////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT Priority Queue μέσω ADTSet.
//
///////////////////////////////////////////////////////////

#include <stdlib.h>
#include <assert.h>

#include "ADTPriorityQueue.h"
#include "ADTSet.h"			// Η υλοποίηση του PriorityQueue χρησιμοποιεί Set

struct priority_queue{
    Set set;
    CompareFunc compare;
    DestroyFunc destroy_value;
};

struct priority_queue_node{
    Pointer value;
    
};

static PriorityQueueNode pqnode_create(Pointer value){
    PriorityQueueNode node = malloc(sizeof(*node));
    node->value = value;
   return node;
}

PriorityQueue pqueue_create(CompareFunc compare, DestroyFunc destroy_value, Vector values){
    assert(compare != NULL);

    PriorityQueue pqueue = malloc(sizeof(*pqueue));
    pqueue->compare = compare;
    pqueue->destroy_value = destroy_value;
    pqueue->set = set_create(compare,destroy_value);

    if(values!=NULL){
        int size = vector_size(values);
        for(int i=0; i<size; i++){
            set_insert(pqueue->set, vector_get_at(values, i));
        }
    }

    return pqueue;
}



int pqueue_size(PriorityQueue pqueue){
    return set_size(pqueue->set);
}


Pointer pqueue_max(PriorityQueue pqueue){
    return set_node_value(pqueue->set, set_last(pqueue->set));
}


PriorityQueueNode pqueue_insert(PriorityQueue pqueue, Pointer value){
   set_insert(pqueue->set, value);
   PriorityQueueNode node = pqnode_create(value);
   return node;
}


void pqueue_remove_max(PriorityQueue pqueue){
    if(pqueue != NULL){
        
    Pointer max = set_node_value(pqueue->set, set_last(pqueue->set));
    set_remove(pqueue->set, max);
    }
}

DestroyFunc pqueue_set_destroy_value(PriorityQueue pqueue, DestroyFunc destroy_value){
    DestroyFunc old = pqueue->destroy_value;
    pqueue->destroy_value = destroy_value;
    return old;
}


void pqueue_destroy(PriorityQueue pqueue){
    set_set_destroy_value(pqueue->set, pqueue->destroy_value);
    set_destroy(pqueue->set);
    free(pqueue);
}



//// Νέες συναρτήσεις για την εργασία 2 //////////////////////////////////////////

// Επιστρέφει το περιεχόμενο του κόμβου node

Pointer pqueue_node_value(PriorityQueue set, PriorityQueueNode node){
    return node->value;
}

// Αφαιρεί τον κόμβο node ο οποίος μπορεί να βρίσκεται σε οποιαδήποτε θέση της ουράς
// (μη ορισμένη συμπεριφορά αν δεν ανήκει στην ουρά).

void pqueue_remove_node(PriorityQueue pqueue, PriorityQueueNode node){
    set_remove(pqueue->set, node->value);
        
        free(node);

}

//void pqueue_update_order(PriorityQueue pqueue, PriorityQueue node){
  //  Pointer value = node->value;
    //set_remove(pqueue->set, value);

//}
