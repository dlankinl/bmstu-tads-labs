#include "bst_graphviz.h"

void to_dot(node_t *root, void *param, char letter, int *counter)
{
    FILE *f = param;
    // fprintf(f, "%s -> %s [color=green];\n", root->word, root->left->word);

    if (root->left)
    {
        if (root->left->word[0] == letter)
        {
            fprintf(f, "%s -> %s [color=green];\n", root->word, root->left->word);
            *counter++;
        }
        else
            fprintf(f, "%s -> %s;\n", root->word, root->left->word);
    }
    if (root->right)
    {
        if (root->right->word[0] == letter)
        {
            fprintf(f, "%s -> %s [color=green];\n", root->word, root->right->word);
            *counter++;
        }
        else
            fprintf(f, "%s -> %s;\n", root->word, root->right->word);
    }
}

void apply(node_t *root, void (*f)(node_t*, void*, char, int *), void *arg, char letter, int *counter)
{
    if (root == NULL)
        return;
    // pre-order
    f(root, arg, letter, counter);
    apply(root->left, f, arg, letter, counter);
    // in-order
    // f(tree, arg);
    apply(root->right, f, arg, letter, counter);
    // post-order
    // f(tree, arg);
}

void export_to_dot(FILE *dst, const char *tree_name, node_t *root, char letter, int *counter)
{
    fprintf(dst, "digraph %s {\n", tree_name);
    if (root->left || root->right)
        apply(root, to_dot, dst, letter, counter);
    else
        fprintf(dst, "%s;", root->word);
    fprintf(dst, "}\n");
}

int export_to_png(const char *png_path, const char *dot_path, const char *tree_name, node_t *root, char letter, int *counter)
{
    FILE *dot = fopen(dot_path, "w");
    if (!dot)
        return EXIT_FAILURE;
    (void) png_path;
    (void) tree_name;
    (void) root;
    export_to_dot(dot, tree_name, root, letter, counter);
    fclose(dot);

    char cmd_draw[1024];
    sprintf(cmd_draw, "dot -Tpng %s > %s", dot_path, png_path);
    system(cmd_draw);
    return EXIT_SUCCESS;
}
