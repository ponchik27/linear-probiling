#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
/* Для того чтобы хранить данные в хеш-таблице */
struct item
{
	int key;
	int value;
};

/* каждая ячейка хеш-таблицы будет собой предствалять следующую структру, состаящая из flag(статус) и data ( данные) */
struct hashtable_item
{

	int flag;
	/*
	 * flag = 0 : ячейка ещё не используется
	 * flag = 1 : ячейка сейчас активна
	 * flag = 2 : ячейка уже использовалась как минимум 1( то есть данные с неё были удалены)
	*/

	struct item* data;

};

struct hashtable_item* array;// хеш=таблица
int size = 0;
int max = 10;

/* создвание хеш-таблицы */
void init_array()
{
	int i;
	for (i = 0; i < max; i++)
	{
		array[i].flag = 0;
		array[i].data = NULL;
	}
}

/* хеш-функция */
int hashcode(int key)
{
	return (key % max);
}

/* вставка элемента в таблицу */
void insert(int key, int value)
{
	int index = hashcode(key);
	int i = index;

	/* создаём новый элемент для вставки в таблицу */
	struct item* new_item = (struct item*)malloc(sizeof(struct item));
	new_item->key = key;
	new_item->value = value;

	/* смотрим все ячейки последовательно, до тех пор пока не найдём совбодную */
	while (array[i].flag == 1)
	{

		if (array[i].data->key == key)
		{

			/* вставляемый элемент уже существует */
			printf("\n Данный ключ уже существует, данные этого ключы успешно обновлены\n");
			array[i].data->value = value;
			return;

		}

		i = (i + 1) % max;
		if (i == index)
		{
			printf("\n Хеш-Таблица уже заполнена! \n");
			return;
		}

	}

	array[i].flag = 1;
	array[i].data = new_item;
	size++;
	printf("\n Ключ (%d) успешно вставлен \n", key);

}


/* Удаление элемента по ключу */
void remove_element(int key)
{
	int index = hashcode(key);
	int  i = index;

	/* проходим все ячейки с текющего адреса до тех пор, пока не достигним пустой ячейки или найдём ключ */
	while (array[i].flag != 0)
	{

		if (array[i].flag == 1 && array[i].data->key == key)
		{

			// Если нашли данный ключ
			array[i].flag = 2;
			array[i].data = NULL;
			size--;
			printf("\n Ключ (%d) успешно удалён! \n", key);
			return;

		}
		i = (i + 1) % max;
		if (i == index)
		{
			break;
		}

	}

	printf("\n Данного ключа не существует \n");

}

/* вывести хеш-таблицу */
void display()
{
	int i;
	for (i = 0; i < max; i++)
	{
		struct item* current = (struct item*)array[i].data;

		if (current == NULL)
		{
			printf("\n Ячейка[%d] пуста \n", i);
		}
		else
		{
			printf("\n Ячейка[%d] не пуста -: \n  %d (ключ) и %d(значение) ", i, current->key, current->value);
		}
	}

}

int size_of_hashtable()
{
	return size;
}
void cleanTable() {

	for (int i = 0; i < max; i++) {
		if (array[i].flag == 1) {
			free(array[i].data);
		}
	}
	if (array != NULL) {
		delete[] array;
	}
}

int main()
{
	int choice, key, value, n, c;
	setlocale(0, "RUS");

	array = new struct hashtable_item[max];
	init_array();

	do {
		printf("MENU-: \n1.Вставка элента в хеш-таблицу"
			"\n2.Удалить элемент из хеш-таблицы"
			"\n3.Размер хеш-таблицы"
			"\n4.Вывести элементы"
			"\n5.Выход"
			"\n\n Ваш выбор-:");

		scanf_s("%d", &choice);

		switch (choice)
		{

		case 1:

			printf("Вставка элента в хеш-таблицу\n");
			printf("Введите ключ и значение-:\t");
			scanf_s("%d %d", &key, &value);
			insert(key, value);

			break;

		case 2:

			printf("Удалить элемент из хеш-таблицы \n Введите ключ-:");
			scanf_s("%d", &key);
			remove_element(key);

			break;

		case 3:

			n = size_of_hashtable();
			printf("Размер хеш-таблицы-:%d\n", n);

			break;

		case 4:

			display();

			break;
		case 5:
			cleanTable();
			return 0;
			break;
		default:

			printf("Неправильный выбор\n");

		}

		
	} while (1);
}