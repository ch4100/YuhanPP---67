#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_BLUE  "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_GREEN    "\x1b[34m"
#define ANSI_COLOR_WHITE  "\x1b[37m"


// Object 클래스
class Object
{
public:
    int positionX;
    int positionY;
    std::string text;

    virtual void Render(char* screenBuffer, int screenWidth)
    {
        // Object의 렌더링 로직 작성
        int bufferIndex = positionY * screenWidth + positionX;
        if (!text.empty())
        {
            for (size_t i = 0; i < text.length(); i++)
            {
                screenBuffer[bufferIndex + i] = text[i];
            }
        }
    }
};

// Scene 클래스
class Scene
{
public:
    char* screenBuffer;
    int screenWidth;
    int screenHeight;
    std::vector<Object*> objects;

    Scene(int width, int height)
    {
        screenWidth = width;
        screenHeight = height;
        screenBuffer = new char[screenWidth * screenHeight];
        ClearScreenBuffer();
    }

    ~Scene()
    {
        delete[] screenBuffer;
    }

    void AddObject(Object* object)
    {
        objects.push_back(object);
    }

    void Draw()
    {
        for (Object* object : objects)
        {
            object->Render(screenBuffer, screenWidth);
        }

        for (int y = 0; y < screenHeight; y++)
        {
            for (int x = 0; x < screenWidth; x++)
            {
                std::cout << screenBuffer[y * screenWidth + x] << " ";
            }
            std::cout << std::endl;
        }
    }

    void ClearScreenBuffer()
    {
        for (int i = 0; i < screenWidth * screenHeight; i++)
        {
            screenBuffer[i] = ' ';
        }
    }
};

int main()
{
    Scene scene(10, 3);

    Object* object = new Object();

    while (true)
    {
        int x, y;
        std::string text;

        std::cout << "Enter X coordinate: ";
        std::cin >> x;
        std::cout << "Enter Y coordinate: ";
        std::cin >> y;
        std::cout << "Enter text: ";
        std::cin.ignore(); // 버퍼 비우기
        std::getline(std::cin, text);

        object->positionX = x;
        object->positionY = y;
        object->text = text;

        scene.AddObject(object);
        scene.Draw();

        if (text == "EXIT")
        {
            break;
        }
        if (text == "RED")
        {
            std::cout << ANSI_COLOR_RED"RED" << std::endl;
        }
        if (text =="BLUE")
        {
            std::cout << ANSI_COLOR_BLUE"BLUE" << std::endl;
        }
        if (text == "GREEN")
        {
            std::cout << ANSI_COLOR_GREEN"GREEN" << std::endl;
        }
        if (text == "YELLOW")
        {
            std::cout << ANSI_COLOR_YELLOW"YELLOW" << std::endl;
        }
        if (text == "WHITE")
        {
            std::cout << ANSI_COLOR_WHITE"WHITE" << std::endl;
        }
        if (text == "CLEAR")
        {
            system("cls");
            std::cout << ANSI_COLOR_WHITE << std::endl;
            main();
        }
    }
    
    delete object;

    return 0;
}