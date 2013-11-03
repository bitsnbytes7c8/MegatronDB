#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<vector>
#include<map>
#include<stack>
#include<queue>
#include<algorithm>
#include<set>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

using namespace std;

class field
{
	public:
		string name;
		char type;
		bool null;
		char key;
		int default1;
		string default2;
		vector<int> value1;
		vector<string> value2;

		field() {
		}

		field(string n, char t, bool nll, char k)
		{
			name = n;
			type = t;
			null = nll;
			key = k;
		}

		void push_data(int v)
		{
			value1.push_back(v);
		}

		void push_data(string v)
		{
			value2.push_back(v);
		}

		void display()
		{
			if(type == 's')
			{
				for(int i = 0; i<value2.size(); i++)
					cout<<value2[i]<<" ";
				cout<<endl;
			}
			else
			{
				for(int i=0; i<value1.size(); i++)
					cout<<value1[i]<<" ";
				cout<<endl;
			}
		}

		void print_value(int i)
		{
			if(type == 'i')
				cout<<value1[i];
			else
				cout<<value2[i];
		}

		void print_distinct()
		{
			set<string> m2;
			set<int> m1;
			if(type == 'i')
			{
				for(int i=0; i<value1.size(); i++)
				{
					if(m1.find(value1[i]) == m1.end())
					{
						m1.insert(value1[i]);
						cout<<value1[i]<<endl;
					}
				}
			}
			else
			{
				for(int i=0; i<value2.size(); i++)
				{
					if(m2.find(value2[i]) == m2.end())
					{
						m2.insert(value2[i]);
						cout<<value2[i]<<endl;
					}
				}
			}
		}

};


class table
{
	public:
		vector<field> columns;
		int no_of_records;
		map<string, int> column_name;

		void create_table(vector<field> c)
		{
			columns = c;
			no_of_records = 0;
			for(int i=0; i<c.size(); i++)
			{
				column_name[c[i].name] = i;
			}
		}

		void show_map()
		{
			map<string, int>::iterator it;
			for(it = column_name.begin(); it!=column_name.end(); it++)
			{
				cout<<it->first<<" "<<it->second<<endl;
			}
		}

		void print_schema()
		{
			for(int i=0; i<columns.size(); i++)
			{
				cout<<columns[i].name<<" "<<columns[i].type<<" "<<columns[i].null<<" "<<columns[i].key<<endl;
			}
		}

		void insert_record(vector<string> s, vector<int> i)
		{
			int st = 0, in = 0;
			no_of_records ++;
			for(int j=0; j<columns.size(); j++)
			{
				if(columns[j].type == 'i')
				{
					columns[j].push_data(i[in++]);
				}
				else
				{
					columns[j].push_data(s[st++]);
				}
			}
		}

		void print_table()
		{
			for(int i=0; i<no_of_records; i++)
			{
				for(int j=0; j<columns.size(); j++)
				{
					columns[j].print_value(i);
					cout<<" ";
				}
				cout<<endl;
			}
		}

		void print_row(int i)
		{
			for(int j=0; j<columns.size(); j++)
			{
				columns[j].print_value(i);
				cout<<" ";
			}
		}

