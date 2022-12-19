#include "tree_t.h"
#include "file.h"
#include "time_mem_test.h"
#include "bst_graphviz.h"
#include "hash_table_t.h"

#define MAX_WORD_LEN 256

void print_menu(void)
{
    // printf("\nМЕНЮ\n\n"
    //        "\033[0;32mДвоичное дерево поиска.\033[0;39m\n"
    //        "1. Прочитать слова из текстового файла.\n"
    //        "2. Добавить элемент в дерево.\n"
    //        "3. Удалить элемент из дерева.\n"
    //        "4. Вывести дерево на экран.\n"
    //        "5. Вывести дерево с выделенными вершинами, начинающимися на указанную букву.\n"
    //        "6. Pre-order обход.\n"
    //        "7. In-order обход.\n"
    //        "8. Post-order обход.\n\n"
    //        "\033[0;32mФайл.\033[0;39m\n"
    //        "9. Вывести слова из файла, начинающиеся с выбранной буквы.\n\n"
    //        "\033[0;32mАВЛ.\033[0;39m\n"
    //        "10. Сбалансировать ДДП.\n"
    //        "11. Найти элемент в АВЛ.\n\n"
    //        "\033[0;32mХэш-таблица.\033[0;39m\n"
    //        "13. Заполнить таблицу из файла.\n"
    //        "14. Добавить элемент в хэш-таблицу.\n"
    //        "15. Вывести хэш-таблицу на экран.\n"
    //        "16. Поиск элемента в хэш-таблице.\n\n"
    //        "\033[0;32mАнализ скорости работы.\033[0;39m\n"
    //        "17. Сравнить скорость поиска начинающихся на указанную букву слов в дереве и в файле.\n"
    //        "18. Анализ скорости добавления в ДДП.\n"
    //        "19. Сравнение скорости поиска в ДДП, АВЛ и хэш-таблицу.\n\n"
    //        "0. Завершить работу.\n\n");
    printf("\nМЕНЮ\n\n"
           "1. Заполнить все типы данных из файла.\n"
           "2. Сбалансировать ДДП.\n"
           "3. Анализ количества сравнений для поиска в ДДП, АВЛ и хеш-таблице.\n"
           "4. Анализ времени поиска в ДДП, АВЛ, хеш-таблице.\n"
           "5. Вывести на экран ДДП.\n"
           "6. Вывести на экран АВЛ.\n"
           "7. Вывести на экран хеш-таблицу.\n"
           "8. Реструктуризировать хеш-таблицы.\n"
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
    hash_elem_t **table = NULL;
    hash_elem_step_t **table_step = NULL;
    size_t collisions = 0;
    size_t hash_len = 0;
    compares_t all = {0};
    times_t times = {0};
    node_t *avl_tree = NULL;
    uint64_t start, end;

    while (1)
    {
        print_menu();
        if (scanf("%zu", &cmd) != 1 || cmd > 20)
        {
            printf("Некорректная команда.\n");
            setbuf(stdin, NULL);
        }
        // if (cmd == 1)
        // {
        //     uint64_t avg_time = 0;
        //     int tmp;
        //     fscanf(f, "%d", &tmp);
        //     tree_t_read_from_file(f, &root, &avg_time, 0);
        //     rewind(f);
        //     printf("Среднее время добавления - %ld тиков.\n", avg_time);
        // }
        // else if (cmd == 2)
        // {
        //     printf("Введите желаемое слово.\n");
        //     char word[MAX_WORD_LEN];
        //     if (scanf("%s", word) != 1)
        //     {
        //         setbuf(stdin, NULL);
        //         printf("Некорректный ввод.\n");
        //     }
        //     uint64_t start, end;
        //     start = tick();
        //     tree_t_insert(&root, word);
        //     end = tick();
        //     printf("Время добавления составило %ld тиков.\n", end - start);
        // }
        // else if (cmd == 3)
        // {
        //     printf("Введите желаемое слово для удаления.\n");
        //     char word[MAX_WORD_LEN];
        //     if (scanf("%s", word) != 1)
        //     {
        //         setbuf(stdin, NULL);
        //         printf("Некорректный ввод.\n");
        //     }
        //     delete(root, word);
        // }
        // else if (cmd == 4)
        // {
        //     // print_tree(root, 0);
        //     int counter = 0;
        //     export_to_png("res.png", "res", "Tree", root, ' ', &counter);
        //     // printf("Количество таких вершин равно %d.\n", counter);
        // }
        // else if (cmd == 5)
        // {
        //     char letter;
        //     setbuf(stdin, NULL);
        //     printf("Введите желаемую букву: ");
        //     if (scanf("%c", &letter) != 1)
        //     {
        //         setbuf(stdin, NULL);
        //         printf("Некорректный ввод.\n");
        //     }
        //     else
        //     {
        //         int counter = 0;
        //         print_tree_chosen(root, 0, letter, 0, &counter);
        //         export_to_png("res.png", "res", "Tree", root, letter, &counter);
        //         // printf("Количество таких вершин равно %d.\n", counter);
        //     }
        // }
        // else if (cmd == 6)
        //     pre_order(root);
        // else if (cmd == 7)
        //     in_order(root);
        // else if (cmd == 8)
        //     post_order(root);
        // else if (cmd == 9)
        // {
        //     char letter;
        //     setbuf(stdin, NULL);
        //     printf("Введите желаемую букву: ");
        //     if (scanf("%c", &letter) != 1)
        //     {
        //         setbuf(stdin, NULL);
        //         printf("Некорректный ввод.\n");
        //     }
        //     else
        //     {
        //         file_find_words(f, letter, 1);
        //         rewind(f);
        //     }
        // }
        // else if (cmd == 10)
        // {
        //     if (root)
        //     {
        //         avl_tree = balance_tree(root, &avl_tree);
        //     }
        //     // uint64_t avg_time = 0;
        //     // tree_t_read_from_file(f, &root, &avg_time, 1);
        //     // root = node_balance(root);
        //     int counter = 0;
        //     export_to_png("res.png", "res", "Tree", avl_tree, ' ', &counter);
        // }
        // else if (cmd == 11)
        // {
        //     char word[MAX_LEN];
        //     printf("Какое слово желаете найти? Введите: ");
        //     if (scanf("%s", word) != 1)
        //     {
        //         setbuf(stdin, NULL);
        //         printf("Некорректный ввод.\n");
        //     }
        //     find_avl(avl_tree, word, &all);
        //     printf("%d - количество сравнений для нахождения элемента.\n", all.count_avl_find);
        //     all.count_avl_find = 0;
        // }
        // else if (cmd == 13)
        // {
        //     if (fscanf(f, "%zu", &hash_len) != 1)
        //     {
        //         setbuf(stdin, NULL);
        //         printf("Не удалось считать количество слов.\n");
        //     }
        //     if (!table)
        //         table = create_hash_table(hash_len);

        //     hash_table_fill_from_file(f, table, hash_len);
        // }
        // else if (cmd == 14)
        // {
        //     if (!table)
        //     {
        //         size_t size = 0;
        //         printf("Таблица не инициализирована. Таблицу какого размера желаете создать? ");
        //         if (scanf("%zu", &size) != 1)
        //         {
        //             setbuf(stdin, NULL);
        //             printf("Некорректный ввод.\n");
        //         }
        //         table = create_hash_table(hash_len);
        //     }
        //     char word[MAX_LEN];
        //     printf("Введите слово: ");
        //     if (scanf("%s", word) != 1)
        //         return INCORRECT_INPUT;
        //     add_element_hash_table(table, word, hash_len);
        //     hash_len++;
        // }
        // else if (cmd == 15)
        // {
        //     hash_table_print(table, hash_len);
        // }
        // else if (cmd == 16)
        // {
        //     char word[MAX_LEN];
        //     printf("Какое слово вы хотите найти? Введите его: ");
        //     if (scanf("%s", word) != 1)
        //     {
        //         setbuf(stdin, NULL);
        //         printf("Некорректный ввод.\n");
        //     }
        //     hash_table_find(table, word, &all, hash_len);
        //     printf("%d - количество сравнений для нахождения элемента.\n", all.count_hash_find);
        //     all.count_hash_find = 0;
        //     // else
        //     //     printf("Такого слова нет.\n");
        // }
        // else if (cmd == 17)
        // {
        //     uint64_t start, end, res_tree, res_file;
        //     start = tick();
        //     int counter = 0;
        //     for (size_t i = 0; i < 10000; i++)
        //         print_tree_chosen(root, 0, 'c', 0, &counter);
        //     end = tick();
        //     res_tree = (end - start) / 10000;
        //     start = tick();
        //     for (size_t i = 0; i < 10000; i++)
        //     {
        //         file_find_words(f, 'c', 0);
        //         rewind(f);
        //     }
        //     end = tick();
        //     res_file = (end - start) / 10000;

        //     printf("Tree: %ld тиков.\n"
        //            "File: %ld тиков\n", res_tree, res_file);
        // }
        // else if (cmd == 18)
        // {
        //     uint64_t start, end;
        //     start = tick();
        //     for (size_t i = 0; i < 10; i++)
        //         tree_t_insert(&root, "test");
        //     end = tick();
        //     printf("Result: %ld тиков.\n", (end - start) / 10);
        // }
        if (cmd == 1)
        {
            if (fscanf(f, "%zu", &hash_len) != 1)
            {
                setbuf(stdin, NULL);
                printf("Не удалось считать количество слов.\n");
            }
            if (!table)
                table = create_hash_table(hash_len);

            hash_table_fill_from_file(f, table, hash_len);
            rewind(f);

            uint64_t avg_time = 0;
            int tmp;
            fscanf(f, "%d", &tmp);
            tree_t_read_from_file(f, &root, &avg_time, 0);
            rewind(f);
        }
        else if (cmd == 2)
        {
            if (root)
                avl_tree = balance_tree(root, &avl_tree);
        }
        else if (cmd == 3)
        {
            char word[MAX_LEN];
            printf("Какое слово вы хотите найти? Введите его: ");
            if (scanf("%s", word) != 1)
            {
                setbuf(stdin, NULL);
                printf("Некорректный ввод.\n");
            }
            for (size_t i = 0; i < 10; i++)
                hash_table_find(table, word, &all.count_hash_find, hash_len, &times.hash_find);
            start = tick();
            for (size_t i = 0; i < 10000; i++)
                find_avl(avl_tree, word, &all.count_avl_find);
            end = tick();
            times.avl_find = (end - start) / 10000;
            start = tick();
            for (size_t i = 0; i < 10000; i++)
                tree_t_find_node(root, word, &all.count_bst_find);
            end = tick();
            times.bst_find = (end - start) / 10000;
            printf("ДДП: %zu сравнений.\nАВЛ: %zu сравнений.\nХэш-таблица: %zu сравнений.\n\n", all.count_bst_find / 10000, all.count_avl_find / 10000, all.count_hash_find + 1);
            printf("ДДП: %ld тиков.\nАВЛ: %ld тиков.\nХеш-таблица: %ld тиков.\n", times.bst_find, times.avl_find, times.hash_find);
        }
        else if (cmd == 5)
        {
            int counter = 0;
            export_to_png("res.png", "res", "Tree", root, ' ', &counter);
        }
        else if (cmd == 6)
        {
            int counter = 0;
            export_to_png("res.png", "res", "Tree", avl_tree, ' ', &counter);
        }
        else if (cmd == 7)
            hash_table_print(table, hash_len);
        else if (cmd == 8)
        {
            size_t mx_dep = max_depth(table, hash_len), cur_mx;
            table = hash_table_restructure(table, &hash_len, mx_dep);
            cur_mx = max_depth(table, hash_len);
            while (cur_mx >= mx_dep && hash_len < 300000)
            {
                table = hash_table_restructure(table, &hash_len, cur_mx);
                cur_mx = max_depth(table, hash_len);
                if (hash_len % 10000 < 10)
                    printf("Пожалуйста, подождите. Идет поиск числа (текущее - %zu).\n", hash_len);
            }
        }
        else if (cmd == 9)
        {
            if (!table_step)
                table_step = create_hash_table_step(hash_len);

            hash_table_step_fill_from_file(f, table_step, hash_len);
            rewind(f);

            hash_table_step_print(table_step, hash_len * 2);
        }
        else if (cmd == 0)
        {
            if (table)
                hash_table_free(table, hash_len);
            fclose(f);
            printf("Завершение работы...\n");
            return EXIT_SUCCESS;
        }
    }
    return EXIT_SUCCESS;
}