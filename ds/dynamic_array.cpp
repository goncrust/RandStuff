#include <iostream>

class IntArray
{
private:
	int *intArray;

	int size;
	int position;

	int default_size;

public:
	IntArray(int size)
	{
		this->intArray = new int[size];

		this->size = size;
		this->default_size = size;
		this->position = 0;
	}

	int getSize()
	{
		return this->position;
	}

	int getActualSize()
	{
		return this->size;
	}

	void insert(int item)
	{
		if (this->position < this->size)
		{
			this->intArray[this->position] = item;

			this->position++;
		}
		else
		{
			int *newArray = new int[this->size + this->default_size];
			memcpy(newArray, this->intArray, 4 * this->size);
			delete[] intArray;
			this->intArray = newArray;

			this->intArray[this->position] = item;

			this->size += this->default_size;
			this->position++;
		}
	}

	void removeAt(int index)
	{
		if (index == this->position - 1)
		{
			this->intArray[index] = NULL;
			this->position--;
		}
		else
		{
			for (int i = index; i < this->position; i++)
			{
				this->intArray[i] = this->intArray[i + 1];
			}

			this->intArray[this->position - 1] = NULL;
			this->position--;
		}
	}

	int indexOf(int item)
	{
		for (int i = 0; i < this->size; i++)
		{
			if (this->intArray[i] == item)
			{
				return i;
			}
		}

		return -1;
	}

	char *toString()
	{
		char *string = new char[this->position * 4];

		string[0] = '[';
		for (int i = 0; i < this->position; i++)
		{
			int pos = 1 + i * 3;
			string[pos] = '0' + this->intArray[i];
			string[pos + 1] = ',';
			string[pos + 2] = ' ';
		}

		string[(1 + (this->position - 1) * 3) + 1] = ']';
		string[(1 + (this->position - 1) * 3) + 2] = '\0';

		return string;
	}
};

int main()
{
	IntArray tarray = IntArray(3);
	tarray.insert(3);
	tarray.insert(7);
	tarray.insert(2);
	tarray.insert(3);
	tarray.insert(4);

	tarray.removeAt(2);

	char *tarray_string = tarray.toString();
	int c_index = 0;
	while (tarray_string[c_index] != '\0')
	{
		std::cout << tarray_string[c_index];
		c_index++;
	}

	std::cout << tarray.indexOf(4);
}
