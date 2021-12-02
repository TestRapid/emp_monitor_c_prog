/* importing libraries */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

/* defining structures, varibles and function prototypes */
// defining custom datatype
typedef struct
{
	size_t id;
	char name[30];
	char address[50];
	char contact[10];
	size_t num_breaks;
	bool isPresent;
	bool isBreak;
	long long breakstart;
	long long breakend;
	long long totalbreak;
} Employee;

// defining variables
size_t count = 0;
long int mysize = 10;
Employee *emp;

// start and stop functions
void init();
void closeit();

// crud operation function prototypes
Employee createEmp(char name[30], char address[50], char contact[10]);
Employee readEmp(int);
int readEmpIndex(int);
Employee deleteEmp(int);

// monitor functions
bool checkin(int);
bool checkout(int);
bool isAvailable(int);
bool startBreak(int);
bool endBreak(int);

// Emp operations
void printAllEmp();
void printEmpInArr(size_t arr[], size_t size);
void addOneEmp();
void deleteOneEmp();

void empCheckin();
void empCheckout();
void empBreakStart();
void empBreakEnd();

// how many employees came today
void empsCameToday();

// did a particular employee came today
void empComeToday();

// how many times an employee took break
void empBreaks();

// employee took most number of breaks
void empMostBreak();

// display at particular range of ids
void empsInRange();

/* the main function */
int main()
{
	int flag;
	bool swap = true;
	bool exit = false;

	init();

	createEmp("test", "test", "1230932334");
	createEmp("test2", "test2", "1230943434");
	createEmp("test3", "test3", "1233452923");
	createEmp("test4", "test4", "1230932334");
	createEmp("test5", "test5", "1230943434");
	createEmp("test6", "test6", "1233452923");

	checkin(1);
	checkin(3);

	startBreak(3);

	printf("\n\n---------------------------------------------");
	printf("\nWelcome to Employee monitoring system:");
	printf("\n---------------------------------------------\n");

	do
	{
		if (swap)
		{
			printf("\n1 - Employee management.\n2 - view in Employees came today.\n3 - check-in.\n4 - check-out.\n5 - Break Start.\n6 - Break end.\n7 - Most breaks taken Employee.\n8 - Check Employee came today.\n9 - Check of Number of breaks of a employee\n10 - Employees in range of ids;\n0 - to Exit.\n");
			printf("\nEnter your choice : ");
			scanf("%d", &flag);
			printf("\n----------------------------------------------------------------------------------------\n");

			switch (flag)
			{
			case 0:
			{
				printf("\nThank you for using the Application\n");
				exit = true;
				break;
			}
			case 1:
				swap = false;
				break;
			case 2:
			{
				empsCameToday();
				break;
			}
			case 3:
				empCheckin();
				break;
			case 4:
				empCheckout();
				break;
			case 5:
				empBreakStart();
				break;
			case 6:
				empBreakEnd();
				break;
			case 7:
				empMostBreak();
				break;
			case 8:
				empComeToday();
				break;
			case 9:
				empBreaks();
				break;
			case 10:
				empsInRange();
				break;
			default:
				printf("\n------------Invalid choice------------\n");
				printf("\n--------------------------------------------------------------------------------\n");
				continue;
			}
		}
		else
		{
			printf("\n1 - Monitor.\n2 - View all Employees.\n3 - Add new Entry.\n4 - Delete a record.\n0 - To exit.\n");
			printf("\nEnter your choice : ");
			scanf("%d", &flag);
			printf("\n----------------------------------------------------------------------------------------\n");

			switch (flag)
			{
			case 0:
			{
				printf("\nThank you for using the Application\n");
				exit = true;
				break;
			}
			case 1:
				swap = true;
				break;
			case 2:
				printAllEmp();
				break;
			case 3:
				addOneEmp();
				break;
			case 4:
				deleteOneEmp();
				break;
			default:
				printf("\n------------Invalid choice------------\n");
				printf("\n--------------------------------------------------------------------------------\n");
				continue;
				break;
			}
		}
		printf("\n----------------------------------------------------------------------------------------\n\n");
	} while (!exit);

	closeit();
	return 0;
}

/* functions */
// start function
void init()
{
	emp = calloc(mysize, sizeof(Employee));
}
// end function
void closeit()
{
	free(emp);
}

// crud operations
Employee createEmp(char name[30], char address[50], char contact[10])
{
	if (count == mysize - 1)
	{
		mysize *= 2;
		emp = realloc(emp, mysize * sizeof(Employee));
	}
	if (count != 0)
	{

		emp[count].id = emp[count - 1].id + 1;
	}
	else
	{
		emp[count].id = 1;
	}
	strcpy(emp[count].name, name);
	strcpy(emp[count].address, address);
	strcpy(emp[count].contact, contact);
	emp[count].isPresent = false;
	emp[count].isBreak = false;
	emp[count].breakstart = 0;
	emp[count].breakend = 0;
	emp[count].num_breaks = 0;
	emp[count].totalbreak = 0;
	++count;
	return emp[count - 1];
}

