#include "Menu.h"
#include <any>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include "BSTree.h"
#include "input.h"
#include <ctime>
#include <random>
#include "FileLogging.h"

void PrintHorisontalBSTree(std::vector<std::any> params);
void PrintHorisontalWithBranchesBSTree(std::vector<std::any> params);
void PrintVerticalBSTree(std::vector<std::any> params);
void PrintVerticalWithBranchesBSTree(std::vector<std::any> params);

void InorderTraversalBSTree(std::vector<std::any> params);
void PreorderTraversalBSTree(std::vector<std::any> params);
void PostorderTraversalBSTree(std::vector<std::any> params);

void InsertNodeInBSTree(std::vector<std::any> params);
void RemoveNodeFromBSTree(std::vector<std::any> params);
void BSTreeIsEmpty(std::vector<std::any> params);
void GetNodeCount(std::vector<std::any> params);
void IndividualTask(std::vector<std::any> params);
void FindNodeInBSTree(std::vector<std::any> params);
void GetRandomBSTree(std::vector<std::any> params);

void ReadErrorLog(std::vector<std::any> params);
void ReadOutputLog(std::vector<std::any> params);
void ReadInputFile(std::vector<std::any> params);

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");
    std::string load_data_file = "Input.txt";
    std::string write_data_file = "output_log.txt";
    std::string log_data_file = "error_log.txt";
    if (argc >= 3)
    {
        load_data_file = argv[1];
        write_data_file = argv[2];
        log_data_file = argv[3];
    }
    BSTree* bstree = new BSTree();
    FileLogging errorLog(log_data_file);
    FileLogging outputLog(write_data_file);
    FileLogging inputFile(load_data_file);
    std::vector<std::any> params { bstree, errorLog, outputLog, inputFile };
    Menu menu = Menu("Главное", std::vector<Menu>
    {
        Menu("Вывести дерево", std::vector<Menu>
        {
            Menu("Горизонтально без ветвей", PrintHorisontalBSTree),
            Menu("Горизонтально с ветвями",  PrintHorisontalWithBranchesBSTree),
            Menu("Вертикально без ветвей",   PrintVerticalBSTree),
            Menu("Вертикально с ветвями",    PrintVerticalWithBranchesBSTree),
        }),
        Menu("Выполнить обход дерева", std::vector<Menu>
        {
            Menu("Симметричный", InorderTraversalBSTree),
            Menu("Прямой", PreorderTraversalBSTree),
            Menu("Обратный", PostorderTraversalBSTree)
        }),
        Menu("Вставить элемент",            InsertNodeInBSTree),
        Menu("Удалить элемент",             RemoveNodeFromBSTree),
        Menu("Проверка дерева на пустоту",  BSTreeIsEmpty),
        Menu("Получить количество узлов в дереве", GetNodeCount),
        Menu("Заполнить дерево случайными элементами", GetRandomBSTree),
        Menu("Индивидуальное задание",      IndividualTask),
        Menu("Есть ли элемент в дереве",    FindNodeInBSTree),
        Menu("Открыть " + log_data_file,       ReadErrorLog),
        Menu("Открыть " + write_data_file,      ReadOutputLog),
        Menu("Считать данные из " + load_data_file, ReadInputFile)
    });
    menu.Run(params);
    delete bstree;
    ShowCursor();
    return 0;
}

void InsertNodeInBSTree(std::vector<std::any> params)
{
    auto bstree = any_cast<BSTree*>(params[0]);
    auto error_log = any_cast<FileLogging>(params[1]);
    auto output_log = any_cast<FileLogging>(params[2]);
    if (!bstree)
    {
        std::cout << "Дерево еще не создано.\n";
        return;
    }
    int data = Input("Введите значение узла, который хотите вставить в дерево: ", INT_MIN, INT_MAX, error_log);
    if (bstree->FindNode(data))
    {
        std::cout << "Узел с таким значением уже есть в дереве.\n";
        return;
    }
    bstree->Insert(data);
    std::cout << "Узел успешно добавлен в дерево!\n";
    output_log.Logging(bstree->getInorderTraversal());
}

void RemoveNodeFromBSTree(std::vector<std::any> params)
{
    auto bstree = any_cast<BSTree*>(params[0]);
    auto error_log = any_cast<FileLogging>(params[1]);
    auto output_log = any_cast<FileLogging>(params[2]);
    if (!bstree)
    {
        std::cout << "Дерево еще не создано.\n";
        return;
    }
    int data = Input("Введите значение узла, который хотите удалить из дерева: ", INT_MIN, INT_MAX, error_log);
    if (!bstree->FindNode(data))
    {
        std::cout << "Узла с таким значением не существует дереве.\n";
        return;
    }
    bstree->RemoveNode(data);
    std::cout << "Узел успешно удален из дерева!\n";
    output_log.Logging(bstree->getInorderTraversal());
}

void BSTreeIsEmpty(std::vector<std::any> params)
{
    auto bstree = any_cast<BSTree*>(params[0]);
    std::cout << "Дерево пусто: " << (bstree->isEmpty() ? "да" : "нет") << "\n";
}

