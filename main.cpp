#include <iostream>
#include <random>

namespace {
    class Minesweeper {
    public:
        Minesweeper(const size_t width, const size_t height)
                : width(width), height(height),
                  table(new char[width * height]) {
            fillTable();
        }

        /* In a real implementation there would also be a
         * - copy constructor
         * - assignment operator
         * - move constructor
         * - move assignment operator
         * We will learn about them later
         */

        virtual ~Minesweeper() {
            delete[] table;
        }

        void countNeighbours() {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    int idx = i * width + j;
                    if (table[idx] == '.') {
                        table[idx] = getCount(i, j);
                    }
                }
            }
        }

        void printTable() const {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    int idx = i * width + j;
                    std::cout << table[idx] << ' ';
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }

    private:
        void fillTable() {
            std::random_device rnd;
            for (int i = 0; i < width * height; i++) {
                table[i] = rnd() % 100 > 10 ? '.' : '*';
            }
        }

        char getCount(const int y, const int x) const {
            int counter = 0;
            for (int i = -1; i <= 1; i++) {
                int cy = y + i;
                if (cy < 0 || cy >= height) continue;
                for (int j = -1; j <= 1; j++) {
                    if (i == 0 && j == 0) continue;
                    int cx = x + j;
                    if (cx < 0 || cx >= width) continue;
                    if (table[cy * width + cx] == '*') counter++;
                }
            }
            return (char) ('0' + counter);
        }

        const size_t width, height;
        char *table;
    };
}

int main() {
    try {
        Minesweeper ms(20, 10);
        ms.printTable();
        ms.countNeighbours();
        ms.printTable();
    } catch (const std::bad_alloc &e) {
        std::cerr << "Couldn't allocate enough memory for minesweeper table" << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}