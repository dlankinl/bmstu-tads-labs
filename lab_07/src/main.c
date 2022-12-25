#include "tree_t.h"
#include "file.h"
#include "time_mem_test.h"
#include "bst_graphviz.h"
#include "hash_table_t.h"

#define MAX_WORD_LEN 256

void print_menu(void)
{
    printf("\nМЕНЮ\n\n"
           "1. Заполнить все типы данных из файла.\n"
           "2. Сбалансировать ДДП.\n"
           "3. Анализ количества сравнений для поиска в ДДП, АВЛ и хеш-таблицах.\n"
           "4. Вывести на экран ДДП.\n"
           "5. Вывести на экран АВЛ.\n"
           "6. Вывести на экран хеш-таблицу (метод цепочек).\n"
           "7. Вывести на экран хеш-таблицу (внутр. хеш-ие).\n"
           "8. Реструктуризировать хеш-таблицу (метод цепочек).\n"
           "9. Реструктуризировать хеш-таблицу (внутр. хеш-ие).\n"
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
    // size_t collisions = 0;
    size_t hash_len = 0, hash_step_len = 0;
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
        if (cmd == 1)
        {
            if (fscanf(f, "%zu", &hash_len) != 1)
            {
                setbuf(stdin, NULL);
                printf("Не удалось считать количество слов.\n");
            }

            hash_step_len = hash_len;
            if (!table)
                table = create_hash_table(hash_len);

            int buf;
            fscanf(f, "%d", &buf);
            hash_table_fill_from_file(f, table, hash_len);
            rewind(f);

            if (!table_step)
                table_step = create_hash_table_step(hash_step_len);

            hash_table_step_fill_from_file(f, table_step, hash_step_len);
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
            all.count_avl_find = 0;
            all.count_bst_find = 0;
            all.count_hash_find = 0;
            all.count_hash_st_find = 0;
            printf("Какое слово вы хотите найти? Введите его: ");
            if (scanf("%s", word) != 1)
            {
                setbuf(stdin, NULL);
                printf("Некорректный ввод.\n");
            }
            for (size_t i = 0; i < 10; i++)
            {
                hash_table_find(table, word, &all.count_hash_find, hash_len, &times.hash_find);
                hash_table_step_find(table_step, word, &all.count_hash_st_find, hash_step_len, &times.hash_st_find);
            }
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

            size_t cnt1 = 0, cnt2 = 0;
            pre_order(root, &cnt1);
            pre_order(avl_tree, &cnt2);

            printf("ДДП: %zu сравнений.\nАВЛ: %zu сравнений.\nХэш-таблица: %zu сравнений.\nХеш-таблица (внутр. хеш.): %zu сравнений.\n\n", all.count_bst_find / 10000, all.count_avl_find / 10000, all.count_hash_find + 1, all.count_hash_st_find + 1);
            printf("ДДП: %ld тиков.\nАВЛ: %ld тиков.\nХеш-таблица: %ld тиков.\nХеш-таблица (внутр. хеш.): %ld тиков.\n\n", times.bst_find, times.avl_find, times.hash_find, times.hash_st_find);
            printf("ДДП: %zu байтов.\nАВЛ: %zu байтов.\nХеш-таблица (метод цепочек): %zu байтов.\nХеш-таблица (внутр. хеш-ие): %zu байтов.\n",
            sizeof(tree_t) * cnt1, sizeof(avl_tree) * cnt2, sizeof(hash_elem_t) * hash_len, sizeof(hash_elem_step_t) * hash_step_len);
        }
        else if (cmd == 4)
        {
            int counter = 0;
            export_to_png("res.png", "res", "Tree", root, ' ', &counter);
        }
        else if (cmd == 5)
        {
            int counter = 0;
            export_to_png("res.png", "res", "Tree", avl_tree, ' ', &counter);
        }
        else if (cmd == 6)
            hash_table_print(table, hash_len);
        else if (cmd == 7)
            hash_table_step_print(table_step, hash_step_len * 2);        
        else if (cmd == 8)
        {
            size_t mx_dep = max_depth(table, hash_len), cur_mx;
            table = hash_table_restructure(table, &hash_len);
            cur_mx = max_depth(table, hash_len);
            while (cur_mx >= mx_dep && hash_len < 300000)
            {
                table = hash_table_restructure(table, &hash_len);
                cur_mx = max_depth(table, hash_len);
                if (hash_len % 10000 < 10)
                    printf("Пожалуйста, подождите. Идет поиск числа (текущее - %zu).\n", hash_len);
            }
        }
        else if (cmd == 9)
        {
            size_t wrong_elems = wrong_hash_elements(table_step, hash_step_len * 2), cur_wrong_elems;
            table_step = hash_table_step_restructure(table_step, &hash_step_len);

            cur_wrong_elems = wrong_hash_elements(table_step, hash_step_len * 2);
            while (cur_wrong_elems >= wrong_elems && hash_len < 300000)
            {
                table_step = hash_table_step_restructure(table_step, &hash_step_len);
                cur_wrong_elems = wrong_hash_elements(table_step, hash_step_len * 2);
            }
            printf("%zu - текущее число коллизий.\n", cur_wrong_elems);
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