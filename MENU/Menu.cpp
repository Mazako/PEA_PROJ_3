#include "Menu.h"
#include "PeaUtils.h"
#include "GeneticAlgorithm.h"
#include "ShortestPathResults.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

void Menu::start() {
    bool program = true;
    std::string option;
    cout << "Pea, zadanie 3" << endl;
    cout << "Autor: Michal Maziarz (263913)" << endl;
    while (program) {
        for (int i = 0; i < 4; i++) {
            cout << endl;
        }
        cout << "Macierz: " << (!matrix ? "BRAK" : matrix->getName()) << endl;
        cout << "Aktualny operator krzyzowania: " << crossingMode << endl;
        cout << "(wsp mutacji, wsp krzyzowania, populacja, czas) = " << "(" << mutationFactor << ", " << crossingFactor << ", " << populationSize << ", " << maxSecondsTime << ")" << endl;
        cout << "1) Wczytaj macierz z pliku" << endl;
        cout << "2) Wybierz wspolczynnik krzyzowania" << endl;
        cout << "3) Wybierz wspolczynnik mutacji" << endl;
        cout << "4) Wybierz wielkosc populacji" << endl;
        cout << "5) Wybierz maksymalny czas" << endl;
        cout << "6) Wykonaj algorytm" << endl;
        cout << "7) Oblicz koszt drogi z pliku (dla aktualnej macierzy)" << endl;
        cout << "8) Zmien operator krzyzowania" << endl;
        cout << "0) Zakoncz program" << endl;
        cout << "Wybierz opcje: ";
        std::getline(std::cin, option);
        if (option == "1") {
            readMatrix();
        } else if (option == "2") {
            setCrossingFactor();
        } else if (option == "3") {
            setMutationFactor();
        } else if (option == "4") {
            setPopulationSize();
        } else if (option == "5") {
            setMaxTime();
        } else if (option == "6") {
            performGA();
        } else if (option == "7") {
            readResultFileAndCalcPath();
        } else if (option == "8") {
            changeCrossingMode();
        } else if (option == "0") {
            program = false;
        } else {
            cout << "Nie ma takiej opcji" << endl;
        }
    }
}

void Menu::readMatrix() {
    std::string path;
    std::string option;
    cout << "1) Plik .atsp" << endl;
    cout << "2) Plik .xml" << endl;
    cout << "Wybierz opcje: ";
    std::getline(cin, option);
    if (option != "1" && option != "2") {
        cout << "Nie ma takiej opcji.";
        return;
    }
    cout << "Podaj sciezke do pliku: ";
    std::getline(std::cin, path);
    try {
        TspMatrix* matrix;
        if (option == "1") {
            matrix = PeaUtils::readMatrixFromAtspFile(path);
        } else {
            matrix = PeaUtils::readMatrixFromXmlFile(path);
        }
        delete this->matrix;
        this->matrix = matrix;
    } catch (std::exception& e) {
        cout << "Problem z wczytaniem pliku" << endl;
    }

}

void Menu::setMutationFactor() {
    cout << "Podaj wartosc: ";
    cin >> mutationFactor;
    getchar();
}

void Menu::setCrossingFactor() {
    cout << "Podaj wartosc: ";
    cin >> crossingFactor;
    getchar();
}

void Menu::setMaxTime() {
    cout << "Podaj wartosc: ";
    cin >> maxSecondsTime;
    getchar();

}

void Menu::setPopulationSize() {
    cout << "Podaj wartosc: ";
    cin >> populationSize;
    getchar();

}

void Menu::readResultFileAndCalcPath() {
    if (matrix == nullptr) {
        cout << "Wybierz macierz!" << endl;
        return;
    }
    std::string path;
    std::string option;
    cout << "Podaj sciezke do pliku: ";
    std::getline(std::cin, path);
    try {
        auto result = PeaUtils::readPathAndCalculateCost(matrix, path);
        cout << "Wynik: " << result << endl;
    } catch (std::exception& e) {
        cout << "Problem z wczytaniem pliku" << endl;
    }
}

void Menu::performGA() {
    if (matrix == nullptr) {
        cout << "Wybierz macierz!" << endl;
        return;
    }
    auto results = GeneticAlgorithm::solve(matrix, maxSecondsTime, populationSize, crossingMode, crossingFactor, mutationFactor);
    cout << results->toString() << endl;
    cout << "Zapisano sciezke rozwiazania w pliku: " << results->getFilePath() << endl;
    delete results;

}

void Menu::changeCrossingMode() {
    if (crossingMode == "OX") {
        crossingMode = "PMX";
    } else {
        crossingMode = "OX";
    }
}
