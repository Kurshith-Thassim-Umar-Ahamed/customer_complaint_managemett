#include <iostream>
#include <string>
using namespace std;

int queue[3], n = 3, front = -1, rear = -1;

struct primary {
	string primaryComplaintId;
	string primaryCustomerName;
	string primaryCustomerAddress;
	string primaryComplaint;
	string primaryDate;
	int	primaryContactNumber;
	struct primary* primaryNextPtr;
};

typedef struct primary Primary;
typedef Primary* PrimaryPtr;

struct secondary {
	string secondaryComplaintId;
	string secondaryCustomerName;
	string secondaryCustomerAddress;
	string secondaryComplaint;
	string secondaryDate;
	int	secondaryContactNumber;
	struct secondary* secondaryNextPtr;
};

typedef struct secondary Secondary;
typedef Secondary* SecondaryPtr;


void options();

void insertPrimary(PrimaryPtr* startPtr, string complaintId, string customerName, string customerAddress, 
	string complaint, string date, int contactNumber);

void insertSecondary(SecondaryPtr* startSecondaryPtr, string complaintId, string customerName, string customerAddress, 
	string complaint, string date, int contactNumber);

char deleteComplaint(PrimaryPtr* startPtr, string complaintId, string customerName,	string customerAddress, string complaint, 
	string date, int contactNumber);

char checkPrimaryForId(PrimaryPtr* startPtr, string complaintId, string customerName, string customerAddress, string complaint, 
	string date, int contactNumber);

char checkSecondaryForId(SecondaryPtr* startSecondaryPtr, string complaintId, string customerName, string customerAddress, 
	string complaint, string date, int contactNumber);

int isEmpty(PrimaryPtr startPtr);

void viewTables();

void printPrimary(PrimaryPtr currentPtr);

char searchPrimary(PrimaryPtr* startPtr, string complaintId, string customerName, string customerAddress, string complaint, 
	string date, int contactNumber);

void printSecondary(SecondaryPtr currentPtr);

char searchSecondary(SecondaryPtr* startSecondaryPtr, string complaintId, string customerName, string customerAddress, 
	string complaint, string date, int contactNumber);

void enqueue(int val);

void dequeue();

void printQueue();

bool checkForIdPrimary(PrimaryPtr* startPtr, string complaintId, bool x);

/*bool checkForIdSecondary(SecondaryPtr* startSecondaryPtr, string complaintId, bool y) {
	SecondaryPtr tempPtr = NULL;
	SecondaryPtr previousPtr = NULL;
	SecondaryPtr currentPtr = NULL;

	if (complaintId == (*startSecondaryPtr)->secondaryComplaintId) {
		tempPtr = *startSecondaryPtr;
		y = true;
		cout << "ID exists\n";
		return y;
	}
	else {
		previousPtr = *startSecondaryPtr;
		currentPtr = (*startSecondaryPtr)->secondaryNextPtr;

		while (currentPtr != NULL && currentPtr->secondaryComplaintId != complaintId) {
			previousPtr = currentPtr;
			currentPtr = currentPtr->secondaryNextPtr;
		}
		if (currentPtr != NULL) {
			tempPtr = currentPtr;
			y = true;
			cout << "ID exists\n";
			return y;
		}
	}
	return y = false;
}*/


