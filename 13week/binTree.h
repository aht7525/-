struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addTree(struct tnode *p, char *w);
void treePrint(struct tnode *p);