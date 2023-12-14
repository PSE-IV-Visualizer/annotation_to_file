#include <iostream>
#include <fstream>
#include <time.h>

int annotations = 450000;

enum class EnumClass : std::uint8_t
{
    CAR,
    TRUCK,
    PEDESTRIAN,
    CYCLIST,
    TRAFFIC_LIGHT,
    TRAFFIC_SIGN,
    UNKNOWN
};

struct Data { // 32 bytes
    time_t timestamp;
    uint32_t frameId;
    uint8_t camera;
    EnumClass classType; // uint8_t
    float_t confidence;
    uint16_t x_1;
    uint16_t y_1;
    uint16_t x_2;
    uint16_t y_2;
};


void writeObjectInstanceToFile(const Data& data, std::ofstream& file)
{
    file.write(reinterpret_cast<const char*>(&data), sizeof(Data));
}

int main()
{
    clock_t start = clock();

    std::ofstream outputFile("data.bin", std::ios::binary);

    for (int i = 0; i < annotations; ++i)
    {
        Data data;
        data.timestamp = time(NULL);
        data.frameId = i;
        data.camera = rand() % 10;
        data.classType = static_cast<EnumClass>(rand() % 7);
        data.x_1 = rand() % 1920;
        data.y_1 = rand() % 1080;
        data.x_2 = rand() % 1920;
        data.y_2 = rand() % 1080;

        writeObjectInstanceToFile(data, outputFile);
    }
    outputFile.close();

    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "Schreibvorgang fur " << annotations << " in " << time << "Sekunden abschlossen" << std::endl;
    std::cout << "Durchschnittliche Zeit pro Annotation: " << time / annotations << std::endl;
    std::cout << "Sizeof Beispiel Struct: " << sizeof(Data) << std::endl;


    return 0;
}
