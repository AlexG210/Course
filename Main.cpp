#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <windows.h>
#include <math.h>
#include <cstdlib>
//#include <random>
using namespace std;

int menu=0,menu1=0,menuFirst=0,menuchange=0;
string baza[10][10][6];//[0][0][0] login ;[0][0][1] parol;[0][0][2] количество входов;[0][0][3] неправильный пароль;[0][0][4] роль;[0][0][5] порядковый номер
string bazadmin[2];
string bazarole [5][3];
string baza_permissions[10][3];

//char ch_pas1[]="qwertyuiopasdfghjklzxcvbnm";
char ch_pas1[]="abcdefghijklmnopqrst";
//char ch_pas2[]="@#";

string checkrole(string log,int file)
{
	string role,perm;
	for(int i = 0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			if(baza[i][j][0]==log)
			{
				role=baza[i][j][4];
				perm=bazarole[atoi(role.c_str())][file];
				return perm;
			}
		}
	}
	return perm;
}
string check_permission(string log,int file)
{
	string permission,number;
	for(int i = 0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			if(baza[i][j][0]==log)
			{
				number = baza[i][j][5];
				permission=baza_permissions[atoi(number.c_str())][file];
				return permission;
			}
		}
	}
	return permission;
}
string shifr(string pas) 
{
	char mat[20][20];
	string shifrpas;

	pas = pas+'0';		//добавляем символ конца строки
	int l,i,j,k,y;

	l = pas.length();
	if(l%3==0)
		y=(l/3)+1;
	else
		y=(l/3)+2;

	for (i=0;i<y;i++)		//заполняем матрицу мусором из маленьких английских букв
	{
		for (j=0;j<y;j++)
		{	mat[i][j]=(rand()%26+0x61);
		//cout<<mat[i][j]<<"   ";
		}
		//cout<<endl;
	}
	//cout<<endl;

	for (i=0, j=y-1, k=0; i<y && k<l; i++,k++)	//начинаем записывать наш пароль в матрицу (последний столбец сверху вниз)
	{
		mat [i][j] = pas[k];
	}

	for (i=y-1, j=y-2,k=y ; j>-1 && k<l ;k++, j--)		//нижняя строка справо налево
	{
		mat [i][j]=pas[k];
	}

	for (i=y-2, j=1, k=2*y-1 ;i>-1 && k<l ;k++, i--, j++)		//побочная диагональ снизу вверх
	{
		mat [i][j]=pas[k];
	}


	/*	for (i=0;i<y;i++)			//выводим получившуюся матрицу с нашим паролем в ней
	{
	for (j=0;j<y;j++)
	{
	cout<<mat[i][j]<<"   ";
	}
	cout<<endl;
	}*/

	for (i=0;i<y;i++)		//записываем матрицу в вектор как зашифрованный пароль
	{
		for(j=0;j<y;j++)
		{
			shifrpas=shifrpas+mat[i][j];
		}
	}
	//cout<<shifrpas<<endl;

	return shifrpas;
}

string deshifr(string shifrpas)
{
	cout<<endl;
	char mat[20][20];
	string pas;
	int i,j,k,l,y;

	k=0;
	l=shifrpas.length();
	y=sqrt((double)l);
	for (i=0;i<y;i++)  //получили нашу матрицу которая была при шифровании
	{
		for (j=0;j<y;j++)
		{
			mat[i][j]=shifrpas[k];
			k++;
		}
	}

	/*	for (i=0;i<y;i++)		//просто проверка (вывод получившейся матрицы)
	{
	for (j=0;j<y;j++)
	{
	cout<<mat[i][j]<<"   ";
	}
	cout<<endl;
	}

	cout<<endl;*/


	for (i=0, j=y-1 ; i<y ;i++)	//начинаем записывать наш пароль из матрицы (последний столбец) 
	{
		pas = pas+mat [i][j];
	}

	for (i=y-1, j=y-2 ; j>-1 && mat[i][j]!='0' ;j--)		//нижняя строка справо налево пишем до символа "0"
	{
		pas = pas+mat [i][j];
	}

	for (i=y-2, j=1; i>-1 && mat[i][j]!='0'; i--, j++)		//побочная диагональ снизу вверх  пишем до символа "0"
	{
		pas = pas+mat [i][j];
	}

	//cout<<pas<<"  <- parol"<<endl;  //выводим получившийся пароль

	return pas;

}

