//
// Created by stas on 6.11.19.
//
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <tuple>
/*
using namespace std;

enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;*/

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo &GetPersonTasksInfo(const string &person) const {
        return TasksInfoOfPerson.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string &person) {
        ++TasksInfoOfPerson[person][TaskStatus::NEW];
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
            const string &person, int task_count) {

        auto& info = TasksInfoOfPerson[person];
        TasksInfo new_info = info;
        TasksInfo updated;
        TasksInfo not_updated;

        for(int i = 1; i < 4; ++i){
            int next_add = min(task_count, info[IntToTaskStatus(i - 1)]);
            new_info[IntToTaskStatus(i - 1)] -= next_add;
            new_info[IntToTaskStatus(i)] += next_add;

            updated[IntToTaskStatus(i)] = next_add;

            not_updated[IntToTaskStatus(i-1)] = info[IntToTaskStatus(i-1)] - next_add;

            task_count -= next_add;
        }

        RemoveEmpty(updated);
        RemoveEmpty(not_updated);
        info = new_info;
        return tie(updated, not_updated );
    }

private:
    void RemoveEmpty(TasksInfo& info){
        vector<TaskStatus> black_list;
        for(const auto &p : info){
            if(p.second <= 0){
                black_list.push_back(p.first);
            }
        }

        for(const auto &item : black_list){
            info.erase(item);
        }
    }

    int TaskStatusToInt(const TaskStatus& status){
        return static_cast<int>(status);
    }

    TaskStatus IntToTaskStatus(int i){
        return static_cast<TaskStatus>(i);
    }

    map<string, TasksInfo> TasksInfoOfPerson;
};

/*
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
         ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
         ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
         ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    return 0;
}*/