
extern IdGenerator idGenerator;

struct TaskManager
{
    std::vector <Task> tasks;
    int activeParent = 0;
    std::string activeParentText = "main";
    std::stack <int> lastParents;

    TaskManager(std::vector <Task> _tasks)
    {
        tasks = _tasks;
    }

    std::vector <Task*> getActiveTasks()
    {
        std::vector <Task*> activeTasks;

        for (int i=0; i<tasks.size(); i++) {
            if (tasks[i].parentId == activeParent) {
                activeTasks.push_back(&tasks[i]);
            }
        }

        return activeTasks;
    }

    void updateParent(int id)
    {
        lastParents.push(activeParent);
        activeParent = id;

        if (activeParent == 0) {activeParentText = "main";}
        else {activeParentText = findTaskById(activeParent)->text;}
    }

    void setLastParent()
    {
        if (lastParents.empty()) {return;}
        int last = lastParents.top();
        lastParents.pop();
        activeParent = last;

        if (activeParent == 0) {activeParentText = "main";}
        else {activeParentText = findTaskById(activeParent)->text;}

    }

    Task* findTaskById(int id)
    {
        // TODO (szymi#1#): binary search
        for (int i=0; i<tasks.size(); i++) {
            if (tasks[i].id == id) {return &tasks[i];}
        }
    }

    void addTask(std::string text)
    {
        tasks.push_back(Task(idGenerator.getNew(), activeParent, 0, text));
    }

    void deleteTask(int id)
    {
        for (int i=0; i<tasks.size(); i++) {
            if (tasks[i].id == id) {
                tasks.erase(tasks.begin() + i);
                i--;
            }
            else if (tasks[i].parentId == id) {
                    std::cout << 'j';
            std::getchar();
                    deleteTask(tasks[i].id);
            }
        }
    }

    void moveTaskForward(int id)
    {
        findTaskById(id) -> column += 1;
    }

    void moveTaskBackward(int id)
    {
        findTaskById(id) -> column -= 1;
    }

};