int main() {
Start:
	PrimaryPtr startPtr = NULL;
	SecondaryPtr startSecondaryPtr = NULL;

	// declaring variables 
	string complaintId, customerName, customerAddress, complaint, date;
	int contactNumber{};

	// options 
	int selectedOptions = 0;

	//table
	int selectTable = 0;

	//choise
	int choise = 0;

	//queue
	int val;

	//bool
	bool x = false;

	//bool y = false;

	options();
	cout << "Enter the number of the selected option: ";
	cin >> selectedOptions;
	cout << "-------------------------------\n\n";

	while (selectedOptions != 8) {
		switch (selectedOptions) {
			//add
		case 1:
			cout << "Complaint ID: ";
			cin >> complaintId;
			if (!isEmpty(startPtr)) {
				
				//checkForIdPrimary(&startPtr, complaintId, x);
				if (checkForIdPrimary(&startPtr, complaintId,x)) { 
					break;
				}
			}
			

			cout << "Customer Name: ";
			cin >> customerName;
			cout << "Customer Address: ";
			cin >> customerAddress;
			cout << "Complaint: ";
			cin >> complaint;
			cout << "Date: ";
			cin >> date;

			contactNumber :

			cout << "Contact Number: ";
			if (cin >> contactNumber) {
				insertPrimary(&startPtr, complaintId, customerName, customerAddress, complaint, date, contactNumber);
				//insertSecondary(&startSecondaryPtr, complaintId, customerName, customerAddress, complaint, date, contactNumber);
				break;
			}
			else {
				cout << "Enter a valid integer value!\n";
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				goto contactNumber;
			}

			
			break;
			//delete
		case 2:
			if (!isEmpty(startPtr)) {
				cout << "Enter complaintId to be deleted: ";
				cin >> complaintId;

				if (deleteComplaint(&startPtr, complaintId, customerName, customerAddress, complaint, date, contactNumber)) {
					insertSecondary(&startSecondaryPtr, complaintId, customerName, customerAddress, complaint, date, contactNumber);
					cout << " deleted.\n" << complaintId << " , " << customerName << " , " << customerAddress << " , " 
						<< complaint << " , " << date << " , " << contactNumber << "\n";
				}
				else {
					cout << "not found.\n\n" << complaintId;
				}
			}
			else {
				cout << "list is empty.\n\n";
			}
			break;
			//update
		case 3:
			if (!isEmpty(startPtr)) {
				cout << "Enter complaintId to be updated: ";
				cin >> complaintId;

				if (checkPrimaryForId(&startPtr,  complaintId, customerName, customerAddress, complaint, date, contactNumber)) {
					cout << " update.\n" << complaintId << " , " << customerName << " , " << customerAddress << " , "
						<< complaint << " , " << date << " , " << contactNumber << "\n";

					cout << "Customer Name: ";
					cin >> customerName;
					cout << "Customer Address: ";
					cin >> customerAddress;
					cout << "Complaint: ";
					cin >> complaint;
					cout << "Date: ";
					cin >> date;
					updateNum:
					cout << "Contact Number: ";
					if (cin >> contactNumber) {
						insertPrimary(&startPtr, complaintId, customerName, customerAddress, complaint, date, contactNumber);

						if (checkSecondaryForId(&startSecondaryPtr, complaintId, customerName, customerAddress, complaint, date, contactNumber)) {
							cout << " update.\n" << complaintId << " , " << customerName << " , " << customerAddress << " , "
								<< complaint << " , " << date << " , " << contactNumber << "\n";

							insertSecondary(&startSecondaryPtr, complaintId, customerName, customerAddress, complaint, date, contactNumber);
						}
						else {
							cout << "complaintId not found.\n\n" << complaintId;
						}
						break;
					}
					else {
						cout << "Enter a valid integer value!\n";
						cin.clear();
						cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
						goto updateNum;
					};	
				}
				else {
					cout << "complaintId not found.\n\n" << complaintId;
				}
			}
			else {
				cout << "list is empty.\n\n";
			}
			break;
		case 4:
Table:
			//viewTables();
			cout << "Input the number of the table\n"
				"1) Complaint Table.\n"
				"2) Deleted Complaint Table.\n\n";
			sTable:
			cout << "Table Num: ";
			
			if (cin >> selectTable) {
				cout << "\n";
				switch (selectTable) {
				case 1:

					cout << "Input the number of option\n"
						"1) print all details.\n"
						"2) search by ID.\n\n";
					choise1:
					cout << "Option: ";
					
					if (cin >> choise) {
						cout << "\n";
						switch (choise)
						{
						case 1:
							printPrimary(startPtr);
							break;
						case 2:
							if (!isEmpty(startPtr)) {
								cout << "Enter complaintId to search: ";
								cin >> complaintId;
								searchPrimary(&startPtr, complaintId, customerName, customerAddress, complaint, date, contactNumber);

							}
							else {
								cout << "list is empty.\n\n";
							}
							break;
						}
						cout << "ID not found";
						break;
					}
					else {
						cout << "Enter a valid integer value!\n";
						cin.clear();
						cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
						goto choise1;
					}
					
					
				case 2:
					cout << "Input the number of choise\n"
						"1) print all details.\n"
						"2) search by ID.\n\n";
					choise2:
					cout << "Option: ";
					if (cin >> choise) {
						cout << "\n";
						switch (choise)
						{
						case 1:
							printSecondary(startSecondaryPtr);
							break;
						case 2:
							if (!isEmpty(startPtr)) {
								cout << "Enter complaintId to search: ";
								cin >> complaintId;
								searchSecondary(&startSecondaryPtr, complaintId, customerName, customerAddress, complaint, date, contactNumber);

							}
							else {
								cout << "list is empty.\n\n";
							}
							break;
						}
						cout << "ID not found";
						break;
					}
					else {
						cout << "Enter a valid integer value!\n";
						cin.clear();
						cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
						goto choise2;
					}
					

				default:
					cout << "Invalid choise \n";
					goto Table;
					break;
				}
				break;
			}
			else {
				cout << "Enter a valid integer value!\n";
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				goto sTable;
			}
			
		case 5:
			cout << "Enter addressed complaint ID: ";
			cin >> val;
			cout << endl;
			enqueue(val);
			break;
		case 6:
			dequeue();
			break;
		case 7:
			printQueue();
			break;
		default:
			cout << "Invalid option.\n\n";
			goto Start;
			break;
		}
		cout << "\n";
		cout << "-------------------------------\n";
		cout << "Enter the number of the selected option: ";
		cin >> selectedOptions;
		cout <<"-------------------------------\n\n";
	}
	cout << "Closing Programme.\n";
	return 0;

}