void PrintHorisontalBSTree(std::vector<std::any> params)
{
    auto bstree = any_cast<BSTree*>(params[0]);
    if (bstree->isEmpty())
    {
        std::cout << "Дерево пусто\n";
        return;
    }
    bstree->PrintHorizontal();
}

void PrintHorisontalWithBranchesBSTree(std::vector<std::any> params)
{
    auto bstree = any_cast<BSTree*>(params[0]);
    if (bstree->isEmpty())
    {
        std::cout << "Дерево пусто\n";
        return;
    }
    bstree->PrintHorizontalWithBranches();
}

void PrintVerticalBSTree(std::vector<std::any> params)
{
    auto bstree = any_cast<BSTree*>(params[0]);
    if (bstree->isEmpty())
    {
        std::cout << "Дерево пусто\n";
        return;
    }
    bstree->PrintVertical();
}

void PrintVerticalWithBranchesBSTree(std::vector<std::any> params)
{
    auto bstree = any_cast<BSTree*>(params[0]);
    if (bstree->isEmpty())
    {
        std::cout << "Дерево пусто\n";
        return;
    }
    bstree->PrintVerticalWithBranches();
}

void GetRandomBSTree(std::vector<std::any> params)
{
    auto bstree = any_cast<BSTree*>(params[0]);
    auto error_log = any_cast<FileLogging>(params[1]);
    auto output_log = any_cast<FileLogging>(params[2]);
    srand(time(nullptr));
    int countNodes = Input("Введите количество узлов в дереве: ", 1, 100, error_log);
    for (int i = 0; i < countNodes; i++)
    {
        bstree->Insert(rand() % 300);
    }
    std::cout << "Дерево успешно заполнено случайными элементами.\n";
    output_log.Logging(bstree->getInorderTraversal());
}

void GetNodeCount(std::vector<std::any> params)
{
    auto bstree = any_cast<BSTree*>(params[0]);
    std::cout << "Количество узлов в дереве: " << bstree->NodeCount() << "\n";
}

void FindNodeInBSTree(std::vector<std::any> params)
{
    auto bstree = any_cast<BSTree*>(params[0]);
    auto error_log = any_cast<FileLogging>(params[1]);
    if (bstree->isEmpty())
    {
        std::cout << "Дерево пусто\n";
        return;
    }
    int data = Input("Введите значение узла, который хотите найти в дереве: ", INT_MIN, INT_MAX, error_log);
    std::cout << "Узел с таким значением есть в дереве: " << (bstree->FindNode(data) ? "да" : "нет");
}

void IndividualTask(std::vector<std::any> params)
{
    auto bstree = any_cast<BSTree*>(params[0]);
    auto error_log = any_cast<FileLogging>(params[1]);
    if (bstree->isEmpty())
    {
        std::cout << "Дерево пусто\n";
        return;
    }
    int level = Input("Введите уровень, на котором хотите узнать количество узлов: ", 0, bstree->getHeight(), error_log);
    std::cout << "Количество узлов на " << level << " уровне: " << bstree->CountNodesOnLevel(level) << "\n";
}

void InorderTraversalBSTree(std::vector<std::any> params)
{
    auto bstree = any_cast<BSTree*>(params[0]);
    if (bstree->isEmpty())
    {
        std::cout << "Дерево пусто\n";
        return;
    }
    bstree->InorderTraversal();
    std::cout << std::endl;
}

void PreorderTraversalBSTree(std::vector<std::any> params)
{
    auto bstree = any_cast<BSTree*>(params[0]);
    if (bstree->isEmpty())
    {
        std::cout << "Дерево пусто\n";
        return;
    }
    bstree->PreorderTraversal();
    std::cout << std::endl;
}

void PostorderTraversalBSTree(std::vector<std::any> params)
{
    auto bstree = any_cast<BSTree*>(params[0]);
    if (bstree->isEmpty())
    {
        std::cout << "Дерево пусто\n";
        return;
    }
    bstree->PostorderTraversal();
    std::cout << std::endl;
}

void ReadErrorLog(std::vector<std::any> params)
{
    auto error_log = any_cast<FileLogging>(params[1]);
    error_log.PrintFile();
}

void ReadOutputLog(std::vector<std::any> params)
{
    auto output_log = any_cast<FileLogging>(params[2]);
    output_log.PrintFile();
}

void ReadInputFile(std::vector<std::any> params)
{
    auto bstree = any_cast<BSTree*>(params[0]);
    auto output_log = any_cast<FileLogging>(params[2]);
    auto fl = any_cast<FileLogging>(params[3]);
    auto inp = fl.getFileName();
    fl.PrintFile();
    std::cout << inp << std::endl;
    std::fstream fin(inp, std::ios::in);
    if (fin.is_open())
    {
        int data;
        while (fin >> data)
        {
            bstree->Insert(data);
        }
    }
    std::cout << "Данные успешно считались!\n";
    fin.close();
    output_log.Logging(bstree->getInorderTraversal());
}
