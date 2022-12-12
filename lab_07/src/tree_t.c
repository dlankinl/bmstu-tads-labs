#include "tree_t.h"

node_t *init_node(size_t height, char *word)
{
    node_t *cur = malloc(sizeof(node_t));
    if (!cur)
        return NULL;

    char *ptmp = strdup(word);
    if (ptmp)
    {
        cur->word = ptmp;
        cur->left = cur->right = NULL;
        cur->height = height;
    }
    else
        return NULL;

    return cur;
}

void tree_t_insert(node_t **head, char *word)
{
    node_t *tmp = NULL;
    if (!(*head))
    {
        *head = init_node(1, word);
        return;
    }

    tmp = *head;
    while (tmp)
    {
        if (strcmp(tmp->word, word) < 0)
        {
            if (tmp->right)
            {
                tmp = tmp->right;
                continue;
            }
            else
            {
                tmp->right = init_node(tmp->height + 1, word);
                return;
            }
        }
        else if (strcmp(tmp->word, word) > 0)
        {
            if (tmp->left)
            {
                tmp = tmp->left;
                continue;
            }
            else
            {
                tmp->left = init_node(tmp->height + 1, word);
                return;
            }
        }
        else
            return;
    }
}

size_t tree_t_read_from_file(FILE *f, node_t **head, uint64_t *avg_ins_time, size_t is_balanced)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    uint64_t start, end, sum = 0;
    size_t counter = 0;
    while ((read = getline(&line, &len, f)) != -1)
    {
        line[strlen(line) - 1] = 0;
        char *ptmp = strdup(line);
        if (ptmp)
        {
            if (!is_balanced)
            {
                start = tick();
                tree_t_insert(head, ptmp);
                end = tick();
            }
            else
            {
                start = tick();
                (*head) = balanced_tree_t_insert(*head, ptmp);
                end = tick();
            }
            sum += end - start;
            counter++;
        }
    }
    free(line);
    *avg_ins_time = (uint64_t)(sum / counter);
    return EXIT_SUCCESS;
}

void print_tree(node_t *head, int level)
{
    if(head)
    {
        print_tree(head->left, level + 1);
        for (int i = 0; i < level; i++)
            printf("      ");
        printf("%s\n", head->word);
        print_tree(head->right, level + 1);
    }
}

void print_tree_chosen(node_t *head, int level, char letter, size_t to_print, int *counter)
{
    if(head)
    {
        print_tree_chosen(head->left, level + 1, letter, to_print, counter);
        if (to_print)
            for (int i = 0; i < level; i++)
                printf("      ");
        if (letter == head->word[0] && to_print)
            printf("\033[0;32m%s\n", head->word);
        else if (letter != head->word[0] && to_print)
            printf("\033[0;39m%s\n", head->word);
        print_tree_chosen(head->right, level + 1, letter, to_print, counter);
    }
}

node_t *tree_t_find_node(node_t *head, char *word)
{
    while (head)
    {
        if (strcmp(word, head->word) > 0)
        {
            head = head->right;
            continue;
        }
        else if (strcmp(word, head->word) < 0)
        {
            head = head->left;
            continue;
        }
        else
            return head;
    }
    return NULL;
}

void free_node(node_t *node)
{
    free(node->word);
    free(node);
}

void tree_t_remove_by_ptr(node_t *to_del)
{ 
    if (to_del->left == NULL || to_del->right == NULL) 
    {
        node_t *cur = to_del;
        if (to_del->left != NULL)
            to_del = to_del->left;
        else
            to_del = to_del->right;
        free_node(cur);
    } 
    else 
    {
        node_t **p2 = &to_del->right;
        while ((*p2)->left)
            p2 = &((*p2)->left);
        char *ptmp = strdup((*p2)->word);
        if (ptmp)
            to_del->word = ptmp;
        tree_t_remove_by_ptr(*p2);
    }
}

void tree_t_delete_node(node_t *head, char *word)
{
    node_t *cur = tree_t_find_node(head, word);
    tree_t_remove_by_ptr(cur);
}

void delete(node_t *head, char *word)
{
    node_t *curr = head;
    node_t *parent = NULL;
    while (curr && strcmp(word, curr->word))
    {
        parent = curr;
        if (strcmp(curr->word, word) > 0)
            curr = curr->left;
        else
            curr = curr->right;
    }
    if (!curr)
        return;
    if (curr->left == NULL)
    {
        if (parent && parent->left == curr)
            parent->left = curr->right;
        if (parent && parent->right == curr)
            parent->right = curr->right;
        free_node(curr);
        return;
    }
    if (curr->right == NULL)
    {
        if (parent && parent->left == curr)
            parent->left = curr->left;
        if (parent && parent->right == curr)
            parent->right = curr->left;
        free_node(curr);
        return;
    }
    node_t *replace = curr->right;
    while (replace->left)
        replace = replace->left;

    char *tmp = strdup(replace->word);
    delete(head, tmp);
    curr->word = strdup(tmp);
}


void pre_order(node_t *node)
{
    if (!node)
        return;
    printf("%s\n", node->word);
    pre_order(node->left);
    pre_order(node->right);
}

void in_order(node_t *node)
{
    if (!node)
        return;
    in_order(node->left);
    printf("%s\n", node->word);
    in_order(node->right);
}

void post_order(node_t *node)
{
    if (!node)
        return;
    post_order(node->left);
    post_order(node->right);
    printf("%s\n", node->word);
}

int balance_factor(node_t *node)
{
    return node->right->height - node->left->height;
}

void recover_height(node_t *node)
{
    int hl = node->left->height, hr = node->right->height;
    node->height = (hl > hr ? hl : hr) + 1;
}

node_t *left_rotate(node_t *node)
{
    node_t *tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    recover_height(node);
    recover_height(tmp);
    return tmp;
}

node_t *right_rotate(node_t *node)
{
    node_t *tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    recover_height(node);
    recover_height(tmp);
    return tmp;
}

node_t *node_balance(node_t *node)
{
    recover_height(node);
    printf("%zu - height for %s\n", node->height, node->word);
    if (balance_factor(node) == 2)
    {
        if (balance_factor(node->right) < 0)
            node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    else if (balance_factor(node) == -2)
    {
        if (balance_factor(node->left) > 0)
            node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    return node;
}

node_t *balanced_tree_t_insert(node_t *head, char *word)
{
    if (!head)
    {
        head = init_node(1, word);
        return head;
    }
    if (strcmp(head->word, word) > 0)
        head->left = balanced_tree_t_insert(head->left, word);
    else
        head->right = balanced_tree_t_insert(head->right, word);
    return node_balance(head);
}