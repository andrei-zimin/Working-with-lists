#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Pair //структура данных для хранения пары символов
{
private:
	char _first;	//первое значение
	char _second;   //второе значение

public:
	Pair() : _first(), _second() {} //конструктор по умолчанию

	Pair(char first, char second) : _first(first), _second(second) {} //конструктор с параметрами, передаем параметры

	char GetFirst() //метод для получения первого значения
	{
		return _first;
	}

	char GetSecond() //метод для получения второго значения
	{
		return _second;
	}

	void ShowInfo() //метод для вывода на монитор
	{
		cout << _first << ' ' << _second << '\n';
	}

	friend ostream& operator << (ostream& out, Pair p) //перегрузка оператора вывода в консоль
	{
		out << p._first << ' ' << p._second;
		return out;
	}
};

template< class T >
class List
{
private:
	//структура, позволяющая хранить указатели на следующие и предыдущие, а также значение узла
	struct Node
	{
		T Value;	//данные, которые передадим в список
		Node* Prev;	//предыдущий узел
		Node* Next; //следующий узел
	};

	Node* _head, * _tail;//указатель на начало и конец списка
	int _count;			 //кол-во узлов в списке

public:
	//конструктор по умолчанию
	List()
	{
		_head = _tail = NULL;
		_count = 0;
	}
	
	int GetCount() //получение кол-ва элементов списка
	{
		return _count;
	}
	
	void Clear()  //удаление списка	
	{
		while (_count != 0)
			Del(1);
	}
	
	void AddTail(T value) //добавление нового узла в конец списка
	{
		Node* node = new Node;
		node->Next = NULL;
		node->Value = value;
		node->Prev = _tail;

		if (_tail != NULL)
			_tail->Next = node;

		if (_count == 0)
			_head = _tail = node;
		else
			_tail = node;

		_count++;
	}
	//перегрузка оператора присваивания
	//возврат ссылки на новый лист
	List<T>& operator = (const List<T>& list)
	{
		if (this == &list)
			return *this;

		this->Clear();

		Node* temp = list._head;

		while (temp != NULL)
		{
			this->AddTail(temp->Value);
			temp = temp->Next;
		}

		return *this;
	}

	void ShowInfo() //метод для вывода списка на экран
	{
		cout << "Список состоит из: " << _count << " элементов\n";

		if (_count != 0)
		{
			Node* temp = _head;
			while (temp->Next != NULL)
			{
				cout << temp->Value << '\n';
				temp = temp->Next;
			}
			cout << temp->Value << '\n';
		}
	}

	void ChangeValueByPosition(int position, T value) //изменение значения по позиции
	{
		Check();
		int i = 1;
		Node* valueOnPosition = _head;
		while (i < position)
		{
			valueOnPosition = valueOnPosition->Next;
			i++;
		}
		valueOnPosition->Value = value;
	}

	void Insert(int position, T value) //вставка элемента на конкретную позицию
	{
		if (position < 1 || position > _count + 1)
		{
			cout << "Нет такой позиции\n";
			exit(0);
		}
		else if (position == _count + 1)
		{
			AddTail(value);
			return;
		}
		else if (position == 1)
		{
			AddHead(value);
			return;
		}

		int i = 1;
		Node* ValueOnPosition = _head;

		while (i < position)
		{
			ValueOnPosition = ValueOnPosition->Next;
			i++;
		}

		Node* prev = ValueOnPosition->Prev;
		Node* temp = new Node;
		temp->Value = value;

		if (prev != NULL && _count != 1)
			prev->Next = temp;

		temp->Next = ValueOnPosition;
		temp->Prev = prev;
		ValueOnPosition->Prev = temp;

		_count++;
	}

	T GetValueByPosition(int position) //метод получения значения по позиции
	{
		if (position < 1 || position > _count)
		{
			cout << "Нет такой позиции\n";
			exit(0);
		}

		Node* temp = _head;
		int i = 1;
		while (i < position && temp)
		{
			temp = temp->Next;
			i++;
		}
		if (temp)
		{
			return temp->Value;
		}
		cout << "На позиции NULL\n";
		exit(0);
	}

	void Sort() //сортировка списка пузырьком
	{
		T n = this->GetCount();
		for (int i = 1; i <= n - 1; i++)
		{
			for (int j = 1; j <= n - i; j++)
			{
				if (this->GetValueByPosition(j) > this->GetValueByPosition(j + 1))
				{
					int temp = this->GetValueByPosition(j);
					this->ChangeValueByPosition(j, this->GetValueByPosition(j + 1));
					this->ChangeValueByPosition(j + 1, temp);
				}
			}
		}
	}

private:

