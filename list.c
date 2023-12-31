#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  struct List* newList = (struct List*)malloc(sizeof(struct List)); // se crea la lista con memoria dinámica
  if (newList == NULL) {
    //no se pudo asignar memoria para la lista
    exit(1);
  }
  newList->head = NULL; // la cabeza se inicia apuntando a null
  newList->tail = NULL; // la colita o "fin" se inicia apuntando a null
  newList->current = NULL; // la posición actual de la cola se inicia apuntando a null
  return newList; // se retorna la nueva lista
}

void * firstList(List * list) {
  if (list->head == NULL) {
      return NULL; // La lista está vacía
  }
  return (list->head->data);
}

void * nextList(List * list) {
  
  if (list->current == NULL) {
      return NULL; // No hay siguiente elemento
    }
    
    list->current = list->current->next;
    
    if (list->current == NULL) {
      return NULL; // No hay siguiente elemento después de avanzar
    }
    
    return (list->current->data);
}

void * lastList(List * list) {
  if (list->tail == NULL) {
    return NULL; // La lista está vacía
  }

    int* lastElement = (list->tail->data);
    list->current = list->tail;

    return lastElement;
}

void * prevList(List * list) {
  if (list->current == NULL) {
    return NULL; // No hay elemento anterior si current es NULL
  }

  struct Node* previousNode = NULL;
  struct Node* currentNode = list->head;

  while (currentNode != NULL && currentNode != list->current) {
    previousNode = currentNode;
    currentNode = currentNode->next;
  }

  if (previousNode == NULL) {
    list->current = NULL; // Si no se encontró el elemento actual en la lista
    return NULL;
  }

  list->current = previousNode;
  return (previousNode->data);
    
}

void pushFront(List * list, void * data) {
  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
       exit(1);
    }
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;

    if (list->tail == NULL) {
        list->tail = newNode;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
   if (list->current == NULL) {
      return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
      exit(1);
    }
    newNode->data = data;
    newNode->next = list->current->next;
    newNode->prev = list->current;

    if (list->current->next != NULL) {
      list->current->next->prev = newNode;
    }

    list->current->next = newNode;

    if (newNode->next == NULL) {
      list->tail = newNode;
      list->tail->prev = list->current;  // Actualizar tail->prev a current
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  if (list->current == NULL) {
    return NULL;
  }

  struct Node* currentNode = list->current;
  void* data = currentNode->data;

  if (currentNode->prev != NULL) {
    currentNode->prev->next = currentNode->next;
  } else {
    list->head = currentNode->next;
  }

  if (currentNode->next != NULL) {
    currentNode->next->prev = currentNode->prev;
  } else {
    list->tail = currentNode->prev;
  }

  list->current = currentNode->next;

  free(currentNode);
  return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}