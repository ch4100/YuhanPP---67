#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>  // 키보드의 입력, 모니터의 출력 담당.

int print_title_screen()
{
    std::cout << "Esc 버튼을 누르면 프로그램이 종료됩니다." << std::endl;
    return 0;
}
int main()
{
    print_title_screen();

    char Escape; //문자열 함수 Escape 생성
    // int i = c;


    while (true)  //<stdio.h> 의 경우 true 대신 1
    {
        Escape = _getch();  // 오류 발생 getch ==> _getch , Escape 는 문자열 함수를 입력받음.
        if (Escape == 27) // 27 = esc의 아스키코드
        {
            break;
        }



    }

    return 0;
}
