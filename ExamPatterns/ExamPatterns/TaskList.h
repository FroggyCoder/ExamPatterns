#pragma once

#include "Search.h"

TaskListFacade* TaskListFacade::instance = nullptr;

TaskListFacade* TaskListFacade::getinstance()
{
	if (instance == nullptr)
	{
		instance = new TaskListFacade();
	}
	return instance;
}

void TaskListFacade::addTask()
{
	Task newTask;
	system("cls");

	{
		int m = 2;
		gotoxy(30, m++);
		cout << "��� ����: " << endl;

		for_each(taskList->tasks.begin(), taskList->tasks.end(), [&](Task& tk)
		{
			gotoxy(30, m++);
			cout << tk.getTask() << endl;
		});
	}

	{
		string task;
		gotoxy(2, 15);
		cout << "������: ";

		getline(cin, task);
		newTask.setTask(task);
	}

	newTask.setPriority(getPriority());

	{
		Time temp(getTime());
		newTask.setDeadline(temp);
	}
	
	{
		system("cls");
		gotoxy(15, 9);

		if (getNoYes("������ �������� ���?"))
		{
			string Tag;
			cout << "���: ";
			getline(cin, Tag);
			newTask.setTag(Tag);
		}

		else
		{
			newTask.setTag("");
		}

	}
	taskList->tasks.push_back(newTask);
	taskList->sort();
}

void TaskListFacade::deleteTask()
{
	system("cls");
	vector<string> tasks;

	for_each(taskList->tasks.begin(), taskList->tasks.end(), [&tasks](Task& tk) {tasks.push_back(tk.getTask()); });

	if (tasks.size() == 0)
	{
		cout << "��� �������" << endl;
		system("pause");
		return;
	}

	tasks.push_back("�����");
	int c = Menu::select_vertical(tasks, HorizontalAlignment::Center, 11);

	if (c == tasks.size() - 1)
	{
		return;
	}

	auto b = taskList->tasks.begin();
	advance(b, c);
	taskList->tasks.erase(b);
}

void TaskListFacade::clear()
{
	if (getNoYes("�� ������� ��� ������ �������� ���� ������?")) taskList->tasks.clear();
}

void TaskListFacade::fullView()const
{
	system("cls");

	if (taskList->tasks.empty())
	{
		cout << "��� �������" << endl;
		system("pause");

		return;
	}

	for_each(taskList->tasks.begin(), taskList->tasks.end(), [&](Task& tk)
	{
		cout << "������: "    << tk.getTask() << endl;
		cout << "���������: " << tk.getPriority() << endl;
		cout << "�������: "   << tk.getDeadline() << endl;

		if (!tk.getTag().empty())
		{
			cout << "���: " << tk.getTag() << endl;
		}
		cout << "----------------------" << endl;
	});
	system("pause");
}

void TaskListFacade::changeTask()
{
	auto task = taskList->tasks.begin();

	{
		vector<string> tasks;
		for_each(taskList->tasks.begin(), taskList->tasks.end(), [&](Task& tk) {tasks.push_back(tk.getTask()); });

		if (tasks.size() == 0)
		{
			cout << "��� �������" << endl;
			system("pause");
			return;
		}

		int choice = Menu::select_vertical(tasks, HorizontalAlignment::Center, 9);
		advance(task, choice);
	}

	auto changeQuest = [&task]()
	{
		string temp;
		cout << "����� ������: ";
		getline(cin, temp);
		(*task).setTask(temp);
	};

	auto changeDeadline = [&task]()
	{
		Time temp = getTime();
		(*task).setDeadline(temp);
	};

	auto changePriority = [&task]()
	{
		task->setPriority(getPriority());
	};

	auto changeTag = [&task]()
	{
		string temp;
		cout << "����� ���: ";
		getline(cin, temp);
		(*task).setTag(temp);
	};

	int c = 0;

	while (c < 4)
	{
		system("cls");

		c = Menu::select_vertical({ "�������� ������","�������� �������","�������� ���������","�������� ���","�����" }, HorizontalAlignment::Left, 15);

		switch (c)
		{
		case 0:
			changeQuest();
			break;
		case 1:
			changeDeadline();
			break;
		case 2:
			changePriority();
			break;
		case 3:
			changeTag();
			break;
		default:
			break;
		}
	}
}

