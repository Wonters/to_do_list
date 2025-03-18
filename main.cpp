#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

struct Task
{
    string description;
    bool completed;
    string dueDate;
};

string getDueDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d-%H-%M-%S", ltm);
    return string(buffer);
}

void displayTasks(vector<Task> &tasks)
{
    if (tasks.empty())
    {
        cout << "No tasks available." << endl;
        return;
    }
    else
    {
        cout << "List of Tasks:\n";
        sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b)
             { return a.dueDate > b.dueDate; });
        for (size_t i = 0; i < tasks.size(); ++i)
        {
            cout << i + 1 << ". " << (tasks[i].completed ? "[Completed]" : "[Not Completed]") << tasks[i].description << " - Due Date: " << tasks[i].dueDate << endl;
        }
    }
}

void addTask(vector<Task> &tasks)
{
    Task newTask;
    cout << "Enter a new task ";
    cin.ignore();
    getline(cin, newTask.description);
    newTask.completed = false;
    newTask.dueDate = getDueDate();
    tasks.push_back(newTask);
    cout << "Task added successfully!" << endl;
}

void completeTask(vector<Task> &tasks)
{
    displayTasks(tasks);
    if (tasks.empty())
        return;
    cout << "Enter the number of the task to complete: ";
    int index;
    cin >> index;
    if (index > 0 && index <= (int)tasks.size())
    {
        tasks[index - 1].completed = true;
        cout << "Task " << index << " complete" << endl;
    }
    else
    {
        cout << "Invalid task number." << endl;
    }
}

void saveTasks(const vector<Task> &tasks)
{
    ofstream file("tasks.txt");
    if (!file)
    {
        cout << "Unable to save tasks." << endl;
        return;
    }
    for (const auto &task : tasks)
    {
        file << task.description << "|" << (task.completed ? "1" : "0") << endl;
    }
    file.close();
    cout << "Tasks saved successfully!" << endl;
}

void loadTasks(vector<Task> &tasks)
{
    ifstream file("tasks.txt");
    if (!file)
    {
        cout << "No saved tasks found." << endl;
        return;
    }
    string line;
    while (getline(file, line))
    {
        size_t delimiter = line.find("|");
        string description = line.substr(0, delimiter);
        bool completed = line.substr(1, delimiter) == "1";
        Task newTask;
        newTask.description = description;
        newTask.completed = completed;
        tasks.push_back(newTask);
    }
    file.close();
    cout << "Tasks loaded successfully!" << endl;
}

int main()
{
    vector<Task> tasks;
    loadTasks(tasks);
    int choice;
    while (true)
    {
        cout << "\nTo-Do List Application\n";
        cout << "1. Display Tasks\n";
        cout << "2. Add Task\n";
        cout << "3. Complete Task\n";
        cout << "4. Save Tasks\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        
        if (!(cin >> choice)) {
            cin.clear();  // Reset l'état d'erreur
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Vide le buffer
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            displayTasks(tasks);
            break;
        case 2:
            addTask(tasks);
            break;
        case 3:
            completeTask(tasks);
            break;
        case 4:
            saveTasks(tasks);
            cout << "Exiting the application..." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}