void options() {
	cout << "-------------------------------\n"
		"Input the number of your choise\n"
		"-------------------------------\n"
		"1) Add a complaint.\n"
		"2) Delete a complaint.\n"
		"3) Update a complaint.\n"
		"4) View Tables.\n"
		"5) Add to addressed complaints.\n"
		"6) Delete an addressed complaint.\n"
		"7) View addressed complaints.\n"
		"8) Exit.\n"
		"-------------------------------\n";
}

//Add a complaint
void insertPrimary(PrimaryPtr* startPtr, string complaintId, string customerName,
	string customerAddress, string complaint, string date, int contactNumber) {
	PrimaryPtr newPtr = NULL;
	PrimaryPtr previousPtr = NULL;
	PrimaryPtr currentPtr = NULL;

	newPtr = new Primary;
	if (newPtr != NULL) {
		newPtr->primaryComplaintId = complaintId;
		newPtr->primaryCustomerName = customerName;
		newPtr->primaryCustomerAddress = customerAddress;
		newPtr->primaryComplaint = complaint;
		newPtr->primaryDate = date;
		newPtr->primaryContactNumber = contactNumber;
		newPtr->primaryNextPtr = NULL;

		previousPtr = NULL;
		currentPtr = *startPtr;

		while (currentPtr != NULL && complaintId > currentPtr->primaryComplaintId) { //?
			previousPtr = currentPtr;
			currentPtr = currentPtr->primaryNextPtr;
		}

		if (previousPtr == NULL) {
			newPtr->primaryNextPtr = *startPtr;
			*startPtr = newPtr;
		}
		else {
			previousPtr->primaryNextPtr = newPtr;
			newPtr->primaryNextPtr = currentPtr;
		}
	}
	else {
		cout << "not inserted. no memory available.\n" << complaintId;
	}
}

