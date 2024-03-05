#include <iostream>
#include <windows.h>
#include <ctime>

#include "CursorObserver.h"

void StartApplication()
{
	const LPCWSTR fileName = L"ActionsLogs.txt"; //Назва та формат файлу, де будуть зберігатися логи.
    const HANDLE logFile = CreateFile(fileName,
                          GENERIC_WRITE, 
                          0,
                          0,
                          CREATE_ALWAYS,
                          FILE_ATTRIBUTE_NORMAL,
                          0);
    if (logFile)
    {
        HANDLE handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        try
        {
			if (handleConsole == INVALID_HANDLE_VALUE) 
	        {
		        throw std::runtime_error("Error getting console handle.");
			}
	        while(!(GetAsyncKeyState('Q') & 0x8000)) //Поки користувач не натиснув клавішу Q.
	        {
                CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
	            if(GetConsoleScreenBufferInfo(handleConsole, &consoleScreenBufferInfo))
	            {
                    CursorObserver cursorObserver;
		            DWORD bytesWritten;

		            POINT cursorPos;
                    GetCursorPos(&cursorPos);
					ScreenToClient(GetConsoleWindow(), &cursorPos);

                    time_t timer;
	            	tm timeInformation{};
	                char timeBuffer[26];
	                time(&timer);
					localtime_s(&timeInformation, &timer);
                    asctime_s(timeBuffer, sizeof(timeBuffer), &timeInformation);

	                if(cursorPos.x >= 0 && cursorPos.x < consoleScreenBufferInfo.dwSize.X && cursorPos.y >= 0 && cursorPos.y < consoleScreenBufferInfo.dwSize.Y)
	                {
						cursorObserver.StartObservation(handleConsole);
						std::string logMessage = "|Enter|" + std::string(timeBuffer);
						WriteFile(logFile,logMessage.c_str(),strlen(logMessage.c_str()),&bytesWritten,nullptr);
	                }
	                else
	                {
		                cursorObserver.StopObservation(handleConsole);
                        std::string logMessage = "|Leave|" + std::string(timeBuffer);
                        WriteFile(logFile,logMessage.c_str(),strlen(logMessage.c_str()),&bytesWritten,nullptr);
	                }
	                std::cout << "Hello world!\n";
                    Sleep(1000);
	            }
	            else
	            {
		            throw std::runtime_error("Error getting console buffer info.");
	            }
	        }
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
