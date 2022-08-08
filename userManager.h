extern TaskManager taskMgr;
extern WindowManager windowMgr;
extern bool running;

struct UserMangager
{
    void handleUserInput(std::string input)
    {
        std::istringstream ssLine(input);

        std::string command;
        ssLine >> command;

        if (command == "goto") {
            int op1, op2; // op1 - column, op2 - task number
            ssLine >> op1 >> op2;
            int selectedTaskIndex = op2 - 1;
            std::vector <Task*> selectedColumn;
            switch (op1)
            {
            case 1:
                selectedColumn = windowMgr.todo;
                break;
            case 2:
                selectedColumn = windowMgr.doing;
                break;
            case 3:
                selectedColumn = windowMgr.done;
                break;
            }
            if (selectedColumn.size() > 0 && selectedTaskIndex < selectedColumn.size() && selectedTaskIndex >= 0) {
                Task* selectedTask = selectedColumn[selectedTaskIndex];
                taskMgr.updateParent(selectedTask->id);
            }
        }

        else if (command == "back") {
            taskMgr.setLastParent();
        }

        else if (command == "add") {
            std::string op1; // op1 - new task name
            std::string name;
            while (ssLine >> op1) {
                name += op1 + ' ';
            }
            name.pop_back();
            taskMgr.addTask(name);
        }

        else if (command == "del" || command == "rem" || command == "delete" || command == "remove") {
            int op1, op2; // op1 - column, op2 - task number
            ssLine >> op1 >> op2;
            int selectedTaskIndex = op2 - 1;
            std::vector <Task*> selectedColumn;
            switch (op1)
            {
            case 1:
                selectedColumn = windowMgr.todo;
                break;
            case 2:
                selectedColumn = windowMgr.doing;
                break;
            case 3:
                selectedColumn = windowMgr.done;
                break;
            }
            if (selectedColumn.size() > 0 && selectedTaskIndex < selectedColumn.size() && selectedTaskIndex >= 0) {
                Task* selectedTask = selectedColumn[selectedTaskIndex];
                taskMgr.deleteTask(selectedTask->id);
            }
        }

        else if (command == "move") {
            std::string op1; int op2, op3; // op1- f/b (forwards backwards), op2 - column, op3 - task number
            ssLine >> op1 >> op2 >> op3;
            int selectedTaskIndex = op3 - 1;
            std::vector <Task*> selectedColumn;

            if(op1 == "f")
            {
                switch (op2)
                {
                case 1:
                    selectedColumn = windowMgr.todo;
                    break;
                case 2:
                    selectedColumn = windowMgr.doing;
                    break;
                }
                if (selectedColumn.size() > 0 && selectedTaskIndex < selectedColumn.size() && selectedTaskIndex >= 0) {
                    Task* selectedTask = selectedColumn[selectedTaskIndex];
                    taskMgr.moveTaskForward(selectedTask->id);
                }
            }

            else if(op1 == "b")
            {
                switch (op2)
                {
                case 2:
                    selectedColumn = windowMgr.doing;
                    break;
                case 3:
                    selectedColumn = windowMgr.done;
                    break;
                }
                if (selectedColumn.size() > 0 && selectedTaskIndex < selectedColumn.size() && selectedTaskIndex >= 0) {
                    Task* selectedTask = selectedColumn[selectedTaskIndex];
                    taskMgr.moveTaskBackward(selectedTask->id);
                }
            }
        }
        else if (command == "tree")
        {
            std::cout << std::endl;
            windowMgr.printTree(taskMgr.activeParent, taskMgr.activeParentText);
            std::getchar();
        }

        else if (command == "q" || command == "quit")
        {
            running = false;
        }

        else if (command == "help" || command == "?" || command == "h")
        {
            std::cout << std::endl <<
            "help/h/? - displays commands" << std::endl <<
            "add [text] - add tasks with given text" << std::endl <<
            "del/delete/rem/remove [column] [number] - removes task (and its subtasks) from given column (1 - todo, 2 - doing, 3 - done), with given number" << std::endl <<
            "goto [column] [number] - goes to task from given column (1 - todo, 2 - doing, 3 - done), with given number" << std::endl <<
            "back - goes task back" << std::endl <<
            "move [f or b] [column] [number] - moves forward(f) or backward(b) (ex. from todo to doing) with given column (1 - todo, 2 - doing, 3 - done), with given number" << std::endl <<
            "tree - displays tree of tasks starting from current" << std::endl <<
            "q/quit - quits" << std::endl << std::endl ;

            std::getchar();
        }

    }
};
