#include<stdio.h>
#include<stdlib.h>

// i'm programming in C like i would program in assembly.
// i'm very sorry.

void fatal(char* str) {
	printf("%s", str);
	exit(1);
}

//           Obj points here v
typedef int Obj;  // [ SIZE, DATA...]
#define HEADER_OFFSET -1

//    Node points here v
typedef int Node; // [ SIZE, NEXT, FREE_SPACE...]
#define FL_SIZE_OFFSET 0
#define FL_NEXT_OFFSET 1
// NODE_SIZE includes the NEXT slot

/* Because of Headers and List Nodes the
 * minimum size of a free slot is at least 2
 * (the size of a list node)
 */
#define MIN_CELL_SIZE 2

#define HEAP_SIZE 16
int heap[HEAP_SIZE];

#define NIL -1
Node head = NIL;

void PrintAll() {
	for (int i = 0; i < HEAP_SIZE; i++) {
		printf("[%d]", heap[i]);
	}
	printf(" head: %d\n", head);
}

int ObjSize(Obj o) {
	int addr = o + HEADER_OFFSET;
	if (addr < 0 || addr >= HEAP_SIZE) {
		fatal("ObjSize: address out of bounds\n");
	}
	return heap[addr];
}

void ObjSet(Obj o, int index, int value) {
	int size = ObjSize(o);
	if (index >= size || index < 0) {
		fatal("ObjSet: index out of bounds\n");
	}
	int addr = o + index;
	if (addr < 0 || addr >= HEAP_SIZE) {
		fatal("ObjSet: address out of bounds\n");
	}
	heap[addr] = value;
}

int ObjGet(Obj o, int index) {
	int size = ObjSize(o);
	if (index >= size || index < 0) {
		fatal("ObjGet: index out of bounds\n");
	}
	int addr = o + index;
	if (addr < 0 || addr >= HEAP_SIZE) {
		fatal("ObjGet: address out of bounds\n");
	}
	return heap[addr];
}

void Init() {
	heap[FL_SIZE_OFFSET] = HEAP_SIZE-1;
	heap[FL_NEXT_OFFSET] = NIL;
	head = 0;
}

void clear(int start, int end) {
	if (end <= start) {
		return;
	}
	for (int i = start; i < end; i++) {
		heap[i] = 0;
	}
}

Obj pop(Node prev, int prev_size,
        Node curr, Node curr_next, int curr_size) {
	if (prev != NIL) { // not head
		heap[prev+FL_NEXT_OFFSET] = curr_next;
	} else {
		head = curr_next;
	}
	// we start zeroing from the FL_NEXT_OFFSET onwards
	clear(curr+FL_NEXT_OFFSET, curr+FL_NEXT_OFFSET+curr_size);
	return curr + FL_NEXT_OFFSET;
}

Obj split(Node prev, int prev_size,
	  Node curr, Node curr_next, int curr_size,
          int requested_size) {
	// +1 because of the curr size slot
	int actual_size = requested_size + 1;

	int newnode_size = curr_size - actual_size;
	Node newnode = curr + actual_size;
	Node newnode_next = curr_next;

	heap[newnode + FL_SIZE_OFFSET] = newnode_size;
	heap[newnode + FL_NEXT_OFFSET] = newnode_next;

	heap[curr + FL_SIZE_OFFSET] = requested_size;
	heap[curr + FL_NEXT_OFFSET] = newnode;

	return pop(prev, prev_size, curr, newnode, requested_size);
}

Obj Alloc(int size) {
	Node curr = head;
	int  curr_size = NIL;
	Node curr_next = NIL;

	Node prev = NIL;
	int  prev_size = NIL;
	Node prev_next = NIL;
	while (curr != NIL) {
		curr_size = heap[curr+FL_SIZE_OFFSET];
		curr_next = heap[curr+FL_NEXT_OFFSET];
		if (curr_size == size) {
			return pop(prev, prev_size, curr, curr_next, curr_size);
		}
		if (curr_size > size) {
			return split(prev, prev_size, curr, curr_next, curr_size, size);
		}
		prev = curr;
		prev_size = curr_size;
		prev_next = curr_next;
		curr = curr_next;
	}
	printf("Out of memory\n");
	return NIL;
}

void insertNode(Node prev, Node curr, Node new) {
	if (prev == NIL) { // curr == head
		if (head != NIL) {
			heap[new+FL_NEXT_OFFSET] = head;
		}
		head = new;
	} else {
		Node prev_next = heap[prev+FL_NEXT_OFFSET];
		if (prev_next == NIL) {
			heap[prev+FL_NEXT_OFFSET] = new;
		} else {
			heap[new+FL_NEXT_OFFSET] = prev_next;
			heap[prev+FL_NEXT_OFFSET] = new;
		}
	}
}

// for debuggin
void clearAll() {
	Node curr = head;
	int curr_size = NIL;
	Node curr_next = NIL;
	while (curr != NIL) {
		curr_next = heap[curr + FL_NEXT_OFFSET];
		curr_size = heap[curr + FL_SIZE_OFFSET];

		clear(curr + 2, curr + FL_NEXT_OFFSET + curr_size);
		curr = curr_next;
	}
}

void defrag() {
	Node curr = head;
	int curr_size = NIL;
	Node curr_next = NIL;
	while (curr != NIL) {
		curr_next = heap[curr + FL_NEXT_OFFSET];
		curr_size = heap[curr + FL_SIZE_OFFSET];
		if (curr + curr_size + 1 == curr_next) {
			int next_size = heap[curr_next+FL_SIZE_OFFSET];
			Node next_next = heap[curr_next+FL_NEXT_OFFSET];
			heap[curr+FL_SIZE_OFFSET] += next_size + 1;
			heap[curr+FL_NEXT_OFFSET] = next_next;
			continue;
		}
		break;
	}
}

void Free(Obj o) {
	int o_size = ObjSize(o);
	Node new = o + HEADER_OFFSET;
	heap[new+FL_NEXT_OFFSET] = NIL;

	Node prev = NIL;
	Node curr = head;
	while (curr != NIL) {
		if (new < curr) {
			insertNode(prev, curr, new);
			break;
		}
		prev = curr;
		curr = heap[curr+FL_NEXT_OFFSET];
	}
	defrag();
	//clearAll();
}

int main() {
	Init();
	PrintAll();

	Obj one = Alloc(1);
	ObjSet(one, 0, 1);
	PrintAll();

	Obj two = Alloc(2);
	ObjSet(two, 0, 2);
	ObjSet(two, 1, 2);
	Free(one);
	PrintAll();

	Obj three = Alloc(3);
	ObjSet(three, 0, 3);
	ObjSet(three, 1, 3);
	ObjSet(three, 2, 3);
	Free(two);
	PrintAll();

	Free(three);
	PrintAll();
}
