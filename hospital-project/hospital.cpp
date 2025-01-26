#include <iostream>
using namespace std;

#define MAX_SPECIALIZATION      20
#define MAX_QUEUE               5

string names[MAX_SPECIALIZATION+1][MAX_QUEUE+1];
int status[MAX_SPECIALIZATION+1][MAX_QUEUE+1];
int queue_length[MAX_SPECIALIZATION+1];

void shift_right(int spec, string names_sp[], int status_sp[]);
void shift_left(int spec, string names_sp[], int status_sp[]);

int Add_new_patient(int spec, string name, int st);
void Print_all_patients(void);
void print_patient(int spec, string names_sp[], int status_sp[]);
void Get_next_patient(void);

int main()
{
  int choice;

  int spec, st;
  string name;
  int err_status;

  while(1)
  {
    cout << "1) Add new patient\n";
    cout << "2) Print all patients\n";
    cout << "3) Get next patient\n";
    cout << "4) Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    switch(choice)
    {
      case 1:
        cout << "Enter specialization, name, status: ";
        cin >> spec >> name >> st;
        err_status = Add_new_patient(spec, name, st);
      break;

      case 2:
        Print_all_patients();
      break;

      case 3:
        Get_next_patient();
      break;

      case 4:
        exit(0);
      break;
    }
  }

  return 0;
}

void shift_right(int spec, string names_sp[], int status_sp[])
{
  int len = queue_length[spec];
  for(int i = len-1; i >= 0; i--)
  {
    names_sp[i+1] = names_sp[i];
    status_sp[i+1] = status_sp[i];
  }
  queue_length[spec]++;
}

void shift_left(int spec, string names_sp[], int status_sp[])
{
  int len = queue_length[spec];
  for(int i = 1; i < len; i++)
  {
    names_sp[i-1] = names_sp[i];
    status_sp[i-1] = status_sp[i];
  }
  queue_length[spec]--;
}

int Add_new_patient(int spec, string name, int st)
{
  int pos = queue_length[spec];
  if(pos >= MAX_QUEUE)
  {
    cout << "Sorry, we can't add more patients for this specialization.\n";
    return 0;
  }
  
  if(st == 0)
  {
    names[spec][pos] = name;
    status[spec][pos] = st;
    queue_length[spec]++;
  }
  else
  {
    // urgent
    shift_right(spec, names[spec], status[spec]);
    names[spec][0] = name;
    status[spec][0] = st;
  }

  return 1;
}

void Print_all_patients(void)
{
  for(int spec = 0; spec < MAX_SPECIALIZATION; spec++)
  {
    print_patient(spec, names[spec], status[spec]);
  }
}

void print_patient(int spec, string names_sp[], int status_sp[])
{
  int len = queue_length[spec];
  if(len == 0)
    return;
  cout << "There are " << len << " patients in specialization " << spec << "\n";
  for(int i = 0; i < len; i++)
  {
    cout << names_sp[i] << " ";
    if(status_sp[i])
      cout << "urgent\n";
    else
      cout << "regular\n";
  }
  cout << "\n";
}

void Get_next_patient(void)
{
  int spec;
  cout << "Enter Specialization: ";
  cin >> spec;
  int len = queue_length[spec];
  if(len == 0)
  {
    cout << "No patients at the moment. Have rest Doc\n";
    return;
  }
  cout << names[spec][0] << " please go with the Doc\n";

  shift_left(spec, names[spec], status[spec]);
}
