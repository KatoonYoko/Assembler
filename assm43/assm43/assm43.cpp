// assm43.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>

//Даны три действительных числа. Возвести в квадрат те из них, значения которых неотрицательны.

int main()
{
	int a = 2;
	int b = -13;
	int c = -4;
	std::cout << a << "; " << b << "; " << c << std::endl;
	__asm {
		mov eax, a
		mov edx, 0
		cmp edx, eax
		jl sqrA; возвести в квадрат а

	hereB:
		mov ebx, b
		cmp edx, ebx
		jl sqrB; возвести в квадрат b

	hereC:
		mov ecx, c
		cmp edx, ecx
		jl sqrC; возвести в квадрат c
		jg end_if

	sqrA:
		imul eax, eax
		mov a, eax
		jmp hereB

	sqrB:
		imul ebx, ebx
		mov b, ebx
		jmp hereC

	sqrC:
		imul ecx, ecx
		mov c, ecx

	end_if:
	}
	std::cout << a << "; " << b << "; " << c;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
