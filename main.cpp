#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <stdlib.h>
#include <sstream>

#define COL_WIDTH 30 // in chars

struct IdGenerator
{
    int currentId;
    IdGenerator()
    {
        std::fstream file;
        file.open("./data/id.txt", std::ios::in);
        file >> currentId;
        file.close();
    }

    int getNew()
    {
        std::fstream file;
        file.open("./data/id.txt", std::ios::out | std::ios::trunc);
        file << ++currentId;
        file.close();
        return currentId;
    }
}idGenerator;;

#include "task.h"
#include "csvReadWrite.h"
#include "taskManager.h"
#include "windowManager.h"
#include "userManager.h"

const std::string FILE_PATH = "./data/data.csv";
const std::string COL_SEPARATOR = " | ", ROW_SEPARATOR = "-";
bool running = true;

int max(int a, int b) { return (a<b)?b:a; }




std::vector <Task> temp()
{
    std::vector <Task> tasks;
    for (int i=0; i<10; i++) {
        std::string str = "fdasdfsdafff fdsf aas, fkdakfk ad:: fdafe ";
        str += std::to_string(i*231);
        tasks.push_back(Task(i, 0, 0, str));
    }
    return tasks;
}

Csv csv;
TaskManager taskMgr(csv.read(FILE_PATH));
WindowManager windowMgr;
UserMangager userMgr;

int main()
{
    windowMgr.updateActiveTasks();
    windowMgr.printColumns();

    std::string userInput;

    while (running) {
        std::cout << std::endl << " > ";
        std::getline(std::cin, userInput);

        userMgr.handleUserInput(userInput);

        system("CLS");
        windowMgr.updateActiveTasks();
        windowMgr.printColumns();

        csv.write(FILE_PATH, taskMgr.tasks);
    }

    return 0;
}