void insertSecondary(SecondaryPtr* startSecondaryPtr, string complaintId, string customerName,
	string customerAddress, string complaint, string date, int contactNumber) {
	SecondaryPtr newPtr = NULL;
	SecondaryPtr previousPtr = NULL;
	SecondaryPtr currentPtr = NULL;

	newPtr = new secondary;
	if (newPtr != NULL) {
		newPtr->secondaryComplaintId = complaintId;
		newPtr->secondaryCustomerName = customerName;
		newPtr->secondaryCustomerAddress = customerAddress;
		newPtr->secondaryComplaint = complaint;
		newPtr->secondaryDate = date;
		newPtr->secondaryContactNumber = contactNumber;
		newPtr->secondaryNextPtr = NULL;

		previousPtr = NULL;
		currentPtr = *startSecondaryPtr;

		while (currentPtr != NULL && complaintId > currentPtr->secondaryComplaintId) { //?
			previousPtr = currentPtr;
			currentPtr = currentPtr->secondaryNextPtr;
		}

		if (previousPtr == NULL) {
			newPtr->secondaryNextPtr = *startSecondaryPtr;
			*startSecondaryPtr = newPtr;
		}
		else {
			previousPtr->secondaryNextPtr = newPtr;
			newPtr->secondaryNextPtr = currentPtr;
		}
	}
	else {
		cout << "not inserted. no memory available.\n" << complaintId;
	}
}

//Delete a complaint
char deleteComplaint(PrimaryPtr* startPtr, string complaintId, string customerName,
	string customerAddress, string complaint, string date, int contactNumber) {
	PrimaryPtr tempPtr = NULL;
	PrimaryPtr previousPtr = NULL;
	PrimaryPtr currentPtr = NULL;

	if (complaintId == (*startPtr)->primaryComplaintId) {
		tempPtr = *startPtr;
		*startPtr = (*startPtr)->primaryNextPtr;
		delete(tempPtr);
		return complaintId, customerName, customerAddress, complaint, date, contactNumber;
	}
	else {
		previousPtr = *startPtr;
		currentPtr = (*startPtr)->primaryNextPtr;

		while (currentPtr != NULL && currentPtr->primaryComplaintId != complaintId) {
			previousPtr = currentPtr;
			currentPtr = currentPtr->primaryNextPtr;
		}
		if (currentPtr != NULL) {
			tempPtr = currentPtr;
			previousPtr->primaryNextPtr = currentPtr->primaryNextPtr;
			delete(tempPtr);
			return complaintId, customerName, customerAddress, complaint, date, contactNumber;
		}
	}
	return '\0';
}

//check primary for id
char checkPrimaryForId(PrimaryPtr* startPtr, string complaintId, string customerName,
	string customerAddress, string complaint, string date, int contactNumber) {
	PrimaryPtr tempPtr = NULL;
	PrimaryPtr previousPtr = NULL;
	PrimaryPtr currentPtr = NULL;

	if (complaintId == (*startPtr)->primaryComplaintId) {
		tempPtr = *startPtr;
		*startPtr = (*startPtr)->primaryNextPtr;
		return complaintId, customerName, customerAddress, complaint, date, contactNumber;
	}
	else {
		previousPtr = *startPtr;
		currentPtr = (*startPtr)->primaryNextPtr;

		while (currentPtr != NULL && currentPtr->primaryComplaintId != complaintId) {
			previousPtr = currentPtr;
			currentPtr = currentPtr->primaryNextPtr;
		}
		if (currentPtr != NULL) {
			tempPtr = currentPtr;
			previousPtr->primaryNextPtr = currentPtr->primaryNextPtr;
			return complaintId, customerName, customerAddress, complaint, date, contactNumber;
		}
	}
	return '\0';
}

