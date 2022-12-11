#include "tree_t.h"
#include "file.h"
#include "time_mem_test.h"
#include "bst_graphviz.h"

#define MAX_WORD_LEN 256

void print_menu(void)
{
    printf("\nМЕНЮ\n"
           "1. Прочитать слова из текстового файла.\n"
           "2. Добавить элемент в дерево.\n"
           "3. Удалить элемент из дерева.\n"
           "4. Вывести дерево на экран.\n"
           "5. Вывести дерево с выделенными вершинами, начинающимися на указанную букву.\n"
           "6. Вывести слова из файла, начинающиеся с выбранной буквы.\n"
           "7. Сравнить скорость поиска начинающихся на указанную букву слов в дереве и в файле.\n"
           "8. Анализ скорости добавления в ДДП.\n"
           "9. Pre-order обход.\n"
           "10. In-order обход.\n"
           "11. Post-order обход.\n"
           "0. Завершить работу.\n\n");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return WRONG_ARGS;

    FILE *f = fopen(argv[1], "r");
    if (!f)
        return FILE_ERROR;

    size_t cmd = 0;
    node_t *root = NULL;

    while (1)
    {
        print_menu();
        if (scanf("%zu", &cmd) != 1 || cmd > 11)
        {
            printf("Некорректная команда.\n");
            setbuf(stdin, NULL);
        }
        if (cmd == 1)
        {
            uint64_t avg_time = 0;
            tree_t_read_from_file(f, &root, &avg_time);
            rewind(f);
            printf("Среднее время добавления - %ld тиков.\n", avg_time);
        }
        else if (cmd == 2)
        {
            printf("Введите желаемое слово.\n");
            char word[MAX_WORD_LEN];
            if (scanf("%s", word) != 1)
            {
                setbuf(stdin, NULL);
                printf("Некорректный ввод.\n");
            }
            uint64_t start, end;
            start = tick();
            tree_t_insert(&root, word);
            end = tick();
            printf("Время добавления составило %ld тиков.\n", end - start);
        }
        else if (cmd == 3)
        {
            printf("Введите желаемое слово для удаления.\n");
            char word[MAX_WORD_LEN];
            if (scanf("%s", word) != 1)
            {
                setbuf(stdin, NULL);
                printf("Некорректный ввод.\n");
            }
            delete(root, word);
        }
        else if (cmd == 4)
        {
            // print_tree(root, 0);
            int counter = 0;
            export_to_png("res.png", "res", "Tree", root, ' ', &counter);
            // printf("Количество таких вершин равно %d.\n", counter);
        }
        else if (cmd == 5)
        {
            char letter;
            setbuf(stdin, NULL);
            printf("Введите желаемую букву: ");
            if (scanf("%c", &letter) != 1)
            {
                setbuf(stdin, NULL);
                printf("Некорректный ввод.\n");
            }
            else
            {
                int counter = 0;
                print_tree_chosen(root, 0, letter, 0, &counter);
                export_to_png("res.png", "res", "Tree", root, letter, &counter);
                // printf("Количество таких вершин равно %d.\n", counter);
            }
        }
        else if (cmd == 6)
        {
            char letter;
            setbuf(stdin, NULL);
            printf("Введите желаемую букву: ");
            if (scanf("%c", &letter) != 1)
            {
                setbuf(stdin, NULL);
                printf("Некорректный ввод.\n");
            }
            else
            {
                file_find_words(f, letter, 1);
                rewind(f);
            }
        }
        else if (cmd == 7)
        {
            uint64_t start, end, res_tree, res_file;
            start = tick();
            int counter = 0;
            for (size_t i = 0; i < 10000; i++)
                print_tree_chosen(root, 0, 'c', 0, &counter);
            end = tick();
            res_tree = (end - start) / 10000;
            start = tick();
            for (size_t i = 0; i < 10000; i++)
            {
                file_find_words(f, 'c', 0);
                rewind(f);
            }
            end = tick();
            res_file = (end - start) / 10000;

            printf("Tree: %ld тиков.\n"
                   "File: %ld тиков\n", res_tree, res_file);
        }
        else if (cmd == 8)
        {
            uint64_t start, end;
            start = tick();
            for (size_t i = 0; i < 10; i++)
            {
                tree_t_insert(&root, "test");
            }
            end = tick();
            printf("Result: %ld тиков.\n", (end - start) / 10);
        }
        else if (cmd == 9)
            pre_order(root);
        else if (cmd == 10)
            in_order(root);
        else if (cmd == 11)
            post_order(root);
        else if (cmd == 0)
        {
            fclose(f);
            printf("Завершение работы...\n");
            return EXIT_SUCCESS;
        }
    }

    return EXIT_SUCCESS;
}