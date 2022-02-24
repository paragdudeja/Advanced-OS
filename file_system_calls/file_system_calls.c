#include<stdio.h> 
#include<fcntl.h> 
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void create_file();
void open_file();
void close_file();
void read_from_file();
void write_to_file();
void jump_to_location();

int main() 
{
    int choice;
    do 
    {
        printf("------------FILE SYSTEM MENU------------\n\n");

        printf("1. Create file\n");
        printf("2. Open file\n");
        printf("3. Close file\n");
        printf("4. Read from file\n");
        printf("5. Write to file\n");
        printf("6. Jump to a location in file\n");
        printf("7. Exit the program\n\n");

        printf("Enter your choice: ");
        scanf("%d\n", &choice);

        switch (choice)
        {
            case 1:
                create_file();
                break;
            case 2:
                open_file();
                break;
            case 3:
                close_file();
                break;
            case 4:
                read_from_file();
                break;
            case 5:
                write_to_file();
                break;
            case 6:
                jump_to_location();
                break;
            default:
                if(choice != 7)
                    printf("Enter a valid choice!!!!!!!!!!!!!!!!!!\n");
        }
    } while(choice != 7);
    return 0;
}

void create_file() {
    char filename[2000];
    printf("Enter filename: ");
    scanf("%s", filename);
    filename[strlen(filename)] = '\0';
    if(access(filename, F_OK ) == 0 ) {
        printf("File with same name exists\n");
        printf("Do you want to create a new file with same name? (y/n)\n");
        char opt;
        scanf("%c", &opt);
        if(opt == 'y')
            creat(filename, 0666);
    } else {
        creat(filename, 0666);
    }
    printf("Done\n\n");
}

void open_file() {
    char filename[2000];
    printf("Enter the filename to open: ");
    scanf("%s", filename);

    int fd = open(filename, O_RDONLY); 
    if (fd < 0) 
        perror("File does not exist "); 
    else 
        printf("opened the fd = % d\n", fd);
}

void close_file() {
    char filename[2000];
    printf("Enter the filename to close: ");
    scanf("%s", filename);
    int fd = open(filename, O_RDONLY); 
    if (close(fd) < 0) 
        perror("Error closing file"); 
    else  
        printf("Closed the file.\n"); 
}

void read_from_file() {
    char filename[2000];
    printf("Enter the filename to read data from: ");
    scanf("%s", filename);
    int fd = open(filename, O_RDONLY); 
    if (fd < 0) 
        perror("Error opening file"); 
    else {
        char *c = (char *) calloc(100, sizeof(char));
        int sz = read(fd, c, 10); 

        printf("\nCalled read(%d, c, 10). returned that %d bytes were read.\n", fd, sz); 

        c[sz] = '\0'; 
        printf("Those bytes are as follows: %s \n", c);
    } 
}

void write_to_file() {
    char filename[2000];
    printf("Enter filename: ");
    scanf("%s", filename);
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644); 
    if (fd < 0) 
        perror("Error "); 
    else{
        char data[2000];
        printf("Enter the data to be written to file: \n");
        fgets(data, strlen(data), stdin);
        
        write(fd, data, strlen(data)); 
        printf("Data written to file");
    }

}

void jump_to_location() {
    int fd = open("foo.txt", O_RDONLY); 
    int sz = lseek(fd,15,SEEK_SET);
    if(sz == -1)
        printf("Error\n");
    else
        printf("%d", sz);
}