//check secondary for id
char checkSecondaryForId(SecondaryPtr* startSecondaryPtr, string complaintId, string customerName,
	string customerAddress, string complaint, string date, int contactNumber) {
	SecondaryPtr tempPtr = NULL;
	SecondaryPtr previousPtr = NULL;
	SecondaryPtr currentPtr = NULL;

	if (complaintId == (*startSecondaryPtr)->secondaryComplaintId) {
		tempPtr = *startSecondaryPtr;
		*startSecondaryPtr = (*startSecondaryPtr)->secondaryNextPtr;
		return complaintId, customerName, customerAddress, complaint, date, contactNumber;
	}
	else {
		previousPtr = *startSecondaryPtr;
		currentPtr = (*startSecondaryPtr)->secondaryNextPtr;

		while (currentPtr != NULL && currentPtr->secondaryComplaintId != complaintId) {
			previousPtr = currentPtr;
			currentPtr = currentPtr->secondaryNextPtr;
		}
		if (currentPtr != NULL) {
			tempPtr = currentPtr;
			previousPtr->secondaryNextPtr = currentPtr->secondaryNextPtr;
			return complaintId, customerName, customerAddress, complaint, date, contactNumber;
		}
	}
	return '\0';
}

//is list empty
int isEmpty(PrimaryPtr startPtr) {
	return startPtr == NULL;
}

//viewTables
void viewTables() {

}

void printPrimary(PrimaryPtr currentPtr) {
	cout << "printPrimary" << endl;
	if (currentPtr == NULL) {
		cout << "List Is Empty.\n\n";
	}
	else {
		cout << "The list is:\n";

		while (currentPtr != NULL) {
			cout << currentPtr->primaryComplaintId << " , " << currentPtr->primaryCustomerName << " , " << currentPtr->primaryCustomerAddress <<
				" , " << currentPtr->primaryComplaint << " , " << currentPtr->primaryDate << " , " << currentPtr->primaryContactNumber << " --> "; //?
			currentPtr = currentPtr->primaryNextPtr;
		}
		cout << "NULL\n\n";
	}
}

char searchPrimary(PrimaryPtr* startPtr, string complaintId, string customerName,
	string customerAddress, string complaint, string date, int contactNumber) {
	PrimaryPtr tempPtr = NULL;
	PrimaryPtr previousPtr = NULL;
	PrimaryPtr currentPtr = NULL;

	if (complaintId == (*startPtr)->primaryComplaintId) {
		tempPtr = *startPtr;
		//*startPtr = (*startPtr)->primaryNextPtr;
		//complaintId = tempPtr->primaryComplaintId;
		customerName = tempPtr->primaryCustomerName;
		customerAddress = tempPtr->primaryCustomerAddress;
		complaint = tempPtr->primaryComplaint;
		date = tempPtr->primaryDate;
		contactNumber = tempPtr->primaryContactNumber;
		cout << " Results.\n" << complaintId << " , " << customerName << " , " << customerAddress << " , "
			<< complaint << " , " << date << " , " << contactNumber << "\n";
	}
	else {
		previousPtr = *startPtr;
		currentPtr = (*startPtr)->primaryNextPtr;

		while (currentPtr != NULL && currentPtr->primaryComplaintId != complaintId) {
			previousPtr = currentPtr;
			currentPtr = currentPtr->primaryNextPtr;
		}
		if (currentPtr != NULL) {
			tempPtr = currentPtr;
			//previousPtr->primaryNextPtr = currentPtr->primaryNextPtr;
			customerName = tempPtr->primaryCustomerName;
			customerAddress = tempPtr->primaryCustomerAddress;
			complaint = tempPtr->primaryComplaint;
			date = tempPtr->primaryDate;
			contactNumber = tempPtr->primaryContactNumber;
			cout << " Results.\n" << complaintId << " , " << customerName << " , " << customerAddress << " , "
				<< complaint << " , " << date << " , " << contactNumber << "\n";
		}
	}
	return '\0';
}

void printSecondary(SecondaryPtr currentPtr) {
	cout << "printSecondary" << endl;
	if (currentPtr == NULL) {
		cout << "List Is Empty.\n\n";
	}
	else {
		cout << "The list is:\n";

		while (currentPtr != NULL) {
			cout << currentPtr->secondaryComplaintId << " , " << currentPtr->secondaryCustomerName << " , " << currentPtr->secondaryCustomerAddress <<
				" , " << currentPtr->secondaryComplaint << " , " << currentPtr->secondaryDate << " , " << currentPtr->secondaryContactNumber << " --> "; //?
			currentPtr = currentPtr->secondaryNextPtr;
		}
		cout << "NULL\n\n";
	}
}

