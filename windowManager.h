
extern TaskManager taskMgr;
extern int max(int, int);
extern const std::string COL_SEPARATOR, ROW_SEPARATOR;

enum
{
    TODO = 0,
    DOING = 1,
    DONE = 2
};;

struct WindowManager
{
    std::vector <Task*> todo, doing, done;

    void updateActiveTasks()
    {
        todo.clear(); doing.clear(); done.clear();

        std::vector <Task*> activeTasks = taskMgr.getActiveTasks();

        for (int i=0; i<activeTasks.size(); i++) {
            switch (activeTasks[i]->column)
            {
            case TODO:
                todo.push_back(activeTasks[i]);
                break;
            case DOING:
                doing.push_back(activeTasks[i]);
                break;
            case DONE:
                done.push_back(activeTasks[i]);
                break;
            }
        }
    }

    void printTree(int taskId, std::string taskText)
    {
        std::cout << createTree(taskId, taskText, 0);
    }
    void printColumns()
    {

        // header

        std::cout << getHeader();


//        int todoLength = vector_length<*Task>(todo);
//        int doingLength = vector_length<*Task>(doing);
//        int doneLength = vector_length<*Task>(done);
        unsigned int todoLength = todo.size();
        unsigned int doingLength = doing.size();
        unsigned int doneLength = done.size();

        for (int i=0; i<( max( max( todoLength, doingLength ), doneLength ) ); i++) {
            std::string todoOverlap = (i < todoLength) ? ( std::to_string(i+1) + ") " + todo[i]->text ) : "";
            std::string doingOverlap = (i < doingLength) ? ( std::to_string(i+1) + ") " + doing[i]->text ) : "";
            std::string doneOverlap = (i < doneLength) ? ( std::to_string(i+1) + ") " + done[i]->text ) : "";

            std::cout << getPrintableLine(todoOverlap, doingOverlap, doneOverlap);

            printRowSeparator();
        }
    }
private:

    std::string getPrintableLine(std::string todoOverlap, std::string doingOverlap, std::string doneOverlap)
    {
        if (todoOverlap.length() == 0 && doingOverlap.length() == 0 && doneOverlap.length() == 0) {
            return "";
        }
        std::string todoString, doingString, doneString;

        if (todoOverlap.length() > COL_WIDTH) {
            todoString = todoOverlap.substr(0, COL_WIDTH);
            todoOverlap = todoOverlap.substr(COL_WIDTH, todoOverlap.length() - COL_WIDTH);
        }
        else {
            todoString = fillToColWidth(todoOverlap, ' ');
            todoOverlap = "";
        }

        if (doingOverlap.length() > COL_WIDTH) {
            doingString = doingOverlap.substr(0, COL_WIDTH);
            doingOverlap = doingOverlap.substr(COL_WIDTH, doingOverlap.length() - COL_WIDTH);
        }
        else {
            doingString = fillToColWidth(doingOverlap, ' ');
            doingOverlap = "";
        }

        if (doneOverlap.length() > COL_WIDTH) {
            doneString = doneOverlap.substr(0, COL_WIDTH);
            doneOverlap = doneOverlap.substr(COL_WIDTH, doneOverlap.length() - COL_WIDTH);
        }
        else {
            doneString = fillToColWidth(doneOverlap, ' ');
            doneOverlap = "";
        }

        std::string line = COL_SEPARATOR + todoString + COL_SEPARATOR + doingString + COL_SEPARATOR + doneString + COL_SEPARATOR + '\n';
        return line + getPrintableLine(todoOverlap, doingOverlap, doneOverlap);
    }

    std::string fillToColWidth(std::string str, char c)
    {
        return str + multiplyString(c, COL_WIDTH - str.length());
    }
    std::string fillToColWidth(std::string str, std::string c)
    {
        return str + multiplyString(c, COL_WIDTH - str.length());
    }

    void printRowSeparator()
    {
        std::cout <<
        COL_SEPARATOR << fillToColWidth("", ROW_SEPARATOR) <<
        COL_SEPARATOR << fillToColWidth("", ROW_SEPARATOR) <<
        COL_SEPARATOR << fillToColWidth("", ROW_SEPARATOR)
        << COL_SEPARATOR << std::endl;
    }