		void print_columns(vector<string> col_to_print, string condition, string col1, string op, string col2, int val1, string val2, int star)
		{

			if(condition.compare("null") == 0)
			{
				for(int j=0; j<col_to_print.size(); j++)
				{
					if(column_name.find(col_to_print[j]) == column_name.end())
					{
						cout<<"Column "<<col_to_print[j]<<" does not exist\n";
						return;
					}
				}
				for(int i=0; i<no_of_records; i++)
				{
					for(int j=0; j<col_to_print.size(); j++)
					{
						columns[column_name[col_to_print[j]]].print_value(i);
						cout<<" ";
					}
					cout<<endl;
				}
			}

			else if(condition == "distinct")
			{
				//cout<<"Printing distinct for: "<<col_to_print[0]<<endl;
				if(column_name.find(col_to_print[0]) == column_name.end())
				{
					cout<<"Column "<<col_to_print[0]<<" does not exist\n";
					return;
				}
				columns[column_name[col_to_print[0]]].print_distinct();
			}

			else if(condition == "col1opvalue")
			{
				if(column_name.find(col1) == column_name.end())
				{
					cout<<"Column "<<col1<<" does not exist\n";
					return;
				}
				field col = columns[column_name[col1]];
				if(col.type == 'i')
				{
					for(int i=0; i<no_of_records; i++)
					{
						int flag = 0;
						if(op.compare("=") == 0)
						{
							if(col.value1[i] == val1)
								flag = 1;
						}
						else if(op.compare(">") == 0)
						{
							if(col.value1[i] > val1)
								flag = 1;
						}
						else if(op.compare("<") == 0)
						{
							if(col.value1[i] < val1)
								flag = 1;
						}
						else if(op.compare("<=") == 0)
						{
							if(col.value1[i] <= val1)
								flag = 1;
						}
						else if(op.compare(">=") == 0)
						{
							if(col.value1[i] >= val1)
								flag = 1;
						}
						if(flag)
						{
							if(star)
							{
								for(int j=0; j<columns.size(); j++)
								{
									columns[j].print_value(i);
									cout<<" ";
								}
								cout<<endl;
							}
							else
							{
								for(int j=0; j<col_to_print.size(); j++)
								{
									if(column_name.find(col_to_print[j]) == column_name.end())
									{
										cout<<"Column "<<col_to_print[j]<<" does not exist\n";
										return;
									}
								}
								for(int j=0; j<col_to_print.size(); j++)
								{
									columns[column_name[col_to_print[j]]].print_value(i);
									cout<<" ";
								}
								cout<<endl;
							}
						}
					}
				}
				if(col.type == 's')
				{
					for(int i=0; i<no_of_records; i++)
					{
						int flag = 0;
						if(op.compare("=") == 0)
						{
							if(col.value2[i].compare(val2) == 0)
								flag = 1;
						}
						if(flag)
						{
							if(star)
							{
								for(int j=0; j<columns.size(); j++)
								{
									columns[j].print_value(i);
									cout<<" ";
								}
								cout<<endl;
							}
							else
							{
								for(int j=0; j<col_to_print.size(); j++)
								{
									if(column_name.find(col_to_print[j]) == column_name.end())
									{
										cout<<"Column "<<col_to_print[j]<<" does not exist\n";
										return;
									}
								}
								for(int j=0; j<col_to_print.size(); j++)
								{
									columns[column_name[col_to_print[j]]].print_value(i);
									cout<<" ";
								}
								cout<<endl;
							}
						}
					}
				}
			}						

			else if(condition == "col1opcol2")
			{
				if(column_name.find(col1) == column_name.end())
				{
					cout<<"Column "<<col1<<" does not exist\n";
					return;
				}
				else if(column_name.find(col2) == column_name.end())
				{
					cout<<"Column "<<col2<<" does not exist\n";
					return;
				}
				field col = columns[column_name[col1]];
				field c2 = columns[column_name[col2]];
				if(col.type == 'i' && c2.type == 'i')
				{
					for(int i=0; i<no_of_records; i++)
					{
						int flag = 0;
						if(op.compare("=") == 0)
						{
							if(col.value1[i] == c2.value1[i])
								flag = 1;
						}
						else if(op.compare(">") == 0)
						{
							if(col.value1[i] > c2.value1[i])
								flag = 1;
						}
						else if(op.compare("<") == 0)
						{
							if(col.value1[i] < c2.value1[i])
								flag = 1;
						}
						else if(op.compare("<=") == 0)
						{
							if(col.value1[i] <= c2.value1[i])
								flag = 1;
						}
						else if(op.compare(">=") == 0)
						{
							if(col.value1[i] >= c2.value1[i])
								flag = 1;
						}
						if(flag)
						{
							if(star)
							{
								for(int j=0; j<columns.size(); j++)
								{
									columns[j].print_value(i);
									cout<<" ";
								}
								cout<<endl;
							}
							else
							{
								for(int j=0; j<col_to_print.size(); j++)
								{
									if(column_name.find(col_to_print[j]) == column_name.end())
									{
										cout<<"Column "<<col_to_print[j]<<" does not exist\n";
										return;
									}
								}
								for(int j=0; j<col_to_print.size(); j++)
								{
									columns[column_name[col_to_print[j]]].print_value(i);
									cout<<" ";
								}
								cout<<endl;
							}
						}
					}
				}
				if(col.type == 's')
				{
					for(int i=0; i<no_of_records; i++)
					{
						int flag = 0;
						if(op.compare("=") == 0)
						{
							if(col.value2[i].compare(c2.value2[i]) == 0)
								flag = 1;
						}
						if(flag)
						{
							if(star)
							{
								for(int j=0; j<columns.size(); j++)
								{
									columns[j].print_value(i);
									cout<<" ";
								}
								cout<<endl;
							}
							else
							{
								for(int j=0; j<col_to_print.size(); j++)
								{
									if(column_name.find(col_to_print[j]) == column_name.end())
									{
										cout<<"Column "<<col_to_print[j]<<" does not exist\n";
										return;
									}
								}
								for(int j=0; j<col_to_print.size(); j++)
								{
									columns[column_name[col_to_print[j]]].print_value(i);
									cout<<" ";
								}
								cout<<endl;
							}
						}	
					}
				}
			}	
		}

