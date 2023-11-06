#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

class CSVRow {
public:
    std::string date, time, cause, direction, car_type;
    int order, speed;
    CSVRow(std::string d, std::string t, int o, std::string c, int s, std::string dir, std::string ct)
        : date(d), time(t), order(o), cause(c), speed(s), direction(dir), car_type(ct) {}
};

class CSVManager {
private:
    std::string filename;
    std::vector<CSVRow> data;

public:
    CSVManager(std::string filename) : filename(filename) {
        load();
    }

    void addRow(CSVRow row) {
        data.push_back(row);
    }

    void save() {
        std::ofstream file(filename);
        for (auto &row : data) {
            file << row.date << "," << row.time << "," << row.order << "," << row.cause << "," << row.speed << "," << row.direction << "," << row.car_type << " ";
        }
        file.close();
    }

    void display(std::string key, std::string value) {
        for (auto &row : data) {
            if ((key == "날짜" && row.date == value) ||
                (key == "순번" && std::to_string(row.order) == value) ||
                (key == "방향" && row.direction == value) ||
                (key == "차종" && row.car_type == value)) {
                std::cout << row.date << "," << row.time << "," << row.order << "," << row.cause << "," << row.speed << "," << row.direction << "," << row.car_type << " ";
            }
        }
    }

    void load() {
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string date, time, cause, direction, car_type;
            int order, speed;
            std::getline(ss, date, ',');
            std::getline(ss, time, ',');
            ss >> order;
            ss.ignore();
            std::getline(ss, cause, ',');
            ss >> speed;
            ss.ignore();
            std::getline(ss, direction, ',');
            std::getline(ss, car_type);
            data.push_back(CSVRow(date, time, order, cause, speed, direction, car_type));
        }
        file.close();
    }
};

int main() {
    CSVManager manager("data.csv");

    while (true) {
        std::cout << "-----------\n1. 데이터 추가\n2. 데이터 확인\n3. 저장 및 종료\n-----------: ";
        int option;
        std::cin >> option;
        std::cin.ignore();

        if (option == 1) {
            std::string date, time, cause, direction, car_type;
            int order, speed;
            std::cout << "날짜, 시간, 순번, 원인, 속력, 방향, 차종을 입력하시오: ";
            std::cin >> date >> time >> order >> cause >> speed >> direction >> car_type;
            manager.addRow(CSVRow(date, time, order, cause, speed, direction, car_type));
        } else if (option == 2) {
            std::string key, value;
            std::cout << "검색 기준(날짜, 순번, 방향, 차종 중)과 값을 입력하시오: ";
            std::cin >> key >> value;
            manager.display(key, value);
        } else if (option == 3) {
            manager.save();
            break;
        }
    }

    return 0;
}