int baz_pas_check(string pas)
{	int sovpal;
if (pas.length()<8)
{cout<<" error: Пароль не меньше 8 символов"<<endl;return 0;} 

for (int i=0;i<pas.length();i=i+2)
{
	sovpal=0;
	for (int j=0;j<sizeof(ch_pas1);j++)
	{
		if (pas[i]==ch_pas1[j])
		{	
			sovpal=1;
			break;
		}
	}
	if (sovpal==0)
	{
		cout<<"error: Первые 20 букв латинского алфавита"<<endl;
		return 0;
	}
}

return 1;

}

int baz_log_equal(string log) //проверка занятости или сравнение логина 
{
	for(int i=0;i<10;i++) //stroka
	{
		for(int j=0;j<10;j++) //stolbec
		{
			if (log==baza[i][j][0])
			{return 1;}
		}
	}
	return 0;
}
int baz_log_reset(string log) 
{
	for(int i=0;i<10;i++) //stroka
	{
		for(int j=0;j<10;j++) //stolbec
		{
			if (log==baza[i][j][0])
			{
				baza[i][j][3].clear();
				return 1;
			}
		}
	}
	return 0;
}
int baz_aut_check(string log,string pas) 
{
	for(int i=0;i<10;i++) //stroka
	{
		for(int j=0;j<10;j++) //stolbec
		{
			if (log==baza[i][j][0])
			{
				if (baza[i][j][3].length()>2)
				{
					cout<<"Вы превысили количество попыток входа, обратитесь к admin"<<endl;
					return 0;
				}

				if(pas==deshifr(baza[i][j][1]))
				{

					baza[i][j][2]=baza[i][j][2]+'a';
					cout<<"Вы успешно зашли в систему"<<endl;
					return 1;
				}
				else
				{	
					baza[i][j][3]=baza[i][j][3]+'a';
					cout<<"Неправильный пароль"<<endl;
					return 0;
				}
			}
		}
	}
	cout<<"Неправильный логин"<<endl;
	return 0;
}

int baz_zapis(string log, string shifrpas,string role,string number)
{
	for(int i=0;i<10;i++) //stroka
	{	
		for(int j=0;j<10;j++) //stolbec
		{
			if (baza[i][j][0].empty())
			{
				baza[i][j][0]=log;
				baza[i][j][1]=shifrpas;
				baza[i][j][4]=role;
				baza[i][j][5]=number;
				return 1;
			}

		}
	}

	return 0;
}

int baz_of_users()
{	
	int t=0;
	cout<<endl<<"Зарегистрированные пользователи"<<endl;
	for(int i=0;i<10;i++) //stroka
	{	
		for(int j=0;j<10;j++) //stolbec
		{
			if (baza[i][j][0].empty()==0)
			{
				//cout<<t<<": "<<baza[i][j][0]<<"	role: "<<baza[i][j][4]<<endl;
				cout<<baza[i][j][5]<<": "<<baza[i][j][0]<<"	role: "<<baza[i][j][4]<<endl;
				t++;
			}

		}
	}
	cout<<endl;
	return 0;
}
int reg()
{
	string log, role, number;
	string pas,shifrpas;

	cout<<"vvedite login"<<endl;
	cin>>log;

	if (baz_log_equal(log)==1) //check login na sovpadenie s bazoy
	{cout<<"error: Твой логин уже занят"<<endl;return 0;}
	else 
		cout<<" логин свободен "<<endl;

	cout<<"Введите пароль по правилам только первые 20 букв латинского алфавита"<<endl;
	cin>>pas;
	if(baz_pas_check(pas)==1)
		cout<<"password ok"<<endl;
	else
	{cout<<"error: Начни заново"<<endl;return 0;}

	if(log==pas)
	{cout<<"error: Пароль и логин должны быть разные"<<endl;return 0;}

	cout<<"введите роль данного пользователя (от 0 до 4)"<<endl;
	cin>>role;
	if (role=="1"||role=="2"||role=="3"||role=="4"||role=="0")
		cout<<"роль принята"<<endl;  
	else
	{cout<<"error: начнем с начала"<<endl;return 0;}

	cout<<"введите порядковый номер пользователя(от 0 до 9)"<<endl;
	cin>>number;
	if (number=="1" || number=="2" || number=="3" || number=="4" || number=="0" || number=="5" || number=="6" || number=="7" || number=="8" || number=="9")
		cout<<"номер принят"<<endl;
	else
	{cout<<"error: начнем с начала"<<endl;return 0;}

	shifrpas=shifr(pas);

	if (baz_zapis(log,shifrpas,role,number)==1)
		cout<<"ты зарегистрирован"<<endl;

	return 1;
}//end of reg

