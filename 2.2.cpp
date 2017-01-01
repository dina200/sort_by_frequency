#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <conio.h>
//https://www.youtube.com
using namespace std;
struct date
{
	short day;
	short mon;
	short year;	
};
struct time
{
	short hour;
	short min;	
};
struct time_spend
{
	short h;
	short m;	
};
struct web
{
	string ip;
	string browser;
	string site;
	date d;
	time t;
	time_spend t1;	
	int index;
	double t_s;
};
void Menu ()
{
	cout << "0.Enter '0' to show the list." << endl;
	cout << "1.Enter '1' to determine the popularity of the browsers." << endl;
	cout << "2.Enter '2' to determine the popularity of the web-sites." << endl;
	cout << "3.Enter '3' to determine ip-addresses." << endl;
	cout << "4.Enter '4' to determine the middle popularity of the site for last month." << endl;
	cout << "5.Enter '5' to exit." << endl;
}
void Info (web* w, int count)
{
	for(short i = 0; i < count; i++)
	{
		cout << "\t-" << 1+i << '-' <<  endl;
		cout << "ip: " << w[i].ip << ' ';
		cout << "browser: " << w[i].browser << endl;
		cout << "site: " << w[i].site << endl;
		cout << "day: " << w[i].d.day << '\t';
		cout << "mon: " << w[i].d.mon << '\t';
		cout << "year: " << w[i].d.year << endl;
		cout << "hour: " << w[i].t.hour << '\t';
		cout << "min: " << w[i].t.min << endl;	
		cout << "Time spending:\nhour: " << w[i].t1.h << '\t';
		cout << "min: " << w[i].t1.m << endl;	
		cout << endl;
	}
}
web *ReadFromFile(ifstream &fin, short count)
{		
	fin.seekg (0, ios::beg);
	web *w = new web [count];
	for (short i = 0; i < count; i++)
	{
		if (i == 0)		
		{
		getline (fin, w[i].ip, ' ');
		}
		else
		{
		fin.get(); getline (fin, w[i].ip, ' ');
		}		
		getline (fin, w[i].browser , ':');
		fin.get();
		getline (fin, w[i].site, ' ');
		fin >> w[i].d.day;
		fin >> w[i].d.mon;
		fin >> w[i].d.year;
		fin >> w[i].t.hour;
		fin >> w[i].t.min;
		fin >> w[i].t1.h;
		fin >> w[i].t1.m;	
	}
	fin.close(); 	
	return w;
}
int main ()
{
	
	cout << "Enter a name of a file: ";
	char file_name[50];
	cin.getline (file_name, 50);
	ifstream fin (file_name);	
	string str;
	short count = 0;
	while (!fin.eof())
	{
		getline (fin, str, '\n');
		count ++;
	}	
	short choice;
	do 
	{	
	Menu ();	
	cin >> choice;	
	switch (choice)
	{
		case 0: 
				{
				ifstream fin (file_name);
				web* w = ReadFromFile (fin, count);			
				Info (w, count); 				
				delete []w;					
				break;
				}
		case 1: 
				{
				ifstream fin (file_name);
				web* w = ReadFromFile (fin, count);
				ofstream f1 ("1.txt");				
				f1 << "The more popular browsers:" << endl;								
				web tmp;								
				for(short i = 0; i < count; i++)
				{
					w[i].index = 1;					
					for (short j = i+1; j < count; j++)
					{
					if (w[i].browser == w[j].browser)
					{					
					w[i].index++;
					w[j].browser = "repeat";									
					}
					else if (w[i].browser == "repeat")
					{
					continue;	
					}
					}
				}				
				for (int k = count-1; k > 0; k--)
					{		
        				for (int i = 0; i < k; i++)
           				{
                			
							if (w[i].browser == "repeat")
								{
								continue;											
								}
							else if (w[i].index < w[i+1].index) 
								{				
								tmp = w[i];
								w[i] = w [i+1];
								w[i+1] = tmp;								
								}												
            			}
					}
				int place = 1;
				for(short i = 0; i < count; i++)
				{
				if (w[i].browser == "repeat")
						{
						
						continue;											
						}					
				else 
					{
					f1 << place << ". " << w[i].browser << " - " << w[i].index << endl;
					cout <<  place << ". " << w[i].browser << " - " << w[i].index << endl;
					place++;
					}
				}
				f1.close();				
				delete []w;					
				break;
				}		
		case 2: 
				{
				ifstream fin (file_name);
				web* w = ReadFromFile (fin, count);
				ofstream f2 ("2.txt");
				f2 << "The more popular web-sites:" << endl;				
				web tmp;								
				for(short i = 0; i < count; i++)
				{
					w[i].index = 1;					
					for (short j = i+1; j < count; j++)
					{
					if (w[i].site == w[j].site)
					{					
					w[i].index++;
					w[j].site = "repeat";									
					}
					else if (w[i].site == "repeat")
					{
					continue;	
					}
					}
				}
				
				for (int k = count-1; k > 0; k--)
					{		
        				for (int i = 0; i < k; i++)
           				{
                			
							if (w[i].site == "repeat")
								{
								continue;											
								}
							else if (w[i].index < w[i+1].index) 
								{				
								tmp = w[i];
								w[i] = w [i+1];
								w[i+1] = tmp;								
								}												
            			}
					}
				int place = 1;
				for(short i = 0; i < count; i++)
				{
				if (w[i].site == "repeat")
						{
						
						continue;											
						}					
				else 
					{
					f2 << place << ". " << w[i].site << " - " << w[i].index << endl;
					cout <<  place << ". " << w[i].site << " - " << w[i].index << endl;
					place++;
					}
				}				
				f2.close();					
				delete []w;				
				break;
				}
				
		case 3: 
				{
				ifstream fin (file_name);
				web* w = ReadFromFile (fin, count);
				ofstream f3 ("3.txt");
				f3 << "The first ip-addresses:" << endl; 
				web tmp;								
				for(short i = 0; i < count; i++)
				{
					w[i].index = 1;					
					for (short j = i+1; j < count; j++)
					{
					if (w[i].ip == w[j].ip)
					{					
					w[i].index++;
					w[j].ip = "repeat";									
					}
					else if (w[i].ip == "repeat")
					{
					continue;	
					}
					}
				}
				
				for (int k = count-1; k > 0; k--)
					{		
        				for (int i = 0; i < k; i++)
           				{
                			
							if (w[i].ip == "repeat")
								{
								continue;											
								}
							else if (w[i].index < w[i+1].index) 
								{				
								tmp = w[i];
								w[i] = w [i+1];
								w[i+1] = tmp;								
								}												
            			}
					}
				int place = 1;
				for(short i = 0; i < count; i++)
				{
				if (w[i].ip == "repeat")
						{						
						continue;											
						}					
				else 
					{
					f3 << place << ". " << w[i].ip << " - " << w[i].index << endl;
					cout <<  place << ". " << w[i].ip << " - " << w[i].index << endl;
					place++;
					}
				}
				f3.close();				
				delete []w;	
				break;
				}
		case 4: 
				{	
				ofstream f4 ("4.txt");	
				f4 << "The middle popularity of the site for last month:" << endl; 
				ifstream fin (file_name);
				web* w = ReadFromFile (fin, count);					
				short m;				
				cout << "Enter a mounth for today [1; 12]:" << endl;	
				while (!(cin >> m) || m < 1 || m > 12)
				{
				cout << "Error. Repeat the input (month [1; 12]).\n"; cin.clear(); cin.sync();
				}
				for (int i = 0; i < count; i++)
				{
				w[i].t_s = 0;
				}
				for (int i = 0; i < count; i++)
				{					
					if (w[i].d.mon == m-1)
					{
					double t_m = w[i].t1.h*60 + w[i].t1.m;
					int av = 1;					
					for (short j = i+1; j < count; j++)
					{
						if (w[i].site == w[j].site && w[j].d.mon == m-1)
						{
							t_m += w[j].t1.h*60+w[j].t1.m;
							av++;
							w[j].site = "repeat";
						}
					}
					w[i].t_s = t_m/av;
					}
				}
				
				for(short i = 0; i < count; i++)
				{
				if (w[i].site == "repeat")
						{						
						continue;											
						}					
				else if (w[i].t_s != 0)			
						{
						f4 << w[i].site << ' ' <<  w[i].t_s << " min" << endl;
						cout << w[i].site << ' ' << w[i].t_s << " min" << endl;
						}						
				}				
				delete []w;	
				f4.close();				
				break;
				}					
		case 5: break;
		default: cout << "Error. Repeat the enter." << endl;
	}
	}
	while (choice != 5);	
	return 0;
}



