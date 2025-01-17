#include <sys/types.h>  // Provides data types used in system calls
#include <sys/stat.h>   // Provides structure of the data returned by functions like stat()
#include <fcntl.h>      // Provides file control options (open, O_RDONLY, O_WRONLY, O_CREAT)
#include <stdlib.h>     // Provides standard library functions like exit()
#include <unistd.h>     // Provides access to the POSIX operating system API (read, write, close)
#include <stdio.h>      // Provides functions for input and output, like printf()

int main(int argc, char *argv[])
{
    char buf[512];      // Buffer to store data read from the source file
    int fd, dfd, r, w;  // File descriptors and read/write counters
    char *src;          // Source file name
    char *dest;         // Destination file name

    src = "sample2.txt";   // Source file name is set to "sample2.txt"
    dest = "sample3.txt";  // Destination file name is set to "sample3.txt"

    // Open the source file in read-only mode
    if ((fd = open(src, O_RDONLY)) < 0) {
        fprintf(stderr, "cp: cannot open source %s\n", src);  // Print error if source file cannot be opened
        exit(1);  // Exit the program with an error code
    }

    // Open the destination file in write-only mode, create it if it doesn't exist
    if ((dfd = open(dest, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR)) < 0) {
        fprintf(stderr, "cp: cannot open destination %s\n", dest);  // Print error if destination file cannot be opened
        close(fd);  // Close the source file before exiting
        exit(1);  // Exit the program with an error code
    }

    // Read from the source file and write to the destination file
    while ((r = read(fd, buf, sizeof(buf))) > 0) {  // Read data into buffer
        w = write(dfd, buf, r);  // Write data from buffer to destination file
        if (w != r || w < 0) 
            break;  // Break the loop if there is a write error or mismatch in bytes written
    }

    // Check for read or write errors
    if (r < 0 || w < 0)
        fprintf(stderr, "cp: error copying %s to %s\n", src, dest);  // Print error message

    // Close the file descriptors
    close(fd);   // Close source file descriptor
    close(dfd);  // Close destination file descriptor

    exit(0);  // Exit the program with a success code
}




