tipo_risultato Marika_Alvisi_130211_conta (lista l){

    struct rbtNode{
        int key;
        int priority;
        char color;
        struct rbtNode *left;
        struct rbtNode *right;
        struct rbtNode *parent;
    };

    struct rbt{
        struct rbtNode *root;
        struct rbtNode *Nil;
    };

    void leftRotate(struct rbt* T, struct rbtNode *x){
        struct rbtNode *y;
        y = x->right;
        x->right = y->left;
        if(y->left != T->Nil){
            y->left->parent = x;
        }
        y->parent = x->parent;
        if(x->parent == T->Nil)
            T->root = y;
        if((x->parent != T->Nil) && (x == x->parent->left))
            x->parent->left = y;
        if((x->parent != T->Nil) && (x == x->parent->right))
            x->parent->right = y;
        y->left = x;
        x->parent = y;
        return;
    }

    void rightRotate(struct rbt* T, struct rbtNode *x){
        struct rbtNode *y;
        y = x->left;
        x->left = y->right;
        if(y->right != T->Nil){
            y->right->parent = x;
        }
        y->parent = x->parent;
        if(x->parent == T->Nil)
            T->root = y;
        if((x->parent != T->Nil) && (x == x->parent->left))
            x->parent->left = y;
        if((x->parent != T->Nil) && (x == x->parent->right))
            x->parent->right = y;
        y->right = x;
        x->parent = y;
        return;
    }

    void rbInsertFixUp(struct rbt *T, struct rbtNode *z){
        struct rbtNode *y;
        while(z->parent->color == 'r'){
            if(z->parent == z->parent->parent->left){
                y = z->parent->parent->right;
                if(y->color == 'r'){
                    z->parent->color = 'b';
                    y->color = 'b';
                    z->parent->parent->color = 'r';
                    z = z->parent->parent;
                }
                else{
                    if(z == z->parent->right){
                        z = z->parent;
                        leftRotate(T, z);
                    }
                    z->parent->color = 'b';
                    z->parent->parent->color = 'r';
                    rightRotate(T, z->parent->parent);
                }
            }

            else{
                y = z->parent->parent->left;
                if(y->color == 'r'){
                    z->parent->color = 'b';
                    y->color = 'b';
                    z->parent->parent->color = 'r';
                    z = z->parent->parent;
                }
                else{
                    if(z == z->parent->left){
                        z = z->parent;
                        rightRotate(T, z);
                    }
                    z->parent->color = 'b';
                    z->parent->parent->color = 'r';
                    leftRotate(T, z->parent->parent);
                }
            }
        }
        T->root->color = 'b';
    }


    void searchInsertKey(struct rbt* T, int val, tipo_risultato* risultato){
     struct rbtNode*x = T->root;
     struct rbtNode *y = T->Nil;

    //ricerca elemento
    while(x != T->Nil){
        y = x;
        if(val > x->key)
            x = x->right;
        else if(val < x->key)
            x = x->left;
        else{
            x->priority = x->priority + 1;
            if(x->priority > risultato->numero)
                risultato->numero = x->priority;
            return;
        }
    }
        struct rbtNode* z = malloc(sizeof(struct rbtNode));
        z->parent = y;
        z->key = val;
        z->right = T->Nil;
        z->left = T->Nil;
        z->color = 'r';
        z->priority = 1;

        if(y == T->Nil){
            T->root = z;
            z->parent = T->Nil;
            risultato->numero = z->priority;
        }
        else{
            if(z->key < y->key){
                y->left = z;
            }
            if(z->key > y->key){
                y->right = z;
            }
        }
        z->left = T->Nil;
        z->right = T->Nil;
        z->color = 'r';
        rbInsertFixUp(T, z);
    }

    void freeTree (struct rbt T, struct rbtNode* n){
        if (n != T.Nil){
            freeTree(T, n->left);
            freeTree(T, n->right);
            free(n);
        }
    }

    void createVirtualChild(struct rbt* T){
        struct rbtNode* figlio_virtuale = malloc(sizeof(struct rbtNode));
		figlio_virtuale->parent = NULL;
    	figlio_virtuale->right = NULL;
    	figlio_virtuale->left = NULL;
    	figlio_virtuale->color = 'b';
		T->root = figlio_virtuale;
		T->Nil = figlio_virtuale;
    }

    tipo_risultato risultato;
    risultato.memoria = 0;
    risultato.numero = 0;

    struct rbt T;
    createVirtualChild(&T);

    nodo* tempnodo = l.testa;
    while(tempnodo){
        searchInsertKey(&T, tempnodo->chiave, &risultato);
        tempnodo = tempnodo->next;
    }

    freeTree(T, T.root);
    free(T.Nil);
    T.root = NULL;

    risultato.memoria = sizeof(risultato) + sizeof(T) + sizeof(tempnodo);

    return risultato;
}
