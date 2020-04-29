///////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT BList μέσω διπλά συνδεδεμένης λίστας.
//
///////////////////////////////////////////////////////////

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "ADTBList.h"


// Ενα BList είναι pointer σε αυτό το struct
struct blist {
	BListNode dummy;
	BListNode last;
	BListNode first;
	int size;
	DestroyFunc destroy_value;
};

struct blist_node {
	BListNode next;
	BListNode previous;
	Pointer value;
};


BList blist_create(DestroyFunc destroy_value) {

	BList blist = malloc(sizeof(*blist));
	blist->size = 0;
	blist->destroy_value = destroy_value;

	blist->dummy = malloc(sizeof(*blist->dummy));
	blist->dummy->next = NULL;
	blist->dummy->previous = NULL;

	blist->last= blist->dummy;
	blist->first= blist->dummy;

	return blist;
}

int blist_size(BList blist) {
	return blist->size;
}

void blist_insert(BList blist, BListNode node, Pointer value) {
	
	BListNode new = malloc(sizeof(*new));
	new->value = value;

	if(node == BLIST_BOF){
		new->previous = NULL;
		new->next = blist->first;
		if(blist->first == NULL){
			blist->last = new;
		}
		else{
			blist->first->previous = new;
		}
		blist->first = new;
	}
 else{
	new->next = node;
	new->previous = node->previous;
	node->previous = new;

 }
	

	blist->size++;

}

void blist_remove(BList blist, BListNode node) {
		if(node == NULL){
			node = blist->dummy;
		}
	
	if(blist->destroy_value != NULL){
		blist->destroy_value(node->value);
	}
	if(node==(blist->first)){
		node->next->previous = NULL;
		blist->first = node->next;
	}
	else if(node==(blist->last)){
		node->previous->next = NULL;
		blist->last = node->previous;
	}
	else{
	node->previous->next = node->next;
	node->next->previous = node->previous;
	}
	free(node);
	blist->size--;
}

Pointer blist_find(BList blist, Pointer value, CompareFunc compare) {
	BListNode node = blist_find_node(blist, value, compare);
	return node == NULL ? NULL : node->value;
}

DestroyFunc blist_set_destroy_value(BList blist, DestroyFunc destroy_value) {
	DestroyFunc old = blist->destroy_value;
	blist->destroy_value = destroy_value;
	return old;
}

void blist_destroy(BList blist) {
		// Διασχίζουμε όλη τη λίστα και κάνουμε free όλους τους κόμβους,
	// συμπεριλαμβανομένου και του dummy!
	//
	BListNode node = blist->dummy;
	while (node != NULL) {				// while αντί για for, γιατί θέλουμε να διαβάσουμε
		BListNode next = node->next;		// το node->next _πριν_ κάνουμε free!

		// Καλούμε τη destroy_value, αν υπάρχει (προσοχή, όχι στον dummy!)
		if (node != blist->dummy && blist->destroy_value != NULL)
			blist->destroy_value(node->value);

		free(node);
		node = next;
	}

	// Τέλος free το ίδιο το struct
	free(blist);
}


// Διάσχιση της λίστας /////////////////////////////////////////////

BListNode blist_first(BList blist) {
	return blist->first;
}

BListNode blist_last(BList blist) {
	if(blist->last == blist->dummy)
		return BLIST_EOF;
	else
		return blist->last;
}

BListNode blist_next(BList blist, BListNode node) {
	return node->next;
}

BListNode blist_previous(BList blist, BListNode node) {
	return node->previous;
}

Pointer blist_node_value(BList blist, BListNode node) {
	return node->value;
}

BListNode blist_find_node(BList blist, Pointer value, CompareFunc compare) {
	// διάσχιση όλης της λίστας, καλούμε την compare μέχρι να επιστρέψει 0
	//
	for (BListNode node = blist->first; node != NULL; node = node->next)
		if (compare(value, node->value) == 0)
			return node;		// βρέθηκε

	return NULL;	// δεν υπάρχει
}