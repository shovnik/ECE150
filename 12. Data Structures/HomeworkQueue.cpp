#include <limits.h>
#include <time.h>

using namespace std;

#ifndef MARMOSET_TESTING
#include <iostream>
#endif


#ifndef MARMOSET_TESTING

enum COURSE {CHE102, MATH115, MATH117, ECE105, ECE150, ECE190, Null};

struct Assignment
{
	COURSE course; // CHE102, MATH117, etc.
	int assnNum; // Assignment Number
	int dueMonth; // Month due (1-12)
	int dueDay; // Day due (1-31)
	char* description; // Assignment description
};

struct HomeworkQueue
{
	Assignment* assn;
	HomeworkQueue* nextInQueue;
};

#endif


bool enqueue(HomeworkQueue*& queue, const Assignment& assignment);
const Assignment* dequeue(HomeworkQueue*& queue);
int daysTillDue(const HomeworkQueue* q, const COURSE course);
const Assignment* dueIn(const HomeworkQueue* q, const int numDays);

int CAPACITY = 1000;

bool isEarlier(const Assignment& assignment1, const Assignment& assignment2) {
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


bool sameDescription(char* description1, char* description2) {
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


int daysTillAss (const Assignment* keepo) {
	time_t t = time(nullptr);
	struct tm* timeTM = localtime(&t);
	int currentMonth = timeTM->tm_mon + 1;
	int currentDay = timeTM->tm_mday;
	int currentDays = currentMonth * 30 + currentDay;
	int daysDue = (keepo->dueMonth * 30 + keepo->dueDay) - currentDays;
	return daysDue;
}


bool enqueue(HomeworkQueue*& queue, const Assignment& assignment) {
	if (assignment.course != Null && assignment.assnNum > - 1 && assignment.dueMonth > 0 && assignment.dueMonth < 13
		&& assignment.dueDay > 0 && assignment.dueDay < 32 && assignment.description != NULL
		&& assignment.description != "" && assignment.description[0] != '\0') {
		if (queue == NULL) {
			queue = new HomeworkQueue;
			queue->nextInQueue = NULL;
			queue->assn = NULL;
		}
		if (queue->assn == NULL && queue->nextInQueue == NULL) {
			queue->assn = new Assignment;
			*queue->assn = assignment;
			queue->nextInQueue = NULL;
			return true;
		}
		else {
			HomeworkQueue* temp = queue;
			while (temp != NULL) {
				if (sameDescription(temp->assn->description, assignment.description)) {
					return false;
				}
				temp = temp->nextInQueue;
			}
		}
		if (isEarlier(*queue->assn, assignment)) {
			HomeworkQueue* traverse = queue;
			while (traverse->nextInQueue != NULL && isEarlier(*traverse->nextInQueue->assn, assignment)) {
				traverse = traverse->nextInQueue;
			}
			HomeworkQueue* spot = new HomeworkQueue;
			spot->assn = new Assignment;
			*spot->assn = assignment;
			spot->nextInQueue = traverse->nextInQueue;
			traverse->nextInQueue = spot;
			traverse = NULL;
			return true;
		}
		HomeworkQueue* spot = new HomeworkQueue;
		spot->assn = new Assignment;
		*spot->assn = assignment;
		spot->nextInQueue = queue;
		queue = spot;
		return true;
	}
	return false;
}


const Assignment* dequeue(HomeworkQueue*& queue) {
	if (queue != NULL) {
		HomeworkQueue* temp = queue;
		Assignment* assignment = queue->assn;
		queue = queue->nextInQueue;
		delete temp;
		return assignment;
	}
	return NULL;
}


int daysTillDue(const HomeworkQueue* q, const COURSE course) {
	const HomeworkQueue* traverse = q;
	while (traverse != NULL) {
		if (traverse->assn->course == course) {
			int daysDue = daysTillAss(traverse->assn);
			traverse = NULL;
			return daysDue;
		}
		traverse = traverse->nextInQueue;
	}
	traverse = NULL;
	return INT_MAX;
}

const Assignment* dueIn(const HomeworkQueue* q, const int numDays) {
	const HomeworkQueue* traverse = q;
	Assignment* dAssignments = new Assignment[CAPACITY];
	int assCounter = 0;
	while (traverse != NULL && daysTillAss(traverse->assn) <= numDays) {
		dAssignments[assCounter].course = traverse->assn->course;
		dAssignments[assCounter].assnNum = traverse->assn->assnNum;
	  dAssignments[assCounter].dueMonth = traverse->assn->dueMonth;
	  dAssignments[assCounter].dueDay = traverse->assn->dueDay;
	  dAssignments[assCounter].description = traverse->assn->description;
		assCounter++;
		traverse = traverse->nextInQueue;
	}
	Assignment* assignments = new Assignment[assCounter + 1];
	for (int i = 0; i < assCounter; i++) {
		assignments[i] = dAssignments[i];
	}
	assignments[assCounter].course = Null;
	assignments[assCounter].assnNum = - 1;
  assignments[assCounter].dueMonth = - 1;
  assignments[assCounter].dueDay = - 1;
  assignments[assCounter].description = NULL;
	delete dAssignments;
	int k = 0;
	dAssignments = NULL;
	traverse = NULL;
	return assignments;
}



#ifndef MARMOSET_TESTING

int main(const int argc, const char* const argv[]) {

	HomeworkQueue* p_queue = new HomeworkQueue;
	p_queue->nextInQueue = NULL;
	p_queue->assn = NULL;

	char sampl1[] = "One";
	char sampl2[] = "Two";
	char sampl3[] = "Three";
	char sampl4[] = "Four";
	Assignment assn1 =
 {
 .course = ECE150,
 .assnNum = 0,
 .dueMonth = 2,
 .dueDay = 3,
 .description = sampl1
 };

 Assignment assn2 =
 {
 .course = ECE105,
 .assnNum = 1,
 .dueMonth = 2,
 .dueDay = 3,
 .description = sampl2
 };

 Assignment assn3 =
{
.course = ECE150,
.assnNum = 0,
.dueMonth = 2,
.dueDay = 3,
.description = sampl3
};

Assignment assn4 =
{
.course = ECE105,
.assnNum = 1,
.dueMonth = 2,
.dueDay = 3,
.description = sampl4
};

bool enqueueSuccess = enqueue(p_queue, assn1);
if(enqueueSuccess)
{
	std::cout << "assn1 enqueued successfully" << std::endl << std::endl;
}
else
{
	std::cout << "enqueue() failed" << std::endl << std::endl;
}
enqueueSuccess = enqueue(p_queue, assn2);
if(enqueueSuccess)
{
	std::cout << "assn2 enqueued successfully" << std::endl << std::endl;
}
else
{
	std::cout << "enqueue() failed" << std::endl << std::endl;
}
enqueueSuccess = enqueue(p_queue, assn3);
if(enqueueSuccess)
{
	std::cout << "assn1 enqueued successfully" << std::endl << std::endl;
}
else
{
	std::cout << "enqueue() failed" << std::endl << std::endl;
}
enqueueSuccess = enqueue(p_queue, assn4);
if(enqueueSuccess)
{
	std::cout << "assn2 enqueued successfully" << std::endl << std::endl;
}
else
{
	std::cout << "enqueue() failed" << std::endl << std::endl;
}

	// int retCode = daysTillDue(p_queue, ECE150);
	// int retCode1 = daysTillDue(p_queue, ECE105);
	// int retCode2 = daysTillDue(p_queue, ECE190);
	// cout << retCode << endl;
	// cout << retCode1 << endl;
	// cout << retCode2 << endl;
	// const Assignment* assignments = dueIn(p_queue, 10);
	// int k = 0;
	// while (assignments[k].course != Null) {
	// 	cout << assignments[k].description << endl;
	// 	k++;
	// }
	const Assignment* p_firstAssignmentInQueue = dequeue(p_queue);
	if (p_firstAssignmentInQueue)
	{
		std::cout << "Dequeue successful..." << std::endl;
		std::cout << "Course: " << p_firstAssignmentInQueue->course << std::endl;
		std::cout << "Assignment #: " << p_firstAssignmentInQueue->assnNum << std::endl;
		std::cout << "Day due: " << p_firstAssignmentInQueue->dueDay << std::endl;
		std::cout << "Month due: " << p_firstAssignmentInQueue->dueMonth << std::endl;
		std::cout << "Description: " << p_firstAssignmentInQueue->description << std::endl;
	}
	else
	{
		std::cout << "dequeue() failed" << std::endl;
	}
	const Assignment* p_secondAssignmentInQueue = dequeue(p_queue);
	if (p_secondAssignmentInQueue)
	{
		std::cout << "Dequeue successful..." << std::endl;
		std::cout << "Course: " << p_secondAssignmentInQueue->course << std::endl;
		std::cout << "Assignment #: " << p_secondAssignmentInQueue->assnNum << std::endl;
		std::cout << "Day due: " << p_secondAssignmentInQueue->dueDay << std::endl;
		std::cout << "Month due: " << p_secondAssignmentInQueue->dueMonth << std::endl;
		std::cout << "Description: " << p_secondAssignmentInQueue->description << std::endl;
	}
	else
	{
		std::cout << "dequeue() failed" << std::endl;
	}
	const Assignment* p_thirdAssignmentInQueue = dequeue(p_queue);
	if (p_thirdAssignmentInQueue)
	{
		std::cout << "Dequeue successful..." << std::endl;
		std::cout << "Course: " << p_thirdAssignmentInQueue->course << std::endl;
		std::cout << "Assignment #: " << p_thirdAssignmentInQueue->assnNum << std::endl;
		std::cout << "Day due: " << p_thirdAssignmentInQueue->dueDay << std::endl;
		std::cout << "Month due: " << p_thirdAssignmentInQueue->dueMonth << std::endl;
		std::cout << "Description: " << p_thirdAssignmentInQueue->description << std::endl;
	}
	else
	{
		std::cout << "dequeue() failed" << std::endl;
	}
	const Assignment* p_fourthAssignmentInQueue = dequeue(p_queue);
	if (p_fourthAssignmentInQueue)
	{
		std::cout << "Dequeue successful..." << std::endl;
		std::cout << "Course: " << p_fourthAssignmentInQueue->course << std::endl;
		std::cout << "Assignment #: " << p_fourthAssignmentInQueue->assnNum << std::endl;
		std::cout << "Day due: " << p_fourthAssignmentInQueue->dueDay << std::endl;
		std::cout << "Month due: " << p_fourthAssignmentInQueue->dueMonth << std::endl;
		std::cout << "Description: " << p_fourthAssignmentInQueue->description << std::endl;
	}
	else
	{
		std::cout << "dequeue() failed" << std::endl;
	}
	delete p_queue;

	return 0;
}

#endif
