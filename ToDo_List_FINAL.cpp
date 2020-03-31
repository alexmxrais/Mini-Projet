#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void ParseFile(string, vector<string>&,vector<string>&, vector<string>&, vector<string>&, vector<string>&, vector<int>&, vector<string>&);
void ShowList(vector<string>,vector<string>, vector<string>, vector<string>, vector<string>, vector<int>, vector<string>);
void ShowMenu();
void AddTask(vector<string>&,vector<string>&, vector<string>&, vector<string>&, vector<string>&, vector<int>&, vector<string>&);
void ModifyPercent(vector<string>&);
void ModifyComment(vector<string>&);
void RemoveTask(vector<string>&,vector<string>&, vector<string>&, vector<string>&, vector<string>&, vector<int>&, vector<string>&);
void SaveFile(string, vector<string>&,vector<string>&, vector<string>&, vector<string>&, vector<string>&, vector<int>&, vector<string>&);

ifstream fileReader;
ofstream fileWriter;

int main()
{
  vector<string> Tasks;
  vector<string> iDates;
  vector<string> fDates;
  vector<string> Titles;
  vector<string> Percents;
  vector<int> Priorities;
  vector<string> Comments;

  ParseFile("ToDo_List.txt", Tasks, iDates, fDates, Titles, Percents, Priorities, Comments);

  while (true)

  {
    if (system("CLS")) system("clear");

    ShowList(Tasks, iDates, fDates, Titles, Percents, Priorities, Comments);
    ShowMenu();

    cout << "Votre choix :";
    int choice;
    cin >> choice;
    cin.ignore(1000, 10);
    cout << endl << endl;

    switch (choice)
    {
      case 1:
        AddTask(Tasks, iDates, fDates, Titles, Percents, Priorities, Comments);
        break;
      case 2:
        ModifyPercent(Percents);
        break;
      case 3:
        ModifyComment(Comments);
        break;
      case 4:
        RemoveTask(Tasks, iDates, fDates, Titles, Percents, Priorities, Comments);
        break;
      case 5:
        return 0;
    }

    SaveFile("ToDo_List.txt", Tasks, iDates, fDates, Titles, Percents, Priorities, Comments);
  }
}

void ParseFile(string fileName,
               vector<string>& tasks,
               vector<string>& idates,
               vector<string>& fdates,
               vector<string>& titles,
               vector<string>& percents,
               vector<int>& priorities,
               vector<string>& comments)
{

  fileReader.open(fileName);

  string line;
  while (getline(fileReader, line))

  {
    string task = line.substr(0, line.length());
    string idate = task.substr(task.find("|") + 1, task.length());
    string fdate = idate.substr(idate.find("§") + 1, idate.length());
    string title = fdate.substr(fdate.find("µ") + 1, fdate.length());
    string percent = title.substr(title.find("&") + 1, title.length());
    string priority = percent.substr(percent.find("¤") + 1, percent.length());
    string comment = priority.substr(priority.find("£") + 1, priority.length());
    priority = priority.substr(0, priority.find("£"));
    percent = percent.substr(0, percent.find("¤"));
    title = title.substr(0, title.find("&"));
    fdate = fdate.substr(0, fdate.find("µ"));
    idate = idate.substr(0, idate.find("§"));
    task = task.substr(0, task.find("|"));

    if (priority == "0")
      { priorities.push_back(0);}
    else
      {
        if (priority == "1")
          { priorities.push_back(1);}
        else
          { priorities.push_back(2);}
      }

    tasks.push_back(task);
    idates.push_back(idate);
    fdates.push_back(fdate);
    titles.push_back(title);
    percents.push_back(percent);
    comments.push_back(comment);
  }

  fileReader.close();
}

void ShowList( vector<string> tasks,
               vector<string> idates,
               vector<string> fdates,
               vector<string> titles,
               vector<string> percents,
               vector<int> priorities,
               vector<string> comments)
{
  for (int i = 0; i < tasks.size(); i++)
  {
    cout << i + 1 << ". ";

    if (percents[i]=="100")
    {
      cout << "[x] ";                                           // ceci correspond, à proprement parler,
    }                                                           // au status de la tâche (ici : la tâche est réalisée)
    else
    {
      cout << "[ ] ";
    }

    cout << titles[i] << endl;

    if (priorities[i] == 0)
      { cout << "       Priorité:          faible" << endl;}
    else
      {
        if (priorities[i] == 1)
          { cout << "       Priorité:          normal" << endl;}
        else
          { cout << "       Priorité:           urgent" << endl;}
      }

    cout << "       Description:       " << tasks[i] << endl;

    cout << "       Avancement:        " << percents[i] << "%" << endl;

    cout << "       Date de création:  " << idates[i] << endl;

    cout << "       Date de fin:       " << fdates[i] << endl << endl;

    cout << "       Commentaires:       " << comments[i] << endl << endl;
  }
}