    std::string centerString(std::string str)
    {
        int leftOffset = (COL_WIDTH - str.length()) / 2;
        int rightOffset = COL_WIDTH - str.length() - leftOffset;
        std::string result = "";

        result += multiplyString(' ', leftOffset);
        result += str;
        result += multiplyString(' ', rightOffset);

        return result;
    }

    std::string getHeader()
    {
        std::string todoLine1 = R"( ___   _   __    _  )";
        std::string todoLine2 = R"(|_ _| / \ |  \  / \ )";
        std::string todoLine3 = R"( | | ( o )| o )( o ))";
        std::string todoLine4 = R"( |_|  \_/ |__/  \_/ )";

        std::string doingLine1 = R"( __    _   _  _  _   __ )";
        std::string doingLine2 = R"(|  \  / \ | || \| | / _|)";
        std::string doingLine3 = R"(| o )( o )| || \\ |( |_n)";
        std::string doingLine4 = R"(|__/  \_/ |_||_|\_| \__/)";

        std::string doneLine1 = R"( __    _   _  _  ___ )";
        std::string doneLine2 = R"(|  \  / \ | \| || __|)";
        std::string doneLine3 = R"(| o )( o )| \\ || _| )";
        std::string doneLine4 = R"(|__/  \_/ |_|\_||___|)";

        return
        multiplyString(' ', COL_SEPARATOR.length() - 1) + "=" + fillToColWidth("", '=') + multiplyString("=", COL_SEPARATOR.length()) + fillToColWidth("", '=') + multiplyString("=", COL_SEPARATOR.length()) + fillToColWidth("", '=') + "=" + '\n' +
        COL_SEPARATOR + centerString(todoLine1) + COL_SEPARATOR + centerString(doingLine1) + COL_SEPARATOR + centerString(doneLine1) + COL_SEPARATOR + '\n' +
        COL_SEPARATOR + centerString(todoLine2) + COL_SEPARATOR + centerString(doingLine2) + COL_SEPARATOR + centerString(doneLine2) + COL_SEPARATOR + '\n' +
        COL_SEPARATOR + centerString(todoLine3) + COL_SEPARATOR + centerString(doingLine3) + COL_SEPARATOR + centerString(doneLine3) + COL_SEPARATOR + '\n' +
        COL_SEPARATOR + centerString(todoLine4) + COL_SEPARATOR + centerString(doingLine4) + COL_SEPARATOR + centerString(doneLine4) + COL_SEPARATOR + '\n' +
        COL_SEPARATOR + fillToColWidth("", '=') + multiplyString("=", COL_SEPARATOR.length()) + fillToColWidth("", '=') + multiplyString("=", COL_SEPARATOR.length()) + fillToColWidth("", '=') + COL_SEPARATOR + '\n' +
        multiplyString(" ", COL_SEPARATOR.length()) + makeTextFitScreen(taskMgr.activeParentText) + '\n' +
        COL_SEPARATOR + fillToColWidth("", '=') + multiplyString("=", COL_SEPARATOR.length()) + fillToColWidth("", '=') + multiplyString("=", COL_SEPARATOR.length()) + fillToColWidth("", '=') + COL_SEPARATOR + '\n';


    }

    std::string makeTextFitScreen(std::string str)
    {
        std::string result = "";
        for (int i=0, charsInLine=0; i<str.length(); i++) {
            if (charsInLine >= COL_WIDTH) {
                charsInLine = 0;
                result += '\n';
            }
            result += str[i];
        }

        return result;
    }

    std::string multiplyString(char c, int n)
    {
        std::string result = "";
        for (int i=0; i<n; i++){
            result += c;
        }
        return result;
    }
    std::string multiplyString(std::string c, int n)
    {
        std::string result = "";
        for (int i=0; i<n; i++){
            result += c;
        }
        return result;
    }

    std::string createTree(int taskId, std::string taskText, int tabs)
    {
        std::string result = taskText + '\n';
        for (int i=0; i<taskMgr.tasks.size(); i++) {
            Task task = taskMgr.tasks[i];
            if (task.parentId == taskId) {
                result += multiplyString("     ", tabs) + "|____" + createTree(task.id, task.text, tabs+1);
            }
        }
        return result;
    }


};
