#include "lib_11.h"


//  копирование файлов
void file_copy(FILE *f1, FILE *f2){
  unsigned char buff[BUF_SIZE];  // создали буфер
  size_t size_of_read = BUF_SIZE;  // переменная с кол-ом прочитанных байт
  while (BUF_SIZE == size_of_read){  // копируем пока файл не закончится
    size_of_read = fread(buff, 1, BUF_SIZE, f1); // прочитали
    fwrite(buff, 1, size_of_read, f2); // записали
  }
  return;
}


//  дальше все про дерево каталогов
void tree(const char *path)
{
  printf("%s\n", path);
  dir_tree(path, 1);  //  функция разбита на две ради этой единички :)))
}


static void dir_tree(const char *path, uint16_t n)   // это функция из урока, изменненная в соотвествии с ДЗ
{
  DIR *dir;
  struct dirent *entry;
  dir = opendir(path);
  if (!dir) {
    fprintf(stderr, "Ошибка открытия: %s\n", path);
    return;
  }
  while ((entry = readdir(dir)) != NULL) {
    if ((entry->d_name[0] == '.' && entry->d_name[1] == 0) ||
        (entry->d_name[0] == '.' && entry->d_name[1] == '.' && entry->d_name[2] == 0)) // боримся с зацикливанием
            continue;
    char fullname[255] = { 0 };
    snprintf(fullname, 254, "%s/%s", path, entry->d_name);
    struct stat st = { 0 };
    int statret = stat(fullname, &st);
    if (statret != 0) {
      fprintf(stderr, "ошибка доступа к %s\n", fullname);
      continue;
    }
    print_spases(n*3);  // выводи пробелы перед названием
    printf("%s\n", entry->d_name); // само название
    if ((st.st_mode & S_IFMT) == S_IFDIR) dir_tree(fullname,n+1); // если это каталог то показываем сожержимое
  }
  closedir(dir);
}



static void print_spases(uint16_t n)
{
  for (int i=0; i<n; ++i) printf(" ");
}
