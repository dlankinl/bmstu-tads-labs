#include "tree_t.h"
#include "file.h"
#include "time_mem_test.h"
#include "bst_graphviz.h"
#include "hash_table_t.h"

#define MAX_WORD_LEN 256

void print_menu(void)
{
    printf("\nМЕНЮ\n\n"
           "\033[0;32mДвоичное дерево поиска.\033[0;39m\n"
           "1. Прочитать слова из текстового файла.\n"
           "2. Добавить элемент в дерево.\n"
           "3. Удалить элемент из дерева.\n"
           "4. Вывести дерево на экран.\n"
           "5. Вывести дерево с выделенными вершинами, начинающимися на указанную букву.\n"
           "6. Pre-order обход.\n"
           "7. In-order обход.\n"
           "8. Post-order обход.\n\n"
           "\033[0;32mФайл.\033[0;39m\n"
           "9. Вывести слова из файла, начинающиеся с выбранной буквы.\n\n"
           "\033[0;32mАнализ скорости работы.\033[0;39m\n"
           "10. Сравнить скорость поиска начинающихся на указанную букву слов в дереве и в файле.\n"
           "11. Анализ скорости добавления в ДДП.\n\n"
           "\033[0;32mАВЛ.\033[0;39m\n"
           "12. Сбалансировать ДДП.\n\n"
           "\033[0;32mХэш-таблица.\033[0;39m\n"
           "15. Заполнить таблицу из файла.\n"
           "16. Добавить элемент в хэш-таблицу.\n"
           "17. Вывести хэш-таблицу на экран.\n"
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
    hash_table_t *table = NULL;

    while (1)
    {
        print_menu();
        if (scanf("%zu", &cmd) != 1 || cmd > 17)
        {
            printf("Некорректная команда.\n");
            setbuf(stdin, NULL);
        }
        if (cmd == 1)
        {
            uint64_t avg_time = 0;
            tree_t_read_from_file(f, &root, &avg_time, 0);
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
            pre_order(root);
        else if (cmd == 7)
            in_order(root);
        else if (cmd == 8)
            post_order(root);
        else if (cmd == 9)
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
        else if (cmd == 10)
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
        else if (cmd == 11)
        {
            uint64_t start, end;
            start = tick();
            for (size_t i = 0; i < 10; i++)
                tree_t_insert(&root, "test");
            end = tick();
            printf("Result: %ld тиков.\n", (end - start) / 10);
        }
        else if (cmd == 12)
        {
            uint64_t avg_time = 0;
            tree_t_read_from_file(f, &root, &avg_time, 1);
            root = node_balance(root);
            int counter = 0;
            export_to_png("res.png", "res", "Tree", root, ' ', &counter);
        }
        else if (cmd == 15)
        {
            size_t len = 0;
            if (fscanf(f, "%zu", &len) != 1)
            {
                setbuf(stdin, NULL);
                printf("Не удалось считать количество слов.\n");
            }
            if (!table)
                table = create_table(len);

            printf("%zu len\n", table->size);
            table_fill_from_file(f, table, len);
        }
        else if (cmd == 16)
        {
            if (!table)
                table = create_table(10);
            char *word = malloc(MAX_LEN * sizeof(char));
            printf("Введите слово: ");
            if (scanf("%s", word) != 1)
                return INCORRECT_INPUT;
            table_add_elem(table, word);
            table_print(table);
        }
        else if (cmd == 17)
        {
            table_print(table);
        }
        else if (cmd == 0)
        {
            fclose(f);
            printf("Завершение работы...\n");
            return EXIT_SUCCESS;
        }
    }

    return EXIT_SUCCESS;
}