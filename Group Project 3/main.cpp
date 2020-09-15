#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

struct Entry
{
	string type;
	string title;
	string artist;
	string year;
};

bool entry_ordering(const Entry& a, const Entry& b)
{
	if(a.type < b.type)
	{
		return true;
	}
	else if(b.type < a.type)
	{
		return false;
	}
	
	else
	{
		if(a.artist < b.artist)
		{
			return true;
		}
		else if(b.artist < a.artist)
		{
			return false;
		}
		else
		{
			if(a.title < b.title)
			{
				return true;
			}
			else if(b.title < a.title)
			{
				return false;
			}
			
			else
			{
				if(a.year < b.year)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
}

bool operator ==(const Entry& a, const Entry& b)
{
	if(a.title == b.title)
	{
		if(a.artist == b.artist)
		{
			if(a.year == b.year)
			{
				return true;
			}
			
			else
			{
				return false;
			}
		}
		
		else
		{
			return false;
		}
	}
	
	else
	{
		return false;
	}
}

auto pred_title = [](const Entry & item) 
{
	Entry entry;
    return item.title == entry.title;
};

auto pred_artist = [](const Entry & item)
{
	Entry entry;
	return item.artist == entry.artist;
};

auto pred_year = [](const Entry & item)
{
	Entry entry;
	return item.year == entry.year;
};

main()
{
	cout << "Welcome to your media manager!\nTo begin, enter the name of the file that contains or will contain this information.\n";
	
	string filename;
	cin >> filename;
	
	ifstream fin;
	fin.open(filename);
	
	vector<Entry> DataSet;
	
	if(!fin.is_open())
	{
		ofstream fout;
		fout.open(filename);
		fout.close();
	}
	
	else
	{
		while(!fin.eof())
		{
			string line;
			getline(fin, line);
			
			replace(line.begin(), line.end(), '\t', '\n');
			stringstream splitter;
			splitter.str(line);
			
			string type;
			string title;
			string artist;
			string year;
			
			getline(splitter, type);
			getline(splitter, title);
			getline(splitter, artist);
			splitter >> year;
			
			Entry cur_entry;
			cur_entry.type = type;
			cur_entry.title = title;
			cur_entry.artist = artist;
			cur_entry.year = year;
			
			DataSet.push_back(cur_entry);
		}
	}
	
	int choice;
	
	ofstream fout;
	fout.open(filename);
		
	while(choice != 0)
	{
		
		cout << "Please enter the number of the operation you would like to perform.\n";
		cout << "1. Add an item\n2. Remove an item\n3. Find an item in the list\n4. Save the list\n0. Close the program.\n";
		cin >> choice;
		
		if(choice == 1)
		{
			Entry cur_entry;
			string type;
			string title;
			string artist;
			string year;
			string blank;
			
			cout << "What type of media is this? (book/music/movie)\n";
			cin >> type;
			
			if(type == "book")
			{
				type = "b";
			}
			
			else if(type == "music")
			{
				type = "m";
			}
			
			else if(type == "movie")
			{
				type = "v";
			}
			
			else
			{
				cout << "Unrecognized type.\n";
			}
			
			cur_entry.type = type;
			
			cout << "What is the name of the item?\n";
			getline(cin, title);
			getline(cin, title);
			cur_entry.title = title;
			
			cout << "Who is the author/artist/director of the item?\n";
			getline(cin, artist);
			cur_entry.artist = artist;
			
			cout << "What year was the item released?\n";
			getline(cin, year);
			cur_entry.year = year;
			
			DataSet.push_back(cur_entry);
		}
		
		else if(choice == 2)
		{
			
			vector<Entry>::iterator it;
			
			
			string title;
			string artist;
			string year;
			
			cout << "What is the name of the item you wish to remove?\n";
			getline(cin,title);
			getline(cin,title);
			
			cout << "Who is the Author/Artist/Director of the item?\n";
			getline(cin,artist);
			
			cout << "What year was the item released?\n";
			getline(cin,year);
			
			string type;
			Entry entry;
			entry.title = title;
			entry.artist = artist;
			entry.year = year;
			
			for(auto data : DataSet)
			{
				entry.type = data.type;
				
				if(data == entry)
				{
					it=find(DataSet.begin(), DataSet.end(), data);
							
					if(it != DataSet.end())
					{
						DataSet.erase(it);
					}
				}
			}
		}
		
		else if(choice == 3)
		{
			cout << "How would you like to search?\n1. Type\n2. Title\n3. Author/Artist/Director\n4. Release Year\n";
			cin >> choice;
			string null;
			getline(cin, null);
			
			if(choice == 1)
			{
				string type;
				
				cout << "Which type would you like to search for? (book/music/movie)\n";
				getline(cin, type);
				
				if(type == "book")
				{
					type = "b";
				}
				
				else if(type == "music")
				{
					type = "m";
				}
				
				else if(type == "movie")
				{
					type = "v";
				}
				
				for(auto data : DataSet)
				{
					if(data.type == type)
					{
						cout << data.type << " " << data.title << " " << data.artist << " " << data.year << "\n";
					}
				}
				
			}
			
			else if(choice == 2)
			{
				string title;
				
				cout << "What is the name of the item you would like to search for?\n";
				getline(cin, title);
				
				for(auto data : DataSet)
				{
					if(data.title == title)
					{
						cout << data.type << " " << data.title << " " << data.artist << " " << data.year << "\n";
					}
				}
			}
			
			else if(choice == 3)
			{
				string artist;
				cout << "What is the name of the artist you are searching for?\n";
				getline(cin,artist);
				
				for(auto data : DataSet)
				{
					if(data.artist == artist)
					{
						cout << data.type << " " << data.title << " " << data.artist << " " << data.year << "\n";
					}
				}
			}
			
			else if(choice == 4)
			{
				string year;
				cout << "What year would you like to search for?\n";
				getline(cin,year);
				
				for(auto data : DataSet)
				{
					if(data.year == year)
					{
						cout << data.type << " " << data.title << " " << data.artist << " " << data.year << "\n";
					}
				}
			}
		}
		
		
		
		else if(choice == 4)
		{
			sort(DataSet.begin(), DataSet.end(), entry_ordering);
			
			cout << "You chose to export the list.\nWhich data types would you like to export?\n";
			cout << "1. Books\n2. Music\n3. Movies\n4. All Data Types\n";
			cin >> choice;
			
			if(choice == 1)
			{
				for(auto data : DataSet)
				{
					if(data.type == "b")
					{
						fout << data.type << "\t" << data.title << "\t" << data.artist << "\t" << data.year << "\n";
					}
				}
			}
			
			else if(choice == 2)
			{
				for(auto data : DataSet)
				{
					if(data.type == "m")
					{
						fout << data.type << "\t" << data.title << "\t" << data.artist << "\t" << data.year << "\n";
					}
				}
			}
			
			else if(choice == 3)
			{
				for(auto data : DataSet)
				{
					if(data.type == "v")
					{
						fout << data.type << "\t" << data.title << "\t" << data.artist << "\t" << data.year << "\n";
					}
				}
			}
			
			else if(choice == 4)
			{
				for(auto data : DataSet)
				{
					fout << data.type << "\t" << data.title << "\t" << data.artist << "\t" << data.year << "\n";
				}
			}
			
		}
		
		else if(choice == 0)
		{
			cout << "If you have not exported, your information will be lost. Are you sure?\n0. Yes, I'm sure. Get me out of here!\n1. No, take me back!\n";
			cin >> choice;
			
			if(choice == 0)
			{
				fout.close();
				return 0;
			}
		}
		
		int choice;	
	}
}
