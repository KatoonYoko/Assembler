// assm427.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>

int main()
{
	short a = 1;
	short b = 2;
	short c = 3;
	short ans = 0;
	/*
		short = 16 бит
		- результат умножения со знаком IMUL(c одним операндом) записывается в AX(8), DX:AX(16), EDX:EAX(32);  
			результат умножения IMUL(с двумя операндами) записывается в первый операнд
			результат умножения IMUL(с тремя операндами) О1 = О2 * О3
	
		- деление со знаком IDIV О1
			8 бит:  делимое в AX, результат в AL, остаток в AH
			16 бит: делимое в DX:AX, результат в AX, остаток в DX

		- сумма
			ADD O1, O2; O1 = O1 + O2
	*/


	/*
		Где регистры заняты:

		BX: max_p
		CX: max_p
		AX: занят при делении
		DX: занят при делении
	*/
	__asm {
		

		; начало процедуры
		max_p: ; сравнивает BX и CX, заносит бОльший в BX

			cmp BX, CX
			jl cx_bigger; если cx больше

			jmp end_p; если bx больше - перейти к концу процедуры

		cx_bigger:
			mov bx, cx;

			end_p:
			ret
		; конец процедуры




		; начало программы
		format mz
		org 100h

		mov ax, a
		mov dx, b
		mov si, c

		push dx ; сохраняем b
		add dx, ax ; dx = a + b
		mov bx, ax
		mov cx, dx
		call max_p; выясняем первый максимум
		mov bp, bx; поместили max(a, a + b) в BP <-------------------------------------- хранит первый максимум
		pop dx; вернули b
		
		push si; сохраняем c
		add si, dx; b + c
		mov bx, ax
		mov cx, si
		call max_p; выясняем второй максимум
		mov di, bx; поместили max(a, a + c) в DI < -------------------------------------- хранит второй максимум
		pop si; вернули с

		; к этому моменту
		; ax == a, dx == b, si == c, bp == firstMax, DI == secondMax

		

		imul dx, si; dx = b * c
		add ax, dx; ax = a + b * c
				; dx, si освободились, их можно использовать
		mov bx, ax
		mov cx, 1
		call max_p; выясняем третий максимум
		mov si, bx; SI < -------------------------------------------- хранит третий максимум
		
		; складываем верхнюю часть
		add bp, di; bp хранит сумму верхней части
		add si, 1

		mov ax, bp
		cwd; перенесли старший байт делимого из AX в DX для деления
		IDIV si; результат деления запишется в AX, Остаток в DX

		mov a, ax; сохраняем результат в A







	; другая версия программы
	;	mov dx, a
	;	mov bx, b
	;	mov cx, c
	;	mov si, a; для сложения с b
	;	mov di, b; для сложения с c
	;	mov bp, a; для сложения с b * c
	;	mov ax, c; для умножения на b
	;
	;
	;	add si, bx; a + b = si
	;	add di, cx; b + c = di
	;	imul bx; b * c = dx:ax
	;
	;Max1:
	;	cmp dx, si; max(a, a + b)
	;	jl Max2
	;	mov si, a
	;	; si = max(a, a + b)
	;
	;Max2: 
	;	cmp dx, di; max(a, b + c)
	;	jl Max3
	;	mov di, a
	;	; di = max(a, b + c)
	;
	;Max3: 
	;	add dx, ax; предположение ax = b * c = > (a + b * c) = dx
	;	cmp dx, 1
	;	jl Solution
	;	mov dx, 1
	;	; dx =  max(a + b * c, 1)
	;
	;Solution:
	;	add si, di; si = si + di
	;	add dx, 1; dx = dx + 1
	;	mov ax, dx; для деления
	;	idiv si; результат ax, остаток dx
	;	mov ans, ax
	;

	}
	std::cout << " a = " << a << "; b = " << b << "; c = " << c;
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