		void join_tables(string col1, string col2, table table2)
		{
			if(column_name.find(col1) == column_name.end())
			{
				cout<<"Column "<<col1<<" does not exist\n";
				return;
			}
			if(table2.column_name.find(col2) == table2.column_name.end())
			{
				cout<<"Column "<<col2<<" does not exist\n";
				return;
			}
			field c1 = columns[column_name[col1]];
			field c2 = table2.columns[table2.column_name[col2]];
			for(int i=0; i<no_of_records; i++)
			{
				if(c1.type == 'i' && c2.type == 'i')
				{
					for(int j=0; j<table2.no_of_records; j++)
					{
						if(c1.value1[i] == c2.value1[j])
						{
							print_row(i);
							table2.print_row(j);
							cout<<endl;
						}
					}
				}
				if(c1.type == 's' && c2.type == 's')
				{
					for(int j=0; j<table2.no_of_records; j++)
					{
						if(c1.value2[i].compare(c2.value2[j]) == 0)
						{
							print_row(i);
							table2.print_row(j);
							cout<<endl;
						}
					}
				}
			}
		}
};


map<string, table> table_map;
char file[100000000];

void parse_files()
{
	int fd_schema = open("schema", O_RDONLY);
	if(fd_schema == 0)
		exit(1);
	char c, word[10000];
	char fld[1000][4];
	int flag = 1;
	int file_length = lseek(fd_schema, 0, SEEK_END);
	lseek(fd_schema, 0, SEEK_SET);
	int size = read(fd_schema, (void*)file, file_length);
	close(fd_schema);
	int i=0, count= 0, pos = 0;
	string table_name;
	while(file[pos] != '\0')
	{
		if(isalnum(file[pos]))
		{
			count = 0;
			while(file[pos]!=':' && file[pos]!='\0')
			{
				word[count++] = file[pos++];
			}
			word[count] = '\0';
			if(strcmp(word, "Table") == 0)
			{
				vector<field> fields;
				table t1;
				count = 0;
				pos++;
				if(isalnum(file[pos]))
				{
					while(file[pos]!=':' && file[pos]!='\0')
					{
						word[count++] = file[pos++];
					}
					pos++;
					word[count] = '\0';
					table_name.assign(word);
				}
				while(!isalnum(file[pos]))
					pos++;
				while(1)
				{
					count = 0;
					int field_prop = 0;
					while(file[pos] != '\n')
					{
						word[count++] = file[pos++];
					}
					word[count] = '\0';
					if(strstr(word, "0end_table0"))
						break;
					string nm;
					char tp;
					bool nl;
					char k;
					int j=0;
					while(field_prop<4)
					{
						count = 0;
						while(word[j] != ':')
						{
							fld[field_prop][count++] = word[j++];
						}
						j++;
						fld[field_prop][count] = '\0';
						if(field_prop == 0)
						{
							nm.assign(fld[field_prop]);
						}
						else if(field_prop == 1)
						{
							if(strstr(fld[field_prop], "int"))
								tp = 'i';
							else
								tp = 's';
						}
						else if(field_prop == 2)
						{
							if(strstr(fld[field_prop], "YES"))
								nl = true;
							else
								nl = false;
						}
						else 
						{
							if(strstr(fld[field_prop], "PRI"))
								k = 'p';
							else
								k = ' ';
						}
						field_prop++;
					}
					while(!isalnum(file[pos]))
						pos++;
					field f(nm, tp, nl, k);
					fields.push_back(f);
				}
				t1.create_table(fields);
				table_map[table_name] = t1;
			}
		}
		else
			pos++;
	}			

}

