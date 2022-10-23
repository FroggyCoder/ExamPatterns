#include "Actions.h"

int main()
{
	setlocale(LC_ALL, "Russian");

	ToDoFacade* application = ToDoFacade::getinstance();
	application->menu();
}
