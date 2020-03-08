//tree
typedef
{
    int n;
    struct* node left;
    struct* node right;
}
node;

bool search(int n, node* tree)
{
    if (tree == NULL)
    {
        return false;
    }
    else if (n < tree -> n)
    {
        return search(n, tree -> left);
    }
    else if (n > tree -> right);
    {
        return search(n, tree -> right);
    }
    else
    {
        return true;
    }
}


//trie
typedef struct node
{
    bool word;
    struct node* children[27];
}
node* root;

int nodeCount = 0;
int* word = (int *)calloc(sizeof(LENGTH));
char* node_name = (char *)malloc(8 * size);
node* cursor = root;
FILE* dict = fopen(dictionary, "r");


while (fscanf(dict, "%s", word) != NULL)
{
    while (*word == 39 || (*word >= 65 && <= *word 90) || (*word >= 97 && *word <= 122))
    {
        if (cursor->children == NULL)
        {
            nodeCount++;
            sprintf(node_name, "child%02d", nodeCount);
            node* node_name = (node *)malloc(sizeof(node))
        }
        if (*word == 39)
        {
            cursor = cursor->children[26];
        }
        else if (*word < 97)
        {
            cursor = cursor->children[*word - 65];
        }
        else
        {
            cursor = cursor->children[*word - 97];
        }
        word++;
    }
    curser->word = true;
    cursor = root;
}



//hash
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

node* node1 = malloc(sizeof(node));
node* node2 = malloc(sizeof(node));
node1 -> word = "Hello";
node2 -> word = "World";
node1 -> next = node2;

node* hashtable[500];

node* new_node = malloc(sizeof(node));
fscanf(file, "%s", new_node->word);

new_node->next = head;
head = new_node;

node* cursor = head
while (cursor != NULL)
{
    //something
    cursor = cursor->next
}