void parse_tables(string table_name)
{
	table t = table_map[table_name];
	char *file_name = (char*)table_name.c_str();
	strcat(file_name, ".csv");
	int fd = open(file_name, O_RDONLY);
	if(!fd)
		exit(1);

	int file_length = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	int size = read(fd, (void*)file, file_length);
	close(fd);
	file[size] = '\0';
	int pos = 0;
	while(file[pos]!='\n')
		pos++;
	pos++;
	char word[10000];
	char value[100];
	int count;
	int line = 2;
	while(file[pos]!='\0')
	{
		line++;
		vector<string> s;
		vector<int> i;
		int field_no = 0;
		count = 0;
		while(file[pos]!='\0' && file[pos]!='\n')
		{
			word[count++] = file[pos++];
		}
		word[count] = '\0';
		if(file[pos] == '\n')
			pos++;
		int j = 1;
		while(word[j] != '\0')
		{
			if(word[j] == ',')
				j+=2;
			int k = 0;
			while(word[j]!='"')
			{
				value[k++] = word[j++];
			}
			value[k] = '\0';
			if(table_map[table_name].columns[field_no].type == 'i')
			{
				int val = atoi(value);
				i.push_back(val);
			}
			else
			{
				string v;
				v.assign(value);
				s.push_back(v);
			}
			j++;
			field_no++;
		}
		table_map[table_name].insert_record(s, i);
	}
}





