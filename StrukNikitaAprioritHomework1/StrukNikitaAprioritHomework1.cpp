#include <iostream>
#include <windows.h>
#include <ctime>

#include "CursorObserver.h"
#include "CursorSubject.h"

/**
 * \brief Слугує початковою точкою роботи застосунку.
 * Поряд виконання:
 * 1) Задається назва файлу. Після цього, створюємо файл для запису.
 * У разі успіху - продовжуємо роботу застосунку. У разі провалу - застосунок завершує свою роботу та виводить помилку у консоль.
 * 2) Ідентифікуємо дескриптор для консольного додатку.
 * У разі успіху - продовжуємо роботу застосунку. У разі провалу - застосунок завершує свою роботу та виводить помилку у консоль.
 * 3) Задаємо спостерігач та об'єкт, за яким буде ввестися спостереження. Додаємо вказікник на спостерігача до об'єкта.
 * 4) Ідентифікуємо дескриптор для вікна консольного додатку. Отримуємо ширину та висоту вікна.
 * 5) Виконуємо стеження за курсором миші, поки не була натиснута клавіша Q.
 *	5.1) Отримаємо координати миші та екранні координати в координати клієнтської області.
 *	5.2) Визначаємо дескриптор консольного вікна та його розмірність. Обчислюжмо висоту та ширину консольного вікна.
 *	5.3) Визначаємо таймер та часову структуру. Зберігаємо інформацію про час. Конвертуємо час у локальний формат. Записуємо дані у С строку.
 *	5.4) Перевіряємо - чи ввійшла виша у вікно консольного застосунку.
 *	Якщо так - змінюємо колір тексту консолі на зелений, записуємо у текстовий файл час входу із тегом Enter.
 *	Якщо ні - повертаємо колір тексту до норми (на білий), записуємо у текстовий файл час входу із тегом Leave.
 * 6) Друкуємо напис Hello world! для перевірки роботи функціоналу.
 * 7) При натискані на клавішу Q - Видаляємо вказівник на спостерігача до об'єкта, закриваємо файл для логів та завершуємо роботу застосунку.
 */
void StartApplication()
{
	const LPCWSTR fileName = L"ActionsLogs.txt"; //Назва та формат файлу, де будуть зберігатися логи.
	if (const HANDLE logFile = CreateFile(fileName, //Назва створюваного файлу
	                                      GENERIC_WRITE, //Запитуваний доступ до файлу
	                                      0, //Запитуваний режим спільного доступу до файлу
	                                      0,//Вказівник на структуру SECURITY_ATTRIBUTES. Дане значення: визначає, чи може повернутий дескриптор бути успадкований дочірніми процесами.
	                                      CREATE_ALWAYS, //Дія, яку потрібно виконати над файлом, який існує або не існує.
	                                      FILE_ATTRIBUTE_NORMAL, //Атрибути та прапори файлів. Дане значення: У файлу не встановлено інших атрибутів. Атрибут дійсний лише у разі його окремого використання.
	                                      0)) //Чи дійсний дескриптор на файл шаблону з правом доступу GENERIC_READ? 
    {
        HANDLE handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        try
        {
			if (handleConsole == INVALID_HANDLE_VALUE) 
	        {
		        throw std::runtime_error("Error getting console handle.");
			}

			std::shared_ptr<CursorObserver> cursorObserver = std::make_shared<CursorObserver>();
        	CursorSubject cursorSubject;
        	cursorSubject.Attach(cursorObserver);

			HWND consoleWindow = GetConsoleWindow();
			RECT windowRectangle;
			GetWindowRect(consoleWindow, &windowRectangle);
			int consoleWindowWidth = windowRectangle.right - windowRectangle.left;
			int consoleWindowHeight = windowRectangle.bottom - windowRectangle.top;
	        while(!(GetAsyncKeyState('Q'))) //Поки користувач не натиснув клавішу Q.
	        {
		            DWORD bytesWritten;

		            POINT cursorPos;
                    GetCursorPos(&cursorPos);
					ScreenToClient(GetConsoleWindow(), &cursorPos);

                    time_t timer;
	            	tm timeInformation{};
	                char timeBuffer[26];
					// Отримуємо поточний час і зберегти його в 'timer'
	                time(&timer);
					// Конвертуємо поточний час з 'timer' у локальну структуру часу 'timeInformation'
					localtime_s(&timeInformation, &timer);
					// Відформатуємо інформацію про місцевий час у рядок і зберігаємо її у 'timeBuffer'
                    asctime_s(timeBuffer, sizeof(timeBuffer), &timeInformation);

	                if(cursorPos.x >= 0 && cursorPos.x < consoleWindowWidth && cursorPos.y >= 0 && cursorPos.y < consoleWindowHeight) //Курсор увійшов до консолі
	                {
						cursorSubject.NotifyEntrance(handleConsole);
						std::string logMessage = "|Enter|" + std::string(timeBuffer);
						//Друкуємо час входу курсора у консоль із тегом Enter
						WriteFile(logFile,logMessage.c_str(),strlen(logMessage.c_str()),&bytesWritten,nullptr); 
	                }
	                else //Курсор вийшов із консолі
	                {
						cursorSubject.NotifyLeaving(handleConsole);
                        std::string logMessage = "|Leave|" + std::string(timeBuffer);
						//Друкуємо час виходу курсора у консоль із тегом Leave
                        WriteFile(logFile,logMessage.c_str(),strlen(logMessage.c_str()),&bytesWritten,nullptr);
	                }
	                std::cout << "Hello world!\n";
                    Sleep(1000);
	          
	        }
			cursorSubject.Detach(cursorObserver);
        }
        catch(const std::runtime_error& errorName)
        {
            std::cout << "Error: "<< errorName.what() << "\n";
            CloseHandle(logFile);
        }
    	Sleep(100);
        CloseHandle(logFile);
    }
    else
    {
        throw std::runtime_error("File creation failed.");
    }
}
int main()
{
    try
    {
	    StartApplication();
    }
    catch(...)
    {
	    std::cerr << "Error: " << GetLastError() << '\n';
        return EXIT_FAILURE;
    }
    return 0;
}
