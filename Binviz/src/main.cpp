#include <iostream>
#include <vector>

#include "common.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define MAP_SIZE 256

static uint32_t pixels[MAP_SIZE][MAP_SIZE] = { 0 };
static uint32_t map[MAP_SIZE][MAP_SIZE];
static uint32_t map_log[MAP_SIZE][MAP_SIZE];

using namespace common;

void visualise(std::vector<char>* content)
{
    memset(map, 0, sizeof(map));
    memset(map_log, 0, sizeof(map_log));

	if (content->empty())
    {
        printf("[visualise]: E: Nothing to visualise!\n");
        return;
    }

    for (size_t i = 0; i < content->size() - 1; i++) {
        uint8_t x = content->data()[i];
        uint8_t y = content->data()[i + 1];
        map[y][x] += 1;
    }

    float max = 0;

    // Take frequency into account: more hits - brighter point.
    // Logarithmic scale, not simple normalisation like divide on max value and multiply by 255.
    for (size_t y = 0; y < MAP_SIZE; y++) {
        for (size_t x = 0; x < MAP_SIZE; x++) {
            float f = 0.0f;
            if (map[y][x] > 0)
            {
                f = logf(map[y][x]);
                max = std::max(max, f);
                map_log[y][x] = f;
            }
        }
    }

    for (size_t y = 0; y < MAP_SIZE; ++y) {
        for (size_t x = 0; x < MAP_SIZE; ++x) {
            uint32_t b = map_log[y][x] / max * 255;
            pixels[y][x] = 0xFF000000 | b | (b << 8) | (b << 16);
        }
    }
}

void save_visualisation(const char* input_file_path)
{
    const char* output_file_path = new char();

    std::string strOutputFilePath = input_file_path;

    size_t lastSlashIndex = strOutputFilePath.find_last_of('\\');
    if (lastSlashIndex != std::string::npos) {
        std::string fileName = strOutputFilePath.substr(lastSlashIndex + 1); // Extract file name
        strOutputFilePath.insert(lastSlashIndex + 1, "[VIZ]");
        strOutputFilePath = strOutputFilePath.substr(0, lastSlashIndex + 1 + 5) + fileName; // Concatenate the modified path with the file name
    }

    strOutputFilePath += ".png";
    output_file_path = strOutputFilePath.c_str();
    
    // 4 - components - rgba
    if (!stbi_write_png(output_file_path, MAP_SIZE, MAP_SIZE, 4, pixels, MAP_SIZE * 4)) {
        printf("[save_visualisation]: E: Could not save image %s", output_file_path);
        return;
    }

    printf("[save_visualisation]: Generated %s \n", output_file_path);
}

int main(int argc, char* argv[]) {

    input_data(&argc, &argv);
    
    for (int i = 0; i < argc; ++i) {
        std::vector<char> content;
        const char* input_file_path = argv[i];      // Path to input file
        printf("[main]: Reading file: %s\n", input_file_path);
        if (!read_entire_file(input_file_path, &content)) 
            return 1;

        visualise(&content);
        save_visualisation(input_file_path);
    }
    printf("[main]: SUCCESS.\n");

    return 0;
}