#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>


typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef struct {
    struct Cell *childl;
    struct Cell *childr;
    struct Cell *parent;
    i32 value;
} Cell;

Cell *create_cell(i32 val){
    Cell *cell = malloc(sizeof(Cell));
    cell->childl = NULL;
    cell->childr = NULL;
    cell->parent = NULL;
    cell->value = val;
    return cell;
}

void print_cell(Cell cell){
    printf("Genitore: %p\nFiglio Sinistro: %p\nFiglio Destro: %p\nValore: %d\n", cell.parent, cell.childl, cell.childr, cell.value);
    return;
}

void print_tree(Cell *root){
    Cell *curr = root;
    printf("\n\n");
    print_cell(*curr);
    Cell *rc = (Cell *) curr->childr;
    Cell *lc = (Cell *) curr->childl;

    if (rc != NULL) print_tree(rc);
    if (lc != NULL) print_tree(lc);
    if (rc == NULL && lc == NULL) return;
}

void free_tree(Cell *root){
    Cell *curr = root;
    Cell *rc = (Cell *) curr->childr;
    Cell *lc = (Cell *) curr->childl;

    if (rc != NULL) free_tree(rc);
    if (lc != NULL) free_tree(lc);
    if (rc == NULL && lc == NULL) free(curr);
}

void add_cell(Cell **root, i32 val){
    Cell *new = create_cell(val);
    if (*root == NULL){
        *root = new;
    } else {
        Cell *curr = *root;
        bool flag = true;
        while (flag){
            if(val >= curr->value){
                if (curr->childr == NULL){

                    new->parent = (struct Cell *) curr;
                    curr->childr = (struct Cell *) new;
                    
                    flag = false;
                } else {
                    curr = (Cell *) curr->childr;
                }

            } else if (val < curr->value){
                if (curr->childl == NULL){

                    new->parent = (struct Cell *) curr;
                    curr->childl = (struct Cell *) new;
                    
                    flag = false;
                } else {
                    curr = (Cell *) curr->childl;
                }
            }
        }
    }
    return;
}

Cell *find_cell(Cell *root, i32 val){
    Cell *curr = root;
    while (true){
        if (curr->value == val){
            return curr;
        }
        if (val > curr->value && curr->childr != NULL){
            curr = (Cell *) curr->childr;
        } else if (val < curr->value && curr->childl != NULL){
            curr = (Cell *) curr->childl;
        } else {
            printf("Il nodo cercato non esiste!\n");
            return NULL;
        }
    }
}

void delete_cell(Cell **root, i32 val){
    Cell *found = find_cell(*root, val);
    if (found == NULL){
        return;
    }
    //primo caso: è un nodo foglia, quindi senza figli
    if (found->childl == NULL && found->childr == NULL){
        if (found->parent != NULL){
            Cell *par = (Cell *) found->parent;
            if (par->value > found->value){
                par->childl = NULL;
            } else {
                par->childr = NULL;
            }
            free(found);
        } else {
            //è il nodo root e non ha figli, devo solo chiamare free
            free(found);
        }
    }
    //secondo caso: è un nodo con 2 figli
    else if (found->childl != NULL && found->childr != NULL){
        //cerchiamo di trovare il successore inorder: un childr, un childl
        Cell *first = (Cell *) found->childr;
        if (first->childl != NULL){
            //trovato successore inorder
            Cell *succ = (Cell *) first->childl;
            succ->childl = found->childl;
            succ->childr = found->childr;
            succ->parent = found->parent;
            if (found->parent != NULL){
                Cell *par = (Cell *) found->parent;
                if (par->value > val){
                    par->childl = (struct Cell *) succ;
                } else {
                    par->childr = (struct Cell *) succ;
                }
            }
            free(found);

        } else {
            //niente successore, posso semplicemente sostituire il padre con il figlio destro
            first->childl = found->childl;
            first->parent = found->parent;
            if (found->parent != NULL){
                Cell *par = (Cell *) found->parent;
                if (par->value > val){
                    par->childl = (struct Cell *) first;
                } else {
                    par->childr = (struct Cell *) first;
                }
            }
            free(found);
        }

    }
    //terzo caso: c'è solo un figlio
    else {
        if (found->childl != NULL){
            if (found->parent != NULL){
                Cell *par = (Cell *) found->parent;
                Cell *child = (Cell *) found->childl;
                child->parent = found->parent;
                if (par->value > val){
                    par->childl = found->childl;
                } else {
                    par->childr = found->childl;
                }
                free(found);
            } else {
                //siamo il nodo root e abbiamo solo un figlio, swap
                Cell *child = (Cell *) found->childl;
                child->parent = NULL;
                free(found);
            }
        } else {
            if (found->parent != NULL){
                Cell *par = (Cell *) found->parent;
                Cell *child = (Cell *) found->childr;
                child->parent = found->parent;
                if (par->value > val){
                    par->childl = found->childr;
                } else {
                    par->childr = found->childr;
                }
                free(found);
            } else {
                //siamo il nodo root e abbiamo solo un figlio, swap
                Cell *child = (Cell *) found->childr;
                child->parent = NULL;
                free(found);
            }
        }
    }

}


int main(void){
    Cell *root = NULL;
    add_cell(&root, 32);
    add_cell(&root, 16);
    add_cell(&root, 48);
    add_cell(&root, 22);
    add_cell(&root, 56);
    add_cell(&root, 55);
    add_cell(&root, 47);
    delete_cell(&root, 56);
    print_tree(root);

    //if (find_cell(root, 50) != NULL) print_cell(*find_cell(root, 50));

    free_tree(root);
    return 0;
}
