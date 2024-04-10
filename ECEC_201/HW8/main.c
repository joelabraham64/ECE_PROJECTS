#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

#define to_person(ptr) \
  container_of(ptr, struct person, node)

struct person {
  char name[128];
  int age;
  int salary;
  int years;
  struct list node;
};

struct list *load_database(const char *filename)
{
  FILE *fp;
  struct person *item;

  fp = fopen("employees.csv", "r");
  if (fp == NULL) {
    fprintf(stdout, "File could not be opened\n");
    return NULL;
  }

  struct list *head = (struct list *)malloc(sizeof(struct list));
  if (head == NULL) {
    fprintf(stdout, "Failed to allocate memory\n");
    fclose(fp);
    return NULL;
  }
  list_init(head);

  char line[256];
  while (fgets(line, sizeof(line), fp)) {
    char name[128];
    int age, salary, years;
    sscanf(line, "%[^,], %d, %d, %d", name, &age, &salary, &years);

    item = (struct person *)malloc(sizeof(struct person));
    if (item == NULL) {
      fprintf(stdout, "Failed to allocate person\n");
      fclose(fp);
      list_remove(head);
      free(head);
      return NULL;
    }

    strncpy(item->name, name, sizeof(item->name));
    item->age = age;
    item->salary = salary;
    item->years = years;

    list_add_after(head, &(item->node));
  }

  fclose(fp);
  return head;
}

void unload_database(struct list *head)
{
  struct list *cur, *sav;
  struct person *item;

  list_safe_for(head, cur, sav) {
    item = to_person(cur);
    list_remove(cur);
    free(item);
  }
}

struct person *find_person(struct list *head, const char *name)
{
  struct list *cur;
  struct person *item;

  list_for(head, cur) {
    item = to_person(cur);
    if (strcmp(item->name, name) == 0)
      return item;
  }

  return NULL;
}

void print_person(struct person *p)
{
  printf("Employee %s:\n", p->name);
  printf("   Age: %d\n", p->age);
  printf("Salary: $%.2f\n", (float)p->salary / 100.0f);
  printf(" Years: %d\n", p->years);
}

int main(int argc, char **argv)
{
  struct list *head;
  struct person *item;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s employee_name\n", argv[0]);
    return EXIT_FAILURE;
  }

  head = load_database("employees.csv");

  if (!head) {
    fprintf(stderr, "Failed to open database.\n");
    return EXIT_FAILURE;
  }

  item = find_person(head, argv[1]);
  if (item)
    print_person(item);
  else
    printf("Employee NOT FOUND!\n");

  unload_database(head);
  free(head);

  return 0;
}
