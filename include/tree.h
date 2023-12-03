#ifndef __TREE__
#define __TREE__


#include "macros.h"     //messaging
#include "libs.h"       //libraries
#include "buffer.h"
#include "lexer.h"


typedef struct TreeNode {
    char data[LEXEME_SIZE];
    struct TreeNodeList *children;
} TreeNode;

typedef struct TreeNodeList {
    TreeNode *node;
    struct TreeNodeList *next;
} TreeNodeList;

// Função para criar um novo nó da árvore
TreeNode *createTreeNode(const char *data) {
    TreeNode *newNode = malloc(sizeof(TreeNode));
    if (newNode) {
        strncpy(newNode->data, data, LEXEME_SIZE);
        newNode->children = NULL;
    }
    return newNode;
}

// Função para adicionar um filho a um nó
void addChild(TreeNode *parent, TreeNode *child) {
    createTreeNode("root");
    if (!parent || !child) return;

    TreeNodeList *newElement = malloc(sizeof(TreeNodeList));
    if (!newElement) return;

    newElement->node = child;
    newElement->next = parent->children;
    parent->children = newElement;
}

// Função para imprimir a árvore
void printTree(TreeNode *root, int level) {
    if (!root) return;

    for (int i = 0; i < level; ++i) {
        printf("  ");
    }
    printf("%s\n", root->data);

    TreeNodeList *current = root->children;
    while (current) {
        printTree(current->node, level + 1);
        current = current->next;
    }
}

// Função para liberar a memória da árvore
void freeTree(TreeNode *root) {
    if (!root) return;

    TreeNodeList *current = root->children;
    while (current) {
        TreeNodeList *temp = current;
        freeTree(current->node);
        current = current->next;
        free(temp);
    }
    free(root);
}
#endif