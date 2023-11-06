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
            if ((key == "date" && row.date == value) ||
                (key == "order" && std::to_string(row.order) == value) ||
                (key == "direction" && row.direction == value) ||
                (key == "car_type" && row.car_type == value)) {
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
        std::cout << "1. Add data\n2. Display data\n3. Save and exit\nChoose an option: ";
        int option;
        std::cin >> option;
        std::cin.ignore();

        if (option == 1) {
            std::string date, time, cause, direction, car_type;
            int order, speed;
            std::cout << "Enter date, time, order, cause, speed, direction, car type: ";
            std::cin >> date >> time >> order >> cause >> speed >> direction >> car_type;
            manager.addRow(CSVRow(date, time, order, cause, speed, direction, car_type));
        } else if (option == 2) {
            std::string key, value;
            std::cout << "Enter key (date, order, direction, car_type) and value: ";
            std::cin >> key >> value;
            manager.display(key, value);
        } else if (option == 3) {
            manager.save();
            break;
        }
    }

    return 0;
}