void parse_query(char *query)
{
	int i = 0, count = 0;
	char word[1000][1000];
	while(query[i] != '\0')
	{
		if(isalnum(query[i]) || query[i] == '*' || query[i] == '=' || query[i] == '>' || query[i] == '<')
		{
			int j = 0;
			while(isalnum(query[i]) || query[i] == '*' || query[i] == '=' || query[i] == '>' || query[i] == '<')
			{
				word[count][j++] = query[i++];
			}
			word[count][j] = '\0';
			count++;
		}
		else if(query[i] == '"')
		{
			int j=0;
			word[count][j++] = query[i++];
			while(query[i] != '"')
				word[count][j++] = query[i++];
			word[count][j++] = query[i++];
			word[count][j] = '\0';
			count++;
		}
		else
		{
			i++;
		}
	}
	if(strcmp(word[0], "select") == 0 && strcmp(word[1], "*") == 0 && strcmp(word[2], "from") == 0 && !strstr(query, "where"))
	{
		//query 1
		if(table_map.find(word[3]) == table_map.end())
		{
			cout<<"Table does not exist\n";
			return;
		}
		if(strstr(query, "|") )
		{
			int bak, n;
			fflush(stdout);
			bak = dup(1);
			n = open(word[count-1], O_WRONLY | O_CREAT | O_TRUNC | O_LARGEFILE);
			dup2(n, 1);
			close(n);
			table_map[word[3]].print_table();
			fflush(stdout);
			dup2(bak, 1);
			close(bak);
			close(n);
		}
		else
			table_map[word[3]].print_table();
	}

	else if(strcmp(word[0], "select") == 0 && strcmp(word[1], "distinct") == 0)
	{
		//query 3
		vector<string> colmn;
		colmn.push_back(word[2]);
		if(table_map.find(word[4]) == table_map.end())
		{
			cout<<"Table does not exist\n";
			return;
		}
		if(strstr(query, "|") )
		{
			int bak, n;
			fflush(stdout);
			bak = dup(1);
			n = open(word[count-1], O_WRONLY | O_CREAT | O_TRUNC | O_LARGEFILE);
			dup2(n, 1);
			close(n);
			table_map[word[4]].print_columns(colmn, "distinct", "", "", "", 0, "", 0);
			fflush(stdout);
			dup2(bak, 1);
			close(bak);
			close(n);
		}
		else 
			table_map[word[4]].print_columns(colmn, "distinct", "", "", "", 0, "", 0);
	}	

	else if(strcmp(word[0], "select") == 0 && !strstr(query, "where"))
	{
		//query 2
		vector<string> colmns;
		string cname;
		i = 1;
		while(i<count && strcmp(word[i], "from")!=0)
		{
			cname.assign(word[i]);
			colmns.push_back(cname);
			i++;
		}
		if(table_map.find(word[i+1]) == table_map.end())
		{
			cout<<"Table does not exist\n";
			return;
		}
		if(strstr(query, "|") )
		{
			int bak, n;
			fflush(stdout);
			bak = dup(1);
			n = open(word[count-1], O_WRONLY | O_CREAT | O_TRUNC | O_LARGEFILE);
			dup2(n, 1);
			close(n);
			table_map[word[i+1]].print_columns(colmns, "null", "", "", "", 0, "", 0);
			fflush(stdout);
			dup2(bak, 1);
			close(bak);
			close(n);
		}
		else 
			table_map[word[i+1]].print_columns(colmns, "null", "", "", "", 0, "", 0);

	}

	else if(strcmp(word[0], "select") == 0)
	{
		vector<string> colmns;
		string cname;
		i = 1;
		while(i<count && strcmp(word[i], "from")!=0)
		{
			cname.assign(word[i]);
			colmns.push_back(cname);
			i++;
		}
		if(strcmp(word[i+2], "where") == 0)
		{
			//query 4
			int flag = 0;
			for(int k=0; k<strlen(word[i+5]); k++)
			{
				if(word[i+5][k]<'0' || word[i+5][k]>'9')
				{
					flag = 1;
					break;
				}
			}
			int star = 0;
			if(colmns.size() == 1 && colmns[0].compare("*") == 0)
				star = 1;
			if(flag == 1)
			{
				if(strstr(word[i+5], "\""))
				{
					string col1, op, value;
					char val[100];
					int pos = 0;
					for(int k=0; word[i+5][k]!='\0'; k++)
					{
						if(word[i+5][k] != '"')
							val[pos++] = word[i+5][k];
					}
					val[pos] = '\0';
					col1.assign(word[i+3]);
					op.assign(word[i+4]);
					value.assign(val);
					if(table_map.find(word[i+1]) == table_map.end())
					{
						cout<<"Table does not exist\n";
						return;
					}
					if(strstr(query, "|") )
					{
						int bak, n;
						fflush(stdout);
						bak = dup(1);
						n = open(word[count-1], O_WRONLY | O_CREAT | O_TRUNC | O_LARGEFILE);
						dup2(n, 1);
						close(n);
						table_map[word[i+1]].print_columns(colmns, "col1opvalue", col1, op, "", 0, value, star);
						fflush(stdout);
						dup2(bak, 1);
						close(bak);
						close(n);
					}
					else
						table_map[word[i+1]].print_columns(colmns, "col1opvalue", col1, op, "", 0, value, star);
				}
				else
				{
					string col1, op, col2;
					col1.assign(word[i+3]);
					op.assign(word[i+4]);
					col2.assign(word[i+5]);
					if(table_map.find(word[i+1]) == table_map.end())
					{
						cout<<"Table does not exist\n";
						return;
					}
					if(strstr(query, "|") )
					{
						int bak, n;
						fflush(stdout);
						bak = dup(1);
						n = open(word[count-1], O_WRONLY | O_CREAT | O_TRUNC | O_LARGEFILE);
						dup2(n, 1);
						close(n);
						table_map[word[i+1]].print_columns(colmns, "col1opcol2", col1, op, col1, 0, "", star);
						fflush(stdout);
						dup2(bak, 1);
						close(bak);
						close(n);
					}
					else
						table_map[word[i+1]].print_columns(colmns, "col1opcol2", col1, op, col2, 0, "", star);
				}
			}
			else
			{
				string col1, op;
				int value;
				value = atoi(word[i+5]);
				col1.assign(word[i+3]);
				op.assign(word[i+4]);
				if(table_map.find(word[i+1]) == table_map.end())
				{
					cout<<"Table does not exist\n";
					return;
				}
				if(strstr(query, "|") )
				{
					int bak, n;
					fflush(stdout);
					bak = dup(1);
					n = open(word[count-1], O_WRONLY | O_CREAT | O_TRUNC | O_LARGEFILE);
					dup2(n, 1);
					close(n);
					table_map[word[i+1]].print_columns(colmns, "col1opvalue", col1, op, "", value, "", star);
					fflush(stdout);
					dup2(bak, 1);
					close(bak);
					close(n);
				}
				else
					table_map[word[i+1]].print_columns(colmns, "col1opvalue", col1, op, "", value, "", star);
			}
		}

		else if(strcmp(word[i+3], "where") == 0)
		{
			//query 5
			if(table_map.find(word[i+1]) == table_map.end() || table_map.find(word[i+2]) == table_map.end())
			{
				cout<<"Table does not exist\n";
				return;
			}
			table table1 = table_map[word[i+1]];
			table table2 = table_map[word[i+2]];
			string col1, col2;
			col1.assign(word[i+4]);
			col2.assign(word[i+6]);
			if(strstr(query, "|") )
			{
				int bak, n;
				fflush(stdout);
				bak = dup(1);
				n = open(word[count-1], O_WRONLY | O_CREAT | O_TRUNC | O_LARGEFILE);
				dup2(n, 1);
				close(n);
				table1.join_tables(col1, col2, table2);
				fflush(stdout);
				dup2(bak, 1);
				close(bak);
				close(n);
			}
			else
				table1.join_tables(col1, col2, table2);
		}

		else {
			cout<<"Invalid query\n";
			return;
		}
	}
	else {
		cout<<"Invalid query\n";
	}
}



