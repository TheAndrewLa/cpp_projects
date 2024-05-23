#include "library/io.hpp"
#include <iostream>

int main() {
    // BFS, he-he
    // But buffered io is the most complicated stuff here, so i decided to test it
    buffered_fstream bfs{"build/file.txt", 25};

    bfs.write_int(120);
    bfs.write_char(' ');
    bfs.write_int(220);
    bfs.write_char(' ');
    bfs.write_int(320);
    bfs.write_char(' ');
    bfs.write_int(420);
    bfs.write_char(' ');
    bfs.write_int(520);
    bfs.write_char(' ');
    bfs.write_int(620);
    bfs.write_char(' ');
    bfs.write_int(720);
    bfs.write_char(' ');

    char8* ptr = bfs.get_writing_buffer();
}
