#include <iostream>
#include <vector>

struct Advance {
    int start;
    int end;
    int distance;
};

int processArray(std::vector<int> &array) {
    if (array.empty()) {
        return 0;
    }

    std::vector<Advance> advances;
    Advance currentAdvance = {0, 0, 0};

    for (size_t i = 1; i < array.size(); ++i) {
        if (array[i] >= array[i - 1]) {
            // The army is moving forward or staying in the same position
            currentAdvance.distance += (array[i] - array[i - 1]);
        } else {
            // The advance has ended, update end even if retreating
            currentAdvance.end = i;
            if (currentAdvance.distance > 0) {
                advances.push_back(currentAdvance);
            }
            currentAdvance = {i, i, 0}; // Reset for a new advance
        }
    }

    // Check the last advance
    currentAdvance.end = array.size() - 1;  // Update end for final advance
    if (currentAdvance.distance > 0) {
        advances.push_back(currentAdvance);
    }

    // Find the advance with the longest duration
    int maxLength = 0;
    for (const auto &adv : advances) {
        if ((adv.end - adv.start) > maxLength) {
            maxLength = adv.end - adv.start;
        }
    }

    return maxLength;
}

int main(void) {
    std::vector<int> array;
    int val;
    while (std::cin >> val) {
        if (val < 0) break;
        array.push_back(val);
    }

    int longestAdvance = processArray(array);
    std::cout << longestAdvance << std::endl;

    return 0;
}