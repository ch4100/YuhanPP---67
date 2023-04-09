//#define DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>  // 키보드의 입력, 모니터의 출력 담당.

int print_title_screen()
{
    std::cout << "******************************" << std::endl;
    std::cout << "*                            *" << std::endl;
    std::cout << "*                            *" << std::endl;
    std::cout << "*                            *" << std::endl;
    std::cout << "*                            *" << std::endl;
    std::cout << "*       지렁이 게임          *" << std::endl;
    std::cout << "*      (Snake Bite)          *" << std::endl;
#ifdef DEBUG
    std::cout << "*       -DEBUG Mode-         *" << std::endl;
#else
    std::cout << "*                            *" << std::endl;
#endif
    std::cout << "*   1. Game Start            *" << std::endl;
    std::cout << "*   2. Help                  *" << std::endl;
    std::cout << "*   3. Game Ranking          *" << std::endl;
    std::cout << "*   4. Exit(esc)             *" << std::endl;
    std::cout << "******************************" << std::endl;
    //int input = 0;
    //std::cin >> input; // 입력받는 함수 * 4 입력 시 게임 종료.
    //if (input == 4)
    //{
    //    break;
    //}

    return 0;
}

int print_introduction_screen()
{
    std::cout << "                               " << std::endl;
    std::cout << "*******************************" << std::endl;
    std::cout << "타이틀화면으로 돌아갈까요?(Y/N)" << std::endl;
    return 0;
}

int print_stage_screen()
{
    std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << std::endl;
    std::cout << "^                              ^" << std::endl;
    std::cout << "^                              ^" << std::endl;
    std::cout << "^                              ^" << std::endl;
    std::cout << "^                              ^" << std::endl;
    std::cout << "^                              ^" << std::endl;
    std::cout << "^                              ^" << std::endl;
    std::cout << "^                              ^" << std::endl;
    std::cout << "^                              ^" << std::endl;
    std::cout << "^                              ^" << std::endl;
    std::cout << "^                              ^" << std::endl;
    std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << std::endl;

    return 0;
}

int main()
{
    print_title_screen();

    char Escape; //문자열 함수 Escape 생성
    // int i = c;
    char T;

    while (true)  //<stdio.h> 의 경우 true 대신 1
    {
        Escape = _getch();  // 오류 발생 getch ==> _getch , Escape 는 문자열 함수를 입력받음.
        if (Escape == 27 || Escape == '4') // 27 = esc의 아스키코드 , 52 = 4의 아스키코드
        {
            break;
        }
        if (Escape == '1')
        {
            system("cls");
            print_stage_screen();
        }

        if (Escape == '2')
            system("cls");

        print_introduction_screen();
        T = _getch();
        if (T == 'Y' || T == 'y')
        {
            system("cls");
            print_title_screen();
        }
        if (T == 'N' || T == 'n')
        {
            print_introduction_screen();
            system("cls");

        }

    }

    return 0;
}