Employee readEmp(int id)
{
	int index;
	for (int i = 0; i < count; i++)
	{
		if (emp[i].id == id)
		{
			index = i;
			break;
		}
	}
	return emp[index];
}

int readEmpIndex(int id)
{
	for (int i = 0; i < count; i++)
	{
		if (emp[i].id == id)
			return i;
	}
	return -1;
}

Employee deleteEmp(int id)
{
	id = id - 1;
	Employee ep = emp[id];
	int index = readEmpIndex(id);
	for (size_t i = index + 1; i < count - 1; i++)
	{
		emp[i] = emp[i + 1];
	}
	--count;
	return ep;
}

void printAllEmp()
{
	int hrs, mins;
	printf("\nAll Employees : ");
	printf("\n\n--\t----\t-------\t\t-------\t\t--------\t----------------\t----------------\t----------------");
	printf("\nid\tname\tcontact\t\taddress\t\tcheck in\tAvailable or not\tNumber of breaks\tTotal break time");
	printf("\n--\t----\t-------\t\t-------\t\t--------\t----------------\t----------------\t----------------");

	for (size_t i = 0; i < count; i++)
	{
		printf("\n%zu\t%s\t%10s\t%8s\t", emp[i].id, emp[i].name, emp[i].contact, emp[i].address);
		if (emp[i].isPresent)
		{
			printf("Yes\t\t");
		}
		else
		{
			printf("No\t\t");
		}
		if (isAvailable(emp[i].id))
		{
			printf("Available\t");
		}
		else
		{
			printf("Not Available\t");
		}
		hrs = (int)emp[i].totalbreak / 60 * 60;
		mins = hrs - ((int)emp[i].totalbreak / 60 * 60);
		printf("\t%lu\t\t\t%d hr/s %d min/s", emp[i].num_breaks, hrs, mins);
	}
	printf("\n--\t----\t-------\t\t-------\t\t--------\t----------------\t----------------\t----------------\n\n");
}

bool checkin(int id)
{
	int index = readEmpIndex(id);
	if (index != -1)
	{
		emp[index].isPresent = true;
		return true;
	}
	return false;
}

bool checkout(int id)
{
	int index = readEmpIndex(id);
	if (index != -1)
	{
		emp[index].isPresent = false;
		return true;
	}
	return false;
}

void printEmpInArr(size_t arr[], size_t size)
{
	int hrs, mins;
	Employee e;

	printf("\n\n--\t----\t-------\t\t--------\t----------------\t----------------\t----------------");
	printf("\nid\tname\tcontact\t\tcheck in\tAvailable or not\tNumber of breaks\tTotal break time");
	printf("\n--\t----\t-------\t\t--------\t----------------\t----------------\t----------------");

	for (size_t i = 0; i < size; i++)
	{
		e = readEmp(arr[i]);
		printf("\n%zu\t%s\t%10s\t", e.id, e.name, e.contact);
		if (e.isPresent)
		{
			printf("Yes\t\t");
		}
		else
		{
			printf("No\t\t");
		}
		if (isAvailable(e.id))
		{
			printf("Available\t");
		}
		else
		{
			printf("Not Available\t");
		}
		hrs = (int)e.totalbreak / 60 * 60;
		mins = hrs - ((int)e.totalbreak / 60 * 60);
		printf("\t%lu\t\t\t%d hr/s %d min/s", e.num_breaks, hrs, mins);
	}
	printf("\n--\t----\t------\t\t--------\t----------------\t----------------\t----------------\n\n");
}

bool startBreak(int id)
{
	int index = readEmpIndex(id);
	if (index != -1)
	{
		emp[index].isBreak = true;
		emp[index].num_breaks++;
		emp[index].breakstart = time(NULL);
		return true;
	}
	return false;
}

bool endBreak(int id)
{
	int index = readEmpIndex(id);
	if (index != -1)
	{
		emp[index].isBreak = false;
		emp[index].breakend = time(NULL);
		emp[index].totalbreak = emp[index].breakend - emp[index].breakstart;
		return true;
	}
	return false;
}

bool isAvailable(int id)
{
	int index = readEmpIndex(id);
	if (index != -1)
	{
		if (emp[index].isPresent && !emp[index].isBreak)
			return true;
	}
	return false;
}

