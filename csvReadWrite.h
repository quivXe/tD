struct Csv
{

    std::vector <Task> read(std::string filePath)
    {
        std::fstream file;
        file.open(filePath, std::ios::in);

        std::vector <Task> tasks;

        std::string line;
        while(std::getline(file, line)) {

            int commaCounter = 0;
            std::string col = "";
            int id, parentId, column;

            for (char c : line) {
                if (c == ',' && commaCounter < 3) {
                    int var = std::stoi(col);


                    switch (commaCounter)
                    {
                    case 0:
                        id = var;
                        break;
                    case 1:
                        parentId = var;
                        break;
                    case 2:
                        column = var;
                        break;
                    }

                    col = "";
                    commaCounter ++;
                    continue;
                }
                col += c;
            }
            tasks.push_back( Task( id, parentId, column, col ) );
        }
        file.close();
        return tasks;
    }

    void write(std::string filePath, std::vector<Task> tasks)
    {
        std::fstream file;
        file.open(filePath, std::ios::out | std::ios::trunc);

        for (Task task : tasks) {
            file << task.id << ','
            << task.parentId << ','
            << task.column << ','
            << task.text << '\n';
        }

        file.close();
    }

};
