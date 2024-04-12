#include "image_processor.h"

void UseFilters(Picture& picture, std::vector<std::vector<std::string>> parameters) {  // Применение фильтров
    parameters.size();
    for (auto i : parameters) {
        if (i[0] == "-gs") {  // Grayscale
            Grayscale grayscale;
            grayscale.ApplyFilter(picture);
        } else if (i[0] == "-neg") {  // Negative
            Negative negative;
            negative.ApplyFilter(picture);
        } else if (i[0] == "-crop") {  // Crop
            if (i.size() != 3 || i[1].find_first_not_of("1234567890") < i[1].size() ||
                i[2].find_first_not_of("1234567890") < i[2].size()) {
                cout << "Incorrect using filter Crop!\nCorrect realization: -crop width(int) height(int)" << endl;
                throw std::invalid_argument("Incorrect using filter Crop!");
            }
            int w = std::stoi(i[1]);
            int h = std::stoi(i[2]);
            Crop crop(w, h);
            crop.ApplyFilter(picture);
        } else if (i[0] == "-sharp") {  // Sharp
            Sharp sharp;
            sharp.ApplyFilter(picture);
        } else if (i[0] == "-edge") {  // Edge Detection
            if (i.size() != 2 || i[1].find_first_not_of("1234567890.") < i[1].size()) {
                cout << "Incorrect using filter Edge Detection!\nПравильная реализация: -edge threshold(int/float)"
                     << endl;
                throw std::invalid_argument("Incorrect using filter Edge Detection!");
            }
            Grayscale grayscale;
            auto f = static_cast<float>(std::stod(i[1]));
            EdgeDetection edge(grayscale, picture, f);
            edge.ApplyFilter(picture);
        } else if (i[0] == "-blur") {  // Gaussian Blur
            if (i.size() != 2 || i[1].find_first_not_of("1234567890.") < i[1].size()) {
                cout << "Incorrect using filter Gaussian Blur!\nПравильная реализация: -blur sigma(int/float)" << endl;
                throw std::invalid_argument("Incorrect using filter Gaussian Blur!");
            }
            GaussianBlur blur(static_cast<float>(std::stod(i[1])));
            blur.ApplyFilter(picture);
        } else if (i[0] == "-mine") {  // Minecraft
            Minecraft minecraft;
            minecraft.ApplyFilter(picture);
        } else if (i[0] == "-glass") {  // Glass
            Glass glass;
            glass.ApplyFilter(picture);
        } else if (i[0] == "-strange1") {  // Strange1
            Strange1 strange1;
            strange1.ApplyFilter(picture);
        } else if (i[0] == "-strange2") {  // Strange2
            Strange2 strange2;
            strange2.ApplyFilter(picture);
        } else if (i[0] == "-rotate") {  // Rotate
            if (i.size() != 2 || i[1].find_first_not_of("1234567890.") < i[1].size()) {
                cout << "Incorrect using filter Rotate Picture!\nПравильная реализация: -rotate angle(int/float)";
                throw std::invalid_argument("Incorrect using filter Rotate Picture!");
            }
            RotatePicture rotate_picture(std::stod(i[1]));
            rotate_picture.ApplyFilter(picture);
        } else {  // Обращение к несуществующему фильтру
            cout << "Using a non-existent filter!" << endl;
            cout << "List of filters and parameters:\n1. Crop (-crop width(int) height(int))\n2. Grayscale "
                    "(-gs)\n3. Negative (-neg)\n4. Sharpening (-sharp)\n5. Edge Detection (-edge "
                    "threshold(float/int))\n6. Gaussian Blur (-blur sigma)\n7. Minecraft (-mine)\n8. Glass "
                    "(-glass)\n9. Strange1 (-strange1)\n10. Strange2 (-strange2)\n11. Rotate Picuture "
                    "(-rotate(float/int))\n"
                 << endl;
            throw std::invalid_argument("Using a non-existent filter!");
        }
    }
}

void BMPFilterController(int argc, char** argv,
                         Picture& picture) {  // Деление argv на отдельные части (пути к файлам или применение фильтров)
    std::vector<std::vector<std::string>> parameters;
    std::vector<std::string> tmp;
    for (size_t i = 3; i < argc; ++i) {  //
        if (argv[i][0] == '-' && !tmp.empty()) {
            parameters.push_back(tmp);
            tmp.clear();
        }
        tmp.push_back(static_cast<std::string>(argv[i]));
    }
    parameters.push_back(tmp);
    UseFilters(picture, parameters);
}

int main(int argc, char** argv) {
    if (argc <= 3 || argv[1][0] == '-' || argv[2][0] == '-') {
        cout << "Incorrect use of program!" << endl;
        cout << "Correct command line format: {program name} {path to input file} {path to output file} "
                "[-{filter name 1} [parameter 1] [parameter 2] ...] [-{filter name 2} [parameter 1] [parameter 2] ...] "
                "..."
             << endl;
        cout << "List of filters and parameters:\n1. Crop (-crop width(int) height(int))\n2. Grayscale "
                "(-gs)\n3. Negative (-neg)\n4. Sharpening (-sharp)\n5. Edge Detection (-edge "
                "threshold(float/int))\n6. Gaussian Blur (-blur sigma)\n7. Minecraft (-mine)\n8. Glass "
                "(-glass)\n9. Strange1 (-strange1)\n10. Strange2 (-strange2)\n11. Rotate Picuture "
                "(-rotate(float/int))\n"
             << endl;
        throw std::invalid_argument("Incorrect use of program!");
    }
    OpenBMPPicture openfile;
    openfile.UploadBMPPicture(argv[1]);        // Открытие файла
    Picture picture(openfile);                 // Создание объекта класса картинки
    BMPFilterController(argc, argv, picture);  // Применение фильтров к картинке
    ExportBMPPicture exp(picture);
    exp.Export(argv[2]);  // Экспорт картинки
    return 0;
}
