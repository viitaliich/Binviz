#pragma once

namespace common {

    char* shift_args(int* argc, char*** argv);
    bool read_entire_file(const char* filePath, std::vector<char>* content);
    bool write_entire_file(const char *path, void *data, size_t size);
    bool is_file_image(const char *filePath);
    void img2raw(int* argc, char ***argv);
    void input_data(int* argc, char ***argv);

}