string aut()
{
	string log,pas,st;

	cout<<"vvedite login"<<endl;
	cin>>log;
	cout<<"vvedite parol"<<endl;
	cin>>pas;
	if(baz_aut_check(log,pas)==1)
	{
		cout<<"pozdravlyaem"<<endl;
		st=log;
		return st;
	} 
	else 
		return st;

}

int change()
{
	string log,pas,pas2;
	cout<<"Введите логин пользователя -> ";
	cin>>log;
	cout<<endl;

	for(int i=0;i<10;i++) //stroka
	{
		for(int j=0;j<10;j++) //stolbec
		{
			if (log==baza[i][j][0])
			{
				do
				{
					menuchange=0;
					cout<<"1:изменить логин"<<endl;
					cout<<"2:изменить пароль"<<endl;
					cout<<"0:exit"<<endl;
					cin>>menuchange;

					switch(menuchange)
					{
					case 1:
						cout<<"введите новый логин"<<endl;
						cin>>log;
						if (!baz_log_equal(log))
							baza[i][j][0]=log;
						else
							cout<<"такой логин уже занят"<<endl;
						break;
					case 2:
						cout<<"введите старый пароль"<<endl;
						cin>>pas;
						if(pas==deshifr(baza[i][j][1]))
						{
							cout<<"введите новый пароль"<<endl;
							cin>>pas;
							if (baz_pas_check(pas)==1)
							{
								cout<<"введите новый пароль снова"<<endl;
								cin>>pas2;
								if (pas==pas2)
								{
									baza[i][j][1]=shifr(pas);
								}
								else
								{
									cout<<"пароли не совпадают"<<endl;
								}
							}

						}
						else
						{
							cout<<"неверный пароль"<<endl;
						}
						break;


					case 0:break;

					default:break;
					}

				}while(menuchange!=0);
				return 0;
			}
		}
	}
	return 0;
}
int autadmin()
{
	string log,pas;

	cout<<"логин"<<endl;
	cin>>log;
	cout<<"пароль"<<endl;
	cin>>pas;

	if (log==bazadmin[0])
	{
		if(pas==deshifr(bazadmin[1]))
		{
			cout<<"вы успешно зашли в систему"<<endl;
			return 1;
		}
		else
		{
			cout<<"неправильный пароль"<<endl;
			return 0;
		}
	}
	cout<<"неправильный логин"<<endl;
	return 0;
}
int task ()
{
	int min = baza[0][0][2].length(); //по умолчанию первый пользователь имеет min входов
	string min_user = baza[0][0][0];

	for(int i=0;i<10;i++) //stroka
	{
		for(int j=0;j<10;j++) //stolbec
		{
			if(baza[i][j][0].empty()==0 && baza[i][j][2].length()<min)	
			{
				min = baza[i][j][2].length();
				min_user = baza[i][j][0];
			}
		}
	}
	cout<<min<<" <- количество входов"<<endl<<endl;
	cout<<min_user<<" <- пользователь с минимальным количеством входов в систему"<<endl;
	return 0;
}


