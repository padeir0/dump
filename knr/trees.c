#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum Op {VALUE, PLUS, MINUS, MULT, DIV, REM};

char* str_op(enum Op op) {
  switch (op) {
    case VALUE:
      return "v";
    case PLUS:
      return "+";
    case MINUS:
      return "-";
    case MULT:
      return "*";
    case DIV:
      return "/";
    case REM:
      return "%";
  }
  return "?";
}

typedef struct _node {
  int value;
  enum Op op;
  struct _node* left;
  struct _node* right;
} Node;

Node* newValue(int value) {
  Node* n = (Node*)malloc(sizeof(Node));
  n->value = value;
  return n;
}

Node* newOp(enum Op op) {
  Node* n = (Node*)malloc(sizeof(Node));
  n->op = op;
  return n;
}

void print_node(Node* n) {
  if (n->op == VALUE) {
    printf("%d\n", n->value);
  } else {
    printf("%s\n", str_op(n->op));
  }
}

typedef Node* T;

typedef struct {
  T* array;
  int cap;
  int top;
} stack;

bool push(stack* s, T item) {
  if (s->top < s->cap-1) {
    s->top++;
    s->array[s->top] = item;
    return true;
  }
  return false;
}

bool pop(stack* s, T* dest) {
  if (s->top >= 0) {
    *dest = s->array[s->top];
    s->top--;
    return true;
  }
  return false;
}

stack* newStack(int cap) {
  stack* s = (stack*)malloc(sizeof(stack));
  s->array = (T*)malloc(cap * sizeof(T));
  s->cap = cap;
  s->top = -1;
  return s;
}

void freeStack(stack* s) {
  free(s->array);
  free(s);
}

typedef struct {
  T* array;
  int cap;
  int front;
  int end;
} queue;

bool enqueue(queue* rq, T item) {
  if ((rq->end+1) % rq->cap == rq->front) {
    return false;
  }
  rq->array[rq->end] = item;
  rq->end = (rq->end+1) % rq->cap;
  return true;
}

bool dequeue(queue* rq, T* dest) {
  if (rq->end == rq->front) {
    return false;
  }
  *dest = rq->array[rq->front];
  rq->front = (rq->front+1) % rq->cap;
  return true;
}

queue* newQueue(int cap) {
  queue* rq = (queue*) malloc(sizeof(queue));
  rq->array = (T*) malloc(cap*sizeof(T));
  rq->front = 0;
  rq->end = 0;
  rq->cap = cap;
  return rq;
}

void freeQueue(queue* rq) {
  free(rq->array);
  free(rq);
}

enum RESULT {OK, OVERFLOW, UNDERFLOW};

char* str_result(enum RESULT res) {
  switch (res) {
    case OK:
      return "OK";
    case OVERFLOW:
      return "OVERFLOW";
    case UNDERFLOW:
      return "UNDERFLOW";
  }
}

bool is_terminal(Node* n) {
  return n->left == NULL && n->right == NULL;
}

enum RESULT preorder_transverse(Node* root) {
  stack* s = newStack(100);
  Node* curr = root;
  bool ok;

  while (curr != NULL) {
    print_node(curr);

    if (curr->right != NULL) {
      ok = push(s, curr->right);
      if (!ok) {
        return OVERFLOW;
      }
    }

    if (curr->left != NULL) {
      curr = curr->left;
    } else {
      ok = pop(s, &curr);
      if (!ok) {
        break;
      }
    }
  }
  return OK;
}

enum RESULT postorder_transverse(Node* root) {
  stack* s1 = newStack(100);
  stack* s2 = newStack(100);
  Node* curr;
  bool ok;

  push(s1, root);

  while (pop(s1, &curr)) {
    push(s2, curr);

    if (curr->left != NULL) {
      push(s1, curr->left);
    }
    if (curr->right != NULL) {
      push(s1, curr->right);
    }
  }

  while (pop(s2, &curr)) {
    print_node(curr);
  }
  return OK;
}

enum RESULT levelorder_transverse(Node* root) {
  queue* q = newQueue(100);
  Node* curr;
  bool ok;
  enqueue(q, root);

  while (dequeue(q, &curr)) {
    print_node(curr);

    if (curr->left != NULL) {
      ok = enqueue(q, curr->left);
      if (!ok) {
        return OVERFLOW;
      }
    }
    if (curr->right != NULL) {
      ok = enqueue(q, curr->right);
      if (!ok) {
        return OVERFLOW;
      }
    }
  }
  return OK;
}

int main() {
  Node* n1 = newValue(1);
  Node* n2 = newValue(2);
  Node* n3 = newValue(3);
  Node* n4 = newValue(4);
  Node* nO1 = newOp(MINUS);
  Node* nO2 = newOp(PLUS);
  Node* nO3 = newOp(MULT);
  enum RESULT res;

  nO1->left = n1;
  nO1->right = n2;

  nO2->left = n3;
  nO2->right = n4;

  nO3->left = nO1;
  nO3->right = nO2;

  printf("preorder:\n");
  res = preorder_transverse(nO3);
  if (res != OK) {
    printf("%s\n", str_result(res));
  }

  printf("level order:\n");
  res = levelorder_transverse(nO3);
  if (res != OK) {
    printf("%s\n", str_result(res));
  }

  printf("postorder:\n");
  res = postorder_transverse(nO3);
  if (res != OK) {
    printf("%s\n", str_result(res));
  }
  
  return 0;
}
