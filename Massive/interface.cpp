#include <iostream>
#include <sstream>
#include "Massive.h"

const std::string DATA_FILE = "massive.txt";
const std::string BINARY_FILE = "massive.bin";

void loadArray(Massive &mas) {
    mas.clear();
    mas.readFromFile(DATA_FILE);
}

void saveArray(Massive &mas) {
    mas.writeToFile(DATA_FILE);
}

void processCommand(Massive &mas, const std::string &commandLine) {
    std::stringstream ss(commandLine);
    std::string cmd;
    ss >> cmd;

    if (cmd == "PRINT") {
        mas.print();
        return;
    }

    if (cmd == "MCLEAR") {
        mas.clear();
        saveArray(mas);
        std::cout << "Massive cleared.\n";
        return;
    }

    if (cmd == "MADDEND") {
        std::string val; ss >> val;
        mas.addEnd(val);
        saveArray(mas);
        std::cout << "Added " << val << " to end.\n";
        return;
    }

    if (cmd == "MADD") {
        int index; std::string val; ss >> index >> val;
        if (mas.addAt(index, val)) {
            saveArray(mas);
            std::cout << "Inserted " << val << " at index " << index << ".\n";
        } else {
            std::cout << "Index out of range.\n";
        }
        return;
    }

    if (cmd == "MGET") {
        int index; ss >> index;
        try {
            std::cout << "Massive[" << index << "] = " << mas.get(index) << "\n";
        } catch (...) {
            std::cout << "Index out of range.\n";
        }
        return;
    }

    if (cmd == "MSET") {
        int index; std::string val; ss >> index >> val;
        if (mas.set(index, val)) {
            saveArray(mas);
            std::cout << "Set index " << index << " = " << val << "\n";
        } else {
            std::cout << "Index out of range.\n";
        }
        return;
    }

    if (cmd == "MREM") {
        int index; ss >> index;
        if (mas.removeAt(index)) {
            saveArray(mas);
            std::cout << "Removed element at index " << index << ".\n";
        } else {
            std::cout << "Index out of range.\n";
        }
        return;
    }

    if (cmd == "BSAVE") {
        if (mas.serializeToBinary(BINARY_FILE)) {
            std::cout << "Massive saved to binary: " << BINARY_FILE << "\n";
        } else {
            std::cout << "Error saving binary\n";
        }
        return;
    }

    if (cmd == "BLOAD") {
        if (mas.deserializeFromBinary(BINARY_FILE)) {
            saveArray(mas);
            std::cout << "Massive loaded from binary: " << BINARY_FILE << "\n";
        } else {
            std::cout << "Error loading binary\n";
        }
        return;
    }

    if (cmd == "INFO") {
        std::cout << "Size: " << mas.getSize() << ", Capacity: " << mas.getCapacity() << "\n";
        return;
    }

    std::cout << "Unknown command: " << cmd << "\n";
}

int main() {
    Massive mas;
    loadArray(mas);

    std::cout << "Massive CLI. Functions:\n"
              << "  MADDEND <val>       - add to end\n"
              << "  MADD <index> <val>  - add at index\n"
              << "  MGET <index>        - get value at index\n"
              << "  MSET <index> <val>  - set value at index\n"
              << "  MREM <index>        - remove element at index\n"
              << "  MCLEAR              - clear massive\n"
              << "  PRINT               - print massive\n"
              << "  BSAVE               - save to binary\n"
              << "  BLOAD               - load from binary\n"
              << "  INFO                - show size/capacity\n"
              << "  EXIT                - quit\n";

    std::string line;
    while (true) {
        std::cout << "> ";
        if (!getline(std::cin, line)) break;
        if (line == "EXIT") break;
        if (!line.empty()) processCommand(mas, line);
    }

    return 0;
}
