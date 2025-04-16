#include "../../inc/so_long.h"
int check_argument_count(int argc)
{
    if (argc != 2)
    {
        write(2, "Error\nInvalid number of arguments.\n", 35);
        return (0);
    }
    return (1);
}

int check_file_extension(const char *filename)
{
    const char *ext = ".ber";
    size_t len = strlen(filename);
    size_t ext_len = strlen(ext);

    if (len < ext_len || strcmp(filename + len - ext_len, ext) != 0)
    {
        write(2, "Error\nInvalid file extension. Use .ber\n", 40);
        return (0);
    }
    return (1);
}

int is_file_accessible(const char *filepath)
{
    if (access(filepath, F_OK) == -1)
    {
        write(2, "Error\nFile not accessible\n", 27);
        return (0);
    }
    return (1);
}

int is_file_empty(int fd)
{
    char buffer;
    if (read(fd, &buffer, 1) <= 0)
    {
        write(2, "Error\nFile is empty\n", 20);
        return (1);
    }
    lseek(fd, 0, SEEK_SET); // Dosya başına geri dön
    return (0);
}

int validate_file(int argc, char *argv[], int *fd)
{
    if (!check_argument_count(argc))
        return (0);

    if (!check_file_extension(argv[1]))
        return (0);

    if (!is_file_accessible(argv[1]))
        return (0);

    *fd = open(argv[1], O_RDONLY);
    if (*fd < 0)
    {
        write(2, "Error\nFailed to open file\n", 26);
        return (0);
    }

    if (is_file_empty(*fd))
    {
        close(*fd);
        return (0);
    }

    return (1);
}