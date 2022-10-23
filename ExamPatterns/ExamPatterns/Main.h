#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <chrono>
#include <ctime>
#include <experimental/filesystem>

#include "Menu.h"

using namespace std;
namespace fs = std::experimental::filesystem;

enum Priority { LOW, MEDIUM, HIGH, EXTREME };
enum Month { JAN = 1, FAB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };

ostream& operator<<(ostream& out, const Priority& prior)
{
	switch (prior)
	{
	case LOW:
		out << "низкий";
		break;
	case MEDIUM:
		out << "средний";
		break;
	case HIGH:
		out << "высокий";
		break;
	case EXTREME:
		out << "сверхвысокий";
		break;
	default:
		break;
	}
	return out;
}

ostream& operator<<(ostream& out, const Month& mth)
{
	switch (mth)
	{
	case JAN:
		out << "Jan";
		break;
	case FAB:
		out << "Fab";
		break;
	case MAR:
		out << "Mar";
		break;
	case APR:
		out << "Apr";
		break;
	case MAY:
		out << "May";
		break;
	case JUN:
		out << "Jun";
		break;
	case JUL:
		out << "Jul";
		break;
	case AUG:
		out << "Aug";
		break;
	case SEP:
		out << "Sep";
		break;
	case OCT:
		out << "Oct";
		break;
	case NOV:
		out << "Nov";
		break;
	case DEC:
		out << "Dec";
		break;
	default:
		break;
	}
	return out;
}

ofstream& operator<<(ofstream& out, const Priority& prior)
{
	out << static_cast<int>(prior);
	return out;
}

ofstream& operator<<(ofstream& out, const Month& mth)
{
	switch (mth)
	{
	case JAN:
		out << "Jan";
		break;
	case FAB:
		out << "Fab";
		break;
	case MAR:
		out << "Mar";
		break;
	case APR:
		out << "Apr";
		break;
	case MAY:
		out << "May";
		break;
	case JUN:
		out << "Jun";
		break;
	case JUL:
		out << "Jul";
		break;
	case AUG:
		out << "Aug";
		break;
	case SEP:
		out << "Sep";
		break;
	case OCT:
		out << "Oct";
		break;
	case NOV:
		out << "Nov";
		break;
	case DEC:
		out << "Dec";
		break;
	default:
		break;
	}
	return out;
}

Month stoM(const string& str)
{
	if (str == "Sep") return SEP;
	else if (str == "Jan") return JAN;
	else if (str == "Fab") return FAB;
	else if (str == "Mar") return MAR;
	else if (str == "Apr") return APR;
	else if (str == "May") return MAY;
	else if (str == "Jun") return JUN;
	else if (str == "Jul") return JUL;
	else if (str == "Aug") return AUG;
	else if (str == "Oct") return OCT;
	else if (str == "Nov") return NOV;
	else return DEC;
}

class Time
{
public:
	size_t hours;
	size_t minutes;
	size_t seconds;
	size_t day;
	Month  month;

	Time(size_t h = 0, size_t m = 0, size_t s = 0, size_t d = 1, Month mth = JAN) : hours{ h }, minutes{ m }, seconds{ s }, day{ d }, month{ mth } {}

	bool operator< (const Time& t)
	{
		if (this->month < t.month || this->day < t.day || this->hours < t.hours || this->minutes < t.minutes || this->seconds < t.seconds)
		{
			return true;
		}
		return false;
	}

	friend ostream& operator<<(ostream& out, const Time& t);

	Time(const Time& t)
	{
		this->hours   = t.hours;
		this->minutes = t.minutes;
		this->seconds = t.seconds;
		this->day	  = t.day;
		this->month   = t.month;
	}

	void setCurrent()
	{
		auto a = std::chrono::system_clock::now();

		time_t temp = std::chrono::system_clock::to_time_t(a);
		string time = ctime(&temp);

		month   = stoM(time.substr(4, 3));
		day     = stoi(time.substr(8, 2));
		hours   = stoi(time.substr(11, 2));
		minutes = stoi(time.substr(14, 2));
		seconds = stoi(time.substr(17, 2));
	}

	Time& operator=(const Time& t)
	{
		if (&t == this) return *this;

		this->hours   = t.hours;
		this->minutes = t.minutes;
		this->seconds = t.seconds;
		this->day     = t.day;
		this->month   = t.month;
	}
};

ostream& operator<<(ostream& out, const Time& t)
{
	out << t.hours << ":";

	if (t.minutes < 10)
	{
		out << "0";
	}

	out << t.minutes << ":";

	if (t.seconds < 10)
	{
		out << "0";
	}

	out << t.seconds;
	out << " " << t.day << " " << t.month;

	return out;
}

