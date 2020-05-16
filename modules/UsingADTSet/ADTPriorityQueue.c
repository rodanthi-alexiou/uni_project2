///////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT Priority Queue μέσω ADTSet.
//
///////////////////////////////////////////////////////////

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "ADTPriorityQueue.h"
#include "ADTSet.h"			// Η υλοποίηση του PriorityQueue χρησιμοποιεί Set

struct priority_queue{
    Set set;        //στο set που αποθηκεύονται τα values
    CompareFunc compare;
    DestroyFunc destroy_value;
};

struct priority_queue_node{
    Pointer value;
    
};

//ΣΥΝΑΡΤΗΣΗ για δημιουργία ενός PriorityQueueNode
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
    pqueue->set = set_create(compare,destroy_value);    //δημιουργώ το set και περνάω ως destroy_value εκείνο που δέχομαι ως όρισμα

    if(values!=NULL){
        int size = vector_size(values);
        for(int i=0; i<size; i++){
            set_insert(pqueue->set, vector_get_at(values, i));      //με μια επανάληψη κάνω insert όλα τα στοιχεία που έχω από το vector στο set
        }
    }

    return pqueue;
}



int pqueue_size(PriorityQueue pqueue){
    return set_size(pqueue->set);
}


Pointer pqueue_max(PriorityQueue pqueue){
    return set_node_value(pqueue->set, set_last(pqueue->set));      //επιστρέφω το value του τελευταίου στοιχείου του set
}


PriorityQueueNode pqueue_insert(PriorityQueue pqueue, Pointer value){
   set_insert(pqueue->set, value);      //κανω insert το value στο set
   PriorityQueueNode node = pqnode_create(value);       //δημιουργώ το pqnode με το ίδιο value
   return node;
}


void pqueue_remove_max(PriorityQueue pqueue){

    if(pqueue != NULL){
    Pointer max = set_node_value(pqueue->set, set_last(pqueue->set)); //βρίσκω το μεγαλύτερο στοιχείο του set

    set_remove(pqueue->set, max); //αφαιρώ αυτό το στοιχείο από το set

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
    set_remove(pqueue->set, node->value);       //αφαιρώ το value της node από το set 
        
        free(node);     //ελευθερώνω την μνήμη για το node

}
