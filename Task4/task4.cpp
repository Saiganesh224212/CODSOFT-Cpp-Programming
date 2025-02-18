#include <iostream>
#include <vector>
using namespace std;

class Task {
private:
    string description;
    bool isCompleted;

public:
    Task(string desc) : description(desc), isCompleted(false) {}

    void markCompleted() {
        isCompleted = true;
    }

    string getDescription() const {
        return description;
    }

    bool getStatus() const {
        return isCompleted;
    }
};

class ToDoList {
private:
    vector<Task> tasks;

public:
    void addTask(const string& description) {
        tasks.emplace_back(description);
        cout << "✅ Task added successfully!\n";
    }

    void viewTasks() const {
        if (tasks.empty()) {
            cout << "📭 No tasks available.\n";
            return;
        }

        cout << "\n📋 To-Do List:\n";
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << tasks[i].getDescription() 
                 << (tasks[i].getStatus() ? " ✅ [Completed]" : " ⏳ [Pending]") << endl;
        }
    }

    void markTaskCompleted(int index) {
        if (index < 1 || index > tasks.size()) {
            cout << "⚠️ Invalid task number!\n";
            return;
        }
        tasks[index - 1].markCompleted();
        cout << "✅ Task marked as completed!\n";
    }

    void removeTask(int index) {
        if (index < 1 || index > tasks.size()) {
            cout << "⚠️ Invalid task number!\n";
            return;
        }
        tasks.erase(tasks.begin() + index - 1);
        cout << "❌ Task removed successfully!\n";
    }
};

int main() {
    ToDoList todoList;
    int choice;
    
    do {
        cout << "\n📌 TO-DO LIST MANAGER 📌\n";
        cout << "1️⃣ Add Task\n2️⃣ View Tasks\n3️⃣ Mark Task as Completed\n4️⃣ Remove Task\n5️⃣ Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  

        switch (choice) {
            case 1: {
                string taskDesc;
                cout << "📝 Enter task description: ";
                getline(cin, taskDesc);
                todoList.addTask(taskDesc);
                break;
            }
            case 2:
                todoList.viewTasks();
                break;
            case 3: {
                int taskNum;
                cout << "✅ Enter task number to mark as completed: ";
                cin >> taskNum;
                todoList.markTaskCompleted(taskNum);
                break;
            }
            case 4: {
                int taskNum;
                cout << "❌ Enter task number to remove: ";
                cin >> taskNum;
                todoList.removeTask(taskNum);
                break;
            }
            case 5:
                cout << "👋 Exiting To-Do List Manager. Have a productive day!\n";
                break;
            default:
                cout << "⚠️ Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
