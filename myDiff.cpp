#include <bits/stdc++.h>
#include <unordered_set>

std::string ReadFileData(std::ifstream& in) {
    std::string text1,s;
    while (std::getline(in, s)) {
        text1 += s + '\n';
    }
    return text1;
}

void WriteDataToFile(std::ofstream& out, const std::string& text) {
    out << text;
}

//Удаляем пробелы в начале предложений.

void StripString(std::string& sequence) {
    size_t spaceCount = 0;
    for (const auto symbol : sequence) {
        if (!std::isspace(symbol)) {
            break;
        }
        ++spaceCount;
    }

    if (spaceCount) {
        sequence.erase(0, spaceCount);
    }
}


// Делим текст на предложения и получаем вектор строк

std::vector<std::string> SplitText(const std::string& text) {
    const std::unordered_set<char> delimeters = {'.', '!', '?'};

    std::vector<std::string> resultSequences;
    std::string tmpSequence;
    for (size_t idx = 0; idx < text.length(); ++idx) {
        if (delimeters.find(text[idx]) != delimeters.end() &&
            (idx == text.length() - 1 ||
            std::isspace(text[idx + 1])) &&
            (!std::isdigit(text[idx-1]))) {
            resultSequences.push_back(tmpSequence);
            tmpSequence.clear();
            continue;
        }

        tmpSequence += text[idx];
    }

    resultSequences.push_back(tmpSequence);

    for (auto& item : resultSequences) {
        StripString(item);
    }

    return resultSequences;
}


// Ищем различия в текстах.

std::string CalculateDifference(const std::string& text1, const std::string& text2) {
    std::vector<std::string> sequences1 = SplitText(text1);
    std::vector<std::string> sequences2 = SplitText(text2);
    std::string result;

    result += std::string("Отсутствует в новой редакции:\n\n");

    for (const auto& item1 : sequences1){
        for (auto& item2 : sequences2) {
            if (item1 == item2) {
                item2 = "pz"; // Если предложение присутствует в обоих редакциях, то присваиваем ему нестандартное значение
                break;
            }
            if (item2 == sequences2.back()) {
                result += item1 + '\n';
            }
        }
    }

    result += std::string("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nОтсутствует в основном документе:\n\n");

    for (const auto& item : sequences2) {
        if (item != "pz") {
            result += item + '\n';
        }
    }

    return result;

}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cout << "Incorrect number of arguments. Please check it" << std::endl;
        return 0;
    }

    std::ifstream fileInput1(argv[1]);
    std::ifstream fileInput2(argv[2]);
    std::ofstream fileOutput1("result.txt");
    std::ofstream fileOutput2("time.txt");

    const std::string text1 = ReadFileData(fileInput1);
    const std::string text2 = ReadFileData(fileInput2);

    std::string resultDiff = CalculateDifference(text1, text2);
    std::string resultTime = std::string("Время выполнения программы в секундах:");

    float runtime = clock();
    resultTime += std::to_string(runtime/CLOCKS_PER_SEC) + '\n';

    WriteDataToFile(fileOutput1, resultDiff);
    WriteDataToFile(fileOutput2, resultTime);

    fileInput1.close();
    fileInput2.close();
    fileOutput1.close();
    fileOutput2.close();
    return 0;
}