/*int menurole(int file,int role,string action)
{
string perm=bazarole[role][file];
for (int i=0;i<perm.length();i++)
{
char bukva = perm[i];
if (bukva==action)
{
cout<<"доступ на действие получен"<<endl;
return 1;
}
}
cout<<"недостаточно прав, обратитесь к администратору"<<endl;
return 0;

}*/
int xacha_i_maga(string perm,string permission,string doit)
{
	for(int i = 0, k = 0, j = 0; j<permission.length() || k<perm.length(); j++,k++) 
	{
		if(perm[k]==doit[i] || permission[j]==doit[i])
			return 1;
	}			
	return 0;

}
int filemenu(string perm,string permission)
{
	int menufile;
	string doit;
	do{
		menufile=0;
		cout<<endl;
		cout<<"1:read"<<endl;
		cout<<"2:write"<<endl;
		cout<<"3:execute "<<endl;
		cout<<"4:очистить экран "<<endl;
		cout<<"0:Выйти из системы "<<endl;

		cin>>menufile;

		switch(menufile)
		{
		case 1:
			doit="r";
			if(xacha_i_maga(perm,permission,doit)==1)
				cout<<"Ok"<<endl;
			else
				cout<<"Deny access"<<endl;
			break;

		case 2:	
			doit="w";
			if(xacha_i_maga(perm,permission,doit)==1)
				cout<<"Ok"<<endl;
			else
				cout<<"Deny access"<<endl;
			break;

		case 3: 	
			doit="e";
			if(xacha_i_maga(perm,permission,doit)==1)
				cout<<"Ok"<<endl;
			else
				cout<<"Deny access"<<endl;
			break;

		case 4:system("cls");break;


		default:break;
		}
	}while(menufile!=0);
	return 0;



}
int menuaut(string log)
{	
	int file;
	string perm,permission;
	do{
		cout<<endl;
		cout<<"1:file 0"<<endl;
		cout<<"2:file 1"<<endl;
		cout<<"3:file 2 "<<endl;
		cout<<"4:очистить экран "<<endl;
		cout<<"0:Выйти из системы "<<endl;


		cin>>menu1;

		switch(menu1)
		{
		case 1:
			file=0;
			perm=checkrole(log,file);
			permission=check_permission(log,file);
			filemenu(perm,permission);
			break;

		case 2:	
			file=1;
			perm=checkrole(log,file);
			permission=check_permission(log,file);
			filemenu(perm,permission);
			break;

		case 3: 	
			file=2;
			perm=checkrole(log,file);
			permission=check_permission(log,file);
			filemenu(perm,permission);
			break;

		case 4:system("cls");break;


		default:break;
		}
	}while(menu1!=0);
	return 0;
}
int menuok()
{	
	string log;
	int i = 0,j = 0;
	string role,permission;
	do{
		menu=0;
		cout<<"1:List of users "<<endl;
		cout<<"2:Registration"<<endl;
		cout<<"3:My task"<<endl;
		cout<<"4:unlock user"<<endl;
		cout<<"5:change users"<<endl;
		cout<<"6:list of bazarole"<<endl;	
		cout<<"7:сhange bazarole"<<endl;		
		cout<<"8:list of permissions"<<endl;
		cout<<"9:сhange baza_permissions"<<endl;
		cout<<"10:cls"<<endl;
		cin>>menu;
		switch(menu)
		{

		case 1:baz_of_users(); break;

		case 2:reg();break;

		case 3:task();break;

		case 4:
			cout<<"Введите логин юзера для разблокировки"<<endl;
			cin>>log;
			baz_log_reset(log);
			break;

		case 5:
			baz_of_users();
			change();
			break;

		case 6:
			for(int i=0;i<5;i++) //stroka
			{
				for(int j=0;j<3;j++) //stolbec
				{
					cout<<i<<" role "<<j<<" file -> "<<bazarole[i][j]<<endl;
				}
			}
			break;

		case 7:
			cout<<"введите номер роли, и номер файла, затем введите право доступа, в порядке r->w->e"<<endl;
			cin>>i>>j>>role;
			if (role=="r"||role=="w"||role=="e"||role=="rw"||role=="re"||role=="we"||role=="rwe")
				bazarole[i][j]=role;
			else
				cout<<"role в порядке r->w->e"<<endl;
			break;

		case 8:
			for(int i=0;i<10;i++) //stroka
			{
				for(int j=0;j<3;j++) //stolbec
				{
					cout<<i<<" login "<<j<<" file -> "<<baza_permissions[i][j]<<endl;
				}
			}
			break;

		case 9:
			cout<<"введите login, и номер файла, затем введите право доступа, в порядке r->w->e"<<endl;
			cin>>i>>j>>permission;
			if (permission=="r"||permission=="w"||permission=="e"||permission=="rw"||permission=="re"||permission=="we"||permission=="rwe")
				baza_permissions[i][j]=permission;
			else
				cout<<"permission в порядке r->w->e"<<endl;
			break;


		case 10:	system("cls");break;

		default:break;
		}
	}while(menu!=0);
	return 0;
}