	void Check() //проверка на пустоту
	{
		if (IsEmpty())
		{
			cout << "Список пуст" << '\n';
			exit(0);
		}
	}

	bool IsEmpty() //проверка на пустоту
	{
		return _head == NULL;
	}
	void Del(int position)//удаление элемента по позиции 
	{
		if (position < 1 || position > _count)
		{
			cout << "Неверная позиция\n";
			exit(0);
		}

		int i = 1;
		Node* Del = _head;

		while (i < position)
		{
			Del = Del->Next;
			i++;
		}

		Node* prevDel = Del->Prev;//сохранение предыдущее
		Node* afterDel = Del->Next;//сохраняем после звена

		if (prevDel != NULL && _count != 1)
			prevDel->Next = afterDel;//след.значение первой части равняется оставшемуся списку
		if (afterDel != NULL && _count != 1)//после звена
			afterDel->Prev = prevDel;//предыдущему равняется то, что было до этого

		if (position == 1)
			_head = afterDel;
		if (position == _count)
			_tail = prevDel;

		delete Del;

		--_count;
	}
	
};

class Determinator
{
private:
	List<Pair> _pairs; //список пар из файла
	int _countPairs;   //кол-во пар

public:
	Determinator() : _pairs(), _countPairs() {} //конструктор по умолчанию

	void ReadFromFile(string fileName)          //метод чтения из файла
	{
		ifstream in;
		in.open(fileName);
		if (in.is_open() == false)
		{
			cout << "Файл не найден!\n";
			exit(0);
		}

		string line;
		getline(in, line);

		try
		{
			_countPairs = stoi(line);

		}
		catch (const std::exception&)
		{
			cout << "На первой строке стоит не число. Введите корректные данные!\n";
			exit(0);
		}
		while (getline(in, line))
		{
			_pairs.AddTail(Pair(line[0], line[2]));
		}
		if (_countPairs != _pairs.GetCount())
		{
			cout << "Число пар не соответсвует количеству введенных строк в файле\n";
			exit(0);
		}

	}

	void Check() //проверка на полноту, противоречивость
	{
		int countSymbols = 256;
		List<int> intSymbols;
		for (int i = 0; i < countSymbols; i++)
		{
			intSymbols.AddTail(-1);
		}

		int countInputSymbols = 0;
		for (int i = 1; i <= _countPairs; i++)
		{
			int first = intSymbols.GetValueByPosition(_pairs.GetValueByPosition(i).GetFirst());
			int second = intSymbols.GetValueByPosition(_pairs.GetValueByPosition(i).GetSecond());
			cout << _pairs.GetValueByPosition(i) << endl;

			if (first == -1)
			{
				++countInputSymbols;
			}
			if (second == -1)
			{
				++countInputSymbols;
			}
			//на позиции, где были "-1" ставим нули
			intSymbols.ChangeValueByPosition(_pairs.GetValueByPosition(i).GetFirst(), 0);
			intSymbols.ChangeValueByPosition(_pairs.GetValueByPosition(i).GetSecond(), 0);
		}

		bool isChange = false;
		char tempFirst;
		char tempSecond;
		int max;
		for (int i = 1; i <= _countPairs; i++)
		{
			isChange = false;
			for (int j = 1; j <= _countPairs; j++)
			{
				tempFirst = _pairs.GetValueByPosition(j).GetFirst();
				tempSecond = _pairs.GetValueByPosition(j).GetSecond();
				max = GetMax(intSymbols.GetValueByPosition(tempFirst) + 1, intSymbols.GetValueByPosition(tempSecond));
				if (max > (countInputSymbols - 1))
				{
					cout << "Порядок противоречив";
					return;
				}
				if (intSymbols.GetValueByPosition(tempSecond) != max)
				{
					isChange = true;
				}
				intSymbols.ChangeValueByPosition(tempSecond, max);
			}
			if (!isChange)
			{
				intSymbols.Sort(); //сортировка массива числовых представлений
				int prev = countInputSymbols;
				int indexForSymbols = countSymbols;

				while (intSymbols.GetValueByPosition(indexForSymbols) > -1)
				{
					if (intSymbols.GetValueByPosition(indexForSymbols) == prev - 1)
					{
						prev--;
					}
					else
					{
						cout << "порядок неполный";
						return;
					}
					indexForSymbols--;
				}
				cout << "полный порядок";
				return;
			}
		}
	}

private:

	int GetMax(int a, int b)//получение максимума
	{
		return (a > b) ? a : b;
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Нет такой позиции\n";
	Determinator determinator;				//создание экземпляра класса
	determinator.ReadFromFile("input.txt"); //чтение из файла
	determinator.Check();					//проверка на полноту, противоречивость
	return 0;
}