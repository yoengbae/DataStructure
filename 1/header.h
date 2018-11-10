typedef struct node {
	char stu_name[20];
	int deathNo;
	int bullNo;
	struct node *link;
}node;

typedef struct list {
	int count;
	node* link;
	node* rear;
}list;

list* createlist();
node* play(list*, node*, char*, int, int);
void delete(list*);