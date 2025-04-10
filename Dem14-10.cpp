//dem14-10.cpp

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <string>

using namespace std;

struct Part_Record
{
  char   id_no[3];
  int    qoh;
  double price;
};

int Get_Menu_Choice();
void Add_Record(fstream&);
void Delete_Record(fstream&);
void Change_Record(fstream&);
int Get_Change();
void Display_File(fstream&);
int Valid_Rec_Num(long);

int main()
{
  int choice;
  int quit = 0;

  cout << setprecision(2)
		 << setiosflags(ios::fixed)
       << setiosflags(ios::showpoint);

  fstream part_file;

  Part_Record null_part = { "", 0, 0.0};

  //Open the file for reading to see if file exists

  part_file.open("partfile.dat", ios::in | ios::binary);

  //If the file does not exist,
  //create a file of 99 dummy records.

  if (part_file.fail())
	 {
		part_file.open("partfile.dat", ios::out | ios::binary);

		for (long rec_num = 1L; rec_num <= 99L; ++rec_num)
		  part_file.write( (char *) &null_part, sizeof(Part_Record) );

		cout << "\nNull File Created.";
	 }


  //Close the file

  part_file.close();


  //Open the file for both input and output

  part_file.open("partfile.dat", ios::in | ios::out | ios::binary);

  //Processing loop

  do
	 {
		choice = Get_Menu_Choice();
		switch (choice)
		  {
			 case 1:
				Add_Record(part_file); break;
			 case 2:
				Delete_Record(part_file); break;
			 case 3:
				Change_Record(part_file); break;
			 case 4:
				Display_File(part_file); break;
			 case 5:
				quit = 1; break;
			 default:
				cout << "\n\nInvalid Choice. Try Again.\n\n"; break;
		  }
	 }
  while (!quit);

  part_file.close();

  cout << endl;
  return 0;
} //End of main()

int Get_Menu_Choice()
{
  int choice;

  cout << "\n\nMain Menu";
  cout << "\n\n1 - Add a Record"
		 << "\n2 - Delete a Record"
		 << "\n3 - Change a Record"
		 << "\n4 - Display the File"
		 << "\n5 - Quit the Program";

  cout << "\n\nEnter your choice: ";
  cin >> choice;

  return choice;
}  //End Get_Menu_Choice()

void Add_Record(fstream& file)
{
  Part_Record part;
  Part_Record temp_part;

  long rec_num;

  cin.get();

  cout << "\nEnter the data for a part:";
  cout << "\n\nPart Number (01-99): ";
  cin.getline(part.id_no, 3);

  rec_num = atol(part.id_no);
  if ( !Valid_Rec_Num(rec_num) )
	 return;

  cout << "\nQuantity On Hand: ";
  cin >> part.qoh;

  cout << "\nPrice: ";
  cin >> part.price;

  file.seekg( (rec_num - 1) * sizeof(Part_Record), ios::beg);

  file.read( (char *)&temp_part, sizeof(Part_Record) );

  if ( strcmp(temp_part.id_no, "") == 0)
	 {
		file.seekg( -(long)sizeof(Part_Record), ios::cur);
		file.write( (char *)&part, sizeof(Part_Record) );
		cout << "\nRecord " << part.id_no << " added to file.";
	 }
  else
	 cout << "\nPart already exists. Make another selection.";
} //End of Add_Record

void Delete_Record(fstream& file)
{
  Part_Record part;
  Part_Record null_part = {"", 0, 0.0};

  long rec_num;

  cout << "\nEnter the number of the record to delete: ";
  cin >> rec_num;

  if (!Valid_Rec_Num(rec_num))
	 return;

  file.seekg( (rec_num - 1) * sizeof(Part_Record), ios::beg);
  file.read( (char *) &part, sizeof(Part_Record) );

  if ( strcmp(part.id_no, "") == 0)
	 cout << "\nThe record does not exist. Make another selection.";
  else
	 {
		file.seekg(-(long)sizeof(Part_Record), ios::cur);
		file.write( (char *) &null_part, sizeof(Part_Record) );
		cout << "\nRecord " << rec_num << " deleted from file.";
	 }

}  //End of Delete_Record

void Change_Record(fstream& file)
{
  Part_Record part;
  long rec_num;
  int change;
  int quit = 0;

  cout << "\nEnter number of record to change: ";
  cin >> rec_num;

  if (!Valid_Rec_Num(rec_num))
	 return;

  file.seekg( (rec_num - 1) * sizeof(Part_Record), ios::beg);
  file.read( (char *) &part, sizeof(Part_Record) );

  if ( strcmp(part.id_no, "") == 0)
	 {
		cout << "\nThe record does not exist. Make another selection.";
		return;
	 }

  cout << "\nThe current record contents are:\n\n";
  cout << setw(20) << "Part Number"
		 << setw(20) << "Quantity On Hand"
		 << setw(20) << "Price" << endl << endl;
  cout << setw(20) << part.id_no
		 << setw(20) << part.qoh
		 << setw(20) << part.price;

  do
	 {
		change = Get_Change();
		switch (change)
		  {
			 case 1:
				cout << "\nEnter Quantity On Hand: ";
				cin >> part.qoh;
				break;
			 case 2:
				cout << "\nEnter Price: ";
				cin >> part.price;
				break;
			 case 3:
				quit = 1;
				file.seekg(-(long)sizeof(Part_Record), ios::cur);
				file.write( (char *) &part, sizeof(Part_Record) );
				cout << "\nChanges made to record " << rec_num;
				break;
			 default:
				cout << "\nInvalid Choice. Try Again.";
				break;
		  }
	 }
  while (!quit);

} //End of Change_Record()

int Get_Change()
{
  int change;

  cout << "\n\nChange Menu\n\n";
  cout << "1 - Change Quantity On Hand\n"
		 << "2 - Change Price\n"
		 << "3 - Write Changes and return to Main Menu\n\n";
  cout << "Enter your choice: ";
  cin >> change;

  return change;
}  //End Get_Change()

void Display_File(fstream& file)
{
  Part_Record part;
  long rec_num;
  long rec_count = 0L;

  file.seekg( 0L, ios::beg);

  cout << setw(20) << "\nPart Number"
		 << setw(20) << "Quantity On Hand"
		 << setw(20) << "Price" << endl << endl;

  for (rec_num = 1L; rec_num <= 99L; ++rec_num)
	 {
		file.read( (char*) &part, sizeof(Part_Record) );
		if (strcmp(part.id_no, "") != 0)
		  {
          cout << setw(20) << part.id_no
					<< setw(20) << part.qoh
					<< setw(20) << part.price << endl;
			 ++rec_count;
		  }
	 }

  cout << "\n\nFile contains " << rec_count << " records.";

}  //End of Display_File()

int Valid_Rec_Num(long rec_num)
{
  if ( rec_num < 1L || rec_num > 99L )
	 {
		cout << "\n\nERROR: Invalid record number. Try again.";
		return 0;
	 }
  else
	 return 1;

}  //End of Valid_Rec_Num()


