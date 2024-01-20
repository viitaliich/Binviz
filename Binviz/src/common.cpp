#include <assert.h>
#include <memory>
#include <fstream>
#include <vector>

#include "common.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define MAX_PATH_LENGTH 128


namespace common {

char* shift_args(int* argc, char*** argv)
{
    assert(argc > 0);
    char *result = **argv;
    (*argv) += 1;
    (*argc) -= 1;
    return result;
}

bool read_entire_file(const char* filePath, std::vector<char>* content) {
    
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        return false;
    }

    // Get the file size
    file.seekg(0, std::ios::end);
    const std::streamoff fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    content->resize(fileSize);

    if (!file.read(content->data(), fileSize)) {
        return false;
    }

    file.close();
    return true;
}

bool write_entire_file(const char *path, void *data, size_t size)
{
    FILE *f = fopen(path, "wb");
    if (f == NULL) {
        printf("[write_entire_file]: Could not open file for writing: %s\n", path);
        return false;
    }

    char *buf = (char*)data;
    while (size > 0) {
        size_t n = fwrite(buf, 1, size, f);
        if (ferror(f)) {
            printf("[write_entire_file]: Could not write into file: %s\n", path);
            return false;
        }
        size -= n;
        buf  += n;
    }
    return true;
}

bool is_file_image(const char *filePath) {
    const std::vector<char*> extensions = { ".jpg", ".jpeg", ".png", ".gif"};
    const char* fileExt = strrchr(filePath, '.');

    if (fileExt != NULL) {
        for (int i = 0; i < extensions.size(); i++) {
            if (strcmp(fileExt, extensions[i]) == 0) {
                return true;
            }
        }
    }
    return false;
}

void img2raw(int* argc, char ***argv)
{
    for (int i = 0; i < *argc; ++i) {
        const char *input_file_path = (*argv)[i];

        if(!is_file_image(input_file_path)) continue;
        
        printf("[img2raw]: Reading image: %s \n", input_file_path);

        int width, height;
        uint32_t *pixels = (uint32_t*)stbi_load(input_file_path, &width, &height, NULL, 4);
        if (pixels == NULL) {
            printf("[img2raw]: Could not load file %s", input_file_path);
            continue;
        }

        char output_file_path[MAX_PATH_LENGTH];
        sprintf(output_file_path, "%s.raw", input_file_path);
        
        if (write_entire_file(output_file_path, pixels, sizeof(uint32_t) * width * height))
            printf("[img2raw]: Generated raw image: %s \n", output_file_path);

        stbi_image_free(pixels);
    }
}


void input_data(int* argc, char ***argv)
{
    // First argument is this program itself, so we skip it.
    shift_args(argc, argv);
    
    if (*argc <= 0) {
        printf("[input_data]: E: No input is provided!\n");
        return;
    }

    img2raw(argc, argv);
}

}