int main()
{
	//map<string, int> table_index;
	//vector<table> tables;
	/*vector<field> table1, table2;
		field id("ID", 'i', false, ' ');
		field code("CODE", 's', false,'p');
		field Name("NAME", 's', false, ' ');
		field continent("CONTINENT", 's', false, ' ');
		field id2("ID", 'i', false, 'p');
		field nm("NAME", 's', true, ' ');
		field cntry("COUNTRY", 's', true, ' ');
		table2.push_back(id2);
		table2.push_back(nm);
		table2.push_back(cntry);
		table1.push_back(id);
		table1.push_back(code);
		table1.push_back(Name);
		table1.push_back(continent);
		table countries, airport;
		countries.create_table(table1);
		airport.create_table(table2);
	// countries.print_schema();
	//cout<<endl;
	// airport.print_schema();
	//cout<<endl;

	int c;
	while(1)
	{
	cin>>c;
	if(c == 0)
	break;
	countries.insert_record();
	}
	getchar();
	while(1)
	{
	cin>>c;
	if(c == 0)
	break;
	airport.insert_record();
	}
	table_map["countries"] = countries;
	table_map["airport"] = airport;*/
	char query[10000] = "";
	char q[100];
	int d;
	parse_files();
	map<string, table>::iterator it;
	for(it=table_map.begin(); it!=table_map.end(); it++)
	{
		parse_tables(it->first);
	}
	
	while(1)
	{
		cout<<"megatron201001043$ "<<flush;
		strcpy(query, "");
		while(1)
		{
			cin.clear();
			cin>>q;
			cin.clear();
			strcat(query, q);
			strcat(query, " ");
			if(q[strlen(q)-1] == ';')
				break;
		}
		if(strcmp(query, "quit; ") == 0)
			break;
		cout<<endl;
		parse_query(query);
		cout<<endl;
	}
	return 0;
}
