#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <filesystem>

namespace fs = std::filesystem;

struct Row {
    std::vector<std::string> row;
};

// 파일 확인 함수
void checkFile() {
    std::string filename;
    std::cout << "확인할 파일 이름을 입력하세요: ";
    std::cin >> filename;

    if (fs::exists(filename)) {
        std::cout << "파일이 존재합니다.\n";
    } else {
        std::cout << "파일이 존재하지 않습니다.\n";
    }
}

// 파일 변환 함수
void convertFile() {
    std::string input_file;
    std::cout << "변환할 파일 이름을 입력하세요: ";
    std::cin >> input_file;

    std::vector<Row> csv_data;
    std::ifstream file(input_file);
    std::string line = "";

    while (getline(file, line)) {
        std::vector<std::string> vec;
        boost::algorithm::split(vec, line, boost::is_any_of(","));
        csv_data.push_back({vec});
    }
    file.close();

    int max_index = 0;
    std::string max_value = "";
    for (int i = 0; i < csv_data.size(); i++) {
        if (csv_data[i].row[4].compare(max_value) > 0) {
            max_value = csv_data[i].row[4];
            max_index = i;
        }
    }

    std::ofstream output_file("output.csv");
    int start = std::max(max_index - 40, 0);
    int end = std::min(max_index + 40, (int)csv_data.size() - 1);
    for (int i = start; i <= end; i++) {
        output_file << boost::algorithm::join(csv_data[i].row, ",") << "\n";
    }
    output_file.close();

    std::cout << "파일 변환 완료.\n";
}

int main() {
    while (true) {
        int choice;
        std::cout << "1. 파일 확인\n";
        std::cout << "2. 파일 변환\n";
        std::cout << "3. 프로그램 종료\n";
        std::cout << "선택: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                checkFile();
                break;
            case 2:
                convertFile();
                break;
            case 3:
                exit(0);
            default:
                std::cout << "잘못된 입력입니다.\n";
        }
    }
}
