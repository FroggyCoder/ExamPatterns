#pragma once

namespace fs = std::experimental::filesystem;
#include "TaskListManager.h"

int chooseList(list<std::shared_ptr<TaskList>> List)
{
	vector<string> lists;

	for_each(List.begin(), List.end(), [&lists](std::shared_ptr<TaskList> tl)
	{
		lists.push_back((*tl).name);
	});

	if (lists.size() == 0)
	{
		cout << "��� �������" << endl;
		system("pause");

		return -1;
	}

	lists.push_back("�����");
	int c = Menu::select_vertical(lists, HorizontalAlignment::Center, 9);

	if (c == lists.size() - 1)
	{
		return -1;
	}
	return c;
}

class ToDoFacade
{
	static ToDoFacade* instance;
	list<std::shared_ptr<TaskList>> List;
	TaskListFacade* manager = TaskListFacade::getinstance();
	ToDoFacade() {};
	void addList();
	void deleteList();
	void configureList();
	void search();
	void save();
	void load();
public:
	static ToDoFacade* getinstance();
	void menu();
};

ToDoFacade* ToDoFacade::instance = nullptr;

ToDoFacade* ToDoFacade::getinstance()
{
	if (instance == nullptr)
	{
		instance = new ToDoFacade();
	}
	return instance;
}

void ToDoFacade::addList()
{
	{
		int m = 2;
		gotoxy(50, m++);
		cout << "��� ����: ";
		for (size_t i = 0; i < List.size(); i++)
		{
			auto b = List.begin();
			advance(b, i);
			gotoxy(50, m++);
			cout << (*b)->name << endl;
		}
	}

	string temp;
	gotoxy(2, 12);
	cout << "�������� ������ ������: ";
	getline(cin, temp);

	TaskList bs(temp);
	List.push_back(make_shared<TaskList>(bs));
}

void ToDoFacade::deleteList()
{
	int c = chooseList(List);

	if (c < 0)
	{
		return;
	}

	auto b = List.begin();
	advance(b, c);

	if (fs::exists("To-Do\\" + (*b)->name + ".txt"))
	{
		fs::remove("To-Do\\" + (*b)->name + ".txt");
	}

	List.erase(b);
}

void ToDoFacade::configureList()
{
	int c = chooseList(List);

	if (c < 0)
	{
		return;
	}
	auto list = List.begin();
	advance(list, c);

	manager->setTaskList(*list);
	manager->menu();
}

void ToDoFacade::search()
{
	ISearchCommand* command = nullptr;
	int c = 0;

	while (c < 5)
	{
		system("cls");

		c = Menu::select_vertical({ "����� �� ������","����� �� ����","����� �� ����","����� �� ����������","�������� ��� �������� �� ����� ��� � 1 ���","�����" }, HorizontalAlignment::Left, 15);

		switch (c)
		{
		case 0:
			command = new SearchConcrete(&List, manager);
			break;
		case 1:
			command = new SearchTag(&List, manager);
			break;
		case 2:
			command = new SearchDate(&List, manager);
			break;
		case 3:
			command = new SearchPriority(&List, manager);
			break;
		case 4:
			command = new SearchDeadline(&List, manager);
			break;
		default:
			break;
		}

		if (command)
		{
			command->execute();
			delete command;
			command = nullptr;
		}
	}
}

void ToDoFacade::save()
{
	if (getNoOrYes("�� ������� ��� ������ ��������� ��������� � ����?"))
	{
		for_each(List.begin(), List.end(), [&](std::shared_ptr<TaskList> ptr)
		{
			manager->setTaskList(ptr);
			manager->save();
		});
	}
}

void ToDoFacade::load()
{
	if (getNoOrYes("�� ������� ��� ������ ��������� �� �����?"))
	{
		List.clear();

		if (!fs::exists("To-Do") || fs::is_empty("To-Do\\"))
		{
			fs::create_directory("To-Do");
			system("cls");
			gotoxy(25, 14);
			cout << "��� �������" << endl;
			system("pause");
			return;
		}

		for (const auto& a : fs::directory_iterator("To-Do\\"))
		{
			string temp = a.path().u8string();
			temp.assign(temp.begin() + temp.find_last_of("\\") + 1, temp.begin() + temp.find_last_of("."));
			TaskList bs(temp);
			List.push_back(make_shared<TaskList>(bs));
		}

		for_each(List.begin(), List.end(), [&](std::shared_ptr<TaskList> ptr)
		{
			manager->setTaskList(ptr);
			manager->load();
		});
	}
}

void ToDoFacade::menu()
{
	if (!fs::exists("To-Do"))
	{
		fs::create_directory("To-Do");
	}

	int c = 0;

	while (c < 6)
	{
		system("cls");

		c = Menu::select_vertical({ "�������� ������","������� ������","��������� ������","�����","��������� � ����","��������� �� �����","�����" }, HorizontalAlignment::Left, 15);

		switch (c)
		{
		case 0:
			addList();
			break;
		case 1:
			deleteList();
			break;
		case 2:
			configureList();
			break;
		case 3:
			search();
			break;
		case 4:
			save();
			break;
		case 5:
			load();
			break;
		default:
			break;
		}
	}
}