int menuadmin()
{
	cout<<"авторизация"<<endl;
	if(autadmin()==1)
		return 1;
	else
		return 0;
}
int menuuser()
{
	string st=aut();
	cout<<"1:Autorization "<<endl;
	if (!st.empty())
		menuaut(st);

	return 0;
}
int save()
{
	ofstream savelog("log.txt",ios::out);
	ofstream savepas("pas.txt",ios::out);
	ofstream saverole("role.txt",ios::out);
	ofstream saveperm("permission.txt",ios::out);

	for(int i=0;i<10;i++) //stroka
	{
		for(int j=0;j<10;j++) //stolbec
		{
			if (!baza[i][j][0].empty())
			{
				savelog<<baza[i][j][0]+"\n";
				savepas<<baza[i][j][1]+"\n";
			}

		}
	}
	cout<<"база успешно сохранена"<<endl;
	for(int i=0;i<5;i++) //stroka
	{
		for(int j=0;j<3;j++) //stolbec
		{
			if (!bazarole[i][j].empty())
			{
				saverole<<bazarole[i][j]+"\n";				
			}			
		}
	}
	cout<<"база ролей успешно сохранена"<<endl;

	for(int i=0;i<10;i++) //stroka
	{
		for(int j=0;j<3;j++) //stolbec
		{
			if (!baza_permissions[i][j].empty())
			{
				saveperm<<baza_permissions[i][j]+"\n";				
			}			
		}
	}
	cout<<"база индивидуальных прав доступа успешно сохранена"<<endl;
	return 1;

}

int load()
{
	string log,pas,role,permission;
	ifstream loadlog("log.txt",ios::in);
	ifstream loadpas("pas.txt",ios::in);
	ifstream loadrole("role.txt",ios::in);
	ifstream loadperm("permission.txt",ios::in);

	for(int i=0;i<10;i++) //stroka
	{
		for(int j=0;j<10;j++) //stolbec
		{
			loadlog>>log;
			loadpas>>pas;
			if (!loadlog.eof())
			{
				baza[i][j][0]=log;
				baza[i][j][1]=pas;
			}			
		}
	}
	cout<<"база успешно загружена"<<endl;
	for(int i=0;i<5;i++) //stroka
	{
		for(int j=0;j<3;j++) //stolbec
		{
			loadrole>>role;
			if (!loadrole.eof())
			{
				bazarole[i][j]=role;
			}
		}
	}
	cout<<"база ролей успешно загружена"<<endl;

	for(int i=0;i<10;i++) //stroka
	{
		for(int j=0;j<3;j++) //stolbec
		{
			loadperm>>permission;
			if (!loadperm.eof())
			{
				baza_permissions[i][j]=permission;
			}
		}
	}
	cout<<"база индивидуальных прав доступа успешно загружена"<<endl;
	return 1;

}
int main()
{	

	setlocale(LC_ALL,"Russian");
	string admin="admin";
	bazadmin[0]=admin;
	bazadmin[1]=shifr(admin);
	load();
	do
	{	
		menuFirst=0;
		cout<<"1: admin"<<endl;
		cout<<"2: user"<<endl;
		cout<<"3: clean"<<endl;
		cin>>menuFirst;

		switch(menuFirst)
		{
		case 1: if (menuadmin()==1)
					menuok();
			break;

		case 2: menuuser();break;

		case 3:system("cls");break;

		default:break;
		}

	}while(menuFirst!=0);
	save();
	system("pause");
	return 0;
}