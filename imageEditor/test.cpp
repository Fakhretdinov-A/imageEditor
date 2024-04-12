/*#include <catch.hpp>

#include "image_processor.h"

TEST_CASE("Incorrect use of program") {
    // 1. Случай, когда введены и input, и output файлы, но не применены фильтры
    int argc1 = 3;
    std::string str1[3] = {"test.cpp", "input.bmp", "output.bmp"};
    REQUIRE((argc1 <= 3 || str1[1][0] == '-' || str1[2][0] == '-') == 1);

    // 2. Случай, когда введен только 1 файл
    int argc2 = 2;
    std::string str2[2] = {"test.cpp", "something.bmp"};
    REQUIRE((argc2 <= 3 || str2[1][0] == '-') == 1);

    // 3. Случай, когда вместо одного из файлов введен фильтр
    int argc3 = 4;
    std::string str3[4] = {"test.cpp", "something.bmp", "-blur", "15"};
    REQUIRE((argc3 <= 3 || str3[1][0] == '-' || str3[2][0] == '-') == 1);

    // 4. Безошибочный случай
    const int test_size = 7;
    int argc4 = test_size;
    std::string str4[test_size] = {"test.cpp", "input.bmp", "output.bmp", "-neg", "-crop", "1024", "1024"};
    REQUIRE((argc4 <= 3 || str4[1][0] == '-' || str4[2][0] == '-') == 0);
}

TEST_CASE("Opening") {
    OpenBMPPicture bmp;

    // 1. Проверка на не корректность входного файла
    REQUIRE_THROWS_WITH(bmp.UploadBMPPicture("random_thing"), "File was not opened!");

    // 2. Проверка на не корректность расширения входного файла
    REQUIRE_THROWS_WITH(bmp.UploadBMPPicture("../tasks/image_processor/test_script/data/test_case.png"),
                        "Incorrect file format!");

    // 3. Безошибочный случай
    REQUIRE_NOTHROW([&]() { bmp.UploadBMPPicture("../tasks/image_processor/test_script/data/lenna.bmp"); });
}

TEST_CASE("Exporting") {
    OpenBMPPicture bmp;
    bmp.UploadBMPPicture("../tasks/image_processor/test_script/data/lenna.bmp");
    Picture picture(bmp);
    ExportBMPPicture exp(picture);

    // 1. Проверка на случай, если файл не удалось открыть
    // Здесь я специально создал файл, к которому никто не имеет доступ
    REQUIRE_THROWS_WITH(exp.Export("../tasks/image_processor/test_script/data/non-readable-file"),
                        "File was not opened!");

    // 2. Безошибочный случай
    REQUIRE_NOTHROW([&]() { exp.Export("../tasks/image_processor/test_script/data/result.bmp"); });
}

TEST_CASE("Filters") {

    // Здесь будет имитироваться работа моей функции UseFilters из image_processor.cpp
    OpenBMPPicture bmp;
    bmp.UploadBMPPicture("../tasks/image_processor/test_script/data/lenna.bmp");
    Picture picture(bmp);

    // 1. Случай, несуществующего фильтра
    REQUIRE_THROWS_WITH(UseFilters(picture, {std::vector<std::string>{"non-existent-filter"}}),
                        "Using a non-existent filter!");

    // 2. Неправильное использование фильтра Crop
    REQUIRE_THROWS_WITH(UseFilters(picture, {std::vector<std::string>{"-crop", "50"}}), "Incorrect using filter Crop!");

    // 3. Неправильное использование фильтра Edge
    REQUIRE_THROWS_WITH(UseFilters(picture, {std::vector<std::string>{"-edge", "abc"}}),
                        "Incorrect using filter Edge Detection!");

    // 4. Неправильное использование фильтра Gaussian Blur
    REQUIRE_THROWS_WITH(UseFilters(picture, {std::vector<std::string>{"-blur", "", ""}}),
                        "Incorrect using filter Gaussian Blur!");

    // 5. Неправильное использование фильтра Rotate (Один из моих собственных фильтров)
    REQUIRE_THROWS_WITH(UseFilters(picture, {std::vector<std::string>{"-rotate"}}),
                        "Incorrect using filter Rotate Picture!");

    // 6. Правильное использование абсолютно всех фильтров одновременно 0_о
    REQUIRE_NOTHROW([&]() {
        std::vector<std::vector<std::string>> parameters;
        parameters.push_back(std::vector<std::string>{"-crop", "1024", "1024"});
        parameters.push_back(std::vector<std::string>{"-gs"});
        parameters.push_back(std::vector<std::string>{"-neg"});
        parameters.push_back(std::vector<std::string>{"-sharp"});
        parameters.push_back(std::vector<std::string>{"-edge", "5"});
        parameters.push_back(std::vector<std::string>{"-blur", "2"});
        parameters.push_back(std::vector<std::string>{"-mine"});
        parameters.push_back(std::vector<std::string>{"-glass"});
        parameters.push_back(std::vector<std::string>{"-strange1"});
        parameters.push_back(std::vector<std::string>{"-strange2"});
        parameters.push_back(std::vector<std::string>{"-rotate", "35"});
        UseFilters(picture, parameters);
    });
}
*/
