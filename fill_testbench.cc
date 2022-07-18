#include <iostream>
#include <cstdlib>
#include <vector>
#include <random>
#include <string>
#include <algorithm>
#include <iterator>
#include <chrono>

int main(int argc, char const *argv[])
{
    using std::cout, std::cerr, std::endl, std::vector, std::string, std::mt19937, std::uniform_int_distribution;
    if (argc != 3 and argc != 4)
    {
        cout << "Invalid argument number: " << argc << endl;
        copy(argv[0], argv[2], std::ostream_iterator<int>(std::cout, " "));
        cout << endl;
        exit(1);
    }
    size_t size = atoi(argv[1]);
    int seed = atoi(argv[2]);
    string mode("lineal");
    if (argc == 4)
        mode = argv[3];
    cout << "Arguments: " << size << ' ' << seed << ' ' << mode << endl;
    vector<int> data(size, 0);
    vector<int> index(size, 0);
    mt19937 rng(seed);
    uniform_int_distribution<int> U(1, 10);
    for (int i = 0; i < size; i++)
        index[i] = i;
    if (mode.compare("random") == 0)
        std::shuffle(index.begin(), index.end(), rng);
    using namespace std::chrono;    
    auto start = high_resolution_clock::now();
    for (auto&& i : index)
        data[i] = U(rng);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    if (size < 100)
    {
        cout << "Index vector: " << endl;
        copy(index.begin(), index.end(), std::ostream_iterator<int>(std::cout, " "));
        cout << endl;
        cout << "Data vector: " << endl;
        copy(data.begin(), data.end(), std::ostream_iterator<int>(std::cout, " "));
        cout << endl;
    }
    cout << "Execution time: " << duration.count() << " ns" << endl;
    return 0;
}
