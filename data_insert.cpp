#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <memory>

// 열 추가 클래스
class CSVRow {
public:
    std::string row_value = 0;
    virtual ~CSVRow() = default;
    virtual std::string getRow() = 0;
};

class DefaultData : public CSVRow {
public:
    std::string date, time, cause, direction, car_type;
    int order, speed;
    DefaultData(std::string d, std::string t, int o, std::string c, int s, std::string dir, std::string ct)
        : date(d), time(t), order(o), cause(c), speed(s), direction(dir), car_type(ct) {}

    std::string getRow() override {
        return date + "," + time + "," + std::to_string(order) + "," + cause + "," + std::to_string(speed) + "," + direction + "," + car_type;
    }
};

//실험용 클래스
class AdditionalData : public CSVRow {
public:
    int wheel_size;
    AdditionalData(int ws) : wheel_size(ws) {}

    std::string getRow() override {
        return std::to_string(wheel_size);
    }
};

class FileSaver {
private:
    std::string filename;
    std::vector<std::unique_ptr<CSVRow>> data;

public:
    FileSaver(std::string filename) : filename(filename) {
        load();
    }

    void addRow(std::unique_ptr<CSVRow> row) {
        data.push_back(std::move(row));
    }

    void save() {
        std::ofstream file(filename);
        for (const auto &row : data) {
            file << row->getRow() << std::endl;
        }
        file.close();
    }

    void display(std::string key, std::string value) {
        for (const auto &row : data) {
            if (key == "날짜") {
                DefaultData *dataRow = dynamic_cast<DefaultData*>(row.get());
                if (dataRow && dataRow->date == value) {
                    std::cout << dataRow->getRow() << std::endl;
                }
            } else if (key == "순번") {
                DefaultData *dataRow = dynamic_cast<DefaultData*>(row.get());
                if (dataRow && std::to_string(dataRow->order) == value) {
                    std::cout << dataRow->getRow() << std::endl;
                }
            } else if (key == "방향") {
                DefaultData *dataRow = dynamic_cast<DefaultData*>(row.get());
                if (dataRow && dataRow->direction == value) {
                    std::cout << dataRow->getRow() << std::endl;
                }
            } else if (key == "차종") {
                DefaultData *dataRow = dynamic_cast<DefaultData*>(row.get());
                if (dataRow && dataRow->car_type == value) {
                    std::cout << dataRow->getRow() << std::endl;
                }
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
            data.push_back(std::make_unique<DefaultData>(date, time, order, cause, speed, direction, car_type));
        }
        file.close();
    }
};

int main() {
    FileSaver manager("data.csv");

    while (true) {
        std::cout << "-----------" << std::endl;
        std::cout << "1. 데이터 추가" << std::endl;
        std::cout << "2. 데이터 확인" << std::endl;
        std::cout << "3. 저장 및 종료" << std::endl;
        std::cout << "-----------: ";

        int option;
        std::cin >> option;
        std::cin.ignore();

        if (option == 1) {
            std::string date, time, cause, direction, car_type;
            int order, speed;
            std::cout << "날짜, 시간, 순번, 원인, 속력, 방향, 차종을 입력하시오: ";
            std::cin >> date >> time >> order >> cause >> speed >> direction >> car_type;
            manager.addRow(std::make_unique<DefaultData>(date, time, order, cause, speed, direction, car_type));
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
