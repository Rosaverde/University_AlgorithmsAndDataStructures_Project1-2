#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

struct entry
{
  int day;
  int month;
  int year;
  int hour;
  int minutes;
  string note;

  entry *next_entry;
};

void print_List(entry *adress)
{
  if(adress == NULL)
    cout << endl << "The list is empty" << endl << endl;
  while(adress != NULL)
  {
    cout << endl << "Note from: " << adress->year << '.' << adress->month << '.' << adress->day << "   " << adress->hour << ':' << adress->minutes << endl;
    cout << '"' << adress->note << '"' << endl << endl;
    adress = adress->next_entry;
  }
}

void delete_List(entry *&head)
{
  entry *tmp;
  while(head != NULL)
    {
      tmp = head;
      head = head->next_entry;
      cout << endl << "Deleting: " << tmp->note << "  of: " << tmp->day << '.' << tmp->month << '.' << tmp->year << endl;
      delete tmp;
    }
  cout<< endl <<"List is empty"<< endl << endl;
}

void show_Day(entry *adress)
{
  int  p_day, p_month, count;
  cout << endl;
  cout << "Which day do you want to check?";
  cin >> p_day;
  cout << "Which month do you want to check?";
  cin >> p_month;
  count = 0;
  while(adress != NULL)
    {
      if(adress->day == p_day && adress->month == p_month)
        {
          count++;
          cout << endl << "On this day it was recorded at "<< adress->hour << ':' << adress->minutes << endl;
          cout << '"' << adress->note << '"' << endl << endl;;
        };
      adress = adress->next_entry;
    }
  if(count ==0)
    cout<< endl <<"There are no notes on this day" << endl << endl;
}

void add_beginning(entry *&head, int year, int month, int day, int hour, int minutes, string note)
{
  entry *current;

  current = new entry;
  current->next_entry = head;
  current->year = year;
  current->month = month;
  current->day = day;
  current->hour = hour;
  current->minutes = minutes;
  current->note = note;
  head = current;

}

void quest(int dni, entry *&head, int year, int month, int &day)
{
  string note;
  int hour, minutes;

  cout << "Enter the day of the note: ";
  cin >> day;
  while(day>dni || day<0)
    {
      cout << endl;
      cout <<"There are not that many days this month." << endl;
      cout <<"Choose a different day: ";
      cin >> day;
      cout << endl;
    }
  if(day !=0 && month != 0 && year != 0)
    {
      cout << "Give me an hour of note: ";
      cin >> hour;
      while(hour>24 || hour<0)
        {
          cout << endl;
          cout << "Invalid hour." << endl;
          cout << "Try again: ";
          cin >> hour;
          cout << endl;
        }
      cout <<"Enter the minutes of the note: ";
      cin >> minutes;
      while(minutes>60 || minutes<0)
        {
          cout << endl;
          cout << "Invalid value of minutes." << endl;
          cout << "Try again: ";
          cin >> minutes;
          cout << endl;
        }
      getchar();
      cout << "Enter a note: ";
      getline(cin, note);
      cout << endl;

      add_beginning(head,year,month,day,hour,minutes,note);
    }
  else if (day !=0 || month != 0 || year != 0)
    cout << endl << "Incorrect date try again: " << endl << endl;
  else
    cout << endl << "END OF WRITING NOTES." << endl << endl;
};

void data_select(entry *&head)
{
  int day, month, year;

  cout << endl << "If you want to finish adding notes, enter 0 in year, month and day" << endl << endl;

  do
    {
      cout <<"Enter the year of the note: ";
      cin>>year;
      cout << "Enter the month of the note: ";
      cin>>month;
      while(month>12 || month<0)
        {
          cout << endl;
          cout << "There are not that many months." << endl;
          cout << "Please enter a valid value: ";
          cin >> month;
          cout << endl;
        }
      if(month % 2== 0 && month != 8)
        {
          if(month == 2)
            quest(28, head, year, month, day);
          else
            quest(30, head, year, month, day);
        }
      else
        quest(31, head, year, month, day);
    }
  while(day !=0 || month != 0 || year != 0);
  cout << endl;
}