void ShowMenu()
{
  cout << "Menu:" << endl
       << "1. Ajouter une tâche" << endl
       << "2. Modifier l'avancement d'une tâche" << endl
       << "3. Modifier les commentaires d'une tâche" << endl
       << "4. Supprimer une tâche" << endl
       << "5. Fin" << endl << endl;
}

void AddTask(vector<string>& tasks,
             vector<string>& idates,
             vector<string>& fdates,
             vector<string>& titles,
             vector<string>& percents,
             vector<int>& priorities,
             vector<string>& comments)
{
  cout << "Ajouter une tâche" << endl
       << "=================" << endl;

  cout << "Titre: ";
  string title;
  getline(cin, title);
  titles.push_back(title);

  cout << endl << endl;
  
  cout << "Priorité :" << endl << endl;

  cout << "1. faible" << endl;
  cout << "2. normal" << endl;
  cout << "3. urgent" << endl << endl;

    int choice;
    cin >> choice;
    cin.ignore(1000, 10);

    switch (choice)
    {
      case 1:
        priorities.push_back(0);
        break;
      case 2:
        priorities.push_back(1);
        break;
      case 3:
        priorities.push_back(2);
        break;
    }

  cout << endl << endl;

  cout << "Description: ";
  string task;
  getline(cin, task);
  tasks.push_back(task);

  cout << endl << endl;

  cout << "Pourcentage d'avancement: ";
  string percent;                               // le pourcentage d'avancement a été mis sous la forme d'une string pour pouvoir
  getline(cin, percent);                        // manipuler des entiers et des flottants sans se poser de questions
  percents.push_back(percent);

  cout << endl << endl;

  cout << "Date de création: ";
  string idate;
  getline(cin, idate);
  idates.push_back(idate);

  cout << endl << endl;

  cout << "Date de fin: ";
  string fdate;
  getline(cin, fdate);
  fdates.push_back(fdate);

  cout << endl << endl;

  cout << "Commentaires: ";
  string comment;
  getline(cin, comment);
  comments.push_back(comment);

  cout << endl << endl;

}

void ModifyPercent (vector<string>& percents)
{
  cout << "Modifier l'avancement" << endl
       << "=====================" << endl;

  cout << "Numéro :";
  int num;
  cin >> num;
  cin.ignore(1000, 10);

  if (num>=1 && num<percents.size()+1)
  {
    
    cout << "Nouveau pourcentage d'avancement: ";
    string percent;
    getline(cin, percent);
    percents[num-1] = percent;

  }
  else
  {
    cout << "Le numéro indiqué n'éxiste pas" << endl;
  }

}

void ModifyComment (vector<string>& comments)
{
  cout << "Modifier les commentaires d'une tâche" << endl
       << "=====================================" << endl;

  cout << "Numéro :";
  int num;
  cin >> num;
  cin.ignore(1000, 10);

  if (num>=1 && num<comments.size()+1)
  {
    
    cout << "Nouveaux commentaires: ";
    string comment;
    getline(cin, comment);
    comments[num-1] = comment;

  }
  else
  {
    cout << "Le numéro indiqué n'éxiste pas" << endl;
  }

}

void RemoveTask(vector<string>& tasks,
                vector<string>& idates,
                vector<string>& fdates,
                vector<string>& titles,
                vector<string>& percents,
                vector<int>& priorities,
                vector<string>& comments)
{
  cout << "Supprimer une tâche" << endl
       << "===================" << endl;

  cout << "Numéro : ";
  int num;
  cin >> num;
  cin.ignore(1000, 10);

  if (num>=1 && num<tasks.size()+1)
  {
    tasks.erase(tasks.begin()+num-1);
    idates.erase(idates.begin()+num-1);
    fdates.erase(fdates.begin()+num-1);
    titles.erase(titles.begin()+num-1);
    percents.erase(percents.begin()-num+1);
    priorities.erase(priorities.begin()-num+1);
    comments.erase(comments.begin()-num+1);

  }
  else
  {
    cout << "Le numéro indiqué n'éxiste pas" << endl;
  }
}

void SaveFile(string fileName,
              vector<string>& tasks,
              vector<string>& idates,
              vector<string>& fdates,
              vector<string>& titles,
              vector<string>& percents,
              vector<int>& priorities,
              vector<string>& comments)
{

  fileWriter.open(fileName);

    for (int i = 0; i < tasks.size(); i++)
    {
      fileWriter << tasks[i] << "|" << idates[i] << "§" << fdates[i] << "µ" << titles[i] << "&" << percents[i] << "¤" ;

      if (priorities[i] == 0)
        { fileWriter << "0" ;}
      else
        {
          if (priorities[i] == 1)
            { fileWriter << "1" ;}
          else
            { fileWriter << "2" ;}
        }

      fileWriter << "£" << comments[i] << endl;
    }

  fileWriter.close();
}