char searchSecondary(SecondaryPtr* startSecondaryPtr, string complaintId, string customerName,
	string customerAddress, string complaint, string date, int contactNumber) {
	SecondaryPtr tempPtr = NULL;
	SecondaryPtr previousPtr = NULL;
	SecondaryPtr currentPtr = NULL;

	if (complaintId == (*startSecondaryPtr)->secondaryComplaintId) {
		tempPtr = *startSecondaryPtr;
		//*startSecondaryPtr = (*startSecondaryPtr)->secondaryNextPtr;
		customerName = tempPtr->secondaryCustomerName;
		customerAddress = tempPtr->secondaryCustomerAddress;
		complaint = tempPtr->secondaryComplaint;
		date = tempPtr->secondaryDate;
		contactNumber = tempPtr->secondaryContactNumber;
		cout << " Results.\n" << complaintId << " , " << customerName << " , " << customerAddress << " , "
			<< complaint << " , " << date << " , " << contactNumber << "\n";
	}
	else {
		previousPtr = *startSecondaryPtr;
		currentPtr = (*startSecondaryPtr)->secondaryNextPtr;

		while (currentPtr != NULL && currentPtr->secondaryComplaintId != complaintId) {
			previousPtr = currentPtr;
			currentPtr = currentPtr->secondaryNextPtr;
		}
		if (currentPtr != NULL) {
			tempPtr = currentPtr;
			//previousPtr->secondaryNextPtr = currentPtr->secondaryNextPtr;
			customerName = tempPtr->secondaryCustomerName;
			customerAddress = tempPtr->secondaryCustomerAddress;
			complaint = tempPtr->secondaryComplaint;
			date = tempPtr->secondaryDate;
			contactNumber = tempPtr->secondaryContactNumber;
			cout << " Results.\n" << complaintId << " , " << customerName << " , " << customerAddress << " , "
				<< complaint << " , " << date << " , " << contactNumber << "\n";
		}
	}
	return '\0';
}

void enqueue(int val) {
	if (rear == n - 1) {
		cout << "Queue over flow" << endl;
	}
	else {
		if (front == -1) {
			front = 0;
		}
		rear++;
		queue[rear] = val;
	}
}

void dequeue() {
	if (front == -1 || front > rear) {
		cout << "Queue undefined" << endl;
		return;
	}
	else {
		
		cout << "eliment deleted from queue is :" << queue[front] << endl;
		front++;
		for (int i = 0; i < rear - 1;i++) {
		queue[i] = queue[i + 1];
		}
		rear--;
	}
	return;
	cout << endl;
	
}

void printQueue() {
	if (front == -1) {
		cout << "Queue is empty" << endl;
	}
	else {
		cout << "Queue eliments are :" << endl;
		for (int i = front;i <= rear;i++) {
			cout << queue[i] << " ";
		}
		cout << endl << endl;
	}
}

bool checkForIdPrimary(PrimaryPtr* startPtr, string complaintId, bool x) {
	PrimaryPtr tempPtr = NULL;
	PrimaryPtr previousPtr = NULL;
	PrimaryPtr currentPtr = NULL;
	x = false;

	if (complaintId == (*startPtr)->primaryComplaintId) {
		tempPtr = *startPtr;
		x = true;
		cout << "ID exists\n";
		return x;
	}
	else {
		previousPtr = *startPtr;
		currentPtr = (*startPtr)->primaryNextPtr;

		while (currentPtr != NULL && currentPtr->primaryComplaintId != complaintId) {
			previousPtr = currentPtr;
			currentPtr = currentPtr->primaryNextPtr;
		}
		if (currentPtr != NULL) {
			tempPtr = currentPtr;
			x = true;
			cout << "ID exists\n";
			return x;
		}
	}

	return x = false;
}
