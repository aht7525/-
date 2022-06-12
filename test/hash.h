typedef struct hlink {
    struct hlink *next;
    void *object;
} HashLink;

typedef struct htab{
    int size;
    struct hlink **table;
    char *(* getSymbol) (void *object);
} HashTable;

HashTable *createHash(int size, char *(* getSymbol) (void *));
void destroyHash(HashTable *table);
void *installHash(HashTable *table, void *object);
void *uninstallHash(HashTable *table, char *symbol);
void *lookUpHash(HashTable *table, char *symbol);