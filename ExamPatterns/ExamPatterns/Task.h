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

using namespace std;
namespace fs = std::experimental::filesystem;

enum Priority { LOW, MEDIUM, HIGH, EXTREME };
enum Month { JAN = 1, FBR, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };

ostream& operator<<(ostream& out, const Priority& prio)
{
	switch (prio)
	{
	case LOW:
		out << "Low";
		break;
	case MEDIUM:
		out << "Medium";
		break;
	case HIGH:
		out << "High";
		break;
	case EXTREME:
		out << "Extreme";
		break;
	default:
		break;
	}
	return out;
}
