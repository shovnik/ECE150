#include <limits.h>
#include <time.h>
using namespace std;

#ifndef MARMOSET_TESTING
#include <iostream>
#endif

#ifndef MARMOSET_TESTING
enum COURSE {
	CHE102,
	MATH115,
	MATH117,
	ECE105,
	ECE150,
	ECE190,
	Null
};

struct Assignment {
	COURSE course;
	int    assnNum;      // Assignment number
	int    dueMonth;     // 1-12
	int    dueDay;       // 1-31
	char*  description;  // Assignment description
};
#endif

int CAPACITY = 1000;

struct Queue {
	Assignment* assn;
	Queue* nextInQueue;
};

class HomeworkQueue
{
public:
  	HomeworkQueue();    //constructor
	  HomeworkQueue(const Assignment assignment);    //constructor
	  ~HomeworkQueue();   //destructor
		bool                isEarlier(const Assignment& assignment1, const Assignment& assignment2);
		bool                sameDescription(char* description1, char* description2);
		int                 daysTillAssn (const Assignment* assignment);
    bool                enqueue(const Assignment& assignment);
    const Assignment*   dequeue();
    int                 daysTillDue(const COURSE course);
    const Assignment*   dueIn(const int numDays);
private:
    Queue* _head = NULL;
};


bool HomeworkQueue::isEarlier(const Assignment& assignment1, const Assignment& assignment2) {
	time_t t = time(0);
	struct tm* timeTM = localtime(&t);
	int currentMonth = timeTM->tm_mon + 1;
	int currentDay = timeTM->tm_mday;
	int currentDays = currentMonth * 30 + currentDay;
	int ass1Days = assignment1.dueMonth * 30 + assignment1.dueMonth;
	int ass2Days = assignment2.dueMonth * 30 + assignment2.dueMonth;
	if (ass1Days <= ass2Days) {
		return true;
	}
	return false;
}


bool HomeworkQueue::sameDescription(char* description1, char* description2) {
	int i = 0;
	while (description1[i] != '\0' && description2[i] != '\0') {
		if (description1[i] != description2[i]) {
			return false;
		}
		i++;
	}
	if (description1[i] != description2[i]) {
		return false;
	}
	return true;
}


int HomeworkQueue::daysTillAssn (const Assignment* assignment) {
	time_t t = time(0);
	struct tm* timeTM = localtime(&t);
	int currentMonth = timeTM->tm_mon + 1;
	int currentDay = timeTM->tm_mday;
	int currentDays = currentMonth * 30 + currentDay;
	int daysDue = (assignment->dueMonth * 30 + assignment->dueDay) - currentDays;
	return daysDue;
}


bool HomeworkQueue::enqueue(const Assignment& assignment) {
	if (assignment.course != Null && assignment.assnNum > - 1 && assignment.dueMonth > 0 && assignment.dueMonth < 13
		&& assignment.dueDay > 0 && assignment.dueDay < 32 && assignment.description != NULL
		&& assignment.description != "" && assignment.description[0] != '\0') {
		if (_head == NULL) {
			_head = new Queue;
			_head->nextInQueue = NULL;
			_head->assn = NULL;
		}
		if (_head->assn == NULL && _head->nextInQueue == NULL) {
			_head->assn = new Assignment;
			*_head->assn = assignment;
			_head->nextInQueue = NULL;
			return true;
		}
		else {
			Queue* temp = _head;
			while (temp != NULL) {
				if (sameDescription(temp->assn->description, assignment.description)) {
					return false;
				}
				temp = temp->nextInQueue;
			}
		}
		if (isEarlier(*_head->assn, assignment)) {
			Queue* traverse = _head;
			while (traverse->nextInQueue != NULL && isEarlier(*traverse->nextInQueue->assn, assignment)) {
				traverse = traverse->nextInQueue;
			}
			Queue* spot = new Queue;
			spot->assn = new Assignment;
			*spot->assn = assignment;
			spot->nextInQueue = traverse->nextInQueue;
			traverse->nextInQueue = spot;
			traverse = NULL;
			return true;
		}
		Queue* spot = new Queue;
		spot->assn = new Assignment;
		*spot->assn = assignment;
		spot->nextInQueue = _head;
		_head = spot;
		return true;
	}
	return false;
}


const Assignment* HomeworkQueue::dequeue() {
	if (_head != NULL) {
		Queue* temp = _head;
		Assignment* assignment = _head->assn;
		_head = _head->nextInQueue;
		delete temp;
		return assignment;
	}
	return NULL;
}


int HomeworkQueue::daysTillDue(const COURSE course) {
	const Queue* traverse = _head;
	while (traverse != NULL) {
		if (traverse->assn->course == course) {
			int daysDue = daysTillAssn(traverse->assn);
			traverse = NULL;
			return daysDue;
		}
		traverse = traverse->nextInQueue;
	}
	traverse = NULL;
	return INT_MAX;
}


const Assignment* HomeworkQueue::dueIn(const int numDays) {
	const Queue* traverse = _head;
	Assignment* dAssignments = new Assignment[CAPACITY];
	int assnCounter = 0;
	while (traverse != NULL && daysTillAssn(traverse->assn) <= numDays) {
		dAssignments[assnCounter].course = traverse->assn->course;
		dAssignments[assnCounter].assnNum = traverse->assn->assnNum;
	  dAssignments[assnCounter].dueMonth = traverse->assn->dueMonth;
	  dAssignments[assnCounter].dueDay = traverse->assn->dueDay;
	  dAssignments[assnCounter].description = traverse->assn->description;
		assnCounter++;
		traverse = traverse->nextInQueue;
	}
	Assignment* assignments = new Assignment[assnCounter + 1];
	for (int i = 0; i < assnCounter; i++) {
		assignments[i] = dAssignments[i];
	}
	assignments[assnCounter].course = Null;
	assignments[assnCounter].assnNum = - 1;
  assignments[assnCounter].dueMonth = - 1;
  assignments[assnCounter].dueDay = - 1;
  assignments[assnCounter].description = NULL;
	delete dAssignments;
	int k = 0;
	dAssignments = NULL;
	traverse = NULL;
	return assignments;
}


HomeworkQueue::HomeworkQueue() {
	//Do Nothing
}


HomeworkQueue::HomeworkQueue(const Assignment assignment) {
	_head = new Queue;
	_head->assn =  new Assignment;
	*_head->assn = assignment;
	_head->nextInQueue = NULL;
}


HomeworkQueue::~HomeworkQueue() {
	Queue* cleaner = _head;
	Queue* temp = _head;
	while (temp != NULL) {
		temp = temp->nextInQueue;
		delete cleaner;
		cleaner = temp;
	}
	cleaner = NULL;
	temp = NULL;
}





#ifndef MARMOSET_TESTING
int main(const int argc, const char* const args[])
{
	//formatting
	std::cout << std::endl;

	HomeworkQueue hwq;

	char boring[] = "Something something solubility something something gases something";

	Assignment someAssignment =
	{
		.course = CHE102,
		.assnNum = 1000000,
		.dueMonth = 12,
		.dueDay = 4,
		.description = boring
	};

	if(!hwq.enqueue(someAssignment))
	{
		std::cout << "enqueue() unsuccessful" << std::endl;
	}
	else
	{
		std::cout << "enqueue() successful" << std::endl;
	}

	const Assignment* assnInTheQueue = hwq.dequeue();

	if (!assnInTheQueue)
	{
		std::cout << "dequeue() unsuccessful" << std::endl;

	}
	else
	{
		std::cout << "dequeue() successful" << std::endl;
	}

	//formatting
	std::cout << std::endl;

    return 0;
}
#endif