int move_first_note(entry *&head,  int p_month, int p_day)
{
  int count, count_old, temp_minutes, temp_hour;
  entry *smallest_element, *temp_current, *prev, *prev_tmp, *tmp;

  temp_current = head;
  prev = NULL;

  if(head == NULL)
    {
      cout << endl << "List is empty" << endl << endl;
      return 0;
    }
  else
  {
    count = 0;
    count_old= 0;
    temp_hour = 25;
    temp_minutes = 60;
    smallest_element = NULL;

    while(temp_current != NULL)
      {
        if(temp_current->day == p_day && temp_current->month == p_month)
          {
            count++;
            if(temp_current->hour < temp_hour )
              {
                temp_hour = temp_current->hour;
                temp_minutes = temp_current->minutes;
                smallest_element = temp_current;

                if(prev != NULL)
                  prev_tmp = prev;
              }
            else if(temp_current->hour == temp_hour )
              {
               if(temp_current->minutes < temp_minutes)
                  {
                    temp_hour = temp_current->hour;
                    temp_minutes = temp_current->minutes;
                    smallest_element = temp_current;

                    if(prev != NULL)
                      prev_tmp = prev;
                  }
              }
          }
            prev = temp_current;
            temp_current = temp_current->next_entry;
      }
    if(count ==0 && head != NULL)
      {
        cout<< endl <<"There are no notes on this day" << endl << endl;
        return 0;
      }
    else
      {
        if(smallest_element == head)
          cout << endl << "The note is already in the first place" << endl << endl;
        else
          {
            prev_tmp->next_entry = smallest_element->next_entry;
            tmp = head;
            head = smallest_element;
            head->next_entry = tmp;
          }
      }

    cout << endl << "LIST OF NOTES: " << endl;
    print_List(head);

    temp_current = head;
    prev = NULL;
    while(temp_current != NULL)
      {
        if(temp_current->month == smallest_element->month && temp_current->day == smallest_element->day)
          {
            if(temp_current != head)
              {
                prev->next_entry = temp_current->next_entry;
                tmp = temp_current;
                temp_current= temp_current->next_entry;
                cout << endl << "Deleting: " << tmp->note << "  of: " << tmp->day << '.' << tmp->month << '.' << tmp->year << "   " << tmp->hour << ':' << tmp->minutes << endl;
                delete tmp;
              }
            else
              {
                prev = temp_current;
                temp_current = temp_current->next_entry;
              }
          }
        else
          {
            prev = temp_current;
            temp_current = temp_current->next_entry;
          }
      }

    temp_current = head;
    while(temp_current != NULL)
      {
        if(temp_current->month < smallest_element->month)
          count_old ++;
        else if(temp_current->month == smallest_element->month && temp_current->day < smallest_element->day)
          count_old ++;

        temp_current = temp_current->next_entry;
      }
    cout << "OTHER NOTES:" << endl;
    print_List(head);
    cout << count_old << endl;
    return count_old;
  }


}
int main()
{
  int selection, p_month, p_day;
  entry *head = NULL;

  cout << " WELCOME TO THE DAY PLANER"<< endl;
  do
    {
      cout <<"---------------------------"<< endl;
      cout << " MAIN MENU:"<< endl;
      cout << "---------------------------"<< endl;
      cout << "1.  Add a note at the beginning"<< endl;
      cout << "2.  Show day"<< endl;
      cout << "3.  Print List"<< endl;
      cout << "4.  Delete List"<< endl;
      cout << "5.  Show your first note"<<endl;
      cout << "6.  Exit"<< endl;
      cout << "---------------------------"<< endl;
      cout << "Selection: ";
      cin >> selection;

      switch (selection)
        {
          case 1: data_select(head); break;
          case 2: show_Day(head);  break;
          case 3: print_List(head);  break;
          case 4: delete_List(head);   break;
          case 5: cout << endl;
                  cout << "Which day do you want to check?";
                  cin >> p_day;
                  cout << "Which month do you want to check?";
                  cin >> p_month;
                  move_first_note(head, p_month, p_day); break;
          case 6: delete_List(head);
                  cout << endl << "END OF THE PROGRAM!" << endl; break;
          default:
          cout<< endl << "ERROR!" << endl << endl;
          break;
        };
    }
  while(selection!=6);
    return 0;
}
