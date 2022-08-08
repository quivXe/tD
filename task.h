class Task
{
public:
    int id, parentId, column;
    std::string text;

    Task(int _id, int _parentId, int _column, std::string _text)
    {
        id = _id;
        parentId = _parentId;
        column = _column;
        text = _text;
    }
};