void TaskListFacade::menu()
{
	int c = 0;

	while (c < 5)
	{
		system("cls");

		{
			int m = 8;
			for_each(taskList->tasks.begin(), taskList->tasks.end(), [&m](Task& tk)
			{
				if (m < 18)
				{
					gotoxy(35, m);
					cout << tk.getTask() << " " << tk.getPriority() << " " << tk.getDeadline() << endl;
				}
				m++;
			});

			if (m > 18)
			{
				gotoxy(40, 20);
				cout << m - 18 << "������ �����" << endl;
			}
		}

		c = Menu::select_vertical({ "�������� ������","������� ������","�������� ������","�������� ������","�������� ��������� ������","�����" }, HorizontalAlignment::Left, 15);
		switch (c)
		{
		case 0:
			addTask();
			break;
		case 1:
			deleteTask();
			break;
		case 2:
			changeTask();
			break;
		case 3:
			clear();
			break;
		case 4:
			fullView();
			break;
		default:
			break;
		}
	}
}

bool TaskListFacade::searchConcrete(const string& tk) const
{
	system("cls");

	for (size_t i = 0; i < taskList->tasks.size(); i++)
	{
		auto b = taskList->tasks.begin();
		advance(b, i);

		if (b->getTask().find(tk) != string::npos)
		{
			cout << "������: " << taskList->name << endl;
			b->print();
			system("pause");
			return true;
		}
	}
	return false;
}

bool TaskListFacade::searchTag(const string& tag) const
{
	bool found = false;
	system("cls");

	for (size_t i = 0; i < taskList->tasks.size(); i++)
	{
		auto b = taskList->tasks.begin();
		advance(b, i);

		if (b->getTag().find(tag) != string::npos)
		{
			cout << "������: " << taskList->name << endl;
			b->print();

			found = true;
		}
	}
	return found;
}

bool TaskListFacade::searchTime(const Time& t) const
{
	bool found = false;
	system("cls");

	for (size_t i = 0; i < taskList->tasks.size(); i++)
	{
		auto b = taskList->tasks.begin();
		advance(b, i);

		if (b->getDeadline() < t)
		{
			cout << "������: " << taskList->name << endl;
			b->print();
			found = true;
		}
	}
	return found;
}

bool TaskListFacade::searchPriority(const Priority& prior) const
{
	bool found = false;
	system("cls");

	for (size_t i = 0; i < taskList->tasks.size(); i++)
	{
		auto b = taskList->tasks.begin();
		advance(b, i);

		if (b->getPriority() == prior)
		{
			cout << "������: " << taskList->name << endl;
			b->print();
			found = true;
		}
	}
	return found;
}

bool TaskListFacade::searchDeadline() const
{
	bool found = false;
	system("cls");

	Time current;
	current.setCurrent();

	for (size_t i = 0; i < taskList->tasks.size(); i++)
	{
		auto b = taskList->tasks.begin();
		advance(b, i);

		if (b->getDeadline() < current || b->withinDay(current))
		{
			cout << "������: " << taskList->name << endl;
			b->print();
			found = true;
		}
	}
	return found;
}

void TaskListFacade::save() const
{
	taskList->save();
}

void TaskListFacade::load()
{
	ifstream in("List\\" + taskList->name + ".txt");
	string newTask, newDeadline, newPriority, newTag;

	while (getline(in, newTask) && getline(in, newDeadline) && getline(in, newPriority) && getline(in, newTag))
	{
		Task temp;
		temp.load(newTask, newDeadline, newPriority, newTag);
		taskList->tasks.push_back(temp);
	}
	taskList->sort();
}