class Task
{
	string   task;
	Priority priority;
	Time	 deadline;
	string   tag;
public:
	Task() {}
	string getTask() { return task; } const
	void setTask(const string& tk) { task = tk; }

	Priority getPriority() { return priority; }const
	void setPriority(const Priority& prior) { priority = prior; }

	Time getDeadline() { return deadline; }const
	void setDeadline(const Time& dl) { deadline = dl; }

	string getTag() { return tag; }const
	void setTag(const string& tg) { tag = tg; }

	void print()const
	{
		cout << "задача: "    << task << endl;
		cout << "дедлайн: "   << deadline << endl;
		cout << "приоритет: " << priority << endl;
		cout << "тег: "		  << tag << endl;
		cout << "-------------------------------" << endl;
	}

	bool withinDay(const Time& t)const
	{
		Time temp = deadline;
		temp.day += 1;
		return temp < t;
	}

	void load(string newTask, string newDeadline, string newPriority, string newTag)
	{
		task = newTask;
		priority = Priority(stoi(newPriority));
		tag = newTag;

		Time temp;
		string buff;

		buff.assign(newDeadline.begin(), newDeadline.begin() + newDeadline.find_first_of(':'));
		newDeadline.erase(newDeadline.begin(), newDeadline.begin() + newDeadline.find_first_of(':') + 1);
		temp.hours = stoi(buff);

		buff.assign(newDeadline.begin(), newDeadline.begin() + newDeadline.find_first_of(':'));
		newDeadline.erase(newDeadline.begin(), newDeadline.begin() + newDeadline.find_first_of(':') + 1);
		temp.minutes = stoi(buff);

		buff.assign(newDeadline.begin(), newDeadline.begin() + newDeadline.find_first_of(' '));
		newDeadline.erase(newDeadline.begin(), newDeadline.begin() + newDeadline.find_first_of(' ') + 1);
		temp.seconds = stoi(buff);


		buff.assign(newDeadline.begin(), newDeadline.begin() + newDeadline.find_first_of(' '));
		newDeadline.erase(newDeadline.begin(), newDeadline.begin() + newDeadline.find_first_of(' ') + 1);
		temp.day = stoi(buff);

		temp.month = stoM(newDeadline);

		deadline = temp;
	}

	Task(const Task& tk)
	{
		this->task	   = tk.task;
		this->priority = tk.priority;
		this->deadline = tk.deadline;
		this->tag	   = tk.tag;
	}

	Task& operator=(const Task& tk)
	{
		if (&tk == this) return *this;

		this->task     = tk.task;
		this->priority = tk.priority;
		this->deadline = tk.deadline;
		this->tag	   = tk.tag;
	}
};

class TaskList
{
public:
	string name;
	list<Task> tasks;
	TaskList(string n) : name{ n } {}

	void save()
	{
		ofstream out("List\\" + name + ".txt");
		for_each(tasks.begin(), tasks.end(), [&out](Task& tk)
		{
			out << tk.getTask()		<< endl;
			out << tk.getDeadline() << endl;
			out << tk.getPriority() << endl;
			out << tk.getTag()		<< endl;
		});
		out.close();
	}

	void sort()
	{
		if (tasks.size() == 0)
		{
			return;
		}

		int i, j;

		for (i = 0; i < tasks.size() - 1; i++)
		{
			auto a = tasks.begin();
			advance(a, i);

			for (j = 0; j < tasks.size() - i - 1; j++)
			{
				auto b = tasks.begin();
				advance(b, j + 1);

				if (a->getPriority() < b->getPriority())
				{
					auto temp = *a;
					*a = *b;
					*b = temp;
				}
			}
		}
	}
};

Time getTime()
{
	system("cls");

	auto getWithCheck = [](size_t& param, size_t higher)->void
	{
		int buff;
		cin >> buff;

		if (buff < 0) buff = 0;
		else if (buff >= higher) buff = higher - 1;

		param = buff;
	};

	size_t h, m, s, d, mon;

	cout << "часы: ";
	getWithCheck(h, 24);

	cout << "минуты: ";
	getWithCheck(m, 60);

	cout << "секунды: ";
	getWithCheck(s, 60);

	cout << "день: ";
	getWithCheck(d, 32);

	cout << "месяц(номер): ";
	getWithCheck(mon, 13);

	cin.ignore();
	return Time(h, m, s, d, Month(mon));
}

bool getNoYes(const string& ny)
{
	system("cls");
	gotoxy(20, 10);

	cout << ny << endl;

	return Menu::select_vertical({ "нет","да" }, HorizontalAlignment::Center, 12);
}

Priority getPriority()
{
	system("cls");
	gotoxy(20, 10);

	cout << "выберите приоритет: ";

	return (Priority(Menu::select_vertical({ "низкий","средний","высокий","сверхвысокий" }, HorizontalAlignment::Center, 11)));
}