void empCheckin()
{
	int id;
	printf("\n\tEnter id : ");
	scanf("%d", &id);
	if (id == 0)
	{
		return;
	}
	if (checkin(id))
		printf("\ncheckin successfull\n");
	else
		printf("\nInvalid id\n");
}

void empCheckout()
{
	int id;
	printf("\n\tEnter id : ");
	scanf("%d", &id);
	if (id == 0)
	{
		return;
	}
	if (checkout(id))
	{
		printf("\ncheckout successfull\n");
	}
	else
	{
		printf("\nInvalid id\n");
	}
}

void empBreakStart()
{
	int id;
	printf("Enter id : ");
	scanf("%d", &id);
	if (id == 0)
	{
		return;
	}
	if (startBreak(id))
	{
		printf("%d break started.", id);
	}
	else
	{
		printf("\nInvalid id\n");
	}
}

void empBreakEnd()
{
	int id;
	printf("Enter id : ");
	scanf("%d", &id);
	if (id == 0)
	{
		return;
	}
	if (endBreak(id))
	{
		printf("%d Break completed.", id);
	}
	else
	{
		printf("\nInvalid id\n");
	}
}

void empsCameToday()
{
	printf("Employees came today:-");
	size_t ct = 0;
	size_t *ids = calloc(mysize, sizeof(Employee));
	for (int i = 0; i < count; i++)
	{
		if (emp[i].isPresent)
		{
			ids[ct] = emp[i].id;
			++ct;
		}
	}
	printEmpInArr(ids, ct);
	free(ids);
}

void empMostBreak()
{
	size_t id[1];
	int max = 0;
	for (int i = 0; i < count; i++)
	{
		if (max < emp[i].num_breaks)
		{
			id[0] = emp[i].id;
		}
	}
	printEmpInArr(id, 1);
}

void empComeToday()
{
	int id;
	printf("\n\t Enter id : ");
	scanf("%d", &id);
	if (id == 0)
	{
		return;
	}
	if (readEmpIndex(id) == -1)
	{
		printf("\nInvalid ID\n");
		return;
	}
	Employee e = readEmp(id);
	if (e.isPresent)
	{
		printf("\n\tid : %lu,\t name : %s \t Has come today\n", e.id, e.name);
	}
	else
	{
		printf("\n\tid : %lu,\t name : %s \t Did not come today\n", e.id, e.name);
	}
}

void empBreaks()
{
	size_t ids[0];
	int id;
	printf("\n\t Enter id : ");
	scanf("%d", &id);
	if (id == 0)
	{
		return;
	}
	if (readEmpIndex(id) == -1)
	{
		printf("\nInvalid ID\n");
		return;
	}
	Employee e = readEmp(id);
	ids[0] = e.id;
	printEmpInArr(ids, 1);
}

void empsInRange()
{
	printf("Employees came today in given range of ids :-");

	int start = 0;
	int end = 0;
	size_t ct = 0;
	size_t *ids = calloc(mysize, sizeof(Employee));

	printf("\n\tEnter start : ");
	scanf("%d", &start);
	printf("\n\tEnter End : ");
	scanf("%d", &end);
	if (start <= 0 || end <= 0)
	{
		printf("\nInvalid range\n");
		free(ids);
		return;
	}

	for (int i = 0; i < count; i++)
	{
		if (emp[i].id >= start && emp[i].id <= end)
		{
			ids[ct] = emp[i].id;
			++ct;
		}
		if (emp[i].id > end)
		{
			break;
		}
	}
	printEmpInArr(ids, ct);
	free(ids);
}

void addOneEmp()
{
	char str1[30], str2[50], str3[10];
	int flag;
	Employee ep;
	size_t ids[0];

	printf("\n\tEnter Employee name : ");
	scanf("%s", str1);
	printf("\tEnter Employee address : ");
	scanf("%s", str2);
	printf("\tEnter mobile number : ");
	scanf("%s", str3);

	ep = createEmp(str1, str2, str3);
	printf("\n\n--------Employee Added successfull--------\n");
	ids[0] = ep.id;
	printEmpInArr(ids, 1);

	printf("\nEnter 1 to add new entry : ");
	scanf("%d", &flag);
	if (flag == 1)
	{
		addOneEmp();
	}
	else
	{
		return;
	}
}
void deleteOneEmp()
{
	int id;
	int index;
	Employee ep;
	printf("\nEnter id : ");
	scanf("%d", &id);
	if (id == 0)
	{
		return;
	}
	index = readEmpIndex(id);
	if (index == -1)
	{
		printf("\n------Invalid id------\n");
	}
	else
	{
		ep = deleteEmp(id);
		printf("\n--- id: %lu, name: %s Employee Deleted successfull----\n", ep.id, ep.name);
	}
}